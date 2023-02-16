#include <vector>
#include <iostream>


typedef struct
{
	int a;
	int b;
	std::vector<int> c;
} try_sizeof_t;

int main() {
	std::vector<int> a(1, 3);
	for (auto i: a) {
		printf("%d\n", i);
	}
	std::cout << sizeof(a) << std::endl;

	try_sizeof_t try_sizeof;
	std::cout << sizeof(try_sizeof) << std::endl;

}