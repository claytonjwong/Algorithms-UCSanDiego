# python3

##
#
# Python implementation to find the maximum pairwise product of two integers
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##


if __name__ == '__main__':
    N = input()
    A = list( map( int, input().split() ))
    i = A.index( max( A ))
    first = A[ i ]
    A[ i ] = 0
    j = A.index( max( A ))
    second = A[ j ]
    print( first * second )
