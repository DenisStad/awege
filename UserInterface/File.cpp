//
//  File.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 24/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "File.hpp"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#ifdef _MSC_VER
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# pragma warning (disable : 4996)
#else
# include <dirent.h>
# include <libgen.h>
# include <sys/stat.h>
# include <stddef.h>
#endif

File::File(const std::string & filename)
:
filename(filename)
{
  isValid = false;
  
  struct stat s;
  if (stat(filename.c_str(), &s) == 0) {
    if (s.st_mode & S_IFDIR) {
      isValid = true;
      isDir = true;
    } else if (s.st_mode & S_IFREG) {
      isValid = true;
      isDir = false;
    }
  }
  
}

std::vector<File> File::listItems()
{
  if (!isValid || !isDir) {
    return std::vector<File>();
  }
  
  std::vector<File> files;
  
  auto dir = opendir(filename.c_str());
  if (dir != nullptr) {
    struct dirent *direntity;
    while ((direntity = readdir(dir)) != nullptr) {
      if (std::string(direntity->d_name) == "." || std::string(direntity->d_name) == "..") {
        continue;
      }
      auto file = File(filename + "/" + direntity->d_name);
      files.push_back(file);
    }
    closedir(dir);
  }
  
  return files;
}

File::operator std::string () const
{
  return filename;
}