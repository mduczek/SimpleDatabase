//
//  Literal.h
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#ifndef QueryProcessing_Literal_h
#define QueryProcessing_Literal_h

class Literal {
    
public:
    Literal();
    bool related;
    int relation;
    int first; //if it's negative then its absolute value it's the number of var
    int second; //same here
};

#endif
