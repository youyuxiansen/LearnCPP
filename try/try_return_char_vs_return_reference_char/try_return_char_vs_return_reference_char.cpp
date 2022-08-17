#include <assert.h>
#include <iostream>

using namespace std;

class CTextBlock {
public:
	CTextBlock (char char1[6]) {pText = char1;}
	char &operator[](int position) const { return pText[position]; }

public:
	char* pText;
};

int main() {
	char char2[6] = "Hello";
	const CTextBlock ctb(char2);
	char* pc = &ctb[0];
	if (pc == ctb.pText)
		cout << "is equal\n";
	*pc = 'J';
	cout << ctb.pText << "\n";
}