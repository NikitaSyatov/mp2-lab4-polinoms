//release function, class
#include "../include/polinom.h"
#include <iostream>

Node::Node(double factor = 1, size_t pow = 0, Node* pNext = nullptr)
{
    this->factor = factor;
    this->pow = pow;
    this->pNext = pNext;
}

List::List()
{
    this->Head = nullptr;
}

Node* List::GetHead()
{
    return this->Head;
}

void List::clear()
{
    Node* ptr1 = this->Head;
    Node* ptr2 = this->Head;
    while (ptr1 != nullptr)
    {
        ptr2 = ptr1;
        ptr1 = ptr1->pNext;
        delete ptr2;
    }
    this->Head = nullptr;
}

void List::Sort()
{
    Node* a, * b, * p, * h = nullptr;

    for (Node* i = Head; i != nullptr; ) {
        a = i;
        i = i->pNext;
        b = h;
        for (p = nullptr; (b != nullptr) && (a->pow < b->pow); ) {
            p = b;
            b = b->pNext;
        }

        if (p == nullptr) {
            a->pNext = h;
            h = a;
        }
        else {
            a->pNext = b;
            p->pNext = a;
        }
    }
    if (h != nullptr)
        Head = h;
}

void List::push_back(double factor, size_t pow)
{
    bool id = false;
    if (Head == nullptr)
    {
        Head = new Node(factor, pow);
    }     
    else
    {
        Node* tmp = Head;

        while (tmp->pNext != nullptr)
        {  
            tmp = tmp->pNext;
        }

        tmp->pNext = new Node(factor, pow);
    }
}

List::~List()
{
    Node* del = Head;
    while (del != nullptr)
    {
        Node* tmp_ptr = del->pNext;
        del = tmp_ptr;
    }
    Head = nullptr;
}

Polinoms::Polinoms() : List() {}

Polinoms::Polinoms(const std::string& pol) : List()
{
    int start_id = 0;
    for (int i = 1; i <= pol.size(); i++)
    { 
        if (pol[i] == '+' || pol[i] == '-' || i == pol.size())   //monommial parsing
        {
            this->Parse(pol, start_id, i-1);
            start_id = i;
        }
    }

    this->Sort();
}

void Polinoms::Parse(std::string pol, int start, int end)
{
    int i = start;
    std::string factor;
    bool fc = false;

    bool exc = false;

    if (pol[i] == '-')
    {
        factor += '-';
        i++;
    }
    if (pol[i] == '+')
        i++;
    
    while (pol[i] != 'x' && pol[i] != 'y' && pol[i] != 'z' && i < pol.size())
    {
        factor += pol[i++];
        fc = true;
    }
    
    if (!fc)
        factor += "1";

    double koef = convert(factor);

    size_t power = 0;

    while (i <= end)
    {
        if (pol[i] == 'x')
        {
            i++;
            if (pol[i] == '^')
            {
                i++;
                power += (int(pol[i]) - 48) * 100;
            }
            else if (i == pol.size() || pol[i] == 'x' || pol[i] == 'y' || pol[i] == 'z' || pol[i] == '+' || pol[i] == '-')
                power += 100;
            else
                throw std::exception("uncorrect polinoms");
        }

        if (pol[i] == 'y')
        {
            i++;
            if (pol[i] == '^')
            {
                i++;
                power += (int(pol[i]) - 48) * 10;
            }
            else if (i == pol.size() || pol[i] == 'x' || pol[i] == 'y' || pol[i] == 'z' || pol[i] == '+' || pol[i] == '-')
                power += 10;
            else
                throw std::exception("uncorrect polinoms");
        }

        if (pol[i] == 'z')
        {
            i++;
            if (pol[i] == '^')
            {
                i++;
                power += int(pol[i]) - 48;
            }
            else if (i == pol.size() || pol[i] == 'x' || pol[i] == 'y' || pol[i] == 'z' || pol[i] == '+' || pol[i] == '-')
                power += 1;
            else
                throw std::exception("uncorrect polinoms");
        }

        i++;
    }

    this->push_back(koef, power);
}

bool Polinoms::operator==(const Polinoms& pln)
{
    Node* j = pln.Head;
    Node* i = this->Head;
    for (; i != nullptr && j != nullptr; i = i->pNext, j = j->pNext)
        if (i->factor != j->factor || i->pow != j->pow)
            return false;

    if (i != nullptr || j != nullptr)
        return false;

    return true;
}

