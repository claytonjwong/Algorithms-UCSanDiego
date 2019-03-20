# python3

##
#
# Python implementation to find the N-th fibonacci number
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

INF = 999999999

def fibonacci_top_down( N ):
    memo = ( N+1 ) * [ INF ]
    return go( N, memo )

def go( N, memo ):
    if memo[ N ] != INF:
        return memo[ N ]
    if N < 2:
        memo[ N ] = N
    else:        
        memo[ N ] = go( N-2, memo ) + go( N-1, memo )
    return memo[ N ]

def fibonacci_bottom_up( N ):
    if N < 2:
        return N
    dp = ( N+1 ) * [ INF ]
    dp[ 0 ] = 0
    dp[ 1 ] = 1
    for i in range( 2, N+1 ):
        dp[ i ] = dp[ i-2 ] + dp[ i-1 ]
    return dp[ N ]

if __name__ == "__main__":
    N = int( input() )
    ans_top_down = fibonacci_top_down( N )
    ans_bottom_up = fibonacci_bottom_up( N )
    assert ans_top_down == ans_bottom_up, "! ( ans_top_down == ans_bottom_up )"
    print( ans_top_down )
