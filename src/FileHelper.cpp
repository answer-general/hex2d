#include <dirent.h>
#include <sys/types.h>
#include "FileHelper.hpp"

std::vector<struct DirEntry> listFiles(const std::string& dirPath) {
  std::vector<DirEntry> res;

  DIR* dir = opendir(dirPath.c_str());
  if (!dir)
    return res;

  dirent* ent = NULL;
  while ((ent = readdir(dir)) != NULL) {
    DirEntry t;
    t.name = ent->d_name;
    if (ent->d_type == DT_DIR)
      t.isDir = true;
    else
      t.isDir = false;

    res.push_back(t);
  }

  closedir(dir);

  return res;
}
