#ifndef AI_INPUT_HPP
#define AI_INPUT_HPP

#include "commons.hpp"
#include "InputMethod.hpp"

class Game;

class AIInput : public InputMethod {
public:
  AIInput(Game& core);

  AIInput(const AIInput&) = delete;
  AIInput& operator =(const AIInput&) = delete;

  ~AIInput();

  enum Command getNextCommand();

  void update();

  int sightRadius() const;
  void setSightRadius(int);
private:
  class Private;
  UPtr<Private> d;
};

#endif
