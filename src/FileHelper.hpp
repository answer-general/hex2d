/**
 * \file FileHelper.hpp
 */
#ifndef FILE_HELPER_HPP
#define FILE_HELPER_HPP

#include <string>
#include <vector>
/*!
 * \struct DirEntry
 * 
 */
struct DirEntry {
  /*!
   * \var std::string name
   * 
   * \public \memberof DirEntry
   */
  std::string name;
  /*!
   * \var bool isDir
   * 
   * \public \memberof DirEntry
   */
  bool isDir;
};
/*!
 * \var std::vector<DirEntry> listFiles(const std::string& dirPath)
 * 
 */
std::vector<DirEntry> listFiles(const std::string& dirPath);

#endif
