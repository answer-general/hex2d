#ifndef INPUT_METHOD_HPP
#define INPUT_METHOD_HPP

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

  InputMethod(int id) : target(id) {};

  InputMethod(const InputMethod&) = delete;
  InputMethod& operator =(const InputMethod&) = delete;

  virtual ~InputMethod() {};

  virtual enum Command getNextCommand() = 0;

  virtual void update() = 0;
protected:
  int target;
};

#endif
