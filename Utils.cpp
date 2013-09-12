//
//  Utils.cpp
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#include <iostream>
#include "Utils.h"

Utils::Utils(){};

bool Utils::compare(std::pair<int, int> p, int first, int second){
    if ( (first <0 || first == p.first) && (second <0 || second == p.second) ) {
        return true;
    }else{
        return false;
    }
}
bool Utils::compareP (pair<string, string> i,pair <string, string> j ) { 
    return (i.first < j.first); 
}