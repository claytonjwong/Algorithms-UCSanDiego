# 1. Money Change Again
[https://en.wikipedia.org/wiki/Change-making_problem](https://en.wikipedia.org/wiki/Change-making_problem)

## Problem
![](docs/1_money_change_again.png)

## Solutions
* [C++](#cpp)
* [Python3](#python3)

### CPP
```cpp
    #include <iostream>
    #include <vector>
    #include <unordered_map>
    #include <algorithm>
    #include <cassert>

    using namespace std;

    using Type = int;
    using Coins = vector< Type >;
    using Memo = unordered_map< int,int >;

    const auto INF{ 9999 };

    namespace TopDown {
        template<typename Type>
        class Solution {
        public:
            Type minCoins( const Coins &C, Type T, Memo memo = {} ){
                return go( C, T, memo );
            }
        private:
            Type go( const Coins &C, Type T, Memo &memo, Type ans = INF ){
                if( T == 0 )
                    return 0;
                if( memo.find( T ) != memo.end() )
                    return memo[ T ];
                for( auto coin: C ){
                    if( 0 <= T - coin ){
                        auto cnt = 1 + go( C, T - coin, memo );
                        ans = min( ans, cnt );
                    }
                }
                return memo[ T ] = ans;
            }
        };
    }
    namespace BottomUp {
        template< typename Type >
        class Solution {
        public:
            Type minCoins( const Coins& C, Type T ){
                using Collection = vector< Type >;
                Collection dp( T+1, INF );
                dp[ 0 ] = 0;
                for( auto i{ 1 }; i <= T; ++i )
                    for( auto coin: C )
                        if( 0 <= i - coin )
                            dp[ i ] = min( dp[ i ], 1 + dp[ i - coin ] );
                return dp[ T ];
            }
        };
    }

    int main() {
        TopDown::Solution< Type > rec_solution;
        BottomUp::Solution< Type > dp_solution;
        Coins C{ 1,3,4 };      // (C)oins
        auto T{ 0 }; cin >> T; // (T)arget
        auto rec_ans = rec_solution.minCoins( C, T );
        auto dp_ans = dp_solution.minCoins( C, T );
        assert( rec_ans == dp_ans );
        cout << rec_ans << endl;
        return 0;
    }
```

### Python3
```python
    from typing import List, Dict

    INF = 9999
    Type = int
    Coins = List[Type]
    Memo = Dict[Type,Type]

    class RECSolution:
        def minCoins( self, C: Coins, T: Type ) -> Type:
            return self.go( C, T )
        def go( self, C: Coins, T: Type, memo: Memo={}, ans: Type=INF ) -> Type:
            if T == 0:
                return 0
            if T in memo:
                return memo[ T ]
            for coin in C:
                if 0 <= T - coin:
                    cnt = 1 + self.go( C, T - coin, memo )
                    ans = min( ans, cnt )
            memo[ T ] = ans
            return ans
    class DPSolution:
        def minCoins( self, C: Coins, T: Type ) -> Type:
            dp = [ INF ] * ( T+1 )
            dp[ 0 ] = 0
            for i in range( T+1 ):
                for coin in C:
                    if 0 <= i - coin:
                        dp[ i ] = min( dp[ i ], 1 + dp[ i - coin ] )
            return dp[ T ]

    if __name__ == '__main__':
        rec_solution = RECSolution()
        dp_solution = DPSolution()
        C = [ 1,3,4 ]      # (C)oins
        T = int( input() ) # (T)arget
        rec_ans = rec_solution.minCoins( C, T )
        dp_ans = dp_solution.minCoins( C, T )
        assert( rec_ans == dp_ans )
        print( rec_ans )
```
