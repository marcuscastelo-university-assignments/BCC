#include <iostream>
#include <utility>

using namespace std;

inline int test() 
{
	static int a = 1;
	return a++;
}

int main(int argc, char const *argv[])
{
	cout << test() << endl;
	cout << test() << endl;
}