/**
 *
 * Java implementation to calculate the sum mod 10 of the squared 1^2,2^2,...,(N-1)^2,(N-th)^2 fibonacci numbers
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Main {

    private static long sum( ArrayList< Long > dp, int N, int M ){
        return( N > 0 )? ( dp.get( N-1 ) * dp.get( N ) ) % M : 0;
    }

    private static long fibonacci( long N, int M ){
        ++N; // the sum of squared fibonacci numbers from 0 to N is equal to fib( N ) * fib( N+1 ), so iterate till fib( N+1 )
        ArrayList< Long > dp = new ArrayList<>( Collections.nCopies( (6*M)+2, Long.valueOf( 0 ) ));
        dp.set( 0, Long.valueOf( 0 ));
        dp.set( 1, Long.valueOf( 1 ));
        dp.set( 2, Long.valueOf( 1 ));
        int i = 3; // start looking for the pisano period from i=3 to ignore the first 0,1 sequence at dp[ 0 ] and dp[ 1 ]
        for(; i <= N && ! ( dp.get( i-2 ) == 0 && dp.get( i-1 ) == 1 ); ++i )
            dp.set( i, ( dp.get( i-2 ) + dp.get( i-1 ) ) % M );
        int P = i-2;                                         // (P)isano period
        return( N <= i-1 )? sum( dp, ( int ) N, M )          // case 1) (P)isano period NOT reached, return the N-th fibonacci number
                          : sum( dp, ( int ) ( N % P ), M ); // case 2) (P)isano period reached, return (N mod P)-th fibonacci number
    }

    public static void main( String[] args ){
        Scanner input = new Scanner( System.in );
        long N = input.nextLong();
        int  M = 10;
        long ans = fibonacci( N, M );
        System.out.println( ans );
    }
}
