# python3

##
#
# Python implementation to find the N mod M-th fibonacci number
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

def sum( dp, N, M ):
    ans = 0
    for i in range( 0, N+1 ):
        ans += dp[ i ]
        ans %= M
    return ans

def fibonacci( N, M ):
    dp = ( (6*M)+2 ) * [ 0 ]
    dp[ 0 ] = 0
    dp[ 1 ] = 1
    dp[ 2 ] = 1
    i = 3 # start looking for the pisano period from i=3 to ignore the first 0,1 sequence at dp[ 0 ] and dp[ 1 ]
    while i <= N and not ( dp[ i-2 ] == 0 and dp[ i-1 ] == 1 ):
        dp[ i ] = ( dp[ i-2 ] + dp[ i-1 ] ) % M
        i += 1
    P = i-2 # (P)isano period
    # case 1) (P)isano period NOT reached, return the N-th fibonacci number
    # case 2) (P)isano period reached, return (N mod P)-th fibonacci number
    ans = sum( dp, N, M ) if N <= i-1 else sum( dp, N % P, M )
    return ans

if __name__ == '__main__':
    N = int( input() )
    M = 10
    ans = fibonacci( N, M )
    print( ans )
