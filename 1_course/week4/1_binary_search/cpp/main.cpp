/**
 *
 * C++ implementation of binary search
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template< typename Type >
class Solution {
public:
    using Collection = vector< Type >;
    using Iter = typename Collection::iterator;
    const static Type NOT_FOUND = -1;
    Type binarySearch( Collection& A, Type T ){
        return go( A, T, 0, A.size() );
    }
private:
    Type go( Collection& A, Type T, size_t lo, size_t hi ){ // search A for (T)arget
        if( lo == hi )
            return NOT_FOUND;
        auto P = ( lo + hi ) / 2;
        if( T < A[ P ] )
            return go( A, T, lo, P );
        if( T > A[ P ] )
            return go( A, T, P+1, hi );
        return P;
    }
};

int main() {
    using Type = int;
    Solution< Type > solution;
    Solution< Type >::Collection A, ans;
    size_t N{ 0 }, M{ 0 };
    cin >> N;
    copy_n( istream_iterator< Type >( cin ), N, back_inserter( A ));
    cin >> M;
    for( Type T{ 0 }; M-- && cin >> T; ){
        auto result = solution.binarySearch( A, T );
        ans.push_back( result );
    }
    copy( ans.begin(), ans.end(), ostream_iterator< Type >( cout, " " ));
    return 0;
}
