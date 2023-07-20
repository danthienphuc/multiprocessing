#include <fileIO.h>

using namespace std;

FileIO::FileIO()
{
}

FileIO::~FileIO()
{
}

void FileIO::openFileToRead(string fileName)
{
    file.open(fileName, ios::in);
}

void FileIO::openFileToWrite(string fileName)
{
    file.open(fileName, ios::out);
}

void FileIO::closeFile()
{
    file.close();
}

void FileIO::write(string content)
{
    file << content;
}

string FileIO::read()
{
    string content;
    getline(file, content);
    return content;
}