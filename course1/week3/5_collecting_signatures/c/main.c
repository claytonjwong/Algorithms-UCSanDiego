/**
 *
 * C implementation to collect signatures
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>
#include <stdlib.h>

typedef int Type;
typedef Type* HType;

const Type INF = 1e9 + 1;

typedef struct {
    Type a, b;
} Segment;
Segment createSegment( Type a, Type b ){
    Segment S;
    S.a = a;
    S.b = b;
    return S;
}
typedef Segment* HSegment;

int comparator( const void* lhs, const void* rhs ){ // descending order of segment end-point b
    Segment first  = *( HSegment ) lhs,
            second = *( HSegment ) rhs;
    if( first.b == second.b )
        return( first.a < second.a )? 1 : -1;
    return( first.b < second.b )? 1 : -1;
}

void minPoints( HSegment cur, Type N, HType ans ){
    size_t w = 0; // (w)rite index into (ans)wer
    for( size_t i=0; i < N; ++i )
        ans[ i ] = INF;
    qsort( cur, N, sizeof( Segment ), comparator );
    for( Segment next[ N ]; 0 < N; ){
        Type B = cur[ N-1 ].b; // greedy choice: the smallest segment end-point b
        ans[ w++ ] = B;
        size_t x = 0; // write index into ne(x)t
        for( size_t i=0; i < N; ++i ) if( ! ( cur[ i ].a <= B && B <= cur[ i ].b )) // next is all (s)egments of cur which do NOT contain B
            next[ x++ ] = cur[ i ];
        N = x;
        for( int i=0; i< N; ++i )
            cur[ i ] = next[ i ];
    }
}

int main() {
    Type N = 0; scanf( "%d", &N );
    Segment S[ N ];
    for( Type i=0, a=0, b=0; i < N; ++i ){
        scanf( "%d %d", &a, &b );
        S[ i ] = createSegment( a, b );
    }
    Type ans[ N ];
    minPoints( S, N, ans );
    int x = 0;
    for(; ans[ x ] != INF; ++x ); // x is the first invalid index
    printf( "%d\n", x );
    for( size_t i=0; i < x; ++i )
        printf( "%d ", ans[ i ] );
    printf( "\n" );
    return 0;
}
