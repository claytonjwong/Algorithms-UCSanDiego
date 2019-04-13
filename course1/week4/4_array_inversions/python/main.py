# python3

##
#
# Python3 implementation to count array inversions
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List

Result = List[int], int

class Solution:
    def inversions( self, A: List[int] ) -> Result:
        A, cnt = self.go( A, 0, len(A) )
        return cnt
    def go( self, A: List[int], L: int, R: int ) -> Result:
        size = ( R - L )
        if size < 2:
            return A[L:R], 0
        mid = L + ( size // 2 )
        A1, cnt1 = self.go( A, L, mid )
        A2, cnt2 = self.go( A, mid, R )
        A3, cnt3 = self.merge( A1, A2 )
        return A3, cnt1 + cnt2 + cnt3
    def merge( self, A: List[int], B: List[int] ) -> Result:
        C = []
        i = 0
        j = 0
        cnt = 0
        while i < len(A) and j < len(B):
            if A[i] <= B[j]:
                C.append( A[i] )
                i += 1
            else:
                C.append( B[j] )
                j += 1
                cnt += len( A[i:] )
        C.extend( A[i:] )
        C.extend( B[j:] )
        return C, cnt

if __name__ == '__main__':
    solution = Solution()
    N = input()
    A = list( map( int, input().split() ))
    ans = solution.inversions( A )
    print( ans )
