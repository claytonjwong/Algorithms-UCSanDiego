# python3

##
#
# Python3 implementation to find the maximum knapsack
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List, Dict

Memo = Dict[ int,int ]

class RECSolution:
    def hash( self, T: int, i: int ) -> int:
        return T + 10001 * i
    def maxKnapsack( self, A: List[int], T: int, memo: Memo={} ) -> int:
        N = len( A )
        return self.go( A, T, N-1, memo )
    def go( self, A: List[int], T: int, i: int, memo: Memo ) -> int:
        key = self.hash( T,i )
        if key in memo:
            return memo[ key ]
        if i < 0:
            memo[ i ] = 0
            return memo[ i ]
        w = A[ i ] + self.go( A, T - A[ i ], i-1, memo ) if 0 <= T - A[ i ] else 0
        wo = self.go( A, T, i-1, memo )
        memo[ key ] = max( w, wo ) # max( with, without )
        return memo[ key ]

class DPSolution:
    def maxKnapsack( self, A: List[int], T: int ):
        N = len( A )
        dp = [[ 0 for _ in range( T+1 )] for _ in range( N+1 )]
        for i in range( 1, N+1 ):
            for j in range( 1, T+1 ):
                if 0 <= j - A[ i-1 ]:
                    dp[ i ][ j ] = max( A[ i-1 ] + dp[ i-1 ][ j - A[ i-1 ]], dp[ i-1 ][ j ] ) # max( with, without )
                else:
                    dp[ i ][ j ] = dp[ i-1 ][ j ] # without
        return dp[ N ][ T ]

if __name__ == '__main__':
    T, N = map( int, input().split() )
    A = list( map( int, input().split() ))
    ans1 = RECSolution().maxKnapsack( A, T )
    ans2 = DPSolution().maxKnapsack( A, T )
    assert( ans1 == ans2 )
    print( ans1 )
