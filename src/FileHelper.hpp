#ifndef FILE_HELPER_HPP
#define FILE_HELPER_HPP

#include <string>
#include <vector>

struct DirEntry {
  std::string name;
  bool isDir;
};

std::vector<DirEntry> listFiles(const std::string& dirPath);

#endif
