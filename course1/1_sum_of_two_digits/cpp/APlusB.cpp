/**
 *
 * Modern C++ implementation to sum two integers
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/


#include <iostream>


using namespace std;


class Solution
{
public:

    int sum_of_two_digits( int first, int second )
    {
        return first + second;
    }

};


int main()
{
    Solution solution;

    auto a{ 0 }, b{ 0 };
    cin >> a >> b;
    cout << solution.sum_of_two_digits(a, b);

    return 0;
}
