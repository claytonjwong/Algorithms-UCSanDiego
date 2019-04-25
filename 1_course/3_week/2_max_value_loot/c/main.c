/**
 *
 * C implementation to find the most valuable combination of items using a fractional knapsack
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>
#include <stdlib.h>

typedef int Type;

typedef struct {
    Type V, W;
} Item;

double ratio( Item item ){
    return( item.W > 0 )? ( double ) item.V / item.W : 0;
}

int comparator( const void* lhs, const void* rhs ){
    Item first = *( Item* ) lhs,
         second = *( Item* ) rhs;
    return( ratio( first ) < ratio( second ))?  1
        : ( ratio( first ) > ratio( second ))? -1
        : ( 0 );
}

double maxValue( Item* items, Type N, Type W ){
    double ans = 0;
    qsort( items, N, sizeof( Item ), comparator );
    for( int i=0; W > 0 && i < N; ++i ){
        Item item = items[ i ];
        if( item.W <= W ){ // item fits in knapsack
            ans += item.V;
            W -= item.W;
        } else {
            double fraction = ( double ) W / item.W;
            ans += fraction * item.V;
            W = 0;
        }
    }
    return ans;
}

int main() {
    Type N = 0,
         W = 0;
    scanf( "%d %d", &N, &W );
    Item items[ N ];
    for( Type i=0, Vi=0, Wi=0; i < N; ++i ){
        scanf( "%d %d", &Vi, &Wi );
        Item item = { .V = Vi, .W = Wi };
        items[ i ] = item;
    }
    double ans = maxValue( items, N, W );
    printf( "%.4lf\n", ans );
    return 0;
}
