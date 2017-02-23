//
//  main.cpp
//  cherryBoom
//
//  Created by huteng on 17/1/9.
//  Copyright © 2017年 huteng. All rights reserved.
//
#include <stdio.h>
#include "controller_maker.hpp"
//
//
//void ServiceMaker(std::string groupName) {
//    std::string serviceFileName = "/tmp/"+ groupName +"service.ts";
//    std::ofstream out(serviceFileName);
//}
//
//void RepositoryMaker(std::string groupName) {
//    std::string repositoryFileName = "/tmp/"+ groupName +"repository.ts";
//    std::ofstream out(repositoryFileName);
//}
//

/*
   use drafter library to parse api-blueprint file to json
   use JsonCpp library to make json readable and could be use
 */
Json::Value ConvertBluePrintToJson(const char* blue_print) {
    drafter_parse_options parse_options = {false};
    drafter_serialize_options options;
    options.sourcemap = false;
    options.format = DRAFTER_SERIALIZE_JSON;
    
    char* res = 0;
    drafter_parse_blueprint_to(blue_print, &res, parse_options, options);
    Json::Value value;
    Json::Reader reader;
    reader.parse(res,value);
    return value;
}

/*
   By reading the json, get the groups name for controller file name, and class name
                        get the href last word and action type for method name
                        get the paremeters for validator
   All controller function are in ControllerMaker Class
 */
void createControllerFile(Json::Value json) {
    for(int index_of_group = 0; index_of_group < json["content"][0]["content"].size(); index_of_group ++)
    {
        Json::Value each_group_json = json["content"][0]["content"][index_of_group];
        
        std::string group_name =  ControllerMaker::GetGroupName(each_group_json);
        
        std::string controller_methods_code = "";
        for (int index_of_method = 1; index_of_method < each_group_json["content"].size(); index_of_method ++)
        {
            Json::Value each_method_in_group_json = each_group_json["content"][index_of_method];
            std::string method_code = ControllerMaker::ControllerMethodsMaker(each_method_in_group_json);
            controller_methods_code.append(method_code+"\n");
        }
        
        ControllerMaker::ControllerFileMaker(group_name, controller_methods_code);
    }
}

int main(int argc, const char * argv[]) {
    mdp::ByteBuffer blueprint = haze::FileSystem::readFile("/Users/huteng/api-cherry/cherry-boom/cherry-boom/test_data/test.apib");
    Json::Value value = ConvertBluePrintToJson(blueprint.c_str());
    createControllerFile(value);
 

//  
//    
//    ServiceMaker(result2);
//    RepositoryMaker(result2);
}
