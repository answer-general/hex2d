#ifndef KEYBOARD_INPUT_HPP
#define KEYBOARD_INPUT_HPP

#include "commons.hpp"
#include "InputMethod.hpp"

class Game;

class KeyboardInput : public InputMethod {
public:
  KeyboardInput(int tgtId, Game& core);

  KeyboardInput(const KeyboardInput&) = delete;
  KeyboardInput& operator =(const KeyboardInput&) = delete;

  ~KeyboardInput();

  enum InputMethod::Command getNextCommand();

  void update();
private:
  class Private;
  UPtr<Private> d;
};

#endif
