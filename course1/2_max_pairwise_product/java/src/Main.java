/**
 *
 * Java implementation to find the maximum pairwise product of two integers
 *
 **/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;

// TLE
public class Main {
    public static void main( String[] args ){
	    Scanner input = new Scanner( System.in );
	    int N = input.nextInt();
	    if( N < 2 )
	        return;
	    ArrayList< Long > A = new ArrayList< Long >( N );
	    for( int i = 0; i < N; ++i )
	        A.add( input.nextLong() );
	    int i = A.indexOf( Collections.max( A ) ); Long first =  A.get( i ); A.set( i, Long.valueOf( 0 ) );
	    int j = A.indexOf( Collections.max( A ) ); Long second = A.get( j );
	    System.out.println( first * second );
    }
}

// TLE
/*
public class Main {
    public static void main( String[] args ){
        Scanner input = new Scanner( System.in );
        int N = input.nextInt();
        if( N < 2 )
            return;
        long[] A = new long[ N ];
        for( int i = 0; i < N; ++i )
            A[ i ] = input.nextLong();
        int i = indexOfMax( A ); Long first  = A[ i ]; A[ i ] = 0;
        int j = indexOfMax( A ); Long second = A[ j ];
        System.out.println( first * second );
    }
    private static int indexOfMax( long[] A ){
        int j = 0;
        for( int i = 1; i < A.length; ++i )
            if( A[ j ] < A[ i ] )
                j = i;
        return j;
    }
}
*/

// Based on the above two TLEs, I suspect the bottleneck is Scanner input,
// however, when I try using a BufferredReader + StringTokenizer, an Exception is thrown
/*
public class Main {
    public static void main( String[] args ){
        try {
            Scanner scanner = new Scanner( System.in );
            int N = scanner.nextInt();
            if( N < 2 )
                return;
            BufferedReader input = new BufferedReader( new InputStreamReader( System.in ));
            long[] A = new long[ N ];
            for( int i = 0; i < N; ){
                StringTokenizer toker = new StringTokenizer( input.readLine() );
                while( toker.hasMoreElements() )
                    A[ i++ ] = Long.parseLong( toker.nextToken() );
            }
            int i = indexOfMax( A ); Long first  = A[ i ]; A[ i ] = 0;
            int j = indexOfMax( A ); Long second = A[ j ];
            System.out.println( first * second );
        } catch (IOException io) {
            io.printStackTrace();
        }
    }
    private static int indexOfMax( long[] A ){
        int j = 0;
        for( int i = 1; i < A.length; ++i )
            if( A[ j ] < A[ i ] )
                j = i;
        return j;
    }
}
*/
