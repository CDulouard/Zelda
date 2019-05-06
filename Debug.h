#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <vector>

class Debug {
    public:
        static void Log(const std::string &msg);
        static void Write(const std::string &msg);
        static void DisplayMap(std::vector<std::string> map);

};


#endif // DEBUG_H
