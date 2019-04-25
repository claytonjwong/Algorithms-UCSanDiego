/**
 *
 * C++ implementation of majority element
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <algorithm>

using namespace std;

using Type = int;
using Collection = vector< Type >;

class Solution {
public:
    using Counter = unordered_map< Type, size_t >;
    bool hasMajorityElement( const Collection& A, Counter C={} ){
        for( auto x: A )
            ++C[ x ];
        auto N = A.size(),
             T = ( N / 2 ) + 1;
        for( auto& pair: C )
            if( T <= pair.second )
                return true;
        return false;
    }
};

int main() {
    Solution solution;
    auto N{ 0 }; cin >> N;
    Collection A;
    copy_n( istream_iterator< Type >( cin ), N, back_inserter( A ));
    auto ans = solution.hasMajorityElement( A );
    cout << ans << endl;
    return 0;
}
