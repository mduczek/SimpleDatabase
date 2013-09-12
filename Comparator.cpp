//
//  Comparator.cpp
//  QueryProcessing
//
//  Created by Michal Duczyński on 02.04.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#ifndef QueryProcessing_Comparator
#define QueryProcessing_Comparator

#include <iostream>
using namespace std;


//I thought about making it a class, but came to conclusion that it wouldn't make sense
struct compByFirst {
    bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) const{
    if (lhs.first<rhs.first) {
        return true;
    }else if(lhs.first == rhs.first && lhs.second < rhs.second){
        return true;
    }else{
        return false;
    }
    }
};

struct compBySecond {
    bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) const{
    if (lhs.second<rhs.second) {
        return true;
    }else if(lhs.second == rhs.second && lhs.first < rhs.first){
        return true;
    }else{
        return false;
    }
    }
};

#endif