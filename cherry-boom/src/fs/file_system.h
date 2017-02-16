//
//  fs.hpp
//  api-tips
//
//  Created by Frank Lin on 27/12/2016.
//  Copyright © 2016 Frank Lin. All rights reserved.
//

#ifndef API_TIPS_FS_FS_H_
#define API_TIPS_FS_FS_H_

#include <stdio.h>

#include "ByteBuffer.h"

#include "macros.h"

NS_HAZE_BEGIN

/**
 File system wraps Objective-C methods.
 */
class FileSystem {
public:
  
  /**
   Read *.apib (blueprint) file as string.

   @param path Absolute path.
   @return File content.
   */
  static mdp::ByteBuffer readFile(const std::string& path);
  
  
  /**
   Write string to file.

   @param content Content.
   @param path Absolute path.
   @return true if success.
   */
  static bool writeToFile(const std::string& content, const std::string& path);
  
private:
  DISALLOW_COPY_AND_ASSIGN(FileSystem);
};

NS_HAZE_END

#endif /* API_TIPS_FS_FS_H_ */
