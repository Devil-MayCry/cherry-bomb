//
//  base_util.cpp
//  cherry-bomb
//
//  Created by huteng on 17/2/17.
//  Copyright © 2017年 huteng. All rights reserved.
//

#include "base_util.hpp"

std::string BaseUtil::WordReplace(std::string origin_string, std::string is_replaced_word, std::string repalcing_word){
    
    std::string regex_templete = "[\$][\{]"+is_replaced_word+"[\}]";
    
    std::regex regex (regex_templete);
    
    std::string new_string = "";
    
    new_string = std::regex_replace(origin_string, regex, repalcing_word);
    
    return new_string;
}
