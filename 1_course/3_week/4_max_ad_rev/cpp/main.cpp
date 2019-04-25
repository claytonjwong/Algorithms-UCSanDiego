/**
 *
 * C++ implementation to find the maximum advertising revenue
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template< typename Type >
class Solution {
public:
    using Collection = vector< Type >;
    Type maxAdRev( Collection& A, Collection& B, Type ans=0 ){
        auto N = A.size();
        sort( A.begin(), A.end() );
        sort( B.begin(), B.end() );
        for( auto i{ 0 }; i < N; ++i )
            ans += A[ i ] * B[ i ];
        return ans;
    }
};

int main() {
    using Type = long long;
    Solution< Type > solution;
    Type N{ 0 }; cin >> N;
    Solution< Type >::Collection A( N ), B( N );
    for( Type i{ 0 }; i < N; cin >> A[ i++ ] );
    for( Type i{ 0 }; i < N; cin >> B[ i++ ] );
    auto ans = solution.maxAdRev( A, B );
    cout << ans << endl;
    return 0;
}
