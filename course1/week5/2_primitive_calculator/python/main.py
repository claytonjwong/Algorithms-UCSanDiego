# python3

##
#
# Python3 implementation to find the minimum amount of operations on a primitive calculator to obtain N
# The primitive calculator has 3 operations: multiply by 2, multiply by 3, and add by 1
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List, Dict

Type = int
INF = 1000001
Memo = Dict[ Type,Type ]

class RECSolution:
    def minOps( self, N: Type, memo: Memo={} ) -> Type:
        return self.go( N, memo )
    def go( self, N: Type, memo: Memo, ans: Type=INF ) -> Type:
        if N == 1:
            return 0
        if N in memo:
            return memo[ N ]
        if N % 2 == 0:
            ans = min( ans, 1 + self.go( N // 2, memo ))
        if N % 3 == 0:
            ans = min( ans, 1 + self.go( N // 3, memo ))
        return min( ans, 1 + self.go( N - 1, memo ))
class DPSolution:
    def minOps( self, N: Type ) -> Type:
        dp = [ INF ] * ( N+1 )
        dp[ 1 ] = 0
        for i in range( 2, N+1 ):
            if i % 2 == 0:
                dp[ i ] = min( dp[ i ], 1 + dp[ i // 2 ] )
            if i % 3 == 0:
                dp[ i ] = min( dp[ i ], 1 + dp[ i // 3 ] )
            dp[ i ] = min( dp[ i ], 1 + dp[ i - 1 ] )
        return dp[ N ]

if __name__ == '__main__':
    rec_solution = RECSolution()
    dp_solution = DPSolution()
    N = int( input() )
    rec_ans = rec_solution.minOps( N )
    dp_ans = dp_solution.minOps( N )
    assert( rec_ans == dp_ans )
    print( rec_ans )
