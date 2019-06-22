/**
 *
 * C++ implementation of Counting Sort ( a stable sort with linear asymptotic time + memory ) note: not in-place sort
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

#define PSEUDOCODE_VERBATIM
#define OUTPUT_ORDER
#define OUTPUT_EQUIVALENCE_CLASS
#define OUTPUT_START
#define OUTPUT_NEW_ORDER
#define OUTPUT_NEW_CLASS

using namespace std;
using Collection = vector< int >;
using Count = Collection;
using EquivalenceClass = Collection;
using Order = Collection;
using Start = Collection;

#ifdef PSEUDOCODE_VERBATIM
int main() {
    /*
     * class   character
     * -----   ---------
     *     0   $
     *     1   a
     *     2   b
     */
    string S{ "ababaa$" }; const auto N = static_cast< int >( S.size() ), L = 1;
    //         ^^^^^^^  ---->  a b a b a a $
    //EquivalenceClass eClass{ 1,2,1,2,1,1,0 };
    /*
     *  suffix array 'order' == begin index of the ordered suffixes of the original string S
     *
     *  order   suffix
     *  -----   ------
     *      6   $
     *      5   a$
     *      4   aa$
     *      2   abaa$
     *      0   ababaa$
     *      3   baa$
     *      1   babaa$
     *
     *  IMPORTANT NOTE: in this example 'order' is the count sort of single characters of the original string S !!!
     *
     */
    /*  Order order{ 6,5,4,2,0,3,1 }; // <-- suffix array 'order' ( not used in this example !!! )
     *               $ a a a a b b
     *                 $ a b b a a
     *                   $ a a a b
     *                     a b $ a
     *                     $ a   a
     *                       a   $
     *                       $
     */
    Order order( N ); { // the order of single characters of the original string S
        /*
         * compute a histogram of the number of times each key occurs within the original string S
         */
        Count count( 123, 0 ); // 123 == 'z' + 1  ( +1 for 'a' through 'z' inclusive )
        for( auto i{ 0 }; i < N; ++i ){
            auto ch = S[ i ];
            count[ ch ] = count[ ch ] + 1;
        }
        /*
         * count[ '$' ] = 1
         * count[ 'a' ] = 4
         * count[ 'b' ] = 2
         */
        /*
         * prefix sum computation on count to determine, for each key,
         * the position range where the items having that key should be placed in;
         * i.e. items of key i should be placed in the range of [ count{ i-1 } : count{ i } )
         * i.e. the range exists from count[ i-1 ] inclusive to count[ i ] non-inclusive ( one-past the actual range )
         */
        for( auto j{ 1 }; j < 123; ++j )
            count[ j ] = count[ j ] + count[ j-1 ]; // offset current count relative to previous count's offset
        /*
         * count[ '$' ] = 1  <--  count[ '$' ] = 1 offset by 0
         * count[ 'a' ] = 5  <--  count[ 'a' ] = 4 offset by 1
         * count[ 'b' ] = 7  <--  count[ 'b' ] = 2 offset by 5
         */
        /*
         * move each (i)ndex into its sorted position
         * NOTE: count[ ch ] is originally non-inclusive of the range (i)ndex will be placed witihin
         *       ( i.e. the value of count[ ch ] is one-past the actual range )
         *       that is why count[ ch ] is decremented before the (i)ndex is placed into that corresponding position
         */
        for( auto i{ N-1 }; 0 <= i; --i ){
            auto ch = S[ i ];
            count[ ch ] = count[ ch ] - 1;
            order[ count[ ch ] ] = i;
        }
    }
#ifdef OUTPUT_ORDER
    cout << "Order: "; copy( order.begin(), order.end(), ostream_iterator< int >( cout, " " ) ); cout << endl;
#endif
    EquivalenceClass eClass( N ); {
        eClass[ order[ 0 ] ] = 0;  // '$' is always order[ 0 ], thus eClass[ '$' ] = 0 as the base case of the recurrence formula
        for( auto i{ 1 }; i < N; ++i )
            if( S[ order[ i ] ] != S[ order[ i-1 ] ] )
                eClass[ order[ i ] ] = eClass[ order[ i-1 ] ] + 1;  // diff equivalence class
            else
                eClass[ order[ i ] ] = eClass[ order[ i-1 ] ];      // same equivalence class
    }
#ifdef OUTPUT_EQUIVALENCE_CLASS
    cout << "Class: "; copy( eClass.begin(), eClass.end(), ostream_iterator< int >( cout, " " ) ); cout << endl;
#endif
    Count count( 123, 0 ); {
        for( auto i{ 0 }; i < N; ++i ){
            auto cl = eClass[ i ];
            count[ cl ] = count[ cl ] + 1;
        }
        for( auto j{ 1 }; j < 123; ++j )
            count[ j ] = count[ j ] + count[ j-1 ];
    }
    Start start( N ); {
        for( auto i{ N-1 }; 0 <= i; --i )
            start[ i ] = ( order[ i ] - L + N ) % N;
    }
#ifdef OUTPUT_START
    cout << "Start: "; copy( start.begin(), start.end(), ostream_iterator< int >( cout, " " ) ); cout << endl;
#endif
    Order newOrder( N ); {
        for( auto i{ N-1 }; 0 <= i; --i ){
            auto cl = eClass[ start[ i ] ];
            count[ cl ] = count[ cl ] - 1;
            newOrder[ count[ cl ] ] = start[ i ];
        }
    }
#ifdef OUTPUT_NEW_ORDER
    cout << "New order: "; copy( newOrder.begin(), newOrder.end(), ostream_iterator< size_t >( cout, " " ) ); cout << endl;
#endif
    return 0;
}
//
// TODO: newClass
//

#else // PSEUDOCODE_ABRIDGED
int main() {
    string A{ "ababaa$" };
    const auto N = A.size();
    //         ^^^^^^^ --->  a b a b a a $
    EquivalenceClass eClass{ 1,2,1,2,1,1,0 };
    Count C( N, 0 ); {
        for( auto i{ 0 }; i < N; ++i ){
            auto cl = eClass[ i ]; // equivalence (cl)ass
            ++C[ cl ];        // increment (C)ount by one
        }
        for( auto j{ 1 }; j < N; ++j )
            C[ j ] += C[ j-1 ]; // what does this do??? semantic meaning of this
    }
    Indexes I( N ); {

    }
    return 0;
}
#endif
