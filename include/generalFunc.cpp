#include <string>
#include <iostream>
#include <algorithm>
#include "../header/txtDB.h"

using namespace std;

char getChoice(){
    cout << "Enter a number for your option:  ";
    
    char output;
    cin >> output;

    return output;
}

string getLineInput(attribute attributeWanted) {
    string outputStr;
    getline(cin, outputStr);

    outputStr = trim(outputStr);
    outputStr = strLengthEnforcer(outputStr, attributeWanted.size);

    return outputStr;
}

string removeSpaces(string str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    return str;
}