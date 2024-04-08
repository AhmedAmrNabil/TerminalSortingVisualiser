#include "Array/Array.h"
#include <iostream>
using std::cout,std::endl;

int main(){
	PrettyArray a(30);
	a.printBars();
	a.shuffle();
	a.markItem(5);
	// a.printBars();
	return 0;
}