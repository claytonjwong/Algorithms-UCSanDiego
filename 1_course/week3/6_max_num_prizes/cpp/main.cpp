/**
 *
 * C++ implementation to find the maximum number of prizes
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template< typename Type >
class Solution {
public:
    using Collection = vector< Type >;
    Collection maxNumPrizes( Type N,Collection ans={} ){
        for( Type i{ 1 }; i+1 <= N-i; N-=i, ++i )
            ans.push_back( i );
        if( 0 < N )
            ans.push_back( N );
        return ans;
    }
};

int main() {
    using Type = int;
    Solution< Type > solution;
    Type N{ 0 }; cin >> N;
    auto ans = solution.maxNumPrizes( N );
    cout << ans.size() << endl;
    copy( ans.begin(), ans.end(), ostream_iterator< Type >( cout, " " ));
    cout << endl;
    return 0;
}
