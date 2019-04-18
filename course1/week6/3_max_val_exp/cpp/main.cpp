#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Solution {
public:
    using VI = vector< int >;
    using VVI = vector< VI >;
    int maxValExp( const string& input ){
        auto[ D, op ] = read( input );
        if( D.empty() )
            return 0;
        auto N = static_cast< int >( D.size() );
        VVI m( N, VI( N ) ), M( N, VI( N ) );
        for( auto i{ 0 }; i < N; ++i )
            m[ i ][ i ] = M[ i ][ i ] = D[ i ];
        for( auto s{ 1 }; s < N; ++s ){ // (s)ize
            for( auto i{ 0 }; i < N - s; ++i ){
                auto j{ i+s };
                auto[ mini, maxi ] = minMax( m, M, op, i, j );
                m[ i ][ j ] = mini;
                M[ i ][ j ] = maxi;
            }
        }
        return M[ 0 ][ N-1 ];
    }
private:
    using Input = pair< VI,VI >;
    Input read( const string& input, VI D={}, VI Op={} ){
        istringstream stream{ input };
        auto d{ 0 }; stream >> d; D.push_back( d );
        for( char op; stream >> op >> d; Op.push_back( op ), D.push_back( d ) );
        return{ D, Op };
    }
    using MinMax = pair< int,int >;
    MinMax minMax( const VVI& m, const VVI& M, const VI& op, int i, int j ){
        auto mini = numeric_limits< int >::max(),
             maxi = numeric_limits< int >::min();
        for( auto k{ i }; k < j; ++k ){
            auto a = calc( M[ i ][ k ], op[ k ], M[ k+1 ][ j ] ),
                 b = calc( M[ i ][ k ], op[ k ], m[ k+1 ][ j ] ),
                 c = calc( m[ i ][ k ], op[ k ], M[ k+1 ][ j ] ),
                 d = calc( m[ i ][ k ], op[ k ], m[ k+1 ][ j ] );
            mini = min({ mini, a,b,c,d });
            maxi = max({ maxi, a,b,c,d });
        }
        return{ mini,maxi };
    }
    int calc( int first, int op, int second ){
        switch( op ){
            case '+': return first + second;
            case '-': return first - second;
            case '*': return first * second;
            case '/': return first / second;
        }
        return 0;
    }
};

int main() {
    Solution solution;
    string input; cin >> input;
    auto ans = solution.maxValExp( input );
    cout << ans << endl;
    return 0;
}
