#include "Calculator.h"
#include <exception>
#include <iostream>

int Calculator::add(int a, int b) {
	return a + b;
}


int Calculator::sub(int a, int b) {
	return a - b;
}

int Calculator::div(int a, int b) {
	if (b == 0) throw b;
	return a / b;

}


int Calculator::mult(int a, int b) {
	return a * b;
}

int Calculator::factorial(int n) {

	if(n < 0) {
		return -1;
	}else if (n == 0 || n == 1)
		return 1;
	else {
		return n * factorial(n - 1);
	}
}