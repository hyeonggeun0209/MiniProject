#include <iostream>
#include "center.h"
#include "stockmanager.h"
#include "productmanager.h"

int main()
{
    ProductManager pm;
    StockManager sm;
    Center center(pm, sm);
    center.run();
    return 0;
}
