/**
 *
 * Modern C++ implementation to find the maximum pairwise product
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>


using namespace std;


template< typename Type >
class Solution {
public:

    using Collection = vector< Type >;
    using Iter = istream_iterator< Type >;

    void test( istream& input, ostream& output, Collection A={} ){
        auto N{ 0 };
        input >> N;
        copy_n( Iter( input ), N, back_inserter( A ));
        Type first{ 0 }, second{ 0 };
        auto i = max_element( A.begin(), A.end() ); first  = *i, *i = 0;
        auto j = max_element( A.begin(), A.end() ); second = *j;
        output << first * second << endl;
    }

};


int main(){

    using Type = unsigned long long;

    Solution< Type > solution;
    solution.test( cin, cout );

    return 0;
}
