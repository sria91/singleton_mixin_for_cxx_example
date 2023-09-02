#include <iostream>
#include <thread>
#include "singleton.hxx"

using namespace std;

class MyClass : public SingletonMixin<MyClass> {
public:
    void showMessage() {
        cout << "Hello from MyClass!" << endl;
    }

private:
    MyClass() {
        cout << "MyClass constructor called: " << this << endl;
    };
    friend class SingletonMixin<MyClass>;
};

void thread_function(const char * s) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    MyClass& singleton = MyClass::getInstance();
    cout << s << ": " << &singleton << endl << flush;
}

int main() {
    thread thread_1(thread_function, "thread 1");
    thread thread_2(thread_function, "thread 2");

    MyClass& singleton1 = MyClass::getInstance();
    MyClass& singleton2 = MyClass::getInstance();
    MyClass& singleton3 = MyClass::getInstance();

    cout << &singleton1 << ", " << &singleton2 << ", " << &singleton3 << endl;

    thread_1.join();
    thread_2.join();

    return 0;
}
