# python3

##
#
# Python3 implementation to find the maximum advertising revenue
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List

class Solution:
    def maxAdRev( self, A: List[int], B: List[int], N: int ) -> int:
        A.sort()
        B.sort()
        ans = 0
        for i in range( 0, N ):
            ans += A[ i ] * B[ i ]
        return ans

if __name__ == '__main__':
    solution = Solution()
    N = int( input() )
    A = list( map( int, input().split() ))
    B = list( map( int, input().split() ))
    ans = solution.maxAdRev( A, B, N )
    print( ans )
