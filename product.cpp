#include "product.h"

#include <iostream>

using namespace std;

Product::Product(int id, string name, string price)
          : m_id(id), m_name(name), m_price(price)
{
}

string Product::getName() const
{
    return m_name;
}

void Product::setName(string& name)
{
    m_name = name;
}

string Product::getPrice() const
{
    return m_price;
}

void Product::setPrice(string& price)
{
    m_price = price;
}

int Product::id() const
{
    return m_id;
}

// Define copy assignment operator.
bool Product::operator==(const Product &other) const {
    return (this->m_name == other.m_name);
}
