#include "TuringMachineState.h"
#include <iostream>
#include <utility>

TuringMachineState::TuringMachineState(int currentState, int currentContent,
                                       int nextState, int nextContent,
                                       std::string moveDirection)
    : m_currentState(currentState), m_currentContent(currentContent),
      m_nextState(nextState), m_nextContent(nextContent),
      m_moveDirection(std::move(moveDirection)) {}

int TuringMachineState::getCurrentState() const { return m_currentState; }

int TuringMachineState::getCurrentContent() const { return m_currentContent; }

int TuringMachineState::getNextState() const { return m_nextState; }

int TuringMachineState::getNextContent() const { return m_nextContent; }

std::string TuringMachineState::getMoveDirection() const {
  return m_moveDirection;
}
// print the state
std::ostream &operator<<(std::ostream &os, const TuringMachineState &state) {
  os << state.m_currentState << " ";
  os << state.m_currentContent << " ";
  os << state.m_nextState << " ";
  os << state.m_nextContent << " ";
  os << state.m_moveDirection;
  return os;
}
// cin the state
std::istream &operator>>(std::istream &is, TuringMachineState &state) {
  is >> state.m_currentState;
  is >> state.m_currentContent;
  is >> state.m_nextState;
  is >> state.m_nextContent;
  is >> state.m_moveDirection;
  return is;
}
// compare
bool TuringMachineState::operator<(const TuringMachineState &other) const {
  if (m_currentState < other.m_currentState) {
    return true;
  } else {
    return (m_currentState == other.m_currentState) &&
           (m_currentContent < other.m_currentContent);
  }
}
bool TuringMachineState::operator>(const TuringMachineState &other) const {
  if (m_currentState > other.m_currentState) {
    return true;
  } else {
    return (m_currentState == other.m_currentState) &&
           (m_currentContent > other.m_currentContent);
  }
}

bool TuringMachineState::operator==(const TuringMachineState &other) const {
  if (m_currentState == other.m_currentState) {
    return m_currentContent == other.m_currentContent;
  } else {
    return false;
  }
}
