#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//�������� ��� ����� �� ������� �������������� � �������� �������
//#include "..\..\Utilities\UnitTestFrameWork.hpp"

void PrintVectorPart(const vector<int>& numbers) {
    auto it = find_if (begin(numbers), end(numbers), [](int number) { return number < 0; });
    while (it != begin(numbers))
        cout << *(--it) << " ";
}

//void Test()
//{
//    AssertEqual(PrintVectorPart({    }), vector<int>{}, "void error");
//    AssertEqual(PrintVectorPart({ -1 }), vector<int>{}, "first negative error");
//    AssertEqual(PrintVectorPart({ -1, 2, 3, -5 }), vector<int>{}, "first negative error");
//    AssertEqual(PrintVectorPart({ 1, -2, 3, -5 }), vector<int>{1});
//    AssertEqual(PrintVectorPart({ 1, 2, -3, -5 }), vector<int>{2,1});
//    AssertEqual(PrintVectorPart({ 1, 2, 3, 5 }),   vector<int>{5,3,2,1});
//}

int main() {
    PrintVectorPart({ 6, 1, 8, -5, 4 });
    cout << endl;
    PrintVectorPart({ -6, 1, 8, -5, 4 });  // ������ �� ���������
    cout << endl;
    PrintVectorPart({ 6, 1, 8, 5, 4 });
    cout << endl;
    return 0;
}