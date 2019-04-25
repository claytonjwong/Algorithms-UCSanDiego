# python3

##
#
# Python3 implementation of max stack [ retrieve maximum value in O(1) time ]
#
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

class Stack:
    def __init__( self ):
        self.stack_ = []
        self.max_ = []
    def push( self, val: int ) -> None:
        self.stack_.append( val )
        if len( self.max_ ) == 0 or self.max_[ -1 ] <= val:
            self.max_.append( val )
    def pop( self ) -> None:
        result = self.stack_[ -1 ]
        self.stack_.pop()
        if result == self.max_[ -1 ]:
            self.max_.pop()
    def max( self ) -> int:
        return self.max_[ -1 ]

if __name__ == '__main__':
    stack = Stack()
    N = int( input() )
    while 0 < N:
        line = input()
        if 0 <= line.find( "push" ):
            cmd, val = line.split()
            val = int( val )
            stack.push( val )
        elif 0 <= line.find( "pop" ):
            stack.pop()
        elif 0 <= line.find( "max" ):
            print( stack.max() )
        N -= 1
