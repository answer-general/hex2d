/**
 * \file Config.hpp
 */
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "commons.hpp"
#include "InputMethod.hpp"
#include <string>
/*!
 * \class Config
 * Configure game
 */
class Config {
public:
  /*!
   * Base constructor for config.
   * \public \memberof Config
   * @param[in]  core Reference to the game core.
   */
  Config(Game& core);
  /*!
   * Prohibit copying objects
   */
  Config(const Config&) = delete;
  Config& operator =(const Config&) = delete;

  ~Config();
  /*!
   * \fn std::string getLevelsPath() const
   * \public \memberof Config
   * Looking for directory, containing game levels.
   */
  std::string getLevelsPath() const;
  /*!
   * \fn enum InputMethod::Command getKbdCommand(int playerId, int key)
   * \brief Get command from the keyboard
   * \public \memberof Config
   * @param[in] playerId Player's identification number
   * @param[in] key Key's code
   * Read information(command = key) from the keyboard. 
   * Returns action: moving or planting bomb.
   */
  enum InputMethod::Command getKbdCommand(int playerId, int key);
private:
  class Private;
  UPtr<Private> d;
};

#endif
