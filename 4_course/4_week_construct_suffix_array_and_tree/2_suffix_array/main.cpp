/**
 *
 * C++ implementation of Burrows Wheeler Transform to trivially create a Suffix Array in near-linear time
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#define TRIVIAL_IMPLEMENTATION
//#define OUTPUT_CYCLIC_ROTATIONS__THE_BURROWS_WHEELER_TRANSFORM_MATRIX
//#define OUTPUT_BURROWS_WHEELER_TRANSFORM
#define OUTPUT_SUFFIX_ARRAY_INDEXES

#ifdef TRIVIAL_IMPLEMENTATION
using namespace std;
using Strings = vector< string >;
using Indexes = vector< size_t >;
int main() {
    Strings S;
    string text; cin >> text;
    const auto N = text.size();
    for( auto i{ 0 }; i < N; ++i ){
        rotate( text.begin(), text.begin()+1, text.end() );
        S.push_back( text );
    }
    sort( S.begin(), S.end() );
#ifdef OUTPUT_CYCLIC_ROTATIONS__THE_BURROWS_WHEELER_TRANSFORM_MATRIX
    copy( S.begin(), S.end(), ostream_iterator< string >( cout, "\n" ) );
#endif
#ifdef OUTPUT_BURROWS_WHEELER_TRANSFORM
    Strings T( N );
    transform( S.begin(), S.end(), T.begin(), []( const auto& str ){ return str.back(); });
    ostringstream os; copy( T.begin(), T.end(), ostream_iterator< string >( os, "" ) );
    cout << endl << os.str() << endl;
#endif
#ifdef OUTPUT_SUFFIX_ARRAY_INDEXES
    Indexes I( N );
    transform( S.begin(), S.end(), I.begin(),
        []( const auto& line ){ return line.size() - line.find( '$' ) - 1; }); // -1 for 0-based indexing
    copy( I.begin(), I.end(), ostream_iterator< int >( cout, " " ) );
#endif
    return 0;
}
#else
int main() {
    return 0;
}
#endif
