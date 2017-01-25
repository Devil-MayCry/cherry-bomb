//
//  main.cpp
//  cherryTest
//
//  Created by huteng on 17/1/9.
//  Copyright © 2017年 huteng. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include "include/drafter/drafter.h"
#include "include/jsoncpp/json-forwards.h"
#include "include/jsoncpp/json.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    const char* blueprint ="# Group Land Weather\n"
    "地块气象实时数据、预测数据、历史数据相关接口，请注意，所以的接口时间默认为 UTM+8 时区\n"
    "## 地块实时天气 [/weather/realtime_land_weather{?land_id,basic_temperature}]\n";
    drafter_parse_options parseOptions = {false};
    drafter_serialize_options options;
    options.sourcemap = false;
    options.format = DRAFTER_SERIALIZE_JSON;
    
    char* res = 0;
    
    drafter_parse_blueprint_to(blueprint, &res, parseOptions, options);
    Json::Value value;
    Json::Reader reader;
    reader.parse(res,value);
    std::cout<< value;
    std::string GroupNameString =  value["content"][0]["content"][0]["meta"]["title"].asString();
    const char *GroupName = GroupNameString.c_str();
    char letter[100];
    strcpy(letter,GroupName);

    const char *d = " ";
    char *p;
    p = strtok(letter,d);
    std::string result;
    while(p)
    {
        result = result + std::string(p);
        p=strtok(NULL,d);
    }
    const char * resultInFile;
    resultInFile = result.c_str();
    char  result2[222];
     strcpy(result2, resultInFile);
    result2[0] = tolower(result2[0]);
    std::cout<<result2;
    std::string controllerFileName = "/tmp/"+std::string(result2)+"Controller.ts";
    std::string serviceFileName = "/tmp/"+std::string(result2)+"Service.ts";
    std::string repositoryFileName = "/tmp/"+std::string(result2)+"Repository.ts";
    std::ofstream out(controllerFileName);
    std::ofstream out2(serviceFileName);
    std::ofstream out3(repositoryFileName);
//    if (out.is_open())
//    {
//        out << "This is a line.\n";
//        out << "This is another line.\n";
//        out.close();
//    }
//    return 0;
}
