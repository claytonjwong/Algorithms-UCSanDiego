# python3

##
#
# Python3 implementation to find the longest common subsequence between three strings
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List, Dict

class RECSolution:
    Memo = Dict[ int,int ]
    def hash( self, i: int, j: int, k: int ) -> int:
        return 101 * 101 * i + 101 * j + k
    def lcs( self, A: List[int], B: List[int], C: List[int], M: int, N: int, O: int, memo: Memo={} ) -> int:
        return self.go( A, B, C, M-1, N-1, O-1, memo )
    def go( self, A: List[int], B: List[int], C: List[int], i: int, j: int, k: int, memo: Memo ) -> int:
        key = self.hash( i,j,k )
        if i < 0 or j < 0 or k < 0:
            memo[ key ] = 0
        if key in memo:
            return memo[ key ]
        if A[ i ] == B[ j ] and A[ i ] == C[ k ]:
            memo[ key ] = 1 + self.go( A, B, C, i-1, j-1, k-1, memo )
        else:
            memo[ key ] = max(
                self.go( A, B, C, i-1, j, k, memo ),
                self.go( A, B, C, i, j-1, k, memo ),
                self.go( A, B, C, i, j, k-1, memo ), )
        return memo[ key ]

class DPSolution:
    def lcs( self, A: List[int], B: List[int], C: List[int], M: int, N: int, O: int ) -> int:
        dp = [[[ 0 for _ in range( O+1 )] for _ in range( N+1 )] for _ in range( M+1 ) ]
        for i in range( 1, M+1 ):
            for j in range( 1, N+1 ):
                for k in range( 1, O+1 ):
                    if A[ i-1 ] == B[ j-1 ] and A[ i-1 ] == C[ k-1 ]:
                        dp[ i ][ j ][ k ] = 1 + dp[ i-1 ][ j-1 ][ k-1 ]
                    else:
                        dp[ i ][ j ][ k ] = max(
                            dp[ i-1 ][ j ][ k ],
                            dp[ i ][ j-1 ][ k ],
                            dp[ i ][ j ][ k-1 ], )
        return dp[ M ][ N ][ O ]

if __name__ == '__main__':
    rec_solution = RECSolution()
    dp_solution = DPSolution()
    M, A = int( input() ), list( map( int, input().split() ))
    N, B = int( input() ), list( map( int, input().split() ))
    O, C = int( input() ), list( map( int, input().split() ))
    ans1 = rec_solution.lcs( A, B, C, M, N, O )
    ans2 = dp_solution.lcs( A, B, C, M, N, O )
    assert( ans1 == ans2 )
    print( ans1 )
