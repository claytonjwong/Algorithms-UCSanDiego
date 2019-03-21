/**
 *
 * Modern C++ implementation to calculate the N-th Fibonacci number
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <vector>
#include <limits>
#include <cassert>

using namespace std;

namespace TopDown {

    template< typename Type >
    class Solution {
    public:

        using Memo = vector< Type >;
        const Type INF = numeric_limits< Type >::max();

        Type fibonacci( Type N ){
            Memo memo( N+1, INF );
            return go( N, memo );
        }

    private:

        Type go( Type N, Memo& memo ){
            if( N < 2 )
                return memo[ N ] = N;
            return memo[ N ] = go( N-2, memo ) + go( N-1, memo );
        }
    };
}

namespace BottomUp {

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
                dp[ i ] = dp[ i-2 ] + dp[ i-1 ];
            return dp[ N ];
        }
    };
}

int main(){
    using Type = int;
    TopDown::Solution< Type > solution_top_down;
    BottomUp::Solution< Type > solution_bottom_up;
    Type N{ 0 };
    cin >> N;
    auto ans_top_down = solution_top_down.fibonacci( N ),
         ans_bottom_up = solution_bottom_up.fibonacci( N );
    assert( ans_top_down == ans_bottom_up );
    cout << ans_top_down << endl;
    return 0;
}
