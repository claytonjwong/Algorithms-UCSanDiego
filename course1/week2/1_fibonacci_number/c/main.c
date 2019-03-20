/**
 *
 * C implementation to calculate the N-th Fibonacci number
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define TOP_DOWN    69
#define BOTTOM_UP   96

typedef int Type;
typedef Type* HType;
const Type INF = INT_MAX;


#ifdef TOP_DOWN

HType createMemo( Type );
void destroyMemo();
Type fibonacci( Type );
Type go( Type, HType );

HType createMemo( Type N ){
    HType memo = ( HType ) malloc(( N+1 ) * sizeof( Type ));
    for( int i = 0; i <= N; ++i )
        memo[ i ] = INF;
    return memo;
}

void destroyMemo( HType memo ){
    free( memo );
}

Type fibonacci_top_down( Type N ){
    HType memo = createMemo( N );
    Type res = go( N, memo );
    destroyMemo( memo );
    return res;
}

Type go( Type N, HType memo ){
    if( memo[ N ] != INF )
        return memo[ N ];
    if( N < 2 )
        return memo[ N ] = N;
    return memo[ N ] = go( N-2, memo ) + go( N-1, memo );
}

#endif

#ifdef BOTTOM_UP

Type fibonacci_bottom_up( Type N ){
    if( N < 2 )
        return N;
    Type dp[ N+1 ];
    dp[ 0 ] = 0;
    dp[ 1 ] = 1;
    for( int i = 2; i <= N; ++i )
        dp[ i ] = dp[ i-2 ] + dp[ i-1 ];
    return dp[ N ];
}

#endif


int main(){
    Type N = 0;
    scanf( "%d", &N );
    Type ans_top_down = fibonacci_top_down( N ),
        ans_bottom_up = fibonacci_bottom_up( N );
    assert( ans_top_down == ans_bottom_up );
    printf( "%d\n", ans_top_down );
    return 0;
}
