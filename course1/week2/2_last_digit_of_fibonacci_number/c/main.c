/**
 *
 * C implementation to calculate the last digit of a large Fibonacci number
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef int Type;
const Type INF = INT_MAX;

Type fibonacci( Type N ){
    if( N < 2 )
        return N;
    Type dp[ N+1 ];
    dp[ 0 ] = 0;
    dp[ 1 ] = 1;
    for( int i = 2; i <= N; ++i )
        dp[ i ] = ( dp[ i-2 ] + dp[ i-1 ] ) % 10;
    return dp[ N ];
}

int main(){
    Type N = 0;
    scanf( "%d", &N );
    Type ans = fibonacci( N );
    printf( "%d\n", ans );
    return 0;
}
