/**
 *
 * Java implementation to find the maximum number of prizes
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.util.Scanner;
import java.util.ArrayList;

public class Main {

    public static ArrayList maxNumPrizes( int N ){
        ArrayList ans = new ArrayList();
        for( int i=1; i+1 <= N-i; N-=i, ++i )
            ans.add( i );
        if( 0 < N )
            ans.add( N );
        return ans;
    }

    public static void main( String[] args ){
        Scanner input = new Scanner( System.in );
        int N = input.nextInt();
        ArrayList ans = maxNumPrizes( N );
        System.out.println( ans.size() );
        ans.forEach(( i ) -> System.out.print( i + " " ));
    }
}
