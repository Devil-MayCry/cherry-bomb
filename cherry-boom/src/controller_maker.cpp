//
//  controller_maker.cpp
//  cherry-bomb
//
//  Created by huteng on 17/2/16.
//  Copyright © 2017年 huteng. All rights reserved.
//

#include "controller_maker.hpp"

std::string ControllerMaker::MakeGetActionMethodCode(std::string methodName, Json::Value parameter_json) {
    std:: string file_input = haze::FileSystem::readFile("/Users/huteng/api-cherry/cherry-boom/cherry-boom/template/templatecontrollermethod.ts");
    std::string result ="";
    result = BaseUtil::WordReplace(file_input, "method_name", methodName);
    if( parameter_json.size() != 0) {
        std::string parameters_validator = haze::FileSystem::readFile("/Users/huteng/api-cherry/cherry-boom/cherry-boom/template/template_controller_method_parameter_validator.ts");
        std::string parameter_validator_templete =  haze::FileSystem::readFile("/Users/huteng/api-cherry/cherry-boom/cherry-boom/template/template_controller_method_parameter_validator_item.ts");
        Json::Value::Members mem = parameter_json.getMemberNames();
        std::string parameter_validator_items = "";
        for(auto iter = mem.begin(); iter != mem.end(); iter++) {
            std::string parameter_validator_temp = BaseUtil::WordReplace(parameter_validator_templete, "parameter_name", *iter);
            std::string to_parameter_type_valitor;
            if(parameter_json[*iter] == "number") {
                to_parameter_type_valitor = "toNumber";
            }else if(parameter_json[*iter] == "string") {
                to_parameter_type_valitor = "toStr";
            }else {
                to_parameter_type_valitor = "toNaN";
            }
            parameter_validator_temp = BaseUtil::WordReplace(parameter_validator_temp, "parameter_type", parameter_json[*iter].asString());
            
            parameter_validator_temp = BaseUtil::WordReplace(parameter_validator_temp, "to_parameter_type", to_parameter_type_valitor);
            parameter_validator_items += parameter_validator_temp;
            parameter_validator_items += "\n";
        }
        std::string method_validator_content = BaseUtil::WordReplace(parameters_validator, "method_parameters_items", parameter_validator_items);
        result = BaseUtil::WordReplace(result, "method_parameters_validator", method_validator_content);
        
    } else {
        result = BaseUtil::WordReplace(result, "method_parameters_validator", "");
    }
    return result;
}

std::string ControllerMaker::MakePostActionMethodCode(std::string methodName) {
    std:: string file_input = haze::FileSystem::readFile("/Users/huteng/api-cherry/cherry-boom/cherry-boom/template/templatecontrollermethod.ts");
    std::string result ="";
    result = BaseUtil::WordReplace(file_input, "method_name", methodName);
    result = BaseUtil::WordReplace(result, "method_parameters_validator", "");
    return result;
}

std::string ControllerMaker::ControllerMethodsMaker(Json::Value method_json) {
    // get templete controller method, replace the tag as "${some_tag}" to create own code
    
    std::string methodName = ControllerMaker::GetMethodName(method_json);
    const char * action_type = method_json["content"][0]["content"][1]["content"][0]["attributes"]["method"].asString().c_str();
    std::string result = "";
    if(strcmp(action_type,"GET") == 0){
        Json::Value parameter_json = ControllerMaker::GetMethodParameters(method_json);
        result = ControllerMaker::MakeGetActionMethodCode( methodName, parameter_json);
    }else if(strcmp(action_type,"POST") == 0){
        result = ControllerMaker::MakePostActionMethodCode(methodName);
    }
    return result;
}

void ControllerMaker::ControllerFileMaker(std::string groupName, std::string methods_code) {
    
    std::string file_group_name=groupName;
    std::string method_group_name=groupName;
    transform(groupName.begin(), groupName.end(), file_group_name.begin(), tolower);
    transform(groupName.begin(), groupName.begin()+1, method_group_name.begin(), toupper);
    std::string controllerFileName = "/tmp/"+ file_group_name +"controller.ts";
    std::ofstream out(controllerFileName);
    std:: string file_input = haze::FileSystem::readFile("/Users/huteng/api-cherry/cherry-boom/cherry-boom/template/templatecontroller.ts");
    
    std::string result ="";
    result = BaseUtil::WordReplace(file_input, "group_name",method_group_name);
    result = BaseUtil::WordReplace(result, "methods",methods_code);
    if (out.is_open())
    {
        out << result;
        out.close();
    }
}

std::string ControllerMaker::GetGroupName( Json::Value json_value){
    const char * group_name = json_value["meta"]["title"].asString().c_str();
    char letter[100];
    strcpy(letter,group_name);
    const char *d = " ";
    char *p;
    p = strtok(letter,d);
    std::string res;
    int counter = 0;
    while(p)
    {
        //        if(counter == 0){
        //            p[0] = tolower(p[0]);
        //        }
        res = res + std::string(p);
        p=strtok(NULL,d);
        counter++;
    }
    return std::string(res);
}

std::string ControllerMaker::GetMethodName(Json::Value json_value) {
    // get href , from frontest to "{"
    const char * href = json_value["attributes"]["href"].asString().c_str();
    const char * action_type = json_value["content"][0]["content"][1]["content"][0]["attributes"]["method"].asString().c_str();
    std::string method_action_type = "";
    std::cout<<action_type;
    if(strcmp(action_type,"GET") == 0){
        method_action_type = "get";
    }else if(strcmp(action_type,"PUT") == 0){
        method_action_type = "edit";
    }else if(strcmp(action_type,"POST") == 0){
        method_action_type = "add";
    }
    char *route;
    const char *div = "{";
    char route_array[100];
    strcpy(route_array,href);
    route = strtok(route_array, div);
    
    // get the last of directory as method name
    char* mehtod_name_underscore;
    const char *div_2 = "/";
    char mehtod_name_underscore_array[100];
    strcpy(mehtod_name_underscore_array,route);
    char *pointer;
    pointer = strtok(mehtod_name_underscore_array,div_2);
    
    while(pointer)
    {
        mehtod_name_underscore = pointer;
        pointer=strtok(NULL,div_2);
    }
    
    // change underscores to carmel case
    char mehtod_name_array[100];
    strcpy(mehtod_name_array,mehtod_name_underscore);
    
    const char *div_3 = "_";
    char *pointer_2;
    pointer_2 = strtok(mehtod_name_array,div_3);
    std::string res;
    char each_word_array[100];
    while(pointer_2)
    {
        strcpy(each_word_array, pointer_2);
        each_word_array[0] = toupper(each_word_array[0]);
        res = res + std::string(each_word_array);
        pointer_2=strtok(NULL,div_3);
    }
    res = method_action_type + res;
    
    return res ;
}

Json::Value ControllerMaker::GetMethodParameters(Json::Value json_value) {
    Json::Value method_parameter_json = json_value["content"][0]["attributes"]["hrefVariables"]["content"];
    Json::Value parameter_type_json;
    
    for(int index = 0; index < method_parameter_json.size(); index ++) {
        std::string parameter_name = method_parameter_json[index]["content"]["key"]["content"].asString();
        std::string parameter_type = method_parameter_json[index]["content"]["value"]["element"].asString();
        parameter_type_json[parameter_name] = parameter_type;
    }
    return parameter_type_json;
}

