#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#include "parse.cpp"

using namespace std;

int main()
{
    JSON test;

    test.parse("PlayerStatistics.json");

    cout << "Printing parsed data" << endl;

    test.print();
    return 0;
}
