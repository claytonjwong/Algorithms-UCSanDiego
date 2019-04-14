# python3

##
#
# Python3 implementation to find the longest common subsequence between two strings
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List, Dict

class RECSolution:
    Memo = Dict[ int,int ]
    def hash( self, i: int, j: int ) -> int:
        return 101 * i + j
    def lcs( self, A: List[int], B: List[int], M: int, N: int, memo: Memo={} ) -> int:
        return self.go( A, B, M-1, N-1, memo )
    def go( self, A: List[int], B: List[int], i: int, j: int, memo: Memo ) -> int:
        key = self.hash( i,j )
        if i < 0 or j < 0:
            memo[ key ] = 0
        if key in memo:
            return memo[ key ]
        if A[ i ] == B[ j ]:
            memo[ key ] = 1 + self.go( A, B, i-1, j-1, memo )
        else:
            memo[ key ] = max( self.go( A, B, i-1, j, memo ), self.go( A, B, i, j-1, memo ))
        return memo[ key ]

class DPSolution:
    def lcs( self, A: List[int], B: List[int], M: int, N: int ) -> int:
        dp = [[ 0 ] * ( N+1 ) for _ in range( M+1 ) ]
        for i in range( 1, M+1 ):
            for j in range( 1, N+1 ):
                if A[ i-1 ] == B[ j-1 ]:
                    dp[ i ][ j ] = 1 + dp[ i-1 ][ j-1 ]
                else:
                    dp[ i ][ j ] = max( dp[ i-1 ][ j ], dp[ i ][ j-1 ] )
        return dp[ M ][ N ]

if __name__ == '__main__':
    rec_solution = RECSolution()
    dp_solution = DPSolution()
    M, A = int( input() ), list( map( int, input().split() ))
    N, B = int( input() ), list( map( int, input().split() ))
    ans1 = rec_solution.lcs( A, B, M, N )
    ans2 = dp_solution.lcs( A, B, M, N )
    assert( ans1 == ans2 )
    print( ans1 )
