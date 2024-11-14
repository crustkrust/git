#include <bits/stdc++.h>
using namespace std;

void raiseInterrupt(const string &opcode) {
    cout << "Invalid opcode present: " << opcode << endl;
}

void operandError(const string &instruction) {
    cout << "Operand error in instruction: " << instruction << endl;
}

int main() {
    // Define valid opcodes and expected operand counts
    map<string, int> validOpcodes = {
        {"MOV", 2},
        {"ADD", 2},
        {"SUB", 2},
        {"DIV", 2},
        {"MUL", 2},
        {"LOAD", 1}
    };

    // List of instructions to validate
    vector<string> job = {
        "MOV R1 R2",     // Valid
        "ADD R1 R3",     // Valid
        "INVALID R4 R5", // Invalid opcode
        "SUB R1",        // Operand error
        "LOAD R1 R2"     // Operand error
    };

    // Check each instruction
    for (const string &instruction : job) {
        // Extract opcode and operands
        stringstream ss(instruction);
        string opcode;
        vector<string> operands;
        ss >> opcode;  // Extract opcode

        // Extract operands
        string operand;
        while (ss >> operand) {
            operands.push_back(operand);
        }

        // Check if the opcode is valid
        if (validOpcodes.find(opcode) == validOpcodes.end()) {
            raiseInterrupt(opcode);  // Invalid opcode
            continue; // Continue with the next instruction after error
        }

        // Check if the operand count matches the expected count
        if (operands.size() != validOpcodes[opcode]) {
            operandError(instruction);  // Operand error
            continue; // Continue with the next instruction after error
        }
    }

    cout << "Instruction validation completed" << endl;
    return 0;
}
