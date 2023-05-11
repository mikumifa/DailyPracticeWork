#ifndef SPARSETURINGMACHINE_H_
#define SPARSETURINGMACHINE_H_
#include "TuringMachine.h"
#include <map>
#include <vector>

class SparseTuringMachine : public TuringMachine {
public:
  TuringMachineState *find(int x, int y) override;
  void add(TuringMachineState &s) override;
  std::vector<TuringMachineState> *getAll() override;
  virtual ~SparseTuringMachine() = default;


private:
  // storage the state
  std::vector<TuringMachineState> states;
  // storage the index of the state
  std::map<int, std::map<int, int>> state_map;
};

#endif /* SPARSETURINGMACHINE_H_ */
