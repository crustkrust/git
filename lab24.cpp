#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream inFile("input.txt");

    if (!inFile)
    {
        cerr << " input file not present";
        return 1;
    }

    char ch;
    while (inFile.get(ch))
    {
        cout << ch << endl;
    }

    inFile.close();
    inFile.open("input.txt");

    string line;
    while (getline(inFile, line))
    {
        cout << line << endl;
    }

    cout << "successfully copied the content";
}