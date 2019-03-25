# python3

##
#
# C++ implementation to find the most valuable combination of items using a fractional knapsack
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

from typing import List
from collections import namedtuple

Item = namedtuple( "Item", "V W" )

def comparator( item: Item ) -> float:
    return item.V / item.W

class Solution:
    def maxValue( self, items: List[Item], W: int ) -> float:
        ans = 0
        items.sort( key=comparator, reverse=True )
        for item in items:
            if W == 0:
                break
            if item.W <= W:
                ans += item.V
                W -= item.W
            else:
                fraction = W / item.W
                ans += fraction * item.V
                W = 0
        return ans

if __name__ == '__main__':
    solution = Solution()
    N, W = map( int, input().split() )
    items = []
    for _ in range( N ):
        Vi, Wi = map( int, input().split() )
        item = Item( Vi, Wi )
        items.append( item )
    ans = solution.maxValue( items, W )
    print( "%.4f" % ans )
