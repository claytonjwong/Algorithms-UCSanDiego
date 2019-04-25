/**
 *
 * C++ implementation to determine if a list of integers can be partitioned into 3 equal sum groups
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

using VI = vector< int >;

class Solution {
public:
    bool canPartition( const VI& A ){
        auto sum = accumulate( A.begin(), A.end(), 0 );
        if( sum % 3 != 0 )
            return false;
        return go( A, sum / 3 );
    }
private:
    bool go( const VI& A, int T, VI P=VI(3), int i=0 ){ // (A)rray to partition and (T)arget value of each (P)art
        auto N = A.size(), M = P.size();
        if( i == N )
            return P[ 0 ] == T && P[ 1 ] == T && P[ 2 ] == T;
        for( auto j{ 0 }; j < M; ++j ){
            P[ j ] += A[ i ];
            if( P[ j ] <= T && go( A, T, P, i+1 ) )
                return true;
            P[ j ] -= A[ i ];
        }
        return false;
    }
};

int main() {
    auto N{ 0 }; cin >> N;
    VI A;
    copy_n( istream_iterator< int >( cin ), N, back_inserter( A ) );
    Solution solution;
    auto ans = solution.canPartition( A );
    cout << ans << endl;
    return 0;
}