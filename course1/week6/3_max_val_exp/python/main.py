# python3

import re
from typing import List, Tuple
from collections import deque

class Solution:
    def maxValExp( self, D: List[int], op: List[int] ) -> int:
        N = len( D )
        if N == 0:
            return 0
        m = [[ 0 for _ in range( N ) ] for _ in range( N ) ]
        M = [[ 0 for _ in range( N ) ] for _ in range( N ) ]
        for i in range( 0, N ):
            m[ i ][ i ], M[ i ][ i ] = D[ i ], D[ i ]
        for s in range( 1, N ):
            for i in range( 0, N - s ):
                j = i + s
                mini, maxi = self.minMax( m, M, op, i, j )
                m[ i ][ j ] = mini
                M[ i ][ j ] = maxi
        return M[ 0 ][ N-1 ]
    def minMax( self, m: List[int], M: List[int], op: List[int], i: int, j: int ) -> Tuple[ int, int ]:
        mini = 777
        maxi = -777
        for k in range( i, j ):
            a = self.calc( M[ i ][ k ], op[ k ], M[ k+1 ][ j ] )
            b = self.calc( M[ i ][ k ], op[ k ], m[ k+1 ][ j ] )
            c = self.calc( m[ i ][ k ], op[ k ], M[ k+1 ][ j ] )
            d = self.calc( m[ i ][ k ], op[ k ], m[ k+1 ][ j ] )
            mini = min( mini, a,b,c,d )
            maxi = max( maxi, a,b,c,d )
        return mini, maxi
    def calc( self, first: int, op: int, second: int ) -> int:
        if op == '+':
            return first + second
        elif op == '-':
            return first - second
        elif op == '*':
            return first * second
        elif op == '/':
            return first / second
        else:
            return 0

Input = List[int], List[int]
def readInput() -> Input:
    exp = input()
    D = list( map( int, re.split( r"[+-\/\*]+", exp ) ) )
    op = deque( re.split( r"\d+", exp ) )
    op.popleft(), op.pop() # remove junk chars from re split
    return D, list( op )
if __name__ == '__main__':
    solution = Solution()
    D, op = readInput()
    ans = solution.maxValExp( D, op )
    print( ans )
