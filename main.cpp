#include <stdio.h>

using namespace std;

int foo1()
{
	return 2;
}

int foo2()
{
	return foo1();
}

int foo3()
{
	return foo2();
}

int main()
{
	foo3();	
	return 0;
}
