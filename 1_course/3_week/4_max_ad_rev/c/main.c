/**
 *
 * C implementation to find the maximum advertising revenue
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>
#include <stdlib.h>

typedef long long Type;
typedef Type* HType;

int comparator( const void* lhs, const void* rhs ){
    Type first  = *( HType ) lhs,
         second = *( HType ) rhs;
    return( first < second )? -1
        : ( first > second )?  1
        : ( 0 );
}

Type maxAdRev( HType A, HType B, Type N ){
    Type ans = 0;
    qsort( A, N, sizeof( Type ), comparator );
    qsort( B, N, sizeof( Type ), comparator );
    for( int i=0; i < N; ++i )
        ans += A[ i ] * B[ i ];
    return ans;
}

int main() {
    Type N = 0;
    scanf( "%lld", &N );
    Type A[ N ],
         B[ N ];
    for( Type i=0; i < N; scanf( "%lld", &A[ i++ ] ));
    for( Type i=0; i < N; scanf( "%lld", &B[ i++ ] ));
    Type ans = maxAdRev( A, B, N );
    printf( "%lld\n", ans );
    return 0;
}
