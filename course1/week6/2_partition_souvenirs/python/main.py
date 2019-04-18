# python3

##
#
# Python3 implementation to determine if a list of integers can be partitioned into 3 equal sums
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List

class Solution:
    def canPartition( self, A: List[int] ) -> bool:
        total = sum( A )
        if total % 3 != 0:
            return False
        return self.go( A, total // 3 )
    def go( self, A: List[int], T: int, P: List[int]=[0,0,0], i: int=0 ) -> bool: # (A)rray to partition and (T)arget value of each (P)art
        if i == len( A ):
            return P[ 0 ] == T and P[ 1 ] == T and P[ 2 ] == T
        for j in range( 0, len( P ) ):
            P[ j ] += A[ i ]
            if P[ j ] <= T and self.go( A, T, P, i+1 ):
                return True
            P[ j ] -= A[ i ]
        return False

if __name__ == '__main__':
    N = input()
    A = list( map( int, input().split() ) )
    solution = Solution()
    ans = solution.canPartition( A )
    print( int( ans ) )
