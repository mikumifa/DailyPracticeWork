#include "SparseTuringMachine.h"
#include <algorithm>

TuringMachineState *SparseTuringMachine::find(int x, int y) {
  if (state_map.find(x) == state_map.end()) {
    return nullptr;
  } else if (state_map[x].end() == state_map[x].find(y))
    return nullptr;

  return &states[state_map[x][y]];
}

void SparseTuringMachine::add(TuringMachineState &s) {
  states.push_back(s);
  state_map[s.getCurrentState()][s.getCurrentContent()] = states.size() - 1;
}

std::vector<TuringMachineState> *SparseTuringMachine::getAll() {
  return &states;
}
