# python3

##
#
# Python3 implementation of majority element
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List

class Solution:
    def hasMajorityElement( self, A: List[int], N: int ) -> bool:
        me = 0
        cnt = 0
        for x in A:
            if cnt == 0:
                me = x
            cnt = cnt + 1 if me == x else cnt - 1
        cnt = 0
        T = ( N // 2 ) + 1
        for x in A:
            cnt = cnt + 1 if me == x else cnt
        return T <= cnt

if __name__ == '__main__':
    solution = Solution()
    N = int( input() )
    A = list( map( int, input().split() ))
    ans = solution.hasMajorityElement( A, N )
    print( "1" if ans else "0" )
