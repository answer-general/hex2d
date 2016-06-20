/*!
 * \file InputMethod.hpp
 */
#ifndef INPUT_METHOD_HPP
#define INPUT_METHOD_HPP

#include "GameObject.hpp"
/*!
 * \class InputMethods
 * Responsible for input methods.
 */
class InputMethod {
public:
  /*!
   * \enum Command
   * Main commands: movement, planting bombs.
   * \public \memberof InputMethod
   */
  enum Command {
    MoveUp, /*!< Move up */
    MoveRight, /*!< MoveRight */
    MoveDown, /*!< Move Down */
    MoveLeft, /*!< Move Left */
    BombPlant, /*!< Planting bomb */
    NoCommand /*!< No Command */
  };
  /*!
   * Base constructor.
   * \public \memberof InputMethod
   */
  InputMethod() : target(GameObject::InvalidObject) {};
  /*!
   * Prohibit copying objects
   */
  InputMethod(const InputMethod&) = delete;
  InputMethod& operator =(const InputMethod&) = delete;
  /*!
   * \fn void assign(int id)
   * Assigns target identification number.
   * \public \memberof InputMethod
   */
  void assign(int id) { target = id; };
  /*!
   * \fn int getTarget() const
   * Gets target identification number.
   * \public \memberof InputMethod
   */
  int getTarget() const { return target; };

  virtual ~InputMethod() {};
  
  /*!
   * \fn virtual enum Command getNextCommand() = 0
   * Gets next command.
   * \pure \public \memberof InputMethod
   */
  virtual enum Command getNextCommand() = 0;
  /*!
   * \fn virtual void update() = 0
   * Update internal state.
   * For player - getting new command,
   * For AI - looking for a new turn(move),
   * For network - downloading command.
   * \pure \public \memberof InputMethod
   */
  virtual void update() = 0;
protected:
  int target;
};

#endif
