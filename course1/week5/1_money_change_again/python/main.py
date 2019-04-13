# python3

##
#
# Python3 implementation to find the minimum amount of coins
# with denominations 1, 3, 4 that changes money
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List, Dict

INF = 9999
Type = int
Coins = List[Type]
Memo = Dict[Type,Type]

class Solution:
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

if __name__ == '__main__':
    solution = Solution()
    C = [ 1,3,4 ]      # (C)oins
    T = int( input() ) # (T)arget
    ans = solution.minCoins( C, T )
    print( ans )
