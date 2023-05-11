#ifndef TURINGMACHINE_H_
#define TURINGMACHINE_H_
#include "TuringMachineState.h"
#include <set>
#include <vector>
class TuringMachine {
public:
  virtual TuringMachineState *find(int x, int y) { return nullptr; }
  virtual void add(TuringMachineState &s){};
  virtual std::vector<TuringMachineState> *getAll() { return nullptr; }
};
#endif /* TURINGMACHINE_H_ */
