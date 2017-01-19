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
int main(int argc, const char * argv[]) {
    
    const char* blueprint ="# Group Land Weather"
    "地块气象实时数据、预测数据、历史数据相关接口，请注意，所以的接口时间默认为 UTM+8 时区"
    "## 地块实时天气 [/weather/realtime_land_weather{?land_id,basic_temperature}]";
    //    drafter_parse_options option={false};
    //    drafter_result * result = NULL;
    //     drafter_check_blueprint(blueprint, &result, option);
    //        // Serialize the result to print the warnings/errors
    //        drafter_serialize_options options;
    //        options.sourcemap = false;
    //        options.format = DRAFTER_SERIALIZE_YAML;
    //      char* out = drafter_serialize(result, options);
    //        printf("The blueprint produces warnings or errors:\n\n%s\n", out);
    //        free(out);
    //
    //        drafter_free_result(result);
    drafter_parse_options parseOptions = {false};
    drafter_serialize_options options;
    options.sourcemap = false;
    options.format = DRAFTER_SERIALIZE_JSON;
    
    char* res = 0;
    
    drafter_parse_blueprint_to(blueprint, &res, parseOptions, options);
    Json::Value value;
    Json::Reader reader;
    reader.parse(res,value);
    std::cout<<value["content"][0];
    // std::cout<<(value.get("content", "null"));
}
