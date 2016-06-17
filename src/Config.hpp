#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "commons.hpp"
#include <string>

class Config {
public:
  Config();

  Config(const Config&) = delete;
  Config& operator =(const Config&) = delete;

  ~Config();

  std::string getLevelsPath() const;
private:
  class Private;
  UPtr<Private> d;
};

#endif
