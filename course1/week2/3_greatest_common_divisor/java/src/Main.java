/**
 *
 * Java implementation to find the greatest common divisor between two numbers
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.Scanner;

public class Main {

    private static int gcd( int a, int b ){
        for( int t = 0; b != 0; ){
            t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    public static void main(String[] args){
        Scanner input = new Scanner( System.in );
        int a = input.nextInt(),
            b = input.nextInt(),
            ans = gcd( a, b );
        System.out.println( ans );
    }
}
