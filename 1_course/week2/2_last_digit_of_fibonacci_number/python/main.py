# python3

##
#
# Python implementation to find the last digit of a large fibonacci number
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

INF = 999999999

def fibonacci( N ):
    if N < 2:
        return N
    dp = ( N+1 ) * [ INF ]
    dp[ 0 ] = 0
    dp[ 1 ] = 1
    for i in range( 2, N+1 ):
        dp[ i ] = ( dp[ i-2 ] + dp[ i-1 ] ) % 10
    return dp[ N ]

if __name__ == "__main__":
    N = int( input() )
    ans = fibonacci( N )
    print( ans )
