/**
 *
 * Java implementation to find the maximum advertising revenue
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.Scanner;
import java.util.Arrays;

public class Main {

    public static long maxAdRev( long[] A, long[] B, int N ){
        Arrays.sort( A );
        Arrays.sort( B );
        long ans = 0;
        for( int i=0; i < N; ++i )
            ans += A[ i ] * B[ i ];
        return ans;
    }

    public static void main( String[] args ){
        Scanner input = new Scanner( System.in );
        int N = input.nextInt();
        long A[] = new long[ N ];
        long B[] = new long[ N ];
        for( int i=0; i < N; A[ i++ ]=input.nextLong() );
        for( int i=0; i < N; B[ i++ ]=input.nextLong() );
        long ans = maxAdRev( A, B, N );
        System.out.println( ans );
    }
}
