# python3

##
#
# Python implementation to check brackets in code, return success if []{}() match,
# otherwise return 1-based index of first mismatching []{}()
# 
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List, Tuple

Pair = Tuple[ str,int ]
Stack = List[ Pair ]

class Solution:
    def match( self, A: str, stack: Stack=[], open: str="[{(", close: str="]})" ) -> int:
        i = 0
        for c in A:
            i += 1 # 1-based indexing
            open_index = open.find( c )
            close_index = close.find( c )
            if open_index == -1 and close_index == -1:
                continue
            if open_index != -1:
                stack.append(( close[ open_index ], i ))
            else:
                if not stack:
                    return i
                target, _ = stack[ -1 ]
                match_index = close.find( target )
                if c != close[ match_index ]:
                    return i
                stack.pop()
        return 0 if not stack else stack[ 0 ][ 1 ]

if __name__ == '__main__':
    solution = Solution()
    ans = solution.match( input() )
    print( "Success" ) if ans == 0 else print( ans )
