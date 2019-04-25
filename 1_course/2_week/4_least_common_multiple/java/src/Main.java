/**
 *
 * Java implementation to find the least common multiple between two numbers
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.Scanner;

public class Main {

    private static long gcd( long a, long b ){
        for( long t = 0; b != 0; ){
            t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    private static long lcm( long a, long b ){
        return a * b / gcd( a, b );
    }

    public static void main(String[] args){
        Scanner input = new Scanner( System.in );
        long a = input.nextLong(),
             b = input.nextLong(),
             ans = lcm( a, b );
        System.out.println( ans );
    }
}
