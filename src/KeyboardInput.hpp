/*!
 * \file KeyboardInput.hpp
 */
#ifndef KEYBOARD_INPUT_HPP
#define KEYBOARD_INPUT_HPP

#include "commons.hpp"
#include "InputMethod.hpp"

class Game;
/*!
 * \class KeyboardInput
 * Responisble for input from the keyboard.
 */
class KeyboardInput : public InputMethod {
public:
  /*!
   * Base constructor.
   * @param[in]  core Reference to the game core.
   * \public \memberof KeyboardInput
   */
  KeyboardInput(Game& core);
  /*!
   * Prohibit copying objects
   */
  KeyboardInput(const KeyboardInput&) = delete;
  KeyboardInput& operator =(const KeyboardInput&) = delete;

  ~KeyboardInput();
  /*!
   * \fn enum InputMethod::Command getNextCommand()
   * Gets next command.
   * \public \memberof KeyboardInput
   */
  enum InputMethod::Command getNextCommand();
  /*!
   * \fn void update()
   * Update internal state.
   * \public \memberof KeyboardInput
   */
  void update();
private:
  class Private;
  UPtr<Private> d;
};

#endif
