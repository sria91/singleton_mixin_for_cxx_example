#include <iostream>
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

int main() {
    MyClass& singleton1 = MyClass::getInstance();
    MyClass& singleton2 = MyClass::getInstance();
    MyClass& singleton3 = MyClass::getInstance();

    cout << &singleton1 << ", " << &singleton2 << ", " << &singleton3 << endl;

    return 0;
}
