#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <iostream>
#include <string>
#include <vector>

float window_width = 1000;
float window_height = 1000;
int num_lines = 100;
float gap;
float stick_length;
float text_height;
float view_height;
Rectangle text_area;

struct Stick {
    Vector2 p1;
    Vector2 p2;
    Color col = DARKGRAY;
};
std::vector<Stick> sticks;

float randf(float max) {
    float r = (float)GetRandomValue(0, RAND_MAX);
    float rmax = (float)RAND_MAX;
    float result = r / (rmax / max);
    return result;
}

bool crosses(Stick s) {
    for(int i = 0; i < num_lines; ++i) {
	float lx = i * gap;
	if((s.p1.x < lx && s.p2.x > lx)|| (s.p2.x < lx && s.p1.x > lx) || s.p1.x == lx || s.p2.x == lx) return true;
    }
    return false;
}

int get_crossings() {
    int crossings = 0;
    for(int i = 0; i < num_lines; ++i) {
	float lx = i * gap;
	for(const Stick& s: sticks) {
	    if(s.p1.x < lx && s.p2.x > lx) crossings++;
	    else if(s.p2.x < lx && s.p1.x > lx) crossings++;
	}
    }
    return crossings;
}

float pi_aprox(float num_crossings) {
    return (2.f * stick_length * (float)sticks.size()) / (gap * num_crossings); 
}

void print_vec(Vector2 vec) {
    std::cout << "== new vec == \n";
    std::cout << "x = " << vec.x << ", y = " << vec.y << "\n";
    std::cout << "==== end ==== \n";
}

Stick random_stick() {
    Stick stick;
    stick.p1.x = randf(window_width);
    stick.p1.y = randf(window_height);
    stick.p2.x = randf(window_width);
    stick.p2.y = randf(window_height);
    Vector2 dir = Vector2Subtract(stick.p2, stick.p1);
    dir = Vector2Normalize(dir);
    dir = Vector2Scale(dir, stick_length);
    stick.p2 = Vector2Add(stick.p1, dir);
    return stick;
}

int main(int argc, char** argv) {
    SetTraceLogLevel(LOG_ERROR);
    int fps = 60;
    if(argc > 1) {
	if(argc < 5) {
	    std::cout << "too few arguments, reverting to standart settings\n"; 
	}
	else if(argc > 5) {
	    std::cout << "too many arguments, reverting to standart settings\n"; 
	}
	else {

	    try {
		window_width = (float)std::stoi(argv[1]);
		window_height = (float)std::stoi(argv[2]);
		num_lines = std::stoi(argv[3]);
		fps = std::stoi(argv[4]);
	    }
	    catch(std::invalid_argument er) {
		std::cout << "invalid arguments, reverting to standart settings\n";	
		window_width = 1000;
		window_height = 1000;
		num_lines = 100;
		fps = 100;
	    }
	}
    }
    else {

	std::cout << "\n\n-------------------------\n";
	std::cout << "starting with standart settings.\nYou can provide window width, height, number of lines and target fps as command arguments\n";
	std::cout << "-------------------------\n\n";
    }
    std::cout << "\nconfiguration:\nwindow width = " << window_width 
	<< "\nwindow height = " << window_height 
	<< "\nnumber of lines = " << num_lines
	<< "\ntarget fps = " << fps << "\n";

    gap = window_width / num_lines;
    stick_length = gap / 2.f;
    text_height = window_height / 30.f;
    view_height = window_height - text_height * 4.f;
    text_area = {0, view_height, window_width, window_height - view_height};
    float config_text_offset = window_width / 2.f;
    SetRandomSeed(GetTime());
    int crossings = 0;
    InitWindow(window_width, window_height, "Buffon's needle");
    SetTargetFPS(fps);
    while(!WindowShouldClose()) {
	Stick stick = random_stick();
	if(crosses(stick)) {
	    crossings++;
	    stick.col = GREEN;
	}
	sticks.push_back(stick);

	BeginDrawing();
	ClearBackground(LIGHTGRAY);

	for(int i = 0; i < num_lines; ++i) {
	    DrawLine(i * gap, 0, i * gap, view_height, BLACK);
	}
	for(int i = 0; i < sticks.size(); ++i) {
	    DrawLineEx(sticks[i].p1, sticks[i].p2, 1.f, sticks[i].col);
	}

	DrawRectangleRec(text_area, DARKGRAY);
	float pi = pi_aprox(crossings);
	DrawText(TextFormat("crossings = %u", crossings), 0, view_height, text_height, LIGHTGRAY);
	DrawText(TextFormat("dropped = %u", sticks.size()), 0, view_height + text_height, text_height, LIGHTGRAY);
	DrawText(TextFormat("pi ~ %f", pi), 0, view_height + text_height * 2.f, text_height, LIGHTGRAY);

	DrawText("configuration: ", config_text_offset, view_height, text_height, LIGHTGRAY);
	DrawText(TextFormat("window width = %u", (int)window_width), config_text_offset, view_height + text_height, text_height, LIGHTGRAY);
	DrawText(TextFormat("window height = %u", (int)window_height), config_text_offset, view_height + text_height * 2.f, text_height, LIGHTGRAY);
	DrawText(TextFormat("number of lines = %u", num_lines), config_text_offset, view_height + text_height * 3.f, text_height, LIGHTGRAY);
	DrawFPS(config_text_offset * 1.7f, view_height);

	EndDrawing();
    }
    CloseWindow();
    return 0;
}

