/**
 *
 * C++ implementation to check brackets in code, return success if []{}() match,
 * otherwise return 1-based index of first mismatching []{}()
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    using Stack = vector< pair< char,int > >;
    int match( const string& A, Stack stack={}, string open="[{(", string close="]})" ){
        auto i{ 0 };
        for( auto c: A ){
            ++i; // 1-based indexing
            auto open_index = open.find( c ),
                 close_index = close.find( c );
            if( open_index == string::npos && close_index == string::npos )
                continue;
            if( open_index != string::npos ){
                stack.push_back({ close[ open_index ], i });
            } else {
                if( stack.empty() )
                    return i;
                auto target = stack.back().first;
                auto match_index = close.find( target );
                if( c != close[ match_index ] )
                    return i;
                stack.pop_back();
            }
        }
        return( stack.empty() )? 0 : stack[ 0 ].second;
    }
};

int main() {
    string input;
    getline( cin, input );
    Solution solution;
    auto ans = solution.match( input );
    if( ans == 0 )
        cout << "Success" << endl;
    else
        cout << ans << endl;
    return 0;
}
