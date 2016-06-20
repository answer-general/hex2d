/**
 * \file FileHelper.hpp
 */
#ifndef FILE_HELPER_HPP
#define FILE_HELPER_HPP

#include <string>
#include <vector>
/*!
 * \struct DirEntry
 * Object in the directory.
 */
struct DirEntry {
  /*!
   * \var std::string name
   * Name of the object
   * \public \memberof DirEntry
   */
  std::string name;
  /*!
   * \var bool isDir
   * Type of the object: file or directory.
   * \public \memberof DirEntry
   */
  bool isDir;
};
/*!
 * \fn std::vector<DirEntry> listFiles(const std::string& dirPath)
 * Returns all files from directory, signing every object: file as a file, subdirectory as a directory.
 * @param[in] dirPath Directory path.
 */
std::vector<DirEntry> listFiles(const std::string& dirPath);

#endif
