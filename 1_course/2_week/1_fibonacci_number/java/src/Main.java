import java.util.Collections;

/**
 *
 * Java implementation to find the N-th fibonacci number
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class Main {

    public static Integer INF = Integer.MAX_VALUE;

    public static Integer fibonacci_top_down( Integer N ){
        ArrayList< Integer > memo = new ArrayList< Integer >( Collections.nCopies( N+1, INF ));
        return go( N, memo );
    }

    private static Integer go( Integer N, ArrayList< Integer > memo ){
        if( memo.get( N ) != INF )
            return memo.get( N );
        if( N < 2 ){
            memo.set( N, N );
            return memo.get( N );
        }
        Integer res = go( N-2, memo ) + go( N-1, memo );
        memo.set( N, res );
        return memo.get( N );
    }

    public static Integer fibonacci_bottom_up( Integer N ){
        if( N < 2 )
            return N;
        ArrayList< Integer > dp = new ArrayList< Integer >( Collections.nCopies( N+1, INF ));
        dp.set( 0, 0 );
        dp.set( 1, 1 );
        for( int i = 2; i <= N; ++i )
            dp.set( i, dp.get( i-2 ) + dp.get( i-1 ));
        return dp.get( N );
    }

    public static void main( String[] args ){
        Scanner input = new Scanner( System.in );
        Integer N = input.nextInt();
        Integer ans_top_down = fibonacci_top_down( N ),
                ans_bottom_up = fibonacci_bottom_up( N );
        assert ans_top_down == ans_bottom_up : "! ( ans_top_down == ans_bottom_up )";
        System.out.println( ans_top_down );
    }
}
