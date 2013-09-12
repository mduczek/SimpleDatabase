//
//  closure.cpp
//  QueryProcessing
//
//  Created by Michal Duczyński on 25.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string>* closure(vector< pair<int, int> > &relation);

vector<string>* closure(vector<pair <int, int> > &relation){
    vector<string>* closureV [relation.size()];
    for (int k=0; k<closureV.size(); k++) {
        //first
        for (int i=0; i<(*closureV)->size(); i++) {
            //first
            for (int k=0; k<closureV.size(); k++) {
                //first
                
                //second
            }
            //second
            for (int k=0; k<closureV.size(); k++) {
                //first
                
                //second
            }
        }
        //second
        for (int i=0; i<closureV.size(); i++) {
            //first
            for (int k=0; k<closureV.size(); k++) {
                //first
                
                //second
            }
            //second
            for (int k=0; k<closureV.size(); k++) {
                //first
                
                //second
            }
        }
    }
    vector<string>* closureVec = new vector<string> (relation.size());
    
    return closureVec;
}