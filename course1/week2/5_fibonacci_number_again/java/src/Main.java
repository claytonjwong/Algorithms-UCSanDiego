/**
 *
 * Java implementation to find the N mod M-th fibonacci number
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import static java.lang.Math.toIntExact;

public class Main {

    private static Long fibonacci( long N, int M ){
        ArrayList< Long > dp = new ArrayList<>( Collections.nCopies( (6*M)+2, Long.valueOf( 0 ) ));
        dp.set( 0, Long.valueOf( 0 ));
        dp.set( 1, Long.valueOf( 1 ));
        dp.set( 2, Long.valueOf( 1 ));
        int i = 3;
        for(; i <= N && ! ( dp.get( i-2 ) == 0 && dp.get( i-1 ) == 1 ); ++i )
            dp.set( i, ( dp.get( i-2 ) + dp.get( i-1 ) ) % M );
        int P = i-2;                                      // (P)isano period
        return( N <= i-1 )? dp.get( toIntExact( N ))      // case 1) (P)isano period NOT reached, return the N-th fibonacci number
                          : dp.get( toIntExact( N % P )); // case 2) (P)isano period reached, return (N mod P)-th fibonacci number
    }

    public static void main( String[] args ){
        Scanner input = new Scanner( System.in );
        long N = input.nextLong();
        int  M = input.nextInt();
        long ans = fibonacci( N, M );
        System.out.println( ans );
    }
}
