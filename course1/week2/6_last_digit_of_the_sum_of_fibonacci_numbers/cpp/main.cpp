/**
 *
 * C++ implementation to calculate the sum mod 10 of 1,2,...,N-1,N-th fibonacci number
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

template< typename Type >
class Solution {
public:

    using Collection = vector< Type >;

    Type sum(Collection &dp, Type N, Type M){
        return accumulate( dp.begin(), dp.begin() + N+1, 0 ) % M;
    }

    Type fibonacci( Type N, Type M ){
        Collection dp( (6*M)+2, 0 );
        dp[ 0 ] = 0;
        dp[ 1 ] = 1;
        dp[ 2 ] = 1;
        Type i = 3; // start looking for the pisano period from i=3 to ignore the first 0,1 sequence at dp[ 0 ] and dp[ 1 ]
        for(; i <= N && ! ( dp[ i-2 ] == 0 && dp[ i-1 ] == 1 ); ++i )
            dp[ i ] = ( dp[ i-2 ] + dp[ i-1 ] ) % M;
        Type P = i-2;                            // (P)isano period
        return( N <= i-1 )? sum( dp, N,     M )  // case 1) (P)isano period NOT reached, return the sum % M of N-th fibonacci number
                          : sum( dp, N % P, M ); // case 2) (P)isano period reached, return the sum % M of (N mod P)-th fibonacci number
    }
};

int main(){
    using Type = unsigned long long;
    Solution< Type > solution;
    Type N{ 0 },
         M{ 10 };
    cin >> N;
    Type ans = solution.fibonacci( N, 10 );
    cout << ans << endl;
    return 0;
}
