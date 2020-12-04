#include <iostream>
#include <utility>

using namespace std;


int main(int argc, char const *argv[])
{
	/* code */
	pair<int, int> p1 = make_pair(1, 2);
	pair<int, int> p2 = make_pair(1, 3);
	cout << (p1 == p2) << endl;
}