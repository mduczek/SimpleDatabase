//
//  Query.h
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#ifndef QueryProcessing_Query_h
#define QueryProcessing_Query_h
#include <vector>
#include "Literal.h"
#include "Dictionary.h"
#include "Dataset.h"

class Query {
     //vector of andClause-> vector of orClause->Clause
    vector<vector<Literal> > andClauses;
    Dataset* database;
    int readTermOrVar(bool& correct);
    void check(int currentAndClause, vector<int> var);
    vector<string> results;
    
public:
    Query(Dataset* _data);
    void read();
    static const int MAX_VARS = 16;
};

#endif
