/**
 *
 * C++ implementation to create a Suffix Array in near-linear time
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

using namespace std;
using Collection = vector< int >;
using Count = Collection;
using Class = Collection;
using Order = Collection;
int main() {
    string S; cin >> S;
    const auto N = static_cast< int >( S.size() );
    Order order( N ); { // order <- SortCharacters( S )
        const auto M = 'T' + 1; // alphabet size
        Count cnt( M, 0 );
        for( auto i{ 0 }; i < N; ++i ){
            auto ch = S[ i ];
            ++cnt[ ch ]; // count of each unique char
        }
        for( auto j{ 1 }; j < M; ++j )
            cnt[ j ] += cnt[ j-1 ]; // prefix sums ( i.e. one-past the end of each unique char's index range )
        for( auto i{ N-1 }; 0 <= i; --i ){
            auto ch = S[ i ];
            --cnt[ ch ];
            order[ cnt[ ch ] ] = i;
        }
    }
    Class classes( N ); { // classes <- ComputeCharClasses( S, order )
        classes[ order[ 0 ] ] = 0;
        for( auto i{ 1 }; i < N; ++i )
            if( S[ order[ i ] ] != S[ order[ i-1 ] ] )
                classes[ order[ i ] ] = classes[ order[ i-1 ] ] + 1; // diff equivalence class
            else
                classes[ order[ i ] ] = classes[ order[ i-1 ] ];     // same equivalence class
    }
    for( auto L{ 1 }; L < N; L *= 2 ){ // order <- SortDoubled( S, L, order, classes )
        Count cnt( N, 0 ); {
            for( auto i{ 0 }; i < N; ++i ){
                auto cl = classes[ i ];
                ++cnt[ cl ];
            }
            for( auto j{ 1 }; j < N; ++j )
                cnt[ j ] += cnt[ j-1 ];
        }
        Order next_order( N ); {
            for( auto i{ N-1 }; 0 <= i; --i ){
                auto start = ( order[ i ] - L + N ) % N; // start is the begin index of the doubled cyclic shift
                auto cl = classes[ start ];
                --cnt[ cl ];
                next_order[ cnt[ cl ] ] = start;
            }
        }
        order.swap( next_order );
        Class next_classes( N ); { // UpdateClasses( L, next_order, classes )
            next_classes[ order[ 0 ] ] = 0;
            for( auto i{ 1 }; i < N; ++i ){
                auto pre = order[ i-1 ], preMid = ( pre + L ) % N,
                     cur = order[ i   ], curMid = ( cur + L ) % N;
                if( classes[ pre ] != classes[ cur ] || classes[ preMid ] != classes[ curMid ] )
                    next_classes[ cur ] = next_classes[ pre ] + 1; // diff equivalence class
                else
                    next_classes[ cur ] = next_classes[ pre ];     // same equivalence class
            }
        }
        classes.swap( next_classes );
    }
    copy_n( order.begin(), N, ostream_iterator< int >( cout, " " ) ); cout << endl;
    return 0;
}
