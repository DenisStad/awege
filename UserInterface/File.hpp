//
//  File.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 24/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef File_hpp
#define File_hpp

#include <vector>
#include <string>

class File {
  
public:
  
  File(const std::string & filename);
  operator std::string() const;
  
  std::vector<File> listItems();
  
  void open();
  void close();
  std::string read();
  
private:
  
  std::string filename;
  bool isValid;
  bool isDir;
  
};

#endif /* File_hpp */
