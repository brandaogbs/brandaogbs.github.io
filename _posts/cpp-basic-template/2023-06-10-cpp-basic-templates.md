---
layout: post
title:  "STL: Basic Templates"
tags: [c++, stl]
date:   2023-06-09 22:57:49 +0000
---

In C++, the Standard Template Library (STL) is a collection of classes and functions that provides several useful algorithms and data structures. Templates are one of the core concepts of the STL.

Templates allow us to create generic functions and classes that can work with different data types without the need to write separate code for each type. This reduces the amount of code duplication and improves code reusability.

## Initial approach

Let's take a look at an example to understand what is the root problem that templates are trying to resolve. For instance, the `int findMax(int, int)` declared function that returns the max between two integers. Let's try to apply two different situations: i) passing `int` arguments; ii) passing `float`.

```cpp
#include <iostream>
#include <typeinfo>

int findMax(int x, int y) { return x >= y ? x : y; }

int main() {
  auto maxInt = findMax(13, 37);
  auto maxFloat = findMax(13.37f, 37.13f);

  std::cout << "maxInt(" << typeid(maxInt).name() << "):" << maxInt << "\n";
  std::cout << "maxFloat(" << typeid(maxFloat).name() << "):" << maxFloat << "\n";

  return 0;
}
```

```bash
gbs@gojira:~/fun/blog/cpp/00-templates $ clang++ main.cc --std=c++2a; ./a.out
main.cc:8:35: warning: implicit conversion from 'float' to 'int' changes value from 37.130001 to 37 [-Wliteral-conversion]
  auto maxFloat = findMax(13.37f, 37.13f);
                  ~~~~~~~         ^~~~~~
main.cc:8:27: warning: implicit conversion from 'float' to 'int' changes value from 13.37 to 13 [-Wliteral-conversion]
  auto maxFloat = findMax(13.37f, 37.13f);
                  ~~~~~~~ ^~~~~~
2 warnings generated.
maxInt(i):37
maxFloat(i):37
```

Oh,  we got compilation warnings cause of the implicit conversion between the types. It was expected. Let's try to fix it with the lazy approach. Just adding a new function `float findMax(float, float)`.

```cpp
int findMax(int x, int y) { return x >= y ? x : y; }
float findMax(float x, float y) { return x >= y ? x : y; }

int main() {
  ...
}
```

```bash
gbs@gojira:~/fun/blog/cpp/00-templates $ clang++ main.cc --std=c++2a; ./a.out
maxInt(i):37
maxFloat(f):37.13
```

Yap, the expected happens. So, what if using `double`, `unsigned`, and other types? Each time should I code a new version of the same function? Basically, this is one of the motivations for `template`. It could provide a generic approach to this type of situation, using the function templates.

## Function Templates

Template functions in C++ are functions that are designed to work with multiple types. Instead of specifying a concrete type for a function parameter or return value, we use a placeholder type known as a template parameter. This allows us to create a generic function that can be used with various data types.

So instead of creating new versions of the same function, we could adopt the template, as follow:

```cpp
template<typename Scalar>
Scalar findMax(Scalar x, Scalar y) { return x >= y ? x : y; }

int main() {
  ...
}
```

```bash
gbs@gojira:~/fun/blog/cpp/00-templates $ clang++ main.cc --std=c++2a; ./a.out
maxInt(i):37
maxFloat(f):37.13
maxDouble(d):37.13
```

The basic syntax is pretty easy. To define a template function, we use the `template` keyword followed by the template parameter list, enclosed in angle brackets `< >`. The template parameter list can include one or more template parameters, which represent the types the function will operate on. In the example, the Scalar type could assume any regular type. 

## Class Templates

We just saw the direct use of templates, it was just a vulgar display of power. Let's move on and look at templating classes. At this point, could be intuitive what it means. But, the class template allows you to create a blueprint for a class that can be customized to work with different data types. It allows you to define a generic class where the types of its members or methods can be parameterized

Now, let's try to create one of these “generic classes”. An easy choice could be a Stack class.

```cpp
template <typename T>
class Stack {
    private:
        std::vector<T> elements;

    public:
        void push(T element) {
            elements.push_back(element);
        }
        
        T pop() {
            if (elements.empty()) {
                throw std::out_of_range("Stack<>::pop(): empty stack");
            }
            T last = elements.back();
            elements.pop_back();
            return last;
        }
};
```

The syntax is similar to the function class. In this example, we are using the typename `T` to create the `Stack` generic class. It means that `T` could assume any regular type. Let's test with some types.

```cpp
 template <typename T>
class Stack { ... };

int main() {
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(3);
    intStack.push(3);
    intStack.push(7);
    for (int i = 0; i < 4; i++) {
        std::cout << intStack.pop() << "\n";
    }

    Stack<std::string> stringStack;
    stringStack.push("Hello"); 
    stringStack.push("World");
    stringStack.push("!");
    for (int i = 0; i < 3; i++) {
        std::cout << stringStack.pop() << "\n";
    }

  return 0;
}
```

Running the code, as expected, we got the correct answer. Working either for `int` or `std::string`.

```cpp
gbs@gojira:~/fun/blog/cpp/00-templates $ clang++ main.cc --std=c++2a; ./a.out
7
3
3
1
!
World
Hello
```

Most attentive have noted that `std::vector` is working with templates.  And yes, it is part of the Standard Template Library.
