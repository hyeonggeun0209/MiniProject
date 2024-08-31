#ifndef __WAREHOUSE_H__
#define __WAREHOUSE_H__

#include "productmanager.h"
#include "inventorymanager.h"

using namespace std;

class WareHouse {
  public:
      WareHouse();
      bool displayMenu();
  private:
      ProductManager bm;
      InventoryManager im;
};

#endif    // __WAREHOUSE_H__
