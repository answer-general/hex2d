#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "commons.hpp"
#include "InputMethod.hpp"
#include <string>

class Config {
public:
  Config();

  Config(const Config&) = delete;
  Config& operator =(const Config&) = delete;

  ~Config();

  std::string getLevelsPath() const;

  enum InputMethod::Command getKbdCommand(int playerId, int key);
private:
  class Private;
  UPtr<Private> d;
};

#endif
