#ifndef TURINGTAPE_H_
#define TURINGTAPE_H_

#include <iostream>
#include <vector>

class TuringTape {
public:
  explicit TuringTape(int n);

  bool moveRight();
  bool isFine();
  bool moveLeft();

  int getContent();

  void setContent(int c);

  int getPosition() const;

  friend std::ostream &operator<<(std::ostream &out, const TuringTape &s);

private:
  bool infinite;
  std::vector<int> tape;
  int currentPos;
  int highestPos;
};

#endif /* TURINGTAPE_H_ */
