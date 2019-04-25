/**
 *
 * Java implementation of majority element
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.Scanner;

public class Main {

    public static boolean hasMajorityElement( int[] A, int N ){
        int me = 0;
        for( int i=( 0 ), cnt=( 0 ); i < N; cnt=(( me == A[ i++ ] ) ? ( cnt + 1 ) : ( cnt - 1 )) )
            if( cnt == 0 )
                me = A[ i ];
        int cnt = 0,
            T = ( N / 2 ) + 1;
        for( int i=( 0 ); i < N; ++i )
            if( me == A[ i ] )
                ++cnt;
        return( T <= cnt );
    }

    public static void main( String[] args ){
        Scanner input = new Scanner( System.in );
        int N = input.nextInt();
        int[] A = new int[ N ];
        for( int i=( 0 ); i < N; A[ i++ ]=( input.nextInt() ));
        boolean ans = hasMajorityElement( A, N );
        System.out.println( ans? "1" : "0" );
    }
}
