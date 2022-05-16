#include <iostream>
#include <string>
using namespace std;

int main() {
	string noun, verb, adjective, sense, name, place;
	
	cout << "Welcome to Madlibs!" << endl;
	cout << endl;

	cout << "Enter a verb:" << endl;
	cin >> verb;
	cout << "Enter a noun:" << endl;
	cin >> noun;
	cout << "She " << verb << " a " << noun << " while it was on sale." << endl;
	cout << endl;

	cout << "Enter a noun:" << endl;
	cin >> noun;
	cout << "Enter one of the five senses:" << endl;
	cin >> sense;
	cout << "Enter an adjective:" << endl;
	cin >> adjective;
	cout << "A " << noun << " by any other name would " << sense << " as " << adjective << "." << endl;
	cout << endl;

	cout << "Enter a name:" << endl;
	cin >> name;
	cout << "Enter a place:" << endl;
	cin >> place;
	cout << "Forget it, " << name << ". It's " << place << "." << endl;
	cout << endl;

	system("pause");
	cin.get();

}