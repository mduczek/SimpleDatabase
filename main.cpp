//
//  Main.cpp
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#include <iostream>
#include <string>
#include "Query.h"
#include "InputParser.h"
#include "Dataset.h"

using namespace std;

int main (int argc, const char * argv[])
{
    Dataset database;
    string str = "_";
    bool correct;
    while (!InputParser::eof) {
        correct = true;
        str = InputParser::readCommand();
        if (str == "ADD_TERM") {
            string str = InputParser::tryToRead();
            if (str!="") database.addTerm(str);
            else correct = false;
            InputParser::status("ADD_TERM", correct);
        } else if (str == "PRINT_ALL_TERMS"){
            InputParser::status("PRINT_ALL_TERMS", true);
            database.printAllTerms();
        } else if (str == "ADD_RELATION") {
            str = InputParser::tryToRead();
            if (str!="") database.addRelation(str);
            else correct = false;
            InputParser::status("ADD_RELATION", correct);
        } else if (str == "PRINT_ALL_RELATIONS"){
            InputParser::status("PRINT_ALL_RELATIONS", true);
            database.printAllRelations();
        } else if (str == "ADD_TERMS_TO_RELATION") {
            string rel = InputParser::tryToRead();
            string left = InputParser::tryToRead();
            string right = InputParser::tryToRead();
            if(!database.addTermsToRelation(rel, left, right))
                correct = false;
            InputParser::status("ADD_TERMS_TO_RELATION", correct);
        } else if (str == "PRINT_RELATION"){
            string rel = InputParser::tryToRead();
            database.printRelation(rel);
        } else if (str == "PRINT_RELATED"){
            string rel = InputParser::tryToRead();
            string term = InputParser::tryToRead();
            database.printRelated(rel, term);
        } else if(str == "QUERY"){
            Query* qu = new Query(&database);
            qu->read();
            delete qu;
        } else if(str=="CLOSURE"){
            string rel = InputParser::tryToRead();
            if(rel!="") database.closure(rel);
            else InputParser::status("CLOSURE", false);
        } else if(str=="PRINT_CLOSURE"){
            string rel = InputParser::tryToRead();
            if(rel!="") database.printClosure(rel);
            else InputParser::status("PRINT_CLOSURE", false);
        } else if(!InputParser::eof){
            cout<< "INVALID COMMAND";
        }
        cout << "\n";
    }
    cout << "\n";
    return 0;
}