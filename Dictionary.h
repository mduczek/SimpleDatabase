//
//  Dictionary.h
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#ifndef QueryProcessing_Dictionary_h
#define QueryProcessing_Dictionary_h

#include <vector>

using namespace std;

class Dictionary {
    vector<string> content;
    
public:
    int getIndex(string str);
    void print();
    void add(string str);
    string atIndex(int index);
    long getSize();
};

#endif
