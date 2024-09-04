#ifndef __CENTER_H__
#define __CENTER_H__

#include "productmanager.h"
#include "stockmanager.h"

using namespace std;

class Center {
  public:
      Center(ProductManager& pm, StockManager& sm);
      void pauseScreen();
      void displayMainMenu();
      void displayDockerMenu();
      void displayStockMenu();
      void displayProductMenu();
      void DockerManagement();
      void StockManagement();
      void ProductManagement();
      void run();
  private:
      ProductManager& pm;
      StockManager& sm;
};

#endif    // __CENTER_H__
