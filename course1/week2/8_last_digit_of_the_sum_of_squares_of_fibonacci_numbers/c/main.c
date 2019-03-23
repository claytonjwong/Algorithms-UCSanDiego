/**
 *
 * C implementation to calculate the sum mod 10 of the squared 1^2,2^2,...,(N-1)^2,(N-th)^2 fibonacci numbers
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>

typedef unsigned long long Type;

Type sum( Type* dp, Type N, Type M ){
    return( N > 0 )? ( dp[ N-1 ] * dp[ N ] ) % M : 0;
}

Type fibonacci( Type N, Type M ){
    ++N; // the sum of squared fibonacci numbers from 0 to N is equal to fib( N ) * fib( N+1 ), so iterate till fib( N+1 )
    Type dp[ (6*M)+2 ];
    dp[ 0 ] = 0;
    dp[ 1 ] = 1;
    dp[ 2 ] = 1;
    Type i = 3; // start looking for the pisano period from i=3 to ignore the first 0,1 sequence at dp[ 0 ] and dp[ 1 ]
    for(; i <= N && ! ( dp[ i-2 ] == 0 && dp[ i-1 ] == 1 ); ++i )
        dp[ i ] = ( dp[ i-2 ] + dp[ i-1 ] ) % M;
    Type P = i-2;                            // (P)isano period
    return( N <= i-1 )? sum( dp, N,     M )  // case 1) (P)isano period NOT reached, return the sum % M of N-th fibonacci number
                      : sum( dp, N % P, M ); // case 2) (P)isano period reached, return the sum % M of (N mod P)-th fibonacci number
}

int main(){
    Type N = 0,
         M = 10;
    scanf( "%llu", &N );
    Type ans = fibonacci( N, M );
    printf( "%llu\n", ans );
    return 0;
}
