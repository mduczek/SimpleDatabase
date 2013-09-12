//
//  Dataset.cpp
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include "Dataset.h"
#include "InputParser.h"
#include "Utils.h"
using namespace std;

Dataset::Dataset(){}

void Dataset::addTerm(string termName){
    terms.add(termName);
}

void Dataset::addRelation(string relationName){
    if (relations.getIndex(relationName)==-1) {
        set< pair<int, int>,compByFirst > relF;
        contentSortedByFirst.push_back(relF);
        set< pair<int, int>,compBySecond > relS;
        contentSortedBySecond.push_back(relS);
    }
    relations.add(relationName);
}
bool Dataset::addTermsToRelation(string relation, string leftTerm, string rightTerm){
    int relI=-1;
    if (relation!="") relI = relations.getIndex(relation);
    int leftI=-1;
    if (leftTerm!="") leftI = terms.getIndex(leftTerm);
    int rightI=-1;
    if (rightTerm!="") rightI = terms.getIndex(rightTerm);
    if (relI != -1 && leftI!=-1 && rightI != -1) {
        pair<int,int> newPair =  make_pair(leftI, rightI);
        contentSortedByFirst[relI].insert(newPair);
        contentSortedBySecond[relI].insert(newPair);
        return true;
    }else return false;
}

void Dataset::printClosure(string relation){
    int relI=-1;
    relI = relations.getIndex(relation);
    if (relI!=-1) {
        InputParser::status("PRINT_CLOSURE", true);
        set<pair<int, int>,compByFirst >* relV = new set<pair<int, int>,compByFirst >(contentSortedByFirst[relI]);
        closureCompute(relV);
        vector<pair<string,string > > relationVString (relV->size());
        set<pair<int,int>, compByFirst >::iterator it;
        int i=0;
        for ( it=relV->begin(); it != relV->end(); it++ ){
            relationVString[i] = make_pair(terms.atIndex(it->first), terms.atIndex(it->second));
            i++;
        } 
        sort(relationVString.begin(), relationVString.end(), Utils::compareP);
        for (int i=0; i< relationVString.size(); i++)
            cout << relationVString[i].first<< "-" << relationVString[i].second << "\n";
        delete relV;
    } else InputParser::status("PRINT_CLOSURE", false);
}
void Dataset::closure(string relation){
    int relI=-1;
    relI = relations.getIndex(relation);
    if (relI!=-1) {
        closureCompute(&contentSortedByFirst[relI]);
        set<pair<int, int>, compByFirst>::iterator it;
        for (it=contentSortedByFirst[relI].begin(); it!=contentSortedByFirst[relI].end(); it++)
            contentSortedBySecond[relI].insert(*it);

    } else InputParser::status("PRINT_CLOSURE", false);
}
void Dataset::closureCompute(set<pair<int, int>, compByFirst >* relV){
    set<int> termsUsed;
    set<pair<int,int> >::iterator it;
    for ( it=relV->begin() ; it != relV->end(); it++ ){
        termsUsed.insert(it->first);
        termsUsed.insert(it->second);
    }
    //Floyd-Warshall
    set<int>::iterator itI;
    set<int>::iterator itJ;
    set<int>::iterator itK;
    for ( itI=termsUsed.begin() ; itI != termsUsed.end(); itI++ ){
        for ( itJ=termsUsed.begin() ; itJ != termsUsed.end(); itJ++ ){
            for ( itK=termsUsed.begin() ; itK != termsUsed.end(); itK++ ){
                if ( relV->count(make_pair(*itI, *itJ))==0 ) {
                    if(relV->count(make_pair(*itI, *itK))==1 && relV->count(make_pair(*itK, *itJ))==1 ){
                        relV->insert(make_pair(*itI, *itJ));
                    }
                }
            }
        }
    }
}

//-----------------------Print
void Dataset::printAllTerms(){
    terms.print();
}
void Dataset::printAllRelations(){
    relations.print();
}

