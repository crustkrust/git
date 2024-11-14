#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    if (!inFile)
    {
        cerr << " input file not present";
        return 1;
    }

    if (!outFile)
    {
        cerr << " out file not present";
        return 1;
    }

    char ch;
    while (inFile.get(ch))
    {
        outFile.put(ch);
    }

    inFile.close();
    outFile.close();
    inFile.open("input.txt");
    outFile.open("output_line.txt");

    string line;
    while (getline(inFile, line))
    {
        outFile << line << '\n';
    }

    cout << "successfully copied the content";
}