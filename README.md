# Converting any class into a Singleton class in C++

Singleton is one of the creational design patterns. A singleton class has only one instance and provides a global point of access to that instance. It's commonly used when you want to restrict the instantiation of a class to a single object, which can be useful for scenarios where you need a single point of control or coordination.

Following are some of the prominent features of Singleton class:

* **Private constructor**: The key idea behind the Singleton pattern is to make the class's constructor private, preventing external code from directly creating instances of the class.
    
* **Static instance**: Inside the class, you have a static object that holds the single instance of the class. This instance is usually created the first time it's requested and then reused.
    
* **Static method**: You provide a static method that acts as the global access point to the single instance. This method checks if an instance already exists and either returns the existing one or creates a new instance if needed.
    
* **Thread safety**: In multithreaded environments, it's important to ensure that the creation of the instance is thread-safe.
    
* **Global access**: The Singleton instance can be accessed globally, allowing different parts of your codebase to interact with the same instance of the class.
    

In this article, I am introducing an approach using which we can convert any class into a Singleton class with minimum effort. To achieve this we are going to create what is called a mixin. Without further ado let's create the `SingletonMixin`.

* `SingletonMixin` is going to be a template class
    
* The default constructor is protected to prevent direct instantiation
    
* The destructor is virtual and protected so that it can be overridden in a derived class
    
* The copy constructor and copy assignment constructor are also disabled to ensure a single instance is present at any point in time
    
* The core logic of the singleton instance creation is implemented inside the `getInstance` method
    

```cpp
#include <iostream>

using namespace std;

template <typename T>
class SingletonMixin {
public:
    static T& getInstance() {
        static T instance;  // Guaranteed to be created and destroyed once in a thread-safe way
        return instance;
    }

    SingletonMixin(const SingletonMixin&) = delete;             // Disable copy constructor
    SingletonMixin& operator=(const SingletonMixin&) = delete;  // Disable copy assignment constructor

protected:
    SingletonMixin() {
        // Protected constructor to prevent direct instantiation
        cout << "SingletonMixin constructor called: " << this << endl;
    }
    virtual ~SingletonMixin() {
        cout << "SingletonMixin destructor called: " << this << endl;
    }
};
```

Now let's take for example the following code. It represents a simple class called `MyClass` which has a default constructor and a single public method implemented. Whereas in real-world use cases, we can have many more methods.

```cpp
class MyClass {
public:
    void showMessage() {
        cout << "Hello from MyClass!" << endl;
    }
    MyClass() {
        cout << "MyClass constructor called: " << this << endl;
    };
};
```

We can convert `MyClass` into a singleton class in the following way:

* First, we inherit from `SingletonMixin<MyClass>`
    
* Make the default constructor private and `SingletonMixin<MyClass>` a friend class of `MyClass`, so that `MyClass` can only be instantiated from the `SingletonMixin<MyClass>` class.
    

```cpp
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
```

To create/access the singleton instance of `MyClass` we can call the `getInstance` method on `MyClass` class. We can call it as many times as we want, we are going to receive the same instance of the `MyClass` class. We can verify it printing out the address of the instance.

```cpp
#include <thread>

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
```

<div data-node-type="callout">
<div data-node-type="callout-emoji">💡</div>
<div data-node-type="callout-text">Since this approach uses the default constructor to create the singleton instance, one could use getter and setter methods to access (read/write) any member variables that may become part of <code>MyClass</code>.</div>
</div>

[Link to the code](https://github.com/sria91/singleton_mixin_for_cxx_example)

[Try online in a new Codespace](https://codespace.new/sria91/singleton_mixin_for_cxx_example)
