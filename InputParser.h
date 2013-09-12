//
//  InputParser.h
//  QueryProcessing
//
//  Created by Michal Duczyński on 27.03.2012.
//  Copyright 2012 Student 320321. All rights reserved.
//

#ifndef QueryProcessing_InputParser_h
#define QueryProcessing_InputParser_h
#include <string>
using namespace std;

//Class handling input, what is worth noting: it uses scanf, so it skips empty lines
//It also keeps track of line numeration and prints status of commands
class InputParser {
    static int lineNumber;
    static int lastCommand;
    
public:
    InputParser();
    static bool readInt(int &value);
    static bool eof;
    static string tryToRead();
    static void status(string command, bool correct);
    static int getLine();
    static string readCommand();
};

#endif
