/*File:Project One.cpp
Author: Trinity Caitlin Atayan Belen
Description: Project One is a simulator for online shopping.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int quantity;
	int price;
	int day;
	int shippingDate;
	int shippingCost;
	int height;
	int width;
	int length;
	int weight;
	int subTotal;
	int Total;

	char shippingMethod;
	char order;

	double volume;
	double tax = 0.875;

	cout << "Welcome to Amazing Accessory Arsenal!" << endl;
	cout << "Please select a product to order!" << endl;
	cout << "(1) Beautiful Barrette" << endl;
	cout << "(2) Handy Hat" << endl;
	cout << "(3) Energetic Earrings" << endl;
	cout << "(4) Wonderful Watch" << endl;
	cout << "(5) Soft Scarf" << endl;
	cin >> order;

	switch (order) {
	case '1':
		cout << "You have chosen the beatiful barrette!" << endl;
		price = rand() % (1 - 5) + 5;
		cout << price << " is the cost per barrette." << endl;
		break;

	case '2':
		cout << "You have chosen the handy hat!" << endl;
		price = rand() % (1 - 5) + 7;
		cout << price << " is the cost per hat." << endl;
		break;

	case '3':
		cout << "You have chosen the energetic earrings!" << endl;
		price = rand() % (1 - 5) + 2;
		cout << price << " is the cost per earrings." << endl;
		break;

	case '4':
		cout << "You have chosen the wonderful watch!" << endl;
		price = rand() % (1 - 5) + 10;
		cout << price << " is the cost per watch." << endl;
		break;

	case '5':
		cout << "You have chosen the soft scarf!" << endl;
		price = rand() % (1 - 5) + 8;
		cout << price << " is the cost per scarf." << endl;
		break;

	default:
		cout << "Invalid!" << endl;
		break;
	}

	cout << "How many would you want to purchase?" << endl;
	cin >> quantity;

	if (quantity <= 0) {
		cout << "Invalid!" << endl;
		return 0;
	}
	if (quantity > 0) {
		subTotal = price * quantity;
		cout << "Your subtotal is " << subTotal << "." << endl;
	}
	else
		cout << "Invalid!" << endl;

	cout << "How would you like your order shipped?" << endl;
	cout << "(1) USPS = 10 days" << endl;
	cout << "(2) UPS = 7 days" << endl;
	cout << "(3) FedEx = 4 days" << endl;
	cin >> shippingMethod;

	cout << "What day of the month is it?" << endl;
	cin >> day;

	switch (shippingMethod) {
	case '1':
		if (day <= 0) {
			cout << "Invalid!" << endl;
			return 0;
		}
		else if (day > 20) {
			shippingDate = (day + 10) - 30;
		}
		else if (day <= 20) {
			shippingDate = day + 10;
		}
		else
			cout << "Invalid!" << endl;
		break; 

	case '2':
		if (day <= 0) {
			cout << "Invalid!" << endl;
			return 0;
		}
		else if (day <= 23) {
			shippingDate = day + 7;
		}
		else if (day > 23) {
			shippingDate = (day + 7) - 30;
		}
		else {
			cout << "Invalid!" << endl;
		}
		break;

	case '3':
		if (day <= 0) {
			cout << "Invalid!" << endl;
			return 0;
		}
		else if (day <= 26) {
			shippingDate = day + 4;
		}
		else if (day > 26) {
			shippingDate = (day + 4) - 30;
		}
		break;

	default:
		if (day <= 0) {
			cout << "Invalid!" << endl;
			return 0;
		}
		else if (day > 20) {
			shippingDate = (day + 10) - 30;
		}
		else if (day <= 20) {
			shippingDate = day + 10;
		}
		else
			cout << "Invalid!" << endl;
		break; 
	}

	cout << "Your estimated shipping date is " << shippingDate << "." << endl;

	cout << "What are the dimensions of the package?" << endl;
	cout << "The height is?" << endl;
	cin >> height;
	cout << "The width is?" << endl;
	cin >> width;
	cout << "The length is?" << endl;
	cin >> length;
	volume = height * width * length;

	cout << "What is the weight of the package?" << endl;
	cin >> weight;

	switch (shippingMethod) {
	case '1':
		if (volume <= 0) {
			cout << "Invalid!" << endl;
			return 0;
		}
		else if (volume < 1000) {
			shippingCost = 1.55 * weight;
		}
		else if (volume >= 1000) {
			shippingCost = 1.55 * weight + (volume / 1000);
		}
		else
			cout << "Invalid!" << endl;
		break;

	case '2':
		if (volume <= 0) {
			cout << "Invalid!" << endl;
			return 0;
		}
		else if (volume >= 1000) {
			shippingCost = 1.65 * weight + (volume / 1000);
		}
		else if (volume < 1000) {
			shippingCost = 1.65 * weight;
		}
		else
			cout << "Invalid!" << endl;
		break;

	case '3':
		if (volume <= 0) {
			cout << "Invalid!" << endl;
			return 0;
		}
		else if (volume >= 1000) {
			shippingCost = 1.72 * weight + (volume / 1000);
		}
		else if (volume < 1000) {
			shippingCost = 1.72 * weight;
		}
		else
			cout << "Invalid!" << endl;
		break;

	default:
		if (volume <= 0) {
			cout << "Invalid!" << endl;
			return 0;
		}
		else if (volume >= 1000) {
			shippingCost = 1.55 * weight + (volume / 1000);
		}
		else if (volume < 1000) {
			shippingCost = 1.55 * weight;
		}
		else
			cout << "Invalid!" << endl;
		break;
	}

	cout << "Your shipping cost is " << shippingCost << "." << endl;

	Total = shippingCost + subTotal + tax;
	cout << Total << " is the cost of your order." << endl;

	system("pause");
}