#include <iostream>
#include <utility>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <deque>

using namespace std;

//#include "../../Utilities/UnitTestFrameWork.hpp"

template<typename It>
void PrintRange (It begin, It end) {
    for (auto it = begin; it != end; ++it)
        cout << *it << " ";
    cout << endl;
}

using  MathExpression = deque<string>;

void PrintWithBrackets(ostream& os, const MathExpression& exp) {
    for (auto it = exp.begin(); it != exp.end(); ++it)
        os << *it;
}

void fillMathExpresionWithBrackets(istream& is, MathExpression& exp) {
    string first_number;
    is >> first_number;

    exp.push_back(first_number);

    size_t amount_of_operations;
    is >> amount_of_operations;

    for (size_t i = 1; i <= amount_of_operations; ++i) {
        exp.push_front("(");
        exp.push_back(")");

        string operation, number;
        is >> operation >> number;
        exp.push_back(" " + operation + " " + number);
    }

}

//void Test()
//{
//    {
//        MathExpression exp;
//        istringstream in("8 0");
//        fillMathExpresion(in, exp);
//        ostringstream out;
//        PrintWithBrackets(out, exp);
//        AssertEqual(out.str(), "8");
//    }
//
//    {
//        MathExpression exp;
//        istringstream in("8 1 * 1");
//        fillMathExpresion(in, exp);
//        ostringstream out;
//        PrintWithBrackets(out, exp);
//        AssertEqual(out.str(), "(8) * 1");
//    }
//    {
//        MathExpression exp;
//        istringstream in("8 5 * 1 / 2 + 3 - 4 * 100");
//        fillMathExpresion(in, exp);
//        ostringstream out;
//        PrintWithBrackets(out, exp);
//        AssertEqual(out.str(), "(((((8) * 1) / 2) + 3) - 4) * 100");
//    }
//}

int main() {
    /*TestRunner r;
    r.RunTest(Test, "Test");*/


    MathExpression exp;
    fillMathExpresionWithBrackets(cin, exp);
    PrintWithBrackets(cout,exp);
    return 0;
}

/*
// ��������� ��������� ��� ������� ����������� ������
struct Operation {
  // ��������� �� ��������� ����� ��� ��������������� �������
  // ���������� ������� (*)
  char type = 0;
  int number = 0;
};


int main() {
  int initial_number;
  cin >> initial_number;

  int number_of_operations;
  cin >> number_of_operations;
  vector<Operation> operations(number_of_operations);  // (*)
  for (int i = 0; i < number_of_operations; ++i) {
    cin >> operations[i].type;
    cin >> operations[i].number;
  }

  deque<string> expression;
  expression.push_back(to_string(initial_number));
  for (const auto& operation : operations) {
    expression.push_front("(");
    expression.push_back(") ");
    expression.push_back(string(1, operation.type));
    expression.push_back(" ");
    expression.push_back(to_string(operation.number));
  }

  for (const string& s : expression) {
    cout << s;
  }

  return 0;
}
*/
