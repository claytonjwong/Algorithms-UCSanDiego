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
#include <queue>
#include <unordered_map>
#include <cassert>

using namespace std;

using Type = int;
const auto INF{ 1e6+1 };

enum class Op {
    Div2,
    Div3,
    Sub1,
};
struct Result {
    Type cnt;
    Op op;
};
using Memo = unordered_map< Type,Result >;
using Collection = deque< Type >;

Collection reconstruct( Type N, Memo& memo, Collection A={} ){
    while( 0 < N ){
        A.push_front( N );
        switch( memo[ N ].op ){
            case Op::Div3: N /= 3; break;
            case Op::Div2: N /= 2; break;
            case Op::Sub1: N -= 1; break;
            default:
                assert( true );
        }
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
            if( memo.find( N ) != memo.end() )
                return memo[ N ].cnt;
            if( N == 1 ){
                memo[ N ] = { 0, Op::Sub1 };
                return memo[ N ].cnt;
            }
            if( N % 3 == 0 ){
                auto alt = 1 + go( N / 3, memo );
                if( ans > alt ){
                    ans = alt;
                    memo[ N ] = { ans, Op::Div3 };
                }
            }
            if( N % 2 == 0 ){
                auto alt = 1 + go( N / 2, memo );
                if( ans > alt ){
                    ans = alt;
                    memo[ N ] = { ans, Op::Div2 };
                }
            }
            auto alt = 1 + go( N - 1, memo );
            if( ans > alt ){
                ans = alt;
                memo[ N ] = { ans, Op::Sub1 };
            }
            return memo[ N ].cnt;
        }
    };
}
namespace BottomUp {
    template< typename Type >
    class Solution {
    public:
        Collection minOps( Type N, Memo memo={} ){
            Collection dp( N+1, INF );
            dp[ 1 ] = 0;
            for( auto i{ 2 }; i <= N; ++i ){
                if( i % 3 == 0 ){
                    auto alt = 1 + dp[ i / 3 ];
                    if( dp[ i ] > alt ){
                        dp[ i ] = alt;
                        memo[ N ] = { dp[ i ], Op::Div3 };
                    }
                }
                if( i % 2 == 0 ) dp[ i ] = min( dp[ i ], 1 + dp[ i / 2 ] );
                dp[ i ] = min( dp[ i ], 1 + dp[ i - 1 ] );
            }
            return reconstruct( N, memo );
        }
    };
}

int main() {
    TopDown::Solution< Type > rec_solution;
    BottomUp::Solution< Type > dp_solution;
    auto N{ 0 }; cin >> N;
    auto A1 = rec_solution.minOps( N );
    auto dp_ans = dp_solution.minOps( N );
//    assert( rec_ans == dp_ans );
    cout << (( A1.empty() )? 0 : A1.size() - 1 ) << endl;
    copy( A1.begin(), A1.end(), ostream_iterator< Type >( cout, " " )); cout << endl;
    return 0;
}
