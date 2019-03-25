/**
 *
 * C implementation to find the car fueling problem
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>

typedef int Type;
typedef Type* Collection;

Type minRefills( Collection S, Type N, Type reach ){
    Type ans = 0,
         T = N-1; // (T)arget index
    for( int i=0, j=i; i < T; i=j ){
        for( j=i; j+1 < N && S[j+1] - S[i] <= reach; ++j ); // increment j to farthest reachable stop
        if( j == i )
            return -1; // ran out of gas
        ans +=( j < T )? 1 : 0;
    }
    return ans;
}

int main() {
    Type target = 0,
         reach = 0,
         N = 0;
    scanf( "%d %d %d", &target, &reach, &N );
    N += 2; // +1 for the beginning stop and +1 for the target stop
    Type stops[ N ];
    stops[ 0 ] = 0;
    for( int i=1, stop=0; i+1 < N; scanf( "%d", &stop ), stops[ i++ ]=stop );
    stops[ N-1 ] = target;
    Type ans = minRefills( stops, N, reach );
    printf( "%d\n", ans );
    return 0;
}
