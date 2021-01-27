#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class FunctionPart {
 public:
    FunctionPart(char new_operation, double new_value) {
        operation = new_operation;
        value     = new_value;
    }
    double Apply(double source_value) const {
        switch (operation) {
        case('+'): return source_value + value;
        case('-'): return source_value - value;
        case('*'): return source_value * value;
        case('/'): return source_value / value;
        default:
            break;
        }
    }

    void Invert() {
        switch (operation) {
        case('+'): operation = '-';
            break;
        case('-'): operation = '+';
            break;
        case('*'): operation = '/';
            break;
        case('/'): operation = '*';
            break;

        default:
            break;
        }
    }

 private:
    char operation;
    double value;
};


class Function {
 public:
    void AddPart(char operation, double value) { parts.push_back({ operation, value }); }

    double Apply(double value) const {
        for (const auto& part : parts)
            value = part.Apply(value);

        return value;
    }
    void Invert() {
        for (auto& part : parts)
            part.Invert();

        reverse(parts.begin(), parts.end());
    }

 private:
    vector<FunctionPart> parts;
};
