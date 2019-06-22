/**
 *
 * C implementation of Counting Sort ( a stable sort with linear asymptotic time + memory ) note: not in-place sort
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>
#include <strings.h>

int main() {
    const char null = '\0';
    const char* alpha = "ACGT";
    const size_t N = 1e3,
                 M = strlen( alpha );
    char S[ N ] = { null }; scanf( "%s", S );
    size_t C[ 'T' + 1 ] = { 0 }; { // (C)ount of character instances in S
        for( int i=0; i < N && S[ i ] != null; ++i ){
            char ch = S[ i ];
            ++C[ ch ];
        }
    }
    char A[ N ] = { null }; { // (A)rray of characters from S in sorted order
        int i=0;
        for( int j=0; j < M; ++j ){
            char ch = alpha[ j ];
            while( C[ ch ]-- )
                A[ i++ ] = ch;
        }
    }
    for( int i=0; i < N && A[ i ] != null; printf( "%c", A[ i++ ] ) ); printf( "\n" );
    return 0;
}
