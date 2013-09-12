//
//  Dictionary.cpp
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#include <iostream>
#include "Dictionary.h"
#include <algorithm>

int Dictionary::getIndex(string str){
    for (int i=0; i< content.size(); i++)
        if (str.compare(content[i])==0) {
            return i;
        }
    return -1;
}

void Dictionary::print(){
    vector<string> sorted (content);
    sort(sorted.begin(), sorted.end());
    for (int i=0; i< sorted.size(); i++)
        cout << sorted[i] << "\n";
}

void Dictionary::add(string str){
    if (getIndex(str)==-1) {
        content.push_back(str);
    }
}

string Dictionary::atIndex(int index){
    return content.at(index);
}
long Dictionary::getSize(){
    return content.size();
}