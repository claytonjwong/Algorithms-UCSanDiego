/**
 *
 * C++ implementation to find the maximum value of a knapsack
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <cassert>

using namespace std;

using Collection = vector< int >;

namespace TopDown {
    class Solution {
    public:
        using PII = pair< int,int >;
        struct Hash {
            size_t operator()( const PII& p ) const {
                return 1e4+1 * p.first + p.second;
            }
        };
        using Memo = unordered_map< PII,int, Hash >;
        int maxKnapsack( const Collection& A, int T, Memo memo={} ){
            auto N = static_cast< int >( A.size() );
            return go( A, T, N-1, memo );
        }
    private:
        int go( const Collection& A, int T, int i, Memo& memo, int with=0 ){
            auto key = make_pair( T,i );
            if( memo.find( key ) != memo.end() )
                return memo[ key ];
            if( i < 0 )
                return memo[ key ] = 0;
            if( 0 <= T - A[ i ] )
                with = A[ i ] + go( A, T - A[ i ], i-1, memo );
            auto without = go( A, T, i-1, memo );
            return memo[ key ] = max( with, without );
        }
    };
}
namespace BottomUp {
    class Solution {
    public:
        using VI = vector< int >;
        using VVI = vector< VI >;
        int maxKnapsack( const Collection& A, int T ){
            auto N = static_cast< int >( A.size() );
            VVI dp( N+1, VI( T+1, 0 ));
            for( auto i{ 1 }; i <= N; ++i )
                for( auto j{ 1 }; j <= T; ++j )
                    if( 0 <= j - A[ i-1 ] )
                        dp[ i ][ j ] = max( A[ i-1 ] + dp[ i-1 ][ j - A[ i-1 ]], dp[ i-1 ][ j ]); // max( with, without )
                    else
                        dp[ i ][ j ] = dp[ i-1 ][ j ]; // without
            return dp[ N ][ T ];
        }
    };
}

int main() {
    auto T{ 0 }; cin >> T; // (T)otal capacity
    auto N{ 0 }; cin >> N; // N unique items ( take it or leave it )
    Collection A;
    copy_n( istream_iterator< int >( cin ), N, back_inserter( A ));
    auto ans1 = TopDown::Solution().maxKnapsack( A, T );
    auto ans2 = BottomUp::Solution().maxKnapsack( A, T );
    assert( ans1 == ans2 );
    cout << ans2 << endl;
    return 0;
}
