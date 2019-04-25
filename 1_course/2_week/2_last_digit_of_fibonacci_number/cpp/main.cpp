/**
 *
 * Modern C++ implementation to calculate the last digit of a large Fibonacci number
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

    using VT = vector< Type >;

    Type fibonacci( Type N ){
        if( N < 2 )
            return N;
        VT dp( N+1 );
        dp[ 0 ] = 0;
        dp[ 1 ] = 1;
        for( auto i{ 2 }; i <= N; ++i )
            dp[ i ] = ( dp[ i-2 ] + dp[ i-1 ] ) % 10;
        return dp[ N ];
    }
};

int main(){
    using Type = int;
    Solution< Type > solution;
    Type N{ 0 };
    cin >> N;
    auto ans = solution.fibonacci( N );
    cout << ans << endl;
    return 0;
}
