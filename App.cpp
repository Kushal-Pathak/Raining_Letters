#include <iostream>
#include <time.h>
#define h 26
#define w 63
using namespace std;

char buffer[h][w];


void init_buffer();
void render();
void delay(float);
void create_new_rain();
void row_falls(int);
void update_buffer();
void clear_cloud();

int main() {
	srand(time(0));
	init_buffer();
	
	while (1) {
		clear_cloud();
		create_new_rain();
		render();
		delay(1);
		update_buffer();
	}
	render();
	return 0;
}

void update_buffer() {
	for (int i = h - 2; i >= 0; i--) {
		row_falls(i);
	}
}

void render() {
	system("cls");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << buffer[i][j];
		}
		cout << endl;
	}
	for (int j = 0; j < w; j++) {
		cout << '=';
	}
}

void init_buffer() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			buffer[i][j] = ' ';
		}
	}
}

void delay(float f) {
	for (float i = 0; i < 10000; i++) {
		for (float j = 0; j < 1000; j++) {
			for (float k = 0; k < f * 10; k++);
		}
	}
}

void create_new_rain() {
	int r = rand() % (w);
	int ascii = rand() % 26 + 97;
	char new_letter = (char)ascii;
	buffer[0][r] = new_letter;
}

void row_falls(int r1) {
	int r2 = r1 + 1;
	for (int j = 0; j < w; j++) {
		if (buffer[r1][j]) buffer[r2][j] = buffer[r1][j];
	}
}

void clear_cloud() {
	for (int j = 0; j < w; j++) {
		buffer[0][j] = ' ';
	}
}



