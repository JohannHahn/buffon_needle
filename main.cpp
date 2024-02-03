#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <iostream>
#include <string>

float window_width = 1000;
float window_height = 1000;
int num_lines = 100;
float gap;
float stick_length;
float text_height;
float view_height;
size_t dropped = 0;
Rectangle text_area;

struct Stick {
    Vector2 p1;
    Vector2 p2;
    Color col = DARKGRAY;
};

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


float pi_aprox(float num_crossings) {
    return (2.f * stick_length * dropped) / (gap * num_crossings); 
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
    int fps = 100;
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

    Image img = GenImageColor(window_width, window_height, LIGHTGRAY);
    Texture tex = LoadTextureFromImage(img);
    for (int i = 0; i < num_lines; ++i) {
	ImageDrawLine(&img, i * gap, 0, i * gap, view_height, BLACK);
    }

    while (!WindowShouldClose()) {
	Stick stick = random_stick();
	if (crosses(stick)) {
	    crossings++;
	    stick.col = GREEN;
	}

	BeginDrawing();

	ImageDrawLineV(&img, stick.p1, stick.p2, stick.col);

	ImageDrawRectangleRec(&img, text_area, DARKGRAY);
	float pi = pi_aprox(crossings);
	ImageDrawText(&img, TextFormat("crossings = %u", crossings), 0, view_height, text_height, LIGHTGRAY);
	ImageDrawText(&img, TextFormat("dropped = %u", dropped), 0, view_height + text_height, text_height, LIGHTGRAY);
	ImageDrawText(&img, TextFormat("pi ~ %f", pi), 0, view_height + text_height * 2.f, text_height, LIGHTGRAY);

	ImageDrawText(&img, "configuration: ", config_text_offset, view_height, text_height, LIGHTGRAY);
	ImageDrawText(&img, TextFormat("window width = %u", (int)window_width), config_text_offset, view_height + text_height, text_height, LIGHTGRAY);
	ImageDrawText(&img, TextFormat("window height = %u", (int)window_height), config_text_offset, view_height + text_height * 2.f, text_height, LIGHTGRAY);
	ImageDrawText(&img, TextFormat("number of lines = %u", num_lines), config_text_offset, view_height + text_height * 3.f, text_height, LIGHTGRAY);

	DrawTexture(tex, 0, 0, WHITE);
	UpdateTexture(tex, img.data);

	DrawFPS(config_text_offset * 1.7f, view_height);
	EndDrawing();
	dropped++;
    }
    CloseWindow();
    return 0;
}

