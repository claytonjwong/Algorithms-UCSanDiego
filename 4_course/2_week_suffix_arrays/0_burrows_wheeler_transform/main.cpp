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
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    using Strings = vector< string >;
    Strings S;
    string str{ "AGACATA$" };
    for( auto N = str.size(); N--; ){
        rotate( str.begin(), str.begin()+1, str.end() );
        S.push_back({ str.begin(), str.end() });
    }
    sort( S.begin(), S.end() );
    copy( S.begin(), S.end(), ostream_iterator< string >( cout, "\n" ) );
    transform( S.begin(), S.end(), S.begin(), []( const auto& s ){ return s.back(); });
    ostringstream os;
    copy( S.begin(), S.end(), ostream_iterator< string >( os, "" ) );
    assert( os.str() == "ATG$CAAA" );
    cout << endl << os.str() << endl;
    return 0;
}
