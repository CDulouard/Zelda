#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Debug.h"

void Debug::Log(const string &msg){
    cout << msg << endl;
}

void Debug::Write(const string &msg){
    cout << msg;
}

void Debug::DisplayMap(vector<string> map){
    cout.flush();
    for (const auto &i : map) {
        Debug::Log(i);
    }
    Debug::Log("");
}
