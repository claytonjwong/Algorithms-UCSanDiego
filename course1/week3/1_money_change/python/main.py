# python3

##
#
# C++ implementation to find the minimum number of coins needed to change the input value ( an integer )
# into coins with denominations 1, 5, and 10
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

class Solution:
    def coin_change( self, N: int ) -> int:
        ans = 0
        for coin in [ 10, 5, 1 ]:
            while N >= coin:
                N -= coin
                ans += 1
        return ans

if __name__ == '__main__':
    solution = Solution()
    N = int( input() )
    ans = solution.coin_change( N )
    print( ans )
