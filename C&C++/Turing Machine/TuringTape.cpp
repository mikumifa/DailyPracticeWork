#include "TuringTape.h"

TuringTape::TuringTape(int n) {
  if (n > 0) {
    tape.resize(n, 0);
  } else if (n == -1) {
    infinite = true;
    tape.resize(1000, 0);
  }
  infinite = false;
  currentPos = 0;
  highestPos = 0;
}
bool TuringTape::isFine() {
  if ((currentPos >= tape.size() || currentPos < 0) && !infinite)
    return false;
  return true;
}

bool TuringTape::moveRight() {
  currentPos++;
  if ((currentPos > tape.size() || currentPos < 0) && !infinite)
    return false;
  if (currentPos > highestPos) {
    highestPos = currentPos;
  }
  if (infinite && !(currentPos < tape.size() && currentPos >= 0)) {
    tape.resize(tape.size() * 2 + 1, 0);
  }
  return true;
}

bool TuringTape::moveLeft() {
  currentPos--;
  if ((currentPos > tape.size() || currentPos < 0) && !infinite)
    return false;
  return true;
}

int TuringTape::getContent() {
  if (currentPos < 0 || currentPos >= tape.size()) {
    return 0;
  }
  return tape[currentPos];
}

void TuringTape::setContent(int c) {
  if (currentPos < 0 || currentPos >= tape.size()) {
    return;
  }
  tape[currentPos] = c;
}

int TuringTape::getPosition() const { return currentPos; }

std::ostream &operator<<(std::ostream &out, const TuringTape &T) {
  for (int i = 0; i <= T.highestPos; i++) {
    out << T.tape[i];
  }
  return out;
}
