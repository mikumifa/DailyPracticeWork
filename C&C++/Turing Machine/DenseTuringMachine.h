#ifndef DENSETURINGMACHINE_H_
#define DENSETURINGMACHINE_H_

#include "TuringMachine.h"
#include <vector>

class DenseTuringMachine : public TuringMachine {
public:
  DenseTuringMachine(int x, int y);

  TuringMachineState *find(int x, int y) override;

  void add(TuringMachineState &s) override;

  std::vector<TuringMachineState> *getAll() override;
  virtual ~DenseTuringMachine() = default;

private:
  int m_x;
  int m_y;
  std::vector<TuringMachineState> m_states;
};

#endif /* DENSETURINGMACHINE_H_ */
