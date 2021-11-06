//
// Created by Felix on 2021/7/17.
//

#include <iostream>

using namespace std;

int main() {
//    example1
    int a[5] = {1, 2, 3, 4, 5};
    int *ptr = (int *) (&a + 1);
    cout << a << " is the same as " << &a << endl;
//    a 和 &a 虽然值一样，但是意思不一样，a是数组的首地址，代表a[0]的地址，a+1，代表这个数组下一个元素的地址，即a[1];
//    &a代表数组这个对象，代表这个对象的首地址，&a+1代表a往后推一个对象，即推一个相同大小数组的首地址。
    cout << (&a + 1) << " is the same as " << (int *) (&a + 1) << endl;
//    同理，(&a + 1)和(int *) (&a + 1)虽然值一样，但是意思也不同，(&a + 1)代表的是"对象"（数组），与&a类型相同；
//    (int *) (&a + 1) 等于将这个"对象"强转成了一个整形。变成跟a一样的类型了，所以下面*(ptr - 1)即等于左移一个int *的大小。
    cout << *ptr << endl;
    printf("%d,%d\n", *(a + 1), *(ptr - 1));

//example2
    void *buffers[2];
    cout << buffers[0] << endl;
    cout << &buffers[0] << endl;
}