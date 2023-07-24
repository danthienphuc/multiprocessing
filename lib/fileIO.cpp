#include <iostream>
#include <unistd.h>
#include "fileIO.h"

using namespace std;

FileIO::FileIO()
{
}

FileIO::~FileIO()
{
}

void FileIO::open(string fileName)
{
    char path[256];
    string p = getcwd(path, 256);
    string fpath = p + "/data/" + fileName + ".csv";
    cout << "open: " << fpath << endl;
    this->file.open(fpath, ios::in | ios::app);
}

void FileIO::close()
{
    this->file.close();
}

void FileIO::write(string fileName, string content)
{
    this->open(fileName);
    this->file << content;
    this->file << endl;
    this->close();
}

string FileIO::read(string fileName)
{
    string content;
    this->open(fileName);
    getline(this->file, content);
    this->close();
    return content;
}