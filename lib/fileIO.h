#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <fstream>

using namespace std;

class FileIO
{
    public:
        fstream file;

        FileIO();
        ~FileIO();
        void open(string fileName);
        void close();
        void write(string fileName, string content);
        string read(string fileName);
        // Directory
        string* listFiles(string dirName, string ext);
};

#endif // !FILEIO_H