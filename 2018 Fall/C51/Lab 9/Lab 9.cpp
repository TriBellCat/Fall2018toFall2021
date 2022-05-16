/*File Name: Lap 9.cpp
  Author: Trinity Caitlin Atayan Belen
  Description : The program will store points in a coordinate system. 
  No user input needed for this lab*/

#include <iostream>
#include <string>
using namespace std;

class Coordinate {

public:
	int x, y;

	//Initialize the coordinates. Two inputs parameters are mapped to X and Y
	void set(int inX, int inY) {
		x = inX;
		y = inY;
	}

	//Returns the value of X
	int getX (){
		return x;
	}

	//Returns the value of y
	int getY (){
		return y;
	}

	//The first parameter movves point horizontally 
	//The second parameter moves point vertically
	void move (int anoX, int anoY){
		x += anoX;
		y += anoY;
	}

	//It rotates the point 90 degrees clockwise
	void rotate() {
		int temp;
		temp = x;
		x = -y;
		y = temp;
	}

	//Shows the current values of the point
	void display() {
		if (x == 0 && y == 0) {
			cout << "(" << x << ", " << y << ")" << endl;
		}
		else {
			cout << "(" << x << ", " << y << ")" << "is located in quadrant " << quadrant() << endl;
		}
	}

	//Can keep it public for this lab.
	//Shows which quadrant the point is located in
	string quadrant() {
		if (x > 0 && y > 0) {
			return "I";
		}

		if (x < 0 && y > 0) {
			return "II";
		}

		if (x < 0 && y < 0) {
			return "III";
		}

		if (x > 0 && y < 0) {
			return "IV";
		}
	}
};

//it finds the slope between two coordinates
double slope(Coordinate p1, Coordinate p2) {
	double m;
	m = (p2.y - p1.y) / (p2.x - p1.x);
	return m;
}

int main() {
	//can hardcode coordinates
	Coordinate A, B, C;
	double m;

	cout << "Rotating A:" << endl;
	A.set(1, 2);
	A.display();

	for (int i = 0; i < 4; i++) {
		A.rotate();
		A.display();
	}

	cout << "Incrementing B:" << endl;
	B.set(2, 3);
	B.display();
	B.move(1, 1);
	B.display();

	cout << "Move C to origin:" << endl;
	C.set(5, -4);
	C.display();
	C.move(-5, 4);
	C.display();
	
	A.set(1, 2);
	A.getX();
	A.getY();
	B.set(2, 3);
	B.getX();
	B.getY();
	cout << "Slope of A to B = " << slope(A, B) << endl;
	system("pause");
}