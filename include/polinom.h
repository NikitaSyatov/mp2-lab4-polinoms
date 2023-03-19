//declaring a class as a polynomial
#pragma once
#include <string>

class Node {
public:
    double factor;
    size_t pow;
    Node* pNext;

    Node(double factor, size_t pow, Node* pNext);
};

class List {
protected:
    Node* Head;
public:
    List();

    Node* GetHead();

    void clear();

    void push_back(double factor, size_t pow);

    void Sort();

    ~List();
};

class Polinoms:public List {
private:
    void Parse(std::string pol, int start, int end);
public:
    Polinoms();

    Polinoms(const Polinoms& pln);

    Polinoms(const std::string& pol);

    bool operator==(const Polinoms& pln);
    
    bool operator!=(const Polinoms& pln);

    const Polinoms& operator=(const Polinoms& pln);

    Polinoms operator*(const double alpha);

    Polinoms operator+(const Polinoms& pln);

    Polinoms operator-(Polinoms& pln);

    Polinoms operator*(const Polinoms& pln);

    ~Polinoms();

    void show();
};

double convert(std::string num);