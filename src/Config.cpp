#include <string>
#include "Config.hpp"

class Config::Private {
public:
  std::string resDir;
};


Config::Config() : d(new Private()) {
  char* home = getenv("HOME"); // Don't need to free -- system-allocated.
  d->resDir = home;
  d->resDir += "/.config/HexedMan";
}

Config::~Config() {}

std::string Config::getLevelsPath() const {
  return d->resDir + "/levels";
}
