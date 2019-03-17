/**
 *
 * C implementation to sum two integers
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>

int sum_of_two_digits( int first, int second ){
    return first + second;
}

int main(){
    int a = 0, b = 0;
    scanf( "%d%d", &a, &b );
    printf( "%d\n", sum_of_two_digits( a, b ));
    return 0;
}
