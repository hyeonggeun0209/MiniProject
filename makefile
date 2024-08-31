all:
	@echo this is all target
	@g++ -std=c++17 main.cpp product.cpp productmanager.cpp warehouse.cpp inventory.cpp inventorymanager.cpp
	@./a.out

clean:
	@echo this is clean target
	@rm a.out
