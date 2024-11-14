#include <bits/stdc++.h>
using namespace std;

void raiseInterrupt(string &opcode)
{
    cout << "Invalid opcode present : " << opcode << endl;
}

int main()
{

    vector<string> validOpcode = {"MOV", "ADD", "SUB", "DIV", "MUL", "LOAD"};

    vector<string> job = {
        "MOV R1 R2",
        "ADD R1 R3",
        "INVALID R4 R5",
        "SUB R1 R2"};

    for (string instruction : job)
    {
        string opcode = instruction.substr(0, instruction.find(' '));
        bool isValid = false;
        for (string op : validOpcode)
        {
            if (opcode == op)
            {
                isValid = true;
                break;
            }
        }
        if (!isValid)
        {
            raiseInterrupt(opcode);
            return 1;
        }
    }

    cout << "all instructions are valid";

    return 0;
}