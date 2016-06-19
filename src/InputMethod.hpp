#ifndef INPUT_METHOD_HPP
#define INPUT_METHOD_HPP

#include "GameObject.hpp"

class InputMethod {
public:
  enum Command {
    MoveUp,
    MoveRight,
    MoveDown,
    MoveLeft,
    BombPlant,
    NoCommand
  };

  InputMethod() : target(GameObject::InvalidObject) {};

  InputMethod(const InputMethod&) = delete;
  InputMethod& operator =(const InputMethod&) = delete;

  void assign(int id) { target = id; };
  int getTarget() const { return target; };

  virtual ~InputMethod() {};

  virtual enum Command getNextCommand() = 0;

  virtual void update() = 0;
protected:
  int target;
};

#endif
