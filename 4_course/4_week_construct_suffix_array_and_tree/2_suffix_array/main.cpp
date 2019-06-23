/**
 *
 * C++ implementation of Burrows Wheeler Transform to trivially create a Suffix Array in near-linear time
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
#include <cassert>

#define OUTPUT_SUFFIX_ARRAY_INDEXES

using namespace std;
using Collection = vector< int >;
using Count = Collection;
using EquivalenceClass = Collection;
using Order = Collection;
using Start = Collection;
int main() {
    string S; cin >> S;
    const auto MAX_N = 2 * int( 1e5 ) + 1,
               N = static_cast< int >( S.size() ),
               M = 256;
    Order order( MAX_N ); { // order <- SortCharacters( S )
        Count cnt( M, 0 );
        for( auto i{ 0 }; i < N; ++i ){
            auto ch = S[ i ];
            ++cnt[ ch ];
        }
        for( auto j{ 1 }; j < M; ++j )
            cnt[ j ] += cnt[ j-1 ]; // offset current count relative to previous count's offset
        for( auto i{ N-1 }; 0 <= i; --i ){
            auto ch = S[ i ];
            --cnt[ ch ];
            order[ cnt[ ch ] ] = i;
        }
    }
    EquivalenceClass classes( MAX_N ); { // eClass <- ComputeCharClasses( S, order )
        classes[ order[ 0 ] ] = 0;
        for( auto i{ 1 }; i < N; ++i )
            if( S[ order[ i ] ] != S[ order[ i-1 ] ] )
                classes[ order[ i ] ] = classes[ order[ i-1 ] ] + 1;  // diff equivalence class
            else
                classes[ order[ i ] ] = classes[ order[ i-1 ] ];      // same equivalence class
    }
    for( auto L = 1; L < N; L *= 2 ){
        Count cnt( M, 0 ); { // use counting sort to sort each equivalence class to determine next order
            for( auto i{ 0 }; i < N; ++i ){
                auto cl = classes[ i ];
                ++cnt[ cl ];
            }
            for( auto j{ 1 }; j < M; ++j )
                cnt[ j ] += cnt[ j-1 ];
        }
        Order new_order( MAX_N ); {
            for( auto i{ N-1 }; 0 <= i; --i ){
                auto start = ( order[ i ] - L + N ) % N;
                auto cl = classes[ start ];
                --cnt[ cl ];
                new_order[ cnt[ cl ] ] = start;
            }
        }
        order.swap( new_order );
        EquivalenceClass new_classes( MAX_N ); { // UpdateClasses( new_order, eClass, L )
            new_classes[ order[ 0 ] ] = 0;
            for( auto i{ 1 }; i < N; ++i ){
                auto pre = order[ i-1 ], preMid = ( pre + L ) % N,
                     cur = order[ i   ], curMid = ( cur + L ) % N;
                if( classes[ pre ] != classes[ cur ] || classes[ preMid ] != classes[ curMid ] )
                    new_classes[ cur ] = new_classes[ pre ] + 1;
                else
                    new_classes[ cur ] = new_classes[ pre ];
            }
        }
        classes.swap( new_classes );
    }
#ifdef OUTPUT_SUFFIX_ARRAY_INDEXES
    copy_n( order.begin(), N, ostream_iterator< int >( cout, " " ) ); cout << endl;
#endif
    return 0;
}
