/**
 *
 * C++ implementation to determine tree height
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

struct TreeNode;
using HTreeNode = shared_ptr< TreeNode >;
using Collection = vector< HTreeNode >;
struct TreeNode {
    int val;
    Collection children;
    TreeNode( int val ) : val{ val } {}
};

class Solution {
public:
    int height( HTreeNode root ){
        return go( root );
    }
private:
    int go( HTreeNode root, int D=1 ){
        if( ! root )
            return 0;
        auto maxD = D;
        for( auto child: root->children )
            maxD = max( maxD, go( child, D + 1 ) );
        return maxD;
    }
};

int main() {
    auto N{ 0 }; cin >> N;
    Collection A;
    generate_n( back_inserter( A ), N, [i=0]() mutable { return make_shared< TreeNode >( i++ ); });
    HTreeNode root;
    for( auto parent{ 0 }, child{ 0 }; child < N && cin >> parent; ++child )
        if( 0 <= parent )
            A[ parent ]->children.push_back( A[ child ] );
        else
            root = A[ child ];
    Solution solution;
    auto ans = solution.height( root );
    cout << ans << endl;
    return 0;
}
