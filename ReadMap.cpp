#include "Map.h"
#include "link.h"
#include "arrow.h"
#include "mainwindow.h"

#include<QGraphicsPixmapItem>
#include<QGraphicsView>


#include <fstream>
#include <stdio.h>

#define WINDOWS
#ifdef WINDOWS

#include <direct.h>

#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include<iostream>
#include <vector>


std::string GetCurrentWorkingDir() {
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}


using namespace std;

vector<string> ReadMap(const string &path) {
    vector<string> map;
    try {

        ifstream mapFile(path);

        if (mapFile) {

            string line;

            while(getline(mapFile, line))
            {
                map.push_back(line);
            }



        } else {
            throw string("Can't open map file.");
        }

    }
    catch (string const &e) {
        cerr << e << endl;
    }
    return map;
}
