/**
 *
 * C++ implementation of Burrows Wheeler Transform
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

//#define OUTPUT_CYCLIC_ROTATIONS__THE_BURROWS_WHEELER_TRANSFORM_MATRIX
#define OUTPUT_BURROWS_WHEELER_TRANSFORM

using namespace std;
using Strings = vector< string >;

int main() {
    Strings S;
    string str; cin >> str;
    for( auto N = str.size(); N--; ){
        rotate( str.begin(), str.begin()+1, str.end() );
        S.push_back( str );
    }
    sort( S.begin(), S.end() );
#ifdef OUTPUT_CYCLIC_ROTATIONS__THE_BURROWS_WHEELER_TRANSFORM_MATRIX
    copy( S.begin(), S.end(), ostream_iterator< string >( cout, "\n" ) );
#endif
#ifdef OUTPUT_BURROWS_WHEELER_TRANSFORM
    transform( S.begin(), S.end(), S.begin(), []( const auto& str ){ return str.back(); });
    ostringstream os; copy( S.begin(), S.end(), ostream_iterator< string >( os, "" ) );
    cout << endl << os.str() << endl;
#endif
    return 0;
}
