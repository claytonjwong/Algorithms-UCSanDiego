/**
 *
 * C++ implementation to find the minimum amount of coins
 * with denominations 1, 3, 4 that changes money
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

using Type = int;
using Coins = vector< Type >;
using Memo = unordered_map< int,int >;

const auto INF{ 9999 };

namespace TopDown {
    template<typename Type>
    class Solution {
    public:
        Type minCoins( const Coins &C, Type T, Memo memo = {} ){
            return go( C, T, memo );
        }

    private:
        Type go( const Coins &C, Type T, Memo &memo, Type ans = INF ){
            if( T == 0 )
                return 0;
            if( memo.find( T ) != memo.end() )
                return memo[ T ];
            for( auto coin: C ){
                if( 0 <= T - coin ){
                    auto cnt = 1 + go( C, T - coin, memo );
                    ans = min( ans, cnt );
                }
            }
            return memo[ T ] = ans;
        }
    };
}
namespace BottomUp {
    template< typename Type >
    class Solution {
    public:
        Type minCoins( const Coins& C, Type T ){
            using Collection = vector< Type >;
            Collection dp( T+1, INF );
            dp[ 0 ] = 0;
            for( auto i{ 1 }; i <= T; ++i )
                for( auto coin: C )
                    if( 0 <= i - coin )
                        dp[ i ] = min( dp[ i ], 1 + dp[ i - coin ] );
            return dp[ T ];
        }
    };
}

int main() {
    TopDown::Solution< Type > rec_solution;
    BottomUp::Solution< Type > dp_solution;
    Coins C{ 1,3,4 };      // (C)oins
    auto T{ 0 }; cin >> T; // (T)arget
    auto rec_ans = rec_solution.minCoins( C, T );
    auto dp_ans = dp_solution.minCoins( C, T );
    assert( rec_ans == dp_ans );
    cout << rec_ans << endl;
    return 0;
}
