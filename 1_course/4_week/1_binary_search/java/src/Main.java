/**
 *
 * Java implementation of binary search
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.Scanner;
import java.util.ArrayList;

public class Main {
    public static final int NOT_FOUND = -1;
    public static int binarySearch( int[] A, int T ){
        return go( A, T, 0, A.length );
    }
    private static int go( int[] A, int T, int lo, int hi ){
        if( lo == hi )
            return NOT_FOUND;
        int P = ( lo + hi ) / 2;
        if( T < A[ P ] )
            return go( A, T, lo, P );
        if( T > A[ P ] )
            return go( A, T, P+1, hi );
        return P;
    }
    public static void main( String[] args ){
        Scanner input = new Scanner( System.in );
        int N = input.nextInt();
        int[] A = new int[ N ];
        for( int i=0; i < N; A[ i++ ]=input.nextInt() );
        int M = input.nextInt();
        ArrayList< Integer > ans = new ArrayList<>();
        for( int i=0; i < M; ++i ){
            int T = input.nextInt();
            int result = binarySearch( A, T );
            ans.add( result );
        }
        ans.forEach(( i ) -> System.out.print( i + " " ));
    }
}
