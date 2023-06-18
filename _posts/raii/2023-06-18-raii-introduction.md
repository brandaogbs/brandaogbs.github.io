---
layout: post
title:  "RAII: an introduction"
tags: [c++, raii, desing-pattern]
date:   2023-06-15 22:57:49 +0000
---
Managing resources effectively in C++ can be a challenge. From memory allocation to file handling, ensuring proper acquisition and release of resources requires careful attention. However, there's a solution that simplifies this process: RAII (Resource Acquisition Is Initialization).

RAII is a powerful design pattern in C++ that ties resource acquisition to object initialization, automating resource management. It promotes cleaner and more maintainable code while preventing resource leaks and bugs.

By leveraging features like constructors and destructors, RAII ensures automatic resource release and exception safety. It can be applied to various resource types, making it versatile and widely applicable.

Join this journey to discover how RAII can streamline your resource management in C++ projects. And how this design pattern could help you.

## The LeakyClass

Let's start creating a simple example of a resource management problem from real-world use. How many times do you write this kind of implementation? A simple class, that holds a resource, e.g. `Mutex`, and performs some dummy task.

```cpp
#pragma once

#include <iostream>
#include <mutex>
#include <string>

class LeakyClass {
  public:
    LeakyClass(){};
    void outputText(const std::string &text) {
        mutex.lock();

        if (isStringToLong(text))
            return;
        std::cout << text << "\n";

        mutex.unlock();
    }

  private:
    std::mutex mutex;

    bool isStringToLong(const std::string &text) { return text.length() >= 25; }
};
```

So, no problems here, right?

```cpp
#include "LeakyClass.h"
#include <iostream>

int main() {
    LeakyClass leakyClass;
    leakyClass.outputText("First test on LeakyClass");

    return 0;
}
```

```cpp
gbs@gojira:~/fun/blog/cpp/raii $ clang++ main.cc -o main -Wall -Wextra -std=c++20; ./main
First test on LeakyClass
```

Ok, no problems yet. Let's test the early return use case: just add a new call to `leakyClass.outputText("Second Test on LeakyClass")`.

```cpp
gbs@gojira:~/fun/blog/cpp/raii $ clang++ main.cc -o main -Wall -Wextra -std=c++20; ./main
First test on LeakyClass
```

Alright, no problems. It worked as expected. Let's just take another example:

```cpp
#include "LeakyClass.h"
#include <iostream>

int main() {
    LeakyClass leakyClass;
    leakyClass.outputText("First test on LeakyClass");
    leakyClass.outputText("Second test on LeakyClass");
    leakyClass.outputText("Third test on LeakyClass");

    return 0;
}
```

```cpp
gbs@gojira:~/fun/blog/cpp/raii $ clang++ main.cc -o main -Wall -Wextra -std=c++20; ./main
First test on LeakyClass
```

Oops, it crashed. Let's try to understand what happens. Looking that the `LeakyClass` implementation will note that the resource (`mutex`) was not properly released when the program ends in the early return. In other words, at the beginning of the function, we take the resource `mutex.lock()` and did not release it, because of the premature return.

And yes, I know. “How many programs I've written that could have this type of problem, created by an early return, an exception, etc.”

## Lazy solution (at least no leaky)

To solve it is to try to guarantee that at the end of the life cycle of the object, the resource was released. Ok? So let's populate the operators that provide this type of guarantee.

```cpp
LeakyClass() { mutex.lock(); };
~LeakyClass() { mutex.unlock(); };

void outputText(const std::string &text) {
    if (isStringToLong(text))
        return;
    std::cout << text << "\n";
}
```

```cpp
gbs@gojira:~/fun/blog/cpp/raii $ clang++ main.cc -o main -Wall -Wextra -std=c++20;./main
First test on LeakyClass
Third test on LeakyClass
```

Oh yeah, bingo. Now the program did not crash. But as excepted, this is not the best way to do it. 

If we try to run a multi-threading program using this approach. We will be in a hard time. Take a look at the implementation. We took the resource at the object creation and release it on the destructor. It means, that the resource is blocked during the full life-cycle of the `LeakyClass` instance. It is very problematic, for instance, when we are trying to parallelize it.

## A more convenient approach

Instead of holding the resource during the life cycle of the object. Let's try to hold it only during the `outputText(const std::string&)` execution.

It could be achieved by creating a mechanism that dies with the ending of the scope, e.g. local variable. So, let's code a `MutexHandler` class to perform this task.

```cpp
class MutexHandler {
  public:
    MutexHandler(std::mutex &mutex) : mutex(mutex) { mutex.lock(); };
    ~MutexHandler() { mutex.unlock(); };

  private:
    std::mutex &mutex;
};
```

Now, we have a specialized class that holds the resource (e.g. `Mutex`) during the entire life cycle. Thus, let's put it in the desired place and test it.

```cpp
class LeakyClass {
  public:
    LeakyClass() {};
    ~LeakyClass() {};
    void outputText(const std::string &text) {
        MutexHandler mutexHandler(mutex);

        if (isStringToLong(text))
            return;
        std::cout << text << "\n";
    }

  private:
    std::mutex mutex;

    bool isStringToLong(const std::string &text) { return text.length() >= 25; }
};
```

```cpp
gbs@gojira:~/fun/blog/cpp/raii $ clang++ main.cc -o main -Wall -Wextra -std=c++20;./main
First test on LeakyClass
Third test on LeakyClass
```

As excepted the solution achieved the results. And now, different from the previous version, the life cycle of the `Mutex` is coupled with the `MutexHandler` instance, not the principal object. 

In Modern C++, we have access to a lot of RAII-style mechanisms, e.g. `lock_guard<std::Mutex>` that have the role of our implementation (https://en.cppreference.com/w/cpp/thread/lock_guard). So, try to look for this type of built-in solution every time possible.
