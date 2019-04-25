/**
 *
 * C++ implementation to find the car fueling problem
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <vector>

using namespace std;

template< typename Type >
class Solution {
public:
    using Collection = vector< Type >;
    Type minRefills( Collection& S, Type reach, Type ans=0 ){
        auto N = S.size(),
             T = N-1; // (T)arget index
        for( auto i{ 0 }, j{ i }; i+1 < N; i=j ){
            for( j=i; j+1 < N && S[j+1] - S[i] <= reach; ++j ); // increment j to farthest reachable stop
            if( j == i )
                return -1; // ran out of gas
            ans +=( j < T )? 1 : 0;
        }
        return ans;
    }
};

int main() {
    using Type = int;
    Solution< Type > solution;
    Solution< Type >::Collection stops{ 0 };
    Type target{ 0 }; cin >> target;
    Type reach{ 0 }; cin >> reach;
    Type N{ 0 }; cin >> N;
    for( Type stop{ 0 }; N--; cin >> stop, stops.push_back( stop ));
    stops.push_back( target );
    auto ans = solution.minRefills( stops, reach );
    cout << ans << endl;
    return 0;
}
