# python3

##
#
# Python implementation to determine tree height
# 
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

import queue

class TreeNode:
    def __init__( self, val: int ):
        self.val = int( val )
        self.children = []

class Solution:
    def height( self, root: TreeNode, D: int=0 ) -> int:
        if not root:
            return 0
        cur = queue.Queue()
        cur.put( root )
        while not cur.empty():
            D += 1
            next = queue.Queue()
            while not cur.empty():
                front = cur.get()
                for child in front.children:
                    next.put( child )
            cur = next
        return D
        
# RecursionError: maximum recursion depth exceeded
# class Solution:
#     def height( self, root: TreeNode ) -> int:
#         return self.go( root )
#     def go( self, root: TreeNode, D: int=1 ) -> int:
#         if not root:
#             return 0
#         maxD = D
#         for child in root.children:
#             maxD = max( maxD, self.go( child, D + 1 ) )
#         return maxD

if __name__ == '__main__':
    N = int( input() )
    A = list( map( TreeNode, range( N ) ) )
    for child, parent in enumerate( list( map( int, input().split() ) ) ):
        if 0 <= parent:
            A[ parent ].children.append( A[ child ] )
        else:
            root = A[ child ]
    solution = Solution()
    ans = solution.height( root )
    print( ans )
