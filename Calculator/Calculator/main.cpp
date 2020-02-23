#include<iostream>
#include "Calculator.h"
using namespace::std;


int main(void) {

	Calculator cal;

	int a, b, ans;

	cout << "a�� b�� ���ʴ�� �Է��Ͻÿ�." << endl;
	cin >> a >> b;

	ans = cal.add(a, b);
	cout << "add ���: " << ans << endl;

	ans = cal.sub(a, b);
	cout << "sub ���: " << ans << endl;

	try {
		ans = cal.div(a, b);
		cout << "div ���: " << ans << endl;
	}
	catch (int exception) {
		std::cout << exception << " division error" << std::endl;
	}
	
	

	ans = cal.mult(a, b);
	cout << "mult ���: " << ans << endl;

	ans = cal.factorial(a);
	cout << "factorial a ���: " << ans << endl;

	ans = cal.factorial(b);
	cout << "factorial b ���: " << ans << endl;

	return 0;

}