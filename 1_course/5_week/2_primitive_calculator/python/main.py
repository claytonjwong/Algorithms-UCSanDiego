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
Collection = List[ Type ]

def reconstruct( N: Type, memo: Memo={}, A: Collection=[] ) -> Collection:
    while 0 < N:
        A.insert( 0, N )
        prev3 = memo[ N // 3 ] if N % 3 == 0 and N // 3 in memo else INF
        prev2 = memo[ N // 2 ] if N % 2 == 0 and N // 2 in memo else INF
        prev1 = memo[ N - 1  ] if N - 1 >= 0 and N - 1  in memo else INF
        prev = min( prev3, prev2, prev1 )
        if prev == prev3:
            N //= 3
        elif prev == prev2:
            N //= 2
        elif prev == prev1:
            N -= 1
    return A

class RECSolution:
    def minOps( self, N: Type, memo: Memo={} ) -> Type:
        self.go( N, memo )
        return reconstruct( N, memo )
    def go( self, N: Type, memo: Memo, ans: Type=INF ) -> Type:
        if N < 2:
            memo[ N ] = 0
        if N in memo:
            return memo[ N ]
        if N % 2 == 0:
            ans = min( ans, 1 + self.go( N // 2, memo ))
        if N % 3 == 0:
            ans = min( ans, 1 + self.go( N // 3, memo ))
        memo[ N ] = min( ans, 1 + self.go( N - 1, memo ))
        return memo[ N ]
class DPSolution:
    def minOps( self, N: Type, memo: Memo={1:0} ) -> Type:
        dp = [ INF ] * ( N+1 )
        dp[ 1 ] = 0
        for i in range( 2, N+1 ):
            if i % 2 == 0:
                dp[ i ] = min( dp[ i ], 1 + dp[ i // 2 ] )
            if i % 3 == 0:
                dp[ i ] = min( dp[ i ], 1 + dp[ i // 3 ] )
            memo[ i ] = dp[ i ] = min( dp[ i ], 1 + dp[ i - 1 ] )
        return reconstruct( N, memo )

if __name__ == '__main__':
    dp_solution = DPSolution()
    N = int( input() )
    A = dp_solution.minOps( N )
    print( len(A) - 1 )
    print( A )
    rec_solution = RECSolution()
    A1 = rec_solution.minOps( N )
    assert( A1 == A )
