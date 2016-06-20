/*!
 * \file Level.hpp
 */
#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "commons.hpp"
#include <string>

class Game;

/*!
 * \class Level
 * Class which describes game's level. 
 */
class Level {
public:
  /*!
   * Base constructor.
   * @param[in]  core Reference to the game core.
   * \public \memberof Level
   */
  Level(Game& core);
  /*!
   * Prohibit copying objects
   */
  Level(const Level&) = delete;
  Level& operator =(const Level&) = delete;

  ~Level();
  /*!
   * \fn const Point& getSize() const
   * Returns level's size
   * \public \memberof Level
   */
  const Point& getSize() const;

  /*!
   * \fn Point nextSpawn()
   * Returns new spawn point.
   * Returns Point(-1,-1) if no places left.
   * \public \memberof Level
   */
  Point nextSpawn();

  /*!
   * \fn bool destroy(const Point& pos)
   * Returns true if object was destroyed.
   * @param[in] pos The position of the destroyed object.
   * \public \memberof Level
   */
  bool destroy(const Point& pos);
  /*!
   * \fn bool canCross(const Point& pos)
   * Return true if there is no wall at the position.
   * @param[in] pos The position at the level.
   * \public \memberof Level
   */
  bool canCross(const Point& pos);

  /*!
   * \fn int print(const Point& pos)
   * Return symbol code for the points.
   * @param[in] pos The position at the level.
   * \public \memberof Level
   */
  int print(const Point& pos);
  /*!
   * \fn bool fromFile(const std::string& name)
   * Open the level from file.
   * @param[in] name The file's name with the level description.
   * \public \memberof Level
   */
  bool fromFile(const std::string& name);
private:
  class Private;
  UPtr<Private> d;
};

#endif
