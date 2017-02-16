//
//  controller_maker.hpp
//  cherry-bomb
//
//  Created by huteng on 17/2/16.
//  Copyright © 2017年 huteng. All rights reserved.
//

#ifndef controller_maker_hpp
#define controller_maker_hpp

#include <stdio.h>
#include <iostream>
#include "drafter.h"
#include "json-forwards.h"
#include "json.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <regex>
#include "file_system.h"
#include <cctype>
#include<vector>
#endif /* controller_maker_hpp */


class ControllerMaker {

public:
    static std::string ControllerMethodsMaker(std::string methodName);
    
    static void ControllerFileMaker(std::string groupName, std::string methods_code);
    
    static std::string GetGroupName( Json::Value json_value);
    
    static std::string GetMethodName(Json::Value json_value);
    
    static Json::Value GetMethodParameters(Json::Value json_value);

};