void Dataset::printRelation(string relationName){
    int relI=-1;
    if (relationName!="") relI = relations.getIndex(relationName);
    if (relI!=-1) {
        InputParser::status("PRINT_RELATION", true);
        vector<pair<string,string > > relationVString (contentSortedByFirst[relI].size());
        set<pair<int,int> >::iterator it;
        int i=0;
        for ( it=contentSortedByFirst[relI].begin() ; it != contentSortedByFirst[relI].end(); it++ ){
            relationVString[i] = make_pair(terms.atIndex(it->first), terms.atIndex(it->second));
            i++;
        } 
        sort(relationVString.begin(), relationVString.end(), Utils::compareP);
        for (int i=0; i< relationVString.size(); i++)
            cout << relationVString[i].first<< "-" << relationVString[i].second << "\n";

    } else InputParser::status("PRINT_RELATION", false);

}
void Dataset::printRelated(string relation, string term){
    int relI=-1;
    if (relation!="") relI = relations.getIndex(relation);
    int leftI=-1;
    if (term!="") leftI = terms.getIndex(term);
    if (relI!=-1 && leftI!=-1) {
        InputParser::status("PRINT_RELATED", true);
        set<string> related;
        set<pair<int,int> >::iterator it;
        for ( it=contentSortedByFirst[relI].begin() ; it != contentSortedByFirst[relI].end(); it++ ){
            if (terms.atIndex(it->first) == term) {
                related.insert(terms.atIndex(it->second));
            }
            if (terms.atIndex(it->second) == term) {
                related.insert(terms.atIndex(it->first));
            }
        }
        set<string>::iterator itS;
        for ( itS=related.begin() ; itS != related.end(); itS++ )
            cout << *itS<<"\n";
    }else InputParser::status("PRINT_RELATED", false);
}

vector< pair<int, int> >* Dataset::matching(Literal patern){
    vector< pair<int, int> >* result = new vector< pair<int, int> >();
    set<pair<int, int>, compByFirst >* relF = &contentSortedByFirst[patern.relation];
    if (patern.first >= 0 && patern.second < 0) {
        //term-var
        set<pair<int, int>, compByFirst>::iterator it,itlow,itup;
        itlow = relF->lower_bound(make_pair(patern.first, 0));
        itup = relF->upper_bound(make_pair(patern.first, terms.getSize() ));
        if (patern.related) {
            for (it=itlow; it!=itup; it++)
                result->push_back(*it);
        }else{
            for (it=relF->begin(); it!=itlow; it++)
                result->push_back(*it);
            for (it=itup; it!=relF->end(); it++)
                result->push_back(*it);
        }
        
    } else if(patern.first < 0 && patern.second>=0) {
        //var-term
        set<pair<int, int>, compBySecond >* relS = &contentSortedBySecond[patern.relation];
        set<pair<int, int>, compBySecond>::iterator it,itlow,itup;
        itlow = relS->lower_bound(make_pair(0, patern.second));
        itup = relS->upper_bound(make_pair(terms.getSize(),patern.second  ));
        if (patern.related) {
            for (it=itlow; it!=itup; it++)
                result->push_back(*it);
        }else{
            for (it=relS->begin(); it!=itlow; it++)
                result->push_back(*it);
            for (it=itup; it!=relS->end(); it++)
                result->push_back(*it);
            
        }
    } else if(patern.first >= 0 && patern.second >= 0) {
        //term-term
        pair<int, int> pairCurrent = make_pair(patern.first, patern.second);
        if (patern.related) {
            if (relF->count(pairCurrent)!=0 ) {
                result->push_back(pairCurrent );
            }
        }else{
            if (relF->count(pairCurrent)==0 ) {
                result->push_back(pairCurrent );
            }
        }
        
    } else {
        //var-var
        if (patern.related) {
            set<pair<int, int>, compByFirst>::iterator it;
            for (it=relF->begin(); it!=relF->end(); it++)
                result->push_back(*it);
        }
    }
    return result;
}
int Dataset::indexOfTerm(string str){
    return terms.getIndex(str);
}
int Dataset::indexOfRelation(string str){
    return relations.getIndex(str);
}
string Dataset::getTerm(int index){
    return terms.atIndex(index);
}
string Dataset::getRelation(int index){
    return relations.atIndex(index);
}



