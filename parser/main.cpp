#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

bool isDataType(const string& word) {
    string dataTypes[] = {"int", "float", "double", "char", "long", "short", "bool"};
    for (const string& type : dataTypes) {
        if (word == type) return true;
    }
    return false;
}

bool isOperator(const string& word) {
    string operators[] = {"=", "+", "-", "*", "/", "%"};
    for (const string& op : operators) {
        if (word == op) return true;
    }
    return false;
}

bool isNumber(const string& word) {
    for (char c : word) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int main() {
    ifstream file("input.txt");
    string line;

    if (getline(file, line)) {
        stringstream ss(line);
        string token;
        while (ss >> token) {

            if (token.back() == ';') token.pop_back();

            if (isDataType(token))
                cout << token << " is a data type" << endl;
            else if (isOperator(token))
                cout << token << " is an operator" << endl;
            else if (isNumber(token))
                cout << token << " is a number" << endl;
            else
                cout << token << " is a variable" << endl;
        }
    } else {
        cout << "Failed to read from file." << endl;
    }

    return 0;
}