#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <iterator>
#include <algorithm>

using namespace std;

struct TreeNode;
using HTreeNode = shared_ptr< TreeNode >;
struct TreeNode {
    int val;
    HTreeNode left, right;
    TreeNode( int val ) : val{ val }, left{ nullptr }, right{ nullptr } {}
    friend ostream& operator<<( ostream& os, const HTreeNode& node ){
        if( node )
            os << node->val;
        return os;
    }
};
bool operator<( const HTreeNode& lhs, const HTreeNode& rhs ){
    return lhs->val < rhs->val;
}
using Collection = vector< HTreeNode >;

class Solution {
public:
    bool isBST( HTreeNode root, Collection inorder={} ){
        go( root, inorder );
        return is_sorted( inorder.begin(), inorder.end() );
    }
private:
    void go( HTreeNode root, Collection& inorder ){
        if( ! root )
            return;
        go( root->left, inorder );
        inorder.push_back( root );
        go( root->right, inorder );
    }
};

int main() {
    string line;
    auto N{ 0 }; {
        getline( cin, line );
        istringstream is{ line };
        is >> N;
    }
    Collection A;
    generate_n( back_inserter( A ), N, [](){ return make_shared< TreeNode >( 0 ); });
    for( auto i{ 0 }; i < N && getline( cin, line ); ++i ){
        istringstream parser{ line };
        auto val{ 0 }, L{ 0 }, R{ 0 };
        parser >> val >> L >> R;
        A[ i ]->val = val;
        A[ i ]->left =  ( -1 < L )? A[ L ] : nullptr;
        A[ i ]->right = ( -1 < R )? A[ R ] : nullptr;
    }
    auto ok = A.empty() || Solution().isBST( A[ 0 ] );
    cout << ( ok? "CORRECT" : "INCORRECT" ) << endl;
    return 0;
}
