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
#include "drafter.h"
#include "json-forwards.h"
#include "json.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "file_system.h"
#include <cctype>
#include<vector>
#include "base_util.hpp"
#endif /* controller_maker_hpp */


class ControllerMaker {

public:
    
    /* get method name, parameters name , parameters type, make base controller method code, as string */
    
    static std::string ControllerMethodsMaker(std::string methodName, Json::Value json);
    
    /* get group name, method content code, create controller file , in /tmp directory */
    
    static void ControllerFileMaker(std::string groupName, std::string methods_code);
    
    /* read json to get group name*/
    
    static std::string GetGroupName( Json::Value json_value);
    
    /* read json to get method name*/
    
    static std::string GetMethodName(Json::Value json_value);
    
    /* read json to get parameters , return a json, key is name , value is type*/
    
    static Json::Value GetMethodParameters(Json::Value json_value);

};
