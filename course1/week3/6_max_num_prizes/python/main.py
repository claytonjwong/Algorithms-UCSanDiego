# python3

##
#
# Python3 implementation to find the maximum number of prizes
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List

class Solution:
    def maxNumPrizes( self, N: int ) -> List[int] :
        ans = []
        i = 1
        while i+1 <= N-i:
            ans.append( i )
            N -= i
            i += 1
        if 0 < N:
            ans.append( N )
        return ans

if __name__ == '__main__':
    solution = Solution()
    N = int( input() )
    ans = solution.maxNumPrizes( N )
    print( len( ans ))
    for x in ans:
        print( x, end=" " )
