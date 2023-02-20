#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#define h 26 // height of the display portion on window
#define w 63 // width of the display portion on window
using namespace std;

struct Queue {
	char value[h] = {};
	int rear = -1;
};

Queue queue;

char buffer[h][w]; // 2d matrix to store all the raining letters at the instant

void how_to_play();
void init_buffer(); // initialize buffer matrix with empty letters i.e. whitespace characters
void render(); // display the buffer matrix on the screen
void create_new_rain(); // creates a new letter on the first row of buffer matrix
void row_falls(int); // this function makes the rain on upper row fall down to lower row
void update_buffer(); // every raining letters are updated by calling row_falls() function
void clear_cloud(); // clears the first row of buffer matrix
int Qfull(); // checks if queue is full
void Qinsert(char); // inserts a character into queue
char Qdelete(); // deletes a character from queue
char Qfirst(); //returns the first character of queue

int main() {
	how_to_play();
	int score = 0;
	srand(time(0)); // seeding for creating random number
	init_buffer(); // initializing the buffer matrix with empty alphabets
	
	while (1) { // program loop
		clear_cloud(); // clearing the first row of buffer matrix
		create_new_rain(); // creating a random letter on random index on first row of buffer matrix
		render(); // displaying the buffer matrix
		cout << " Score: " << score;
		if (_kbhit()) {
			char c = _getch();
			if (c == Qfirst()) {
				score++;
				Qdelete();
			}
			cout << " " << c;
		}
		Sleep(1000); // creating certain time delay
		update_buffer(); // updating the buffer in each loop, this helps to make the raining letters fall downwards
	}
	return 0;
}

void update_buffer() {
	// Buffer rows are updated from below to above i.e down (h-2) to top(0)
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

	// Ending line i.e ground
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

void create_new_rain() {
	int r = rand() % (w);
	int ascii = rand() % 26 + 97; // generating a random number from 97 to 122
	char new_letter = (char)ascii; // converting the ascii number into character
	buffer[0][r] = new_letter; // putting the newly generated character on the first row of buffer matrix
	if (Qfull()) Qdelete();
	Qinsert(new_letter);
}

void row_falls(int r1) {
	int r2 = r1 + 1;
	// Replacing r2 by r1 where r2 is lower row and r1 is upper row
	for (int j = 0; j < w; j++) {
		if (buffer[r1][j]) buffer[r2][j] = buffer[r1][j];
	}
}

void clear_cloud() {
	for (int j = 0; j < w; j++) {
		buffer[0][j] = ' ';
	}
}

int Qfull() {
	if (queue.rear == h - 1) return 1;
	return 0;
}
void Qinsert(char c) {
	if (!Qfull()) {
		queue.rear++;
		queue.value[queue.rear] = c;
	}
}

char Qdelete() {
	char c = queue.value[0];
	queue.value[0] = NULL;
	for (int i = 0; i < queue.rear; i++) {
		queue.value[i] = queue.value[i + 1];
	}
	queue.rear--;
	return c;
}

char Qfirst() {
	if (queue.value[0]) return queue.value[0];
	return NULL;
}

void how_to_play() {
	cout << "Letters will start raining one by one." << endl;
	cout << "Try to type all the letters in order before they touch the ground."<<endl;
	cout << "Press any key to start ";
	char c = _getch();
}



