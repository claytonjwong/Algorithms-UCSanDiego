/**
 *
 * Java implementation to sum two integers
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.Scanner;

class APlusB {

    static int sumOfTwoDigits( int first, int second ){
        return first + second;
    }

    public static void main( String[] args ){
        Scanner s = new Scanner( System.in );
        int a = s.nextInt();
        int b = s.nextInt();
        System.out.println( sumOfTwoDigits( a, b ) );
    }
}
