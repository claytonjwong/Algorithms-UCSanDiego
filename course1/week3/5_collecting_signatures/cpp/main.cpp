/**
 *
 * C++ implementation to collect signatures
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

using Type = int;
struct Segment {
    Type a{ 0 }, b{ 0 };
    bool operator<( const Segment& rhs ) const {
        return ! ( b < rhs.b ); // descending order of segment end-point b
    }
};
ostream& operator<<( ostream& stream, const Segment& rhs ){
    stream << "{ " << rhs.a << "," << rhs.b << " }";
    return stream;
}
using Segments = vector< Segment >;

class Solution {
public:
    using Collection = vector< Type >;
    Collection minPoints( Segments& cur, Collection ans={} ){
        sort( cur.begin(), cur.end() );
        int trim = 0;
        for( Segments next; ! cur.empty(); swap( cur,next ), next.clear(), ++trim ){
            auto B = cur.back().b; // greedy choice: the smallest segment end-point b
            ans.emplace_back( B );
            cur.pop_back();
            for( auto s: cur ) if( ! ( s.a <= B && B <= s.b )) // next is all (s)egments of cur which do NOT contain B
                next.emplace_back( s );
        }
        return ans;
    }
};

int main() {
    Type N{ 0 }; cin >> N;
    Segments S( N );
    for( int i{ 0 }; i < N; ++i ){
        Type a{ 0 }, b{ 0 }; cin >> a >> b;
        S[ i ] = { a,b };
    }
    Solution solution;
    auto ans = solution.minPoints( S );
    cout << ans.size() << endl;
    copy( ans.begin(), ans.end(), ostream_iterator< Type >( cout, " " ));
    cout << endl;
    return 0;
}
