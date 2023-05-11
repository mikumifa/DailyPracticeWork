#ifndef MENUSYSTEM_H_
#define MENUSYSTEM_H_
#include <iostream>
#include <vector>
#include <algorithm>
#include "DenseTuringMachine.h"
#include "TuringTape.h"
#include "SparseTuringMachine.h"
class MenuSystem {
public:
	void menu();
private:
    static void show_chosen();
};
TuringMachine* createDenseTuringMachine( std::vector<TuringMachineState>& states);
void renameStatesAndContents(std::vector<TuringMachineState>& states, std::map<int,int>& state_map, std::map<int,int>& content_map);
#endif /* MENUSYSTEM_H_ */
