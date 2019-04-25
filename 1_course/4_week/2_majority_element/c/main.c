/**
 *
 * C implementation of majority element
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>

typedef int Type;
typedef Type* HType;

Type hasMajorityElement( HType A, Type N ){
    Type me = 0;
    for( size_t i=( 0 ), cnt=( 0 ); i < N; cnt=(( me == A[ i++ ] )? ( cnt + 1 ) : ( cnt - 1 )) )
        if( cnt == 0 )
            me = A[ i ];
    int cnt = 0,
        T = ( N / 2 ) + 1;
    for( size_t i=( 0 ); i < N; ++i )
        if( me == A[ i ] )
            ++cnt;
    return( T <= cnt );
}

int main() {
    Type N = 0;
    scanf( "%d", &N );
    Type A[ N ];
    for( size_t i=( 0 ); i < N; scanf( "%d", &A[ i++ ] ));
    Type ans = hasMajorityElement( A, N );
    printf( "%d", ans );
    return 0;
}