//
// Created by Felix on 2021/7/18.
//

#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

using namespace std;

void hello_thread() {
    cout << "Hello thread!" << endl;
}

void msum(int a, int b) {
    int c = a + b;
    cout << a << "+" << b << "=" << c << endl;
}

class HelloThread {
public:
    static void hellothread() {
        cout << "Hello world, I'm a thread!" << endl;
    }

    static void start() {
        thread thrd(hellothread);
        thrd.join();
    }
};

class HelloWorld {
public:
    void hello() {
        cout << "Hello world, I'm a thread!" << endl;
    }

    static HelloWorld &getInstance() {
        if (!instance) instance = new HelloWorld;
        return *instance;
    }

    static void start() {
        thread thrd(bind(&HelloWorld::hello, &HelloWorld::getInstance()));
        thrd.join();
    }

private:
    HelloWorld() = default;

    static HelloWorld *instance;
};

// TODO static变量可以初始化为int??
HelloWorld *HelloWorld::instance = nullptr;

class HelloWorld3 {
public:
    static void hello(int year) {
        cout << "I am " << year << " years old" << endl;
    }
};

void hello_thread1() {
    cout << "Hello thread!" << endl;
    cout << endl;
}

mutex mt;
int data = 1;

void addmethod(int a) {
    mt.lock();
    data += a;
    cout << "added data = " << data << endl;
    mt.unlock();
}

void multi(int a) {
    mt.lock();
    data *= a;
    cout << "multi data = " << data << endl;
    mt.unlock();
}

int main() {
    // 1. 普通函数多线程调用
    // 1.1 无参数函数
    thread t1(hello_thread);
    //主线程等待子线程运行结束后方可执行下一步
    t1.join();
    //主线程代码
    cout << "Main here" << endl;
//    getchar(); // 清空缓冲区。

    // 1.2 有参数函数
    thread t2(msum, 1, 2);
    t2.join();
    cout << "Main here" << endl;
//    getchar();

    cout << "---------------------------------" << endl;
    // 2. 在类内部创建线程
    // 2.1 类内部函数为静态函数
    HelloThread::start();
//    getchar();
    // 这里的start和hellothread方法都必须是static方法，不然就不能直接通过类来调用。

    // 2.2 在Singleton开发模式内部创建线程
    HelloWorld::start();
//    getchar();

    cout << "---------------------------------" << endl;
    // 3. 用类内部函数在类外部创建线程
    // 非常普通的类，只是用多线程调用其内部的函数
    thread thrd3(bind(&HelloWorld3::hello, 28));
    thrd3.join();

    cout << "---------------------------------" << endl;
    // 4. join()和detech()的区别
    // join()的作用是让主线程等待子线程结束方可执行下一步(串行)；
    // detach()使得子线程放飞自我，独立于主线程并发执行，主线程后续代码段无需等待。
    // 4.1 join()
    std::thread t3(hello_thread1);
    t3.join();
    std::thread t4(hello_thread1);
    t4.join();
    cout << "Main here" << endl;

    // 4.2 detach()
    std::thread t5(hello_thread1);
    std::thread t6(msum, 2, 3);
    t5.detach();
    t6.detach();
    cout << "Main here" << endl;

    this_thread::sleep_for(std::chrono::seconds(2));
    cout << "---------------------------------" << endl;
    // 5. 数据同步（线程同时操作一个数据的安全性）
    thread t7(addmethod, 2);
    thread t8(multi, 10);
    t7.detach();
    t8.detach();
    this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}















