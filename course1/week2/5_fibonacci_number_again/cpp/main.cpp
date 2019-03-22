/**
 *
 * C++ implementation to find the N mod M-th fibonacci number
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <vector>

using namespace std;

template< typename Type >
class Solution {
public:

    using Collection = vector< Type >;

    Type fibonacci( Type N, Type M ){
        Collection dp( (6*M)+1 );
        dp[ 0 ] = 0;
        dp[ 1 ] = 1;
        dp[ 2 ] = 1;
        Type i = 3; // start looking for the pisano period from i=3 to ignore the first 0,1 sequence at dp[ 0 ] and dp[ 1 ]
        for(; i <= N && ! ( dp[ i-2 ] == 0 && dp[ i-1 ] == 1 ); ++i )
            dp[ i ] = ( dp[ i-2 ] + dp[ i-1 ] ) % M;
        Type P = i-2;                    // (P)isano period
        return( N <= i-1 )? dp[ N ]      // case 1) (P)isano period NOT reached, return the N-th fibonacci number
                          : dp[ N % P ]; // case 2) (P)isano period reached, return (N mod P)-th fibonacci number
    }
};

int main(){
    using Type = unsigned long long;
    Solution< Type > solution;
    Type N = 0,
         M = 0;
    cin >> N >> M;
    Type ans = solution.fibonacci( N, M );
    cout << ans << endl;
    return 0;
}
