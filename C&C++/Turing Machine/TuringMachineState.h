

#ifndef TURING_MACHINE_STATE_H
#define TURING_MACHINE_STATE_H

#include <string>

class TuringMachineState {
public:
  explicit TuringMachineState(int currentState = 0, int currentContent = 0,
                              int nextState = 0, int nextContent = 0,
                              std::string moveDirection = "");

  int getCurrentState() const;

  int getCurrentContent() const;

  int getNextState() const;

  int getNextContent() const;

  std::string getMoveDirection() const;
  friend std::ostream &operator<<(std::ostream &os,
                                  const TuringMachineState &state);
  friend std::istream &operator>>(std::istream &is, TuringMachineState &state);
  bool operator>(const TuringMachineState &other) const;
  bool operator<(const TuringMachineState &other) const;
  bool operator==(const TuringMachineState &other) const;

private:
  int m_currentState;
  int m_currentContent;
  int m_nextState;
  int m_nextContent;
  std::string m_moveDirection;
};

#endif // MACHINE_TURINGMACHINESTATE_H
