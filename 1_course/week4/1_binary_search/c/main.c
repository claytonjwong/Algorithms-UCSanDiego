/**
 *
 * C implementation of binary search
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>

typedef int Type;
const Type NOT_FOUND = -1;

Type go( Type* A, Type T, size_t lo, size_t hi ){ // search A for (T)arget
    if( lo == hi )
        return NOT_FOUND;
    size_t P = ( lo + hi ) / 2;
    if( T < A[ P ] )
        return go( A, T, lo, P );
    if( T > A[ P ] )
        return go( A, T, P+1, hi );
    return P;
}
Type binarySearch( Type* A, Type T, size_t N ){
    return go( A, T, 0, N );
}

int main() {
    size_t N = 0;
    scanf( "%zu", &N );
    Type A[ N ];
    for( size_t i=0; i < N; scanf( "%d", &A[ i++ ] ));
    size_t M = 0;
    scanf( "%zu", &M );
    for( Type T = 0; M--; ){
        scanf( "%d", &T );
        Type ans = binarySearch( A, T, N );
        printf( "%d ", ans );
    }
    return 0;
}
