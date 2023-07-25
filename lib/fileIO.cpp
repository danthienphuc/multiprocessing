#include <iostream>
#include <unistd.h>
#include <filesystem>
#include "fileIO.h"

using namespace std;
namespace fs = std::filesystem;

FileIO::FileIO()
{
}

FileIO::~FileIO()
{
}

string getcwdir(){
    char path[256];
    string p = getcwd(path, 256);
    return p;
}

void FileIO::open(string fileName)
{
    string fpath = getcwdir() + "/data/" + fileName;
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
    string content, line;
    this->open(fileName);
    while (getline(this->file, line))
        // if line has : then it has lable and value. we need to split it and get the value
        if(line.find(":") != string::npos)
            content.append(line.substr(line.find(":") + 2) + ",");
        else
            content.append(line + ",");
    this->close();
    return content;
}

string *FileIO::listFiles(string dirName, string ext)
{
    string *files = new string[100];
    string path = getcwdir() + dirName;
    int i = 0;
    for (const auto & entry : fs::directory_iterator(path))
        if(entry.path().extension() == ext){
            files[i] = entry.path().filename().string();
            i++;
        }
    return files;
}