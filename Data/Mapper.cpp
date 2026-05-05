#include "Mapper.h"

Record Mapper::lineToRecord(const string& line) {
    int day, month, year;
    string* fields = splitLine(line, ','); 
    string* dateStr = splitLine(fields[2], '/');
    try {
        day = stoi(dateStr[0]);
        month = stoi(dateStr[1]);
        year = stoi(dateStr[2]);
    } catch (const exception& e) {
        throw runtime_error("Invalid date format in line: " + line);
    }
    return Record(Date(day, month, year), stoll(fields[8]), stoll(fields[9]));
}

string* Mapper::splitLine(const string& line, char delimiter) {
    string* fields = new string[10]; 
    string field;
    bool insideQuotes = false;
    size_t field_i = 0;
    
    for (size_t char_i = 0; char_i < line.length(); ++char_i) {
        char ch = line[char_i];
        if (ch == '"') {
            insideQuotes = !insideQuotes; 
        } else if (ch == delimiter && !insideQuotes) {
            fields[field_i++] = field; 
            field.clear();
        } else {
            field += ch; 
        }
    }

    if (!field.empty() || line.back() == delimiter) {
        fields[field_i] = field; 
    }
    return fields;
}

vector<Record> Mapper::fileToRecords(const string& file) {
    ifstream infile(file);
    if (!infile.is_open()) {
        throw runtime_error("Could not open file: " + file);
    }
    string line;
    vector<Record> records;
    bool skipHeader = true;

    while (getline(infile, line)) {
        if (skipHeader) {
            skipHeader = false; 
            continue;
        }
        try {
            Record record = lineToRecord(line);
            records.push_back(record);
        } catch (const exception& e) {
            throw runtime_error("Error processing line: " + line);
        }
    }

    return records;   
}