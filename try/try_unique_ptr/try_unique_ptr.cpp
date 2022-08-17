#include <iostream>
#include <memory>
#include "try_unique_ptr.h"

void try1()
{
	std::unique_ptr<B> b;
	b->try2();
}

void B::try2()
{
	B *b1 = const_cast<B *>(this);
	b1->prt();
}

int main() {
	try1();
	return 0;
}