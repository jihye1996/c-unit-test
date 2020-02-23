#include<iostream>
#include "Calculator.h"
using namespace::std;


int main(void) {

	Calculator cal;

	int a, b, ans;

	cout << "a와 b를 차례대로 입력하시오." << endl;
	cin >> a >> b;

	ans = cal.add(a, b);
	cout << "add 결과: " << ans << endl;

	ans = cal.sub(a, b);
	cout << "sub 결과: " << ans << endl;

	try {
		ans = cal.div(a, b);
		cout << "div 결과: " << ans << endl;
	}
	catch (int exception) {
		std::cout << exception << " division error" << std::endl;
	}
	
	

	ans = cal.mult(a, b);
	cout << "mult 결과: " << ans << endl;

	ans = cal.factorial(a);
	cout << "factorial a 결과: " << ans << endl;

	ans = cal.factorial(b);
	cout << "factorial b 결과: " << ans << endl;

	return 0;

}