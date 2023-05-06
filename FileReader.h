#ifndef DEF_FILE_READER
#define DEF_FILE_READER

#include <iostream>
#include <vector>
#include <string>
#include "Job.h"

using namespace std;

class FileReader {
public:
    FileReader();
    void read_file(string & file_name, vector<Job*> & jobs);
    void write_csv(string & file_name, vector<int> results);
};


#endif