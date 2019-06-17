/**
 *
 * C++ implementation of inverse Burrows Wheeler Transform
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_map>

//#define TRIVIAL_IMPLEMENTATION
//#define OUTPUT_CYCLIC_ROTATIONS__THE_BURROWS_WHEELER_TRANSFORM_MATRIX
#define OUTPUT_INVERSE_BURROWS_WHEELER_TRANSFORM__THE_ORIGINAL_GENOME

using namespace std;

#ifdef TRIVIAL_IMPLEMENTATION // Failed case #27/44: time limit exceeded (Time used: 4.05/2.00)
using Deque = deque< char >;
using Strings = vector< Deque >;
int main() {
    string str; cin >> str;
    const auto N = str.size();
    Strings S( N );
    for( auto i{ 0 }; i < N; ++i ){
        for( auto j{ 0 }; j < N; ++j )
            S[ j ].push_front( str[ j ] );
        sort( S.begin(), S.end() );
    }
#ifdef OUTPUT_CYCLIC_ROTATIONS__THE_BURROWS_WHEELER_TRANSFORM_MATRIX
    for( auto i{ 0 }; i < N; ++i, cout << endl )
        for( auto j{ 0 }; j < S[ i ].size(); ++j )
            cout << S[ i ][ j ];
    cout << endl;
#endif
#ifdef OUTPUT_INVERSE_BURROWS_WHEELER_TRANSFORM__THE_ORIGINAL_GENOME
    auto it = find_if( S.begin(), S.end(), []( const auto& str ){ return str.back() == '$'; });
    string inverse{ it->begin(), it->end() };
    cout << inverse << endl;
#endif
    return 0;
}
#else // First-Last Property Optimization
using Counter = unordered_map< char, int >;
using Path = unordered_map< string, string >;
int main() {
    Path path; {
        string transformed; cin >> transformed;
        auto sorted{ transformed }; sort( sorted.begin(), sorted.end() );
        const auto N = transformed.size();
        Counter begCnt, endCnt;
        for( auto i{ 0 }; i < N; ++i ){
            ostringstream first, last;
            auto beg = sorted[ i ],
                 end = transformed[ i ];
            first << beg << ++begCnt[ beg ];
            last  << end << ++endCnt[ end ];
            path[ first.str() ] = last.str();
        }
    }
    string inverse{ '$' }; {
        const auto sentinel{ "$1" };
        for( auto cur = path[ sentinel ]; cur != sentinel; cur = path[ cur ] )
            inverse.push_back( cur.front() );
    }
#ifdef OUTPUT_INVERSE_BURROWS_WHEELER_TRANSFORM__THE_ORIGINAL_GENOME
    cout << string{ inverse.rbegin(), inverse.rend() } << endl;
#endif
    return 0;
}
#endif
