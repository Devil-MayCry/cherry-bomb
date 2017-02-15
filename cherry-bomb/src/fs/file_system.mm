//
//  fs.cpp
//  api-tips
//
//  Created by Frank Lin on 27/12/2016.
//  Copyright © 2016 Frank Lin. All rights reserved.
//

#include "file_system.h"

#import <Foundation/Foundation.h>

NS_HAZE_BEGIN

////////////////////////////////////////////////////////////////////////////////
// FileSystem, public:

mdp::ByteBuffer FileSystem::readFile(const std::string& path) {
  NSString *objc_file_path = [NSString stringWithUTF8String:path.c_str()];
  NSError *error;
  NSString *objc_file_contents = [NSString stringWithContentsOfFile:objc_file_path
                                                           encoding:NSUTF8StringEncoding
                                                              error:&error];
  
  if (error) {
    NSLog(@"Error reading file: %@", error.localizedDescription);
  }
  
  std::string file_contents = [objc_file_contents UTF8String];
  return file_contents;
}

bool FileSystem::writeToFile(const std::string& content, const std::string& path) {
  BOOL success = [[NSFileManager defaultManager] createFileAtPath:[NSString stringWithUTF8String:path.c_str()]
                                                         contents:[[NSString stringWithUTF8String:content.c_str()]
                                                                   dataUsingEncoding:NSUTF8StringEncoding]
                                                       attributes:nil];
  return static_cast<bool>(success);
}

NS_HAZE_END
