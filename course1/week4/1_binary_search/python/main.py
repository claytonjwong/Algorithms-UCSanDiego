# python3

##
#
# Python3 implementation of binary search
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List

NOT_FOUND = -1

class Solution:
    def binarySearch( self, A: List[int], T: int ) -> List[int]:
        return self.go( A, T, 0, len( A ))
    def go( self, A: List[int], T: int, lo: int, hi: int ) -> List[int]:
        if lo == hi:
            return NOT_FOUND
        P = int(( lo + hi ) / 2 )
        if T < A[ P ]:
            return self.go( A, T, lo, P )
        if T > A[ P ]:
            return self.go( A, T, P+1, hi )
        return P

if __name__ == '__main__':
    solution = Solution()
    A = list( map( int, input().split() ))
    N = A[ 0 ]
    A.pop( 0 )
    T = list( map( int, input().split() ))
    M = T[ 0 ]
    T.pop( 0 )
    for i in range( 0, M ):
        ans = solution.binarySearch( A, T[ i ] )
        print( ans, end=" " )
