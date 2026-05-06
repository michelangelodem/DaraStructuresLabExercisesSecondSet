#ifndef MAPPER_H
#define MAPPER_H

#include "Record.h"
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

class Mapper {
    private:
        static Record lineToRecord(const string& line);
        static string* splitLine(const string& line, char delimiter);
    public: 
        static vector<Record> fileToRecords(const string& file);
};

#endif