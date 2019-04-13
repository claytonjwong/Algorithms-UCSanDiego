/**
 *
 * C++ implementation to find the minimum amount of operations on a primitive calculator to obtain N
 * The primitive calculator has 3 operations: multiply by 2, multiply by 3, and add by 1
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cassert>

using namespace std;

using Type = int;
using Memo = unordered_map< Type,Type >;
using Collection = deque< Type >;

const auto INF = static_cast< Type >( 1e6+1 );

Collection reconstruct( Type N, Memo& memo, Collection A={} ){
    while( 0 < N ){
        A.push_front( N );
        auto prev3 = ( N % 3 == 0 && memo.find( N / 3 ) != memo.end() )? memo[ N / 3 ] : INF;
        auto prev2 = ( N % 2 == 0 && memo.find( N / 2 ) != memo.end() )? memo[ N / 2 ] : INF;
        auto prev1 = ( N - 1 >= 0 && memo.find( N - 1 ) != memo.end() )? memo[ N - 1 ] : INF;
        auto prev = min({ prev3, prev2, prev1 });
        if(      prev == prev3 ) N /= 3;
        else if( prev == prev2 ) N /= 2;
        else if( prev == prev1 ) N -= 1;
    }
    return A;
}

namespace TopDown {
    template< typename Type >
    class Solution {
    public:
        Collection minOps( Type N, Memo memo={}, Collection A={} ){
            go( N, memo );
            return reconstruct( N, memo );
        }
    private:
        Type go( Type N, Memo& memo, Type ans=INF ){
            if( N < 2 )
                memo[ N ] = 0;
            if( memo.find( N ) != memo.end() )
                return memo[ N ];
            if( N % 3 == 0 ) ans = min( ans, 1 + go( N / 3, memo ));
            if( N % 2 == 0 ) ans = min( ans, 1 + go( N / 2, memo ));
            return memo[ N ] = min( ans, 1 + go( N - 1, memo ));
        }
    };
}
namespace BottomUp {
    template< typename Type >
    class Solution {
    public:
        Collection minOps( Type N, Memo memo={{ 1,0 }} ){
            Collection dp( N+1, INF );
            dp[ 1 ] = 0;
            for( auto i{ 2 }; i <= N; ++i ){
                if( i % 3 == 0 ) dp[ i ] = min( dp[ i ], 1 + dp[ i / 3 ] );
                if( i % 2 == 0 ) dp[ i ] = min( dp[ i ], 1 + dp[ i / 2 ] );
                memo[ i ] = dp[ i ] = min( dp[ i ], 1 + dp[ i - 1 ] );
            }
            return reconstruct( N, memo );
        }
    };
}

int main() {
    BottomUp::Solution< Type > dp_solution;
    auto N{ 0 }; cin >> N;
    auto A = dp_solution.minOps( N );
    cout << (( A.empty() )? 0 : A.size() - 1 ) << endl;
    copy( A.begin(), A.end(), ostream_iterator< Type >( cout, " " )); cout << endl;
//    TopDown::Solution< Type > rec_solution;
//    auto A1 = rec_solution.minOps( N );
//    assert( A1 == A );
    return 0;
}
