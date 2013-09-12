//
//  Dataset.h
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#ifndef QueryProcessing_Dataset_h
#define QueryProcessing_Dataset_h

#include "Dictionary.h"
#include <string>
#include "Literal.h"
#include <set>
#include "Comparator.cpp"

class Dataset {
    //content[i] = set of all pairs in relation (relations[i]),
    vector<set<pair<int, int>, compByFirst > > contentSortedByFirst;
    vector<set<pair<int, int>, compBySecond > > contentSortedBySecond;
    Dictionary terms;
    Dictionary relations;

    void closureCompute(set<pair<int, int>, compByFirst >* relV);
    
public:
    Dataset();
    //change
    void addTerm(string termName);//it does nothing if the term is already present
    void addRelation(string relationName);//it does nothing if the relation is already present
    bool addTermsToRelation(string relation, string leftTerm, string rightTerm);
    void closure(string relation);
    void printClosure(string relation);
    //print
    void printAllTerms();
    void printAllRelations();
    void printRelation(string relationName);
    void printRelated(string relation, string term);
    //data access functions
    int indexOfTerm(string str);
    int indexOfRelation(string str);
    string getTerm(int index);
    string getRelation(int index);
    //returns all the pairs that match the pattern in log time + vector.size
    vector< pair<int, int> >* matching(Literal pattern); 
};

#endif
