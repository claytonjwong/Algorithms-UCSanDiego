/**
 *
 * Java implementation to find the last digit of a large fibonacci number
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.ArrayList;
import java.util.Scanner;
import java.util.Collections;

public class Main {

    public static Integer INF = Integer.MAX_VALUE;

    public static Integer fibonacci( Integer N ){
        if( N < 2 )
            return N;
        ArrayList< Integer > dp = new ArrayList<>( Collections.nCopies( N+1, INF ));
        dp.set( 0, 0 );
        dp.set( 1, 1 );
        for( int i = 2; i <= N; ++i )
            dp.set( i, (dp.get( i-2 ) + dp.get( i-1 )) % 10 );
        return dp.get( N );
    }

    public static void main( String[] args ){
        Scanner input = new Scanner( System.in );
        Integer N = input.nextInt(),
                ans = fibonacci( N );
        System.out.println( ans );
    }
}
