#include <iostream>
#include <string>
using namespace std;

#define BLACK "\033[0m"
#define RED   "\033[1;31m"
#define Green "\033[1;32m"
#define CYAN "\033[1;36m"

int main()
{
	string color;
	color = RED;
	cout << color << "Hello! ";
	color = Green;
	cout << color << "How are you today? ";
	color = CYAN;
	cout << color << "I'm Rath by the way!";
	return 0;
}
