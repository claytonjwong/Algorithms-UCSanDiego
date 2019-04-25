/**
 *
 * C implementation to calculate the sum mod 10 of L,L+1,...,N-1,N-th fibonacci number
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>

typedef unsigned long long Type;

Type sum( Type* dp, Type N, Type M, Type L ){
    Type ans = 0;
    for( Type i = L; i <= N; ++i )
        ans += dp[ i ],
        ans %= M;
    return ans;
}

Type fibonacci( Type N, Type M, Type L ){
    Type dp[ (6*M)+2 ];
    dp[ 0 ] = 0;
    dp[ 1 ] = 1;
    dp[ 2 ] = 1;
    Type i = 3; // start looking for the pisano period from i=3 to ignore the first 0,1 sequence at dp[ 0 ] and dp[ 1 ]
    for(; i <= N && ! ( dp[ i-2 ] == 0 && dp[ i-1 ] == 1 ); ++i )
        dp[ i ] = ( dp[ i-2 ] + dp[ i-1 ] ) % M;
    Type P = i-2;                                   // (P)isano period
    return( N <= i-1 )? sum( dp, N,     M, L     )  // case 1) (P)isano period NOT reached, return the sum % M of N-th fibonacci number
                      : sum( dp, N % P, M, L % P ); // case 2) (P)isano period reached, return the sum % M of (N mod P)-th fibonacci number
}

int main(){
    Type N = 0,
         M = 10,
         L = 0;
    scanf( "%llu %llu", &L, &N );
    Type ans = fibonacci( N, M, L );
    printf( "%llu\n", ans );
    return 0;
}
