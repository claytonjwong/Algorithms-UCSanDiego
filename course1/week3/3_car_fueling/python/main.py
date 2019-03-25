# python3

##
#
# Python3 implementation to find the most valuable combination of items using a fractional knapsack
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

class Solution:
    def minRefills( self, S, N, reach ):
        ans = 0
        i = 0
        T = N-1 # (T)arget index
        while i < T:
            j = i
            while j+1 < N and S[j+1] - S[i] <= reach:
                j += 1
            if j == i:
                return -1 # ran out of gas
            ans += 1 if j < T else 0
            i = j
        return ans

if __name__ == '__main__':
    target = int( input() )
    reach = int( input() )
    N = int( input() ) + 2 # +1 for the beginning stop and +1 for the target stop
    stops = [ 0 ]
    stops.extend( map( int, input().split() ))
    stops.append( target )
    solution = Solution()
    ans = solution.minRefills( stops, N, reach )
    print( ans )
