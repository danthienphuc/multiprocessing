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
        void openFileToRead(string fileName);
        void openFileToWrite(string fileName);
        void closeFile();
        void write(string content);
        string read();
};

#endif // !FILEIO_H