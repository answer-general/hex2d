/**
 * \file Engine.hpp
 */
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "commons.hpp"
#include <string>

class Game;
/*!
 * \class Engine
 * Engine of the game.
 */
class Engine {
public:
  /*!
   * \enum Mode
   * Game mode: single-play, hot seat, multi-play.  
   * \public \memberof Engine
   */
  enum Mode {
    ModeSingle,   /*!< single-play */
    ModeHotseat,  /*!< hot seat */
    ModeMulti     /*!< multi-player */
  };
  /*!
   * Base constructor
   * @param[in]  core Reference to the game core.
   * \public \memberof Engine
   */
  Engine(Game& core);
  /*!
   * Prohibit copying objects
   */
  Engine(const Engine&) = delete;
  Engine& operator =(const Engine&) = delete;

  ~Engine();

  bool isRunning() const;
  /*!
   * \fn void run()
   * \brief Start the game
   * \public \memberof Engine
   * Start the game. Choose the game mode.
   */
  void run();
  /*!
   * \fn void stop()
   * \public \memberof Engine
   * Finishes the game.
   */
  void stop();
  /*!
   * \fn void update()
   * Update the game's state.
   * \public \memberof Engine
   */
  void update();

  // Settings for simulation.
  /*!
   * \fn enum Mode getMode() const
   * Returns game's mode. Setting for simulation.
   * \public \memberof Engine
   */
  enum Mode getMode() const;
  /*!
   * \fn void setMode(enum Mode);
   * Set game's mode. Setting for simulation.
   * \public \memberof Engine
   */
  void setMode(enum Mode);
  /*!
   * \fn const std::string& levelName() const
   * Returns level's name
   * \public \memberof Engine
   */
  const std::string& levelName() const;
  /*!
   * \fn void setLevelName(const std::string& name)
   * Set level's name
   * @param[in] name Level's name
   * \public \memberof Engine
   */
  void setLevelName(const std::string&);

  // Gameplay methods.
  /*!
   * \fn bool explode(Point start, Point end)
   * @param[in] start The point, from which everything in the line is exploded.
   * @param[in] end The last point, which explodes.
   * \public \memberof Engine
   * Explode everything in the line from start to end or
   * until the first non-explodable cell. If start and
   * end are not on horizontal or vertical line -- fails.
   */
  bool explode(Point start, Point end);
private:
  class Private;
  UPtr<Private> d;
};

#endif
