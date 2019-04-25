/**
 *
 * C implementation to calculate the least common multiple between two numbers
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>

typedef size_t Type;

Type gcd( Type a, Type b ){
    for( Type t = 0; b != 0; ){
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

Type lcm( Type a, Type b ){
    return a * b / gcd( a, b );
}

int main(){
    Type a = 0,
         b = 0;
    scanf( "%ld %ld", &a, &b );
    Type ans = lcm( a, b );
    printf( "%ld\n", ans );
    return 0;
}
