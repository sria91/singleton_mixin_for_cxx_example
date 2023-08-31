#pragma once

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
