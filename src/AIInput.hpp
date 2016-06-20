/*!
 * \file AIInput.hpp
 */
#ifndef AI_INPUT_HPP
#define AI_INPUT_HPP

#include "commons.hpp"
#include "InputMethod.hpp"

class Game;
/*!
 * \class AIInput
 * Responsible for AI input method.
 */
class AIInput : public InputMethod {
public:
  /*!
   * Constructor.
   * @param[in]  core Reference to the game core
   * \public \memberof AIInput
   */
  AIInput(Game& core);
  /*!
   * Prohibit copying objects
   */
  AIInput(const AIInput&) = delete;
  AIInput& operator =(const AIInput&) = delete;

  ~AIInput();
  /*!
   * \fn enum Command getNextCommand()
   * Gets next command.
   * \public \memberof AIInput
   */
  enum Command getNextCommand();
  /*!
   * \fn void update()
   * Update internal state.
   * \public \memberof AIInput
   */
  void update();

  /*!
   * \fn int sightRadius() const
   * Returns AI's sight radius.
   * \public \memberof AIInput
   */
  int sightRadius() const;
  /*!
   * \fn void setSightRadius(int r)
   * Set AI's sight radius.
   * @param[in] r AI's sight radius.
   * \public \memberof AIInput
   */
  void setSightRadius(int);
private:
  class Private;
  UPtr<Private> d;
};

#endif
