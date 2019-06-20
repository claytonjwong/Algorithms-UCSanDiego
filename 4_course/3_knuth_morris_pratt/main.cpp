/**
 *
 * C++ implementation of the Knuth-Morris-Pratt algorithm
 * to find all matches of pattern in text in O(|pattern|+|text|) time
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

//#define BRUTE_FORCE_SEARCH
//#define OUTPUT_PREFIX_FUNCTION
#define OUTPUT_INDEXES_OF_NEEDLE_IN_HAYSTACK

using namespace std;

#ifdef BRUTE_FORCE_SEARCH // Failed case #57/64: time limit exceeded (Time used: 1.98/1.00, memory used: 72019968/536870912.)
using Indexes = vector< int >;
int main() {
    string needle, haystack; cin >> needle >> haystack;
    auto M = needle.size(),
         N = haystack.size();
    Indexes I; {
        for( auto i{ 0 }, j{ 0 }; i + M <= N; ++i ){
            for( j = 0; j < M && needle[ j ] == haystack[ i+j ]; ++j );
            if( j == M )
                I.push_back( i );
        }
    }
#ifdef OUTPUT_INDEXES_OF_NEEDLE_IN_HAYSTACK
    copy( I.begin(), I.end(), ostream_iterator< int >( cout, " " ) ); cout << endl;
#endif
}
#else // Knuth-Morris-Pratt
using PrefixFunction = vector< int >;
using Indexes = vector< int >;
int main() {
    string needle, haystack; cin >> needle >> haystack;
    string S; {
        ostringstream os; os << needle << '$' << haystack;
        S = os.str();
    }
    auto M = needle.size(),
         N = S.size();
    PrefixFunction P( N, 0 ); {
        for( auto i{ 1 }, j{ 0 }; i < N; ++i ){ // let j denote the "border" of the string
            while( 0 < j && S[ i ] != S[ j ] )
                j = P[ j-1 ];
            P[ i ] = j = ( S[ i ] == S[ j ] )? j+1 : 0;
        }
    }
#ifdef OUTPUT_PREFIX_FUNCTION
    cout << S << endl;
    copy( P.begin(), P.end(), ostream_iterator< int >( cout, "" ) ); cout << endl;
#endif
    Indexes I; {
        auto offset = 2 * M;
        for( auto i{ offset }; i < S.size(); ++i )
            if( P[ i ] == M )
                I.push_back( i - offset );
    }
#ifdef OUTPUT_INDEXES_OF_NEEDLE_IN_HAYSTACK
    copy( I.begin(), I.end(), ostream_iterator< int >( cout, " " ) ); cout << endl;
#endif
    return 0;
}
#endif
