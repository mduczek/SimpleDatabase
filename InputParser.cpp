//
//  InputParser.cpp
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#include <iostream>
#include "InputParser.h"
#include <cstdio>

InputParser::InputParser(){};

int InputParser::lineNumber = 0;
int InputParser::lastCommand = 0;
bool InputParser::eof = false;
bool InputParser::readInt(int &value){
    lineNumber++;
    return (scanf("%d", &value) == 1) && (value>0);
}
string InputParser::tryToRead(){
    lineNumber++;
    char strC [80];
    if(scanf ("%s", strC)==EOF)
        eof=true;
    string str (strC);
    if (str.compare(0,1,"-") == 0) {
        return tryToRead();
    }else if (str != "") {
        return str;
    }else{
        return "";
    }
}
string InputParser::readCommand(){
    lastCommand = lineNumber +1;
    return tryToRead();
}
void InputParser::status(string command, bool correct){
    string okidoki;
    if (correct) okidoki = "OK";
    else okidoki = "ERROR";
    cout << lastCommand << " "<< command << " " << okidoki <<"\n";
}
int InputParser::getLine(){
    return lineNumber;
}