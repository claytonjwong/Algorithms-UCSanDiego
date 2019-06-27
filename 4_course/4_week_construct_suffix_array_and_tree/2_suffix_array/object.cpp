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
using VI = vector< int >;

class SuffixArray {
public:
    using VI = vector< int >;
    static VI build( const string& S, const int N ){
        auto order = sortChars( S, N );
        auto classes = computeCharClasses( S, N, order );
        for( auto L{ 1 }; L < N; L *= 2 ){
            order = sortDoubled( S, N, L, order, classes );
            classes = updateClasses( N, L, order, classes );
        }
        return order;
    }
private:
    static VI sortChars( const string& S, const int N ){
        const int M = 'T' + 1; // alphabet size
        VI order( N ), cnt( M );
        for( auto i{ 0 }; i < N; ++i ){
            auto c = S[ i ];
            ++cnt[ c ];
        }
        for( auto j{ 1 }; j < M; ++j )
            cnt[ j ] += cnt[ j-1 ];
        for( auto i{ N-1 }; 0 <= i; --i ){
            auto c = S[ i ];
            --cnt[ c ];
            order[ cnt[ c ] ] = i;
        }
        return order;
    }
    static VI computeCharClasses( const string& S, const int N, const VI& order ){
        VI classes( N, 0 );
        for( auto i{ 1 }; i < N; ++i )
            if( S[ order[ i ] ] != S[ order[ i-1 ] ] )
                classes[ order[ i ] ] = classes[ order[ i-1 ] ] + 1;
            else
                classes[ order[ i ] ] = classes[ order[ i-1 ] ];
        return classes;
    }
    static VI sortDoubled( const string& S, const int N, const int L, const VI& order, const VI& classes ){
        VI next_order( N, 0 ), cnt( N, 0 );
        for( auto i{ 0 }; i < N; ++i ){
            auto cl = classes[ i ];
            ++cnt[ cl ];
        }
        for( auto j{ 1 }; j < N; ++j )
            cnt[ j ] += cnt[ j-1 ];
        for( auto i{ N-1 }; 0 <= i; --i ){
            auto start = ( order[ i ] - L + N ) % N; // start is the begin index of the doubled cyclic shift
            auto cl = classes[ start ];
            --cnt[ cl ];
            next_order[ cnt[ cl ] ] = start;
        }
        return next_order;
    }
    static VI updateClasses( const int N, const int L, const VI& order, const VI& classes ){
        VI next_classes( N, 0 );
        for( auto i{ 1 }; i < N; ++i ){
            auto pre = order[ i-1 ], preMid = ( pre + L ) % N,
                cur = order[ i   ], curMid = ( cur + L ) % N;
            if( classes[ pre ] != classes[ cur ] || classes[ preMid ] != classes[ curMid ] )
                next_classes[ cur ] = next_classes[ pre ] + 1; // diff equivalence class
            else
                next_classes[ cur ] = next_classes[ pre ];     // same equivalence class
        }
        return next_classes;
    }
};

int main() {
    string S; cin >> S;
    const auto N = static_cast< int >( S.size() );
    auto order = SuffixArray::build( S, N );
    copy( order.begin(), order.end(), ostream_iterator< int >( cout, " " ) );
    return 0;
}
