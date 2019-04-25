# python3

##
#
# Python3 implementation to find the edit distance between 2 strings
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

class Solution:
    def editDistance( self, A: str, B: str ) -> int:
        M, N = len( A ), len( B )
        dp = [[ 0 ] * ( N+1 ) for _ in range( M+1 )]
        for i in range( 1, M+1 ):
            dp[ i ][ 0 ] = i
        for j in range( 1, N+1 ):
            dp[ 0 ][ j ] = j
        for i in range( 1, M+1 ):
            for j in range( 1, N+1 ):
                cost = 0 if A[ i-1 ] == B[ j-1 ] else 1
                dp[ i ][ j ] = min(
                    dp[ i-1 ][ j-1 ] + cost,
                    dp[ i-1 ][ j ] + 1,
                    dp[ i ][ j-1 ] + 1,
                )
        return dp[ M ][ N ]

if __name__ == '__main__':
    solution = Solution()
    A, B = input(), input()
    ans = solution.editDistance( A, B )
    print( ans )
