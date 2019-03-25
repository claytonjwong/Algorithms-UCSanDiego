/**
 *
 * Java implementation to find the most valuable combination of items using a fractional knapsack
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

import java.text.DecimalFormat;
import java.util.Collections;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Iterator;

public class Main {

    public static class Item implements Comparable< Item >{
        int V = 0,
            W = 0;
        public Item( int value, int weight ){
            super();
            V = value;
            W = weight;
        }
        public double ratio(){
            return( W > 0 )? ( double ) V  / W : 0;
        }
        public int compareTo( Item rhs ){
            return( ratio() < rhs.ratio() )?  1
                : ( ratio() > rhs.ratio() )? -1
                : ( 0 );
        }
    }

    public static double maxValue( ArrayList< Item > items, int W ){
        double ans = 0;
        Collections.sort( items );
        Iterator< Item > it = items.iterator();
        while( W > 0 && it.hasNext() ){
            Item item = it.next();
            if( item.W <= W ){ // item fits in knapsack
                ans += item.V;
                W -= item.W;
            } else {
                double fraction = ( double ) W / item.W;
                ans += fraction * item.V;
                W = 0;
            }
        }
        return ans;
    }

    public static void main( String[] args ){
        Scanner input = new Scanner( System.in );
        int N = input.nextInt(),
            W = input.nextInt();
        ArrayList< Item > items = new ArrayList<>( Collections.nCopies( N, new Item( 0, 0 ) ) );
        for( int i=0; i < N; ++i ){
            int Vi = input.nextInt(),
                Wi = input.nextInt();
            Item item = new Item( Vi, Wi );
            items.set( i, item );
        }
        double ans = maxValue( items, W );
        System.out.println( new DecimalFormat( "#0.0000" ).format( ans ));
    }
}
