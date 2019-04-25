/**
 *
 * C++ implementation to find the maximum salary
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <sstream>
#include <set>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

struct cmp {
    bool operator()( const string& lhs, const string& rhs ) const {
        int i{ 0 }, N = min( lhs.size(), rhs.size() );
        for(; i < N; ++i )
            if( lhs[ i ] < rhs[ i ] )
                return false;
            else
            if( lhs[ i ] > rhs[ i ] )
                return true;
        return(( lhs.size() == rhs.size() ) || ( lhs.size() < rhs.size() && lhs[ 0 ] > rhs[ i ] ))? true : false;
    }
};

template< typename Type >
class Solution {
public:
    using Collection = vector< Type >;
    string maxSalary( Collection A, ostringstream outStream=ostringstream() ){
        multiset< string, cmp > S;
        transform( A.begin(), A.end(), inserter( S, S.end() ), []( auto x ){ return to_string( x ); });
        copy( S.begin(), S.end(), ostream_iterator< string >( outStream ));
        return outStream.str();
    }
};

int main() {
    using Type = int;
    Solution< Type > solution;
    Solution< Type >::Collection A;
    auto N{ 0 }; cin >> N;
    for( int x{ 0 }; N--; cin >> x, A.push_back( x )); // copy_n( istream_iterator< int >( cin ), N, back_inserter( A ));
    auto ans = solution.maxSalary( A );
    cout << ans << endl;
    return 0;
}
