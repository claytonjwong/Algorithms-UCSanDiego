/**
 *
 * C implementation to calculate the greatest common divisor between two numbers
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>

using namespace std;

template< typename Type >
class Solution {
public:
    Type gcd( Type a, Type b ){
        for( auto t{ b }; b != 0; ){
            t = b;
            b = a % b;
            a = t;
        }
        return a;
    }
};

int main(){
    using Type = size_t;
    Solution< Type > solution;
    Type a = 0,
         b = 0;
    cin >> a >> b;
    Type ans = solution.gcd( a, b );
    cout << ans << endl;
    return 0;
}
