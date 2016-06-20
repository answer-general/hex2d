/*!
 * \file UI.hpp
 */
#ifndef UI_HPP
#define UI_HPP

#include "commons.hpp"

class Game;
/*!
 * \class UI
 * User interface class
 */
class UI {
public:
  /*!
   * \enum ScreenType
   * Defines screen type.
   * \public \memberof UI
   */
  enum ScreenType {
    MainMenuScreen, /*!< Main Menu Screen */
    LevelSelSingle, /*!< Level Selection (Single-play) */
    GameSingle,     /*!< Single Game */
    ScreensCount,   /*!< Screens count */
    NoScreen        /*!< Signals shutdown */
  };
  /*!
   * Base constructor
   * @param[in] core Reference to the game core.
   * \public \memberof UI
   */
  UI(Game&);
  /*!
   * Prohibit copying objects
   */
  UI(const UI&) = delete;
  UI& operator =(const UI&) = delete;

  ~UI();
  /*!
   * \fn void update()
   * Update screen.
   * \public \memberof UI
   */
  void update();
  /*!
   * \fn void switchScreen(enum ScreenType targetType)
   * Change screen type to targetType.
   * @param[in] targetType The screen, which we want to switch to. 
   * \public \memberof UI
   */
  void switchScreen(enum ScreenType);
private:
  class Private;
  UPtr<Private> d;
};

#endif
