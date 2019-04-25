/**
 *
 * C implementation to find the minimum number of coins needed to change the input value ( an integer )
 * into coins with denominations 1, 5, and 10
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>

typedef int Type;

Type coin_change( Type N ){
    Type ans = 0;
    for( int C[ 3 ]={ 10, 5, 1 }, i=0; i < 3; ++i )
        for(; N >= C[ i ]; N -= C[ i ], ++ans );
    return ans;
}

int main(){
    Type N = 0;
    scanf( "%d", &N );
    Type ans = coin_change( N );
    printf( "%d\n", ans );
    return 0;
}
