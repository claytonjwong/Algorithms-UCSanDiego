/**
 *
 * C++ implementation to find the most valuable combination of items using a fractional knapsack
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

template< typename Type >
class Solution {
public:
    struct Item {
        Type V{ 0 },
             W{ 0 };
        double ratio() const {
            return( W > 0 )? double( V ) / W : 0;
        };
    };
    using Collection = vector< Item >;
    double maxValue( Collection& items, Type W, double ans=0 ){
        sort( items.begin(), items.end(), []( const Item& lhs, const Item& rhs ){ return lhs.ratio() > rhs.ratio(); });
        for( auto& item: items ){
            if( W == 0 )
                break;
            if( item.W <= W ){ // item fits in knapsack
                ans += item.V;
                W -= item.W;
            } else {
                auto fraction = double( W ) / item.W;
                ans += fraction * item.V;
                W = 0;
            }
        }
        return ans;
    }
};

int main() {
    using Type = int;
    Solution< Type > solution;
    Solution< Type >::Collection items;
    Type N{ 0 }, // N items
         W{ 0 }; // Weight capacity of knapsack
    cin >> N >> W;
    for( Type Vi{ 0 }, Wi{ 0 }; N--; cin >> Vi >> Wi, items.push_back({ Vi, Wi }) );
    auto ans = solution.maxValue( items, W );
    cout << fixed << setprecision( 4 ) << ans << endl;
    return 0;
}
