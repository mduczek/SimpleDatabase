//
//  Query.cpp
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#include <iostream>
#include <string>
#include "InputParser.h"
#include "Utils.h"
#include "Query.h"


using namespace std;

Query::Query(Dataset* _data):database(_data){}

void Query::read(){
    bool correct = true;
    int varNumber, andClauseNumber;
    if(InputParser::readInt(varNumber) && varNumber <= MAX_VARS && InputParser::readInt(andClauseNumber)){
        andClauses.resize(andClauseNumber);
        for (int i=0; i<andClauseNumber; i++) {
            int orClauseNumber;
            if ( InputParser::readInt(orClauseNumber) ) {
                for (int j=0; j<orClauseNumber; j++) {
                    //Read Clause
                    string related = InputParser::tryToRead();
                    if (related.compare("RELATED") == 0 || related.compare("NOT_RELATED") == 0) {
                        string relation = InputParser::tryToRead();
                        int relationI = database->indexOfRelation(relation);
                        if (relationI!=-1) {
                            Literal current;
                            current.relation = relationI;
                            current.related = (related.compare("RELATED") == 0);
                            current.first = readTermOrVar(correct);
                            current.second = readTermOrVar(correct);
                            andClauses[i].push_back(current);
                        }else correct = false;
                    }else correct = false;
                }
            } else correct = false;
        }
        if (correct) {
            InputParser::status("QUERY", true);
            vector<int> var (varNumber,-1);
            check(0, var);
            sort(results.begin(), results.end());
            for (int i=0; i<results.size(); i++) {
                cout << results[i] << "\n";
            }
        }else InputParser::status("QUERY", false);
    }else InputParser::status("QUERY", false);
    andClauses.clear();
    results.clear();
}
int Query::readTermOrVar(bool& correct){
    string type = InputParser::tryToRead();
    int varNum;
    if (type.compare("VAR")==0 && InputParser::readInt(varNum) ) {
        return -varNum;
    }else if(type.compare("TERM")==0){
        string term = InputParser::tryToRead();
        int termI = database->indexOfTerm(term);
        if (termI!=-1) {
            return termI;
        }
    }
    correct =false;
    return 0;
}

void Query::check(int currentAndClause, vector<int> var){
    if (currentAndClause == andClauses.size()) {
        bool alreadyAdded = false;
        for (int i=0; !alreadyAdded && i<results.size(); i++){
            if (results[i] == database->getTerm(var[0])) {
                alreadyAdded = true;
            }
        }
        if (!alreadyAdded) {
            results.push_back(database->getTerm(var[0]));
        }
    }else{
        vector<Literal> currentAnd = andClauses[currentAndClause];
        for (int i=0; i< currentAnd.size(); i++) {
            //substitue vars from already solved
            Literal current = currentAnd[i];
            if (current.first<0 && var[-current.first-1]!=-1) {
                current.first = var[-current.first-1];
            }
            if (current.second<0 && var[-current.second-1]!=-1) {
                current.second = var[-current.second-1];
            }
            vector< pair<int, int> >* result = database->matching(current);
            for (int j=0; j< result->size(); j++) {
                pair<int, int> currentPair = result->at(j);
                vector<int> newVar (var);
                //substitue vars for value if possible
                if(current.first < 0){
                    newVar[-current.first-1] = currentPair.first;
                }
                if(current.second < 0){
                    newVar[-current.second-1] = currentPair.second;
                }
                check(currentAndClause+1, newVar);
            }
            delete result;
        }
    }
}

