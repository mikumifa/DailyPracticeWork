#include "DenseTuringMachine.h"
#include <stdexcept>

DenseTuringMachine::DenseTuringMachine(int x, int y) {
  if (x >= 0 && y >= 0)
    m_x = x, m_y = y;
  if (x == -1) {
    m_x = INT32_MAX;
  }
  if (y == -1) {
    m_y = INT32_MAX;
  }
}

TuringMachineState *DenseTuringMachine::find(int x, int y) {

  if (x < 0 || x > m_x || y < 0 || y > m_y) {
    return nullptr;
  }
  for (auto &state : m_states) {
    if (state.getCurrentState() == x && state.getCurrentContent() == y)
      return &state;
  }
  return nullptr;
}

std::vector<TuringMachineState> *DenseTuringMachine::getAll() {
  return &m_states;
}

void DenseTuringMachine::add(TuringMachineState &s) {
  if (s.getCurrentState() >= 0 && s.getCurrentState() <= m_x &&
      s.getCurrentContent() >= 0 && s.getCurrentContent() <= m_y) {
    m_states.push_back(s);
  }
}
