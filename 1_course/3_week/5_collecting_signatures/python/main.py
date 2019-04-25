# python3

##
#
# Python3 implementation to collect signatures
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List

class Segment:
    a = 0
    b = 0

    def __init__( self, a, b ):
        self.a = a
        self.b = b

    def __lt__( self, rhs ): # descending order of segment end-point b
        if self.b == rhs.b:
            return True if self.a > rhs.a else False 
        return True if self.b > rhs.b else False

class Solution:
    def minPoints( self, cur: List[int] ):
        ans = []
        cur.sort()
        while 0 < len( cur ):
            B = cur[ -1 ].b # greedy choice: the smallest segment end-point b
            ans.append( B )
            next = []
            for i in range( len( cur )):
                if not ( cur[ i ].a <= B and B <= cur[ i ].b ): # next is all (s)egments of cur which do NOT contain B
                    next.append( cur[ i ] )
            cur = next
        return ans

if __name__ == '__main__':
    solution = Solution()
    N = int( input() )
    S = []
    for _ in range( N ):
        a, b = map( int, input().split() )
        S.append( Segment( a,b ))
    ans = solution.minPoints( S )
    print( len( ans ))
    for x in ans:
        print( x, end=" " )
