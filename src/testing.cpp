#include "Array/Array.h"
#include <iostream>
using std::cout,std::endl;

int main(){
	PrettyArray a(25);
	a.print();
	a.shuffle();
	a.print();
	return 0;
}