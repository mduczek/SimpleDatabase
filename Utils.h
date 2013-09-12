//
//  Utils.h
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#ifndef QueryProcessing_Utils_h
#define QueryProcessing_Utils_h

using namespace std;

class Utils {
    
public:
    Utils();
    static bool compare(std::pair<int, int> p, int first, int second);
    static bool compareP(pair<string, string> i,pair <string, string> j );
};

#endif
