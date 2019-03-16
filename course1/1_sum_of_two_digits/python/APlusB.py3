# python3

##
#
# Python implementation to sum two integers
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##


def sum_of_two_digits( first, second ):
    return first + second

if __name__ == '__main__':
    a, b = map( int, input().split() )
    print( sum_of_two_digits( a, b ) )
