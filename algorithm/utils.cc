
#include "iostream"
#include <vector>
#include <sstream>
#include <stack>
#include "defines.h"
using namespace std; 

std::ostream& operator << (std::ostream& in, std::vector<int>& target) {
    in << "[";
    for (int i = 0; i < target.size(); ++i) {
        if (i == target.size() - 1) {
            in << target[i];
        }
        else {
            in << target[i] << ",";
        }
    }
     in << "]";
    return in;
}

std::istream& operator >> (std::istream& in, std::vector<int>& target) {
    char c;
    in >> c;
    while (true) {
        int num = 0;
        char comma = ']';
        in >> num >> comma;
        target.push_back(num);
        if (comma == ']') {
            break;
        }
    }
    return in;
}