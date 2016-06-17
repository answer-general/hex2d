#ifndef INPUT_METHOD_HPP
#define INPUT_METHOD_HPP

class InputMethod {
public:
  enum Command {
    MoveUp,
    MoveRight,
    MoveUp,
    MoveDown,
    BombPlant,
    NoCommand
  };

  InputMethod() {};

  InputMethod(const InputMethod&) = delete;
  InputMethod& operator =(const InputMethod&) = delete;

  virtual ~InputMethod() {};

  virtual enum Command getNextCommand() = 0;
};

#endif