bool Polinoms::operator!=(const Polinoms& pln)
{
    return !(*this == pln);
}

const Polinoms& Polinoms::operator=(const Polinoms& pln)
{
    if (*this != pln)
    {
        this->clear();
        Node* tmp = pln.Head;
        while (tmp != nullptr)
        {
            this->push_back(tmp->factor, tmp->pow);
            tmp = tmp->pNext;
        }
    }
    return *this;
}

Polinoms Polinoms::operator*(const double alpha)
{
    Polinoms res;
    bool checkNULL = false;
    for (Node* i = Head; i != nullptr; i = i->pNext)
    {
        if ((i->factor * alpha) != 0)
        {
            checkNULL = true;
            res.push_back(i->factor * alpha, i->pow);
        }
    }

    if (!checkNULL)
        return Polinoms("0");

    return res;
}

Polinoms Polinoms::operator+(const Polinoms& pln)
{
    Polinoms res;
    Node* pln_ptr = pln.Head;
    Node* i = Head;
    while (i != nullptr && pln_ptr != nullptr)
    {
        if (pln_ptr->pow > i->pow)
        {
            res.push_back(pln_ptr->factor, pln_ptr->pow);
            pln_ptr = pln_ptr->pNext;
        }
        else if (pln_ptr->pow == i->pow)
        {
            if (i->factor + pln_ptr->factor != 0)
                res.push_back(i->factor + pln_ptr->factor, i->pow);
            pln_ptr = pln_ptr->pNext;
            i = i->pNext;
        }
        else
        {
            res.push_back(i->factor, i->pow);
            i = i->pNext;
        } 
    }
    while (i != nullptr)
    {
        res.push_back(i->factor, i->pow);
        i = i->pNext;
    }

    while (pln_ptr != nullptr)
    {
        res.push_back(pln_ptr->factor, pln_ptr->pow);
        pln_ptr = pln_ptr->pNext;
    }

    return res;
}

Polinoms Polinoms::operator-(Polinoms& pln)
{
    return *this + (pln * (-1));
}

Polinoms Polinoms::operator*(const Polinoms& pln)
{
    Polinoms res;
    for (Node* i = Head; i != nullptr; i = i->pNext)
    {
        Polinoms tmp;
        for (Node* j = pln.Head; j != nullptr; j = j->pNext)
        {
            if (i->pow + j->pow > 999) //x
                throw std::exception("x:power is very longest");
            if ((i->pow + j->pow) % 10 < (i->pow % 10)) //z
                throw std::exception("z:power is very longest");
            if (((i->pow + j->pow) / 10) % 10 < (i->pow / 10) % 10) //y
                throw std::exception("y:power is very longest");

            tmp.push_back(i->factor * j->factor, i->pow + j->pow);
        }
        res = res + tmp;
    }
    return res;
}

Polinoms::~Polinoms() {}

std::ostream& operator<<(std::ostream& ostr, Polinoms pln)
{
    for (Node* i = pln.GetHead(); i != nullptr; i = i->pNext)
    {
        ostr << i->factor;
        if (int(i->pow / 100) != 0)
            ostr << "x^" << int(i->pow / 100);
        if ((int(i->pow % 100) / 10) != 0)
            ostr << "y^" << int((i->pow % 100) / 10);
        if ((i->pow % 10) != 0)
            ostr << "z^" << (i->pow % 10);
        if (i->pNext != nullptr && i->pNext->factor > 0)
            ostr << "+";
    }
    return ostr;
}

double convert(std::string num)
{
    size_t i = 0;
    double result = 0;

    int sign = 1;

    if (num[i] == '-')
    {
        sign *= -1;
        i++;
    }

    int power = 1;
    for (; num[i] != ',' && i < num.size(); i++)     //integer part
    {
        if (int(num[i]) >= 48 && int(num[i]) <= 57)
        {
            result *= power;
            result += (double(num[i]) - 48);
            power *= 10;
        }
        else
            throw std::exception("uncorrect koef");
    }
    power = 10;
    i++;
    for (; i < num.size(); i++)    //tail
    {
        result += (double(num[i]) - 48) / power;
        power *= 10;
    }

    return result*sign;
}
