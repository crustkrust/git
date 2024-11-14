#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream inFile("program.alp");

    if (!inFile)
    {
        cerr << "error in program";
        return 1;
    }

    vector<string> memory;

    string instruction;
    while (getline(inFile, instruction))
    {
        memory.push_back(instruction);
    }

    inFile.close();

    cout << "program loaded into the main memory";
    for (int i = 0; i < memory.size(); i++)
    {
        cout << "memory[" << i << "] : " << memory[i] << endl;
    }
}
