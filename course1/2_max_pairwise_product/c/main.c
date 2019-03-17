/**
 * 
 * C implementation to find the maximum pairwise product of two integers
 * 
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 * 
 **/ 

#include <stdio.h>

typedef long long Type;

Type find( Type* A, size_t N ){
    size_t i = 0;
    for( size_t j = 1; j < N; ++j )
        if( A[ i ] < A[ j ] )
            i = j;
    Type val = A[ i ];
    A[ i ] = 0; // "remove" (val)ue from A
    return val;
}

int main(){
    size_t N = 0;
    scanf( "%d", &N );
    Type A[ N ];
    for( size_t i = 0; i < N; ++i )
        scanf( "%lld", &A[ i ] );
    printf( "%lld", find( A, N ) * find( A, N ) );
    return 0;
}
