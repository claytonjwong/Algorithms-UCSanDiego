# python3

##
#
# Python3 implementation of quick sort with 3-way partition
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

import random
from typing import List

class Solution:
    def quickSort( self, A: List[int] ):
        self.go( A, 0, len(A) )
    def go( self, A: List[int], L: int, R: int ):
        if R - L < 2:
            return
        P = random.randint( L, R-1 ) # R is non-inclusive
        A[ L ], A[ P ] = A[ P ], A[ L ]
        M1, M2 = self.partition3( A, L, R )
        self.go( A, L, M1 )
        self.go( A, M2, R )
    def partition( self, A: List[int], L: int, R: int ):
        threshold = A[ L ]
        less = L + 1
        more = less
        while more != R:
            if A[ more ] < threshold:
                A[ less ], A[ more ] = A[ more ], A[ less ]
                less += 1
            more += 1
        pivot = less - 1
        A[ L ], A[ pivot ] = A[ pivot ], A[ L ]
        return pivot
    def partition3( self, A: List[int], L: int, R: int ):
        P = self.partition( A, L, R )
        M1 = P
        M2 = P
        i = R - 1
        while M2 < i:
            if A[ i ] == A[ P ]:
                A[ M2 ], A[ i ] = A[ i ], A[ M2 ]
                M2 += 1
            else:
                i -= 1
        return M1, M2
        
if __name__ == '__main__':
    N = input()
    A = list( map( int, input().split() ))    
    Solution().quickSort( A )
    for x in A:
        print( x, end=" " )
