/*!
 * \file Game.hpp
 */
#ifndef GAME_HPP
#define GAME_HPP

#include "commons.hpp"

class Config;
class Engine;
class InputMethod;
class Level;
class ObjectContainer;
class UI;
/*!
 * \class Game
 * Responsible for the game process.
 * Provide the components an access to each other.
 * Update game's state.
 */
class Game {
public:
  /*!
   * Base constructor
   * \public \memberof Game
   */
  Game();
  /*!
   * Prohibit copying objects
   */
  Game(const Game&) = delete;
  Game& operator =(const Game&) = delete;

  ~Game();
  /*!
   * \fn void run()
   * Runs the game. Updates game's state.
   * \public \memberof Game
   */
  void run();

  /*!
   * \fn bool isRunning() const
   * Returns game's state.
   * \public \memberof Game
   */
  bool isRunning() const;
  /*!
   * \fn void quit()
   * Finishes the game.
   * \public \memberof Game
   */
  void quit();

  // Component access
  /*!
   * \fn SPtr<Config> getConfig()
   * Returns game's config.
   * \public \memberof Game
   */
  SPtr<Config> getConfig();
  /*!
   * \fn const SPtr<Config> getConfig() const
   * Returns game's config.
   * \public \memberof Game
   */
  const SPtr<Config> getConfig() const;

  /*!
   * \fn SPtr<Engine> getEngine()
   * Returns engine.
   * \public \memberof Game
   */
  SPtr<Engine> getEngine();
  /*!
   * \fn const SPtr<Engine> getEngine() const
   * Returns engine.
   * \public \memberof Game
   */
  const SPtr<Engine> getEngine() const;

  /*!
   * \fn SPtr<Level> getLevel()
   * Returns loaded level.
   * \public \memberof Game
   */
  SPtr<Level> getLevel();
  /*!
   * \fn const SPtr<Level> getLevel() const
   * Returns loaded level.
   * \public \memberof Game
   */
  const SPtr<Level> getLevel() const;

  /*!
   * \fn SPtr<ObjectContainer> getObjects()
   * Returns game objects.
   * \public \memberof Game
   */
  SPtr<ObjectContainer> getObjects();
  /*!
   * \fn const SPtr<ObjectContainer> getObjects() const
   * Returns game objects.
   * \public \memberof Game
   */
  const SPtr<ObjectContainer> getObjects() const;
  
  /*!
   * \fn SPtr<UI> getUI()
   * Returns game UI.
   * \public \memberof Game
   */
  SPtr<UI> getUI();
  /*!
   * \fn const SPtr<UI> getUI() const
   * Returns game UI.
   * \public \memberof Game
   */
  const SPtr<UI> getUI() const;
  
  /*!
   * \fn SPtr<InputMethod> newKbdInput()
   * Adds & returns new keyboard input. 
   * \public \memberof Game
   */
  SPtr<InputMethod> newKbdInput();

  // Player character
  /*!
   * \fn int getPCId() const
   * Returns player's identification number.
   * \public \memberof Game
   */
  int getPCId() const;
  /*!
   * \fn void setPC(int)
   * Sets player's identification number.
   * \public \memberof Game
   */
  void setPC(int);
private:
  class Private;
  UPtr<Private> d;
};

#endif
