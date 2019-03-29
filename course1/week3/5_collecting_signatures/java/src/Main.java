/**
 *
 * Java implementation to find collect signatures
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.Scanner;
import java.util.Arrays;

public class Main {

    public static int INF = 1000000001;

    public static class Segment implements Comparable< Segment >{
        int a, b;
        Segment( int a, int b ){
            this.a = a;
            this.b = b;
        }
        public int compareTo( Segment rhs ){
            if( b == rhs.b )
                return( a < rhs.a )? 1 : -1;
            return( b < rhs.b )? 1: -1;
        }
    }

    public static int[] minPoints( Segment[] cur, int N ){
        int w = 0; // (w)rite index into (ans)wer
        int[] ans = new int[ N ];
        for( int i=0; i < N; ++i )
            ans[ i ] = INF;
        Arrays.sort( cur );
        for( Segment[] next = new Segment[ N ]; 0 < N; ){
            int B = cur[ N-1 ].b; // greedy choice: the smallest segment end-point b
            ans[ w++ ] = B;
            int x = 0; // write index into ne(x)t
            for( int i=0; i < N; ++i ) if( ! ( cur[ i ].a <= B && B <= cur[ i ].b )) // next is all segments of cur which do NOT contain B
                next[ x++ ] = cur[ i ];
            N = x;
            for( int i=0; i< N; ++i )
                cur[ i ] = next[ i ];
        }
        return ans;
    }

    public static void main( String[] args ){
        Scanner input = new Scanner( System.in );
        int N = input.nextInt();
        Segment[] S = new Segment[ N ];
        for( int i=0, a=0, b=0; i < N; ++i ){
            a = input.nextInt();
            b = input.nextInt();
            S[ i ] = new Segment( a, b );
        }
        int[] ans = minPoints( S, N );
        int x = 0;
        for(; ans[ x ] != INF; ++x );
        System.out.println( x );
        for( int i=0; i < x; ++i )
            System.out.print( ans[ i ] + " " );
    }
}
