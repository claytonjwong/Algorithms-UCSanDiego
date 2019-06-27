/**
 *
 * C++ implementation to create a Suffix Array in near-linear time and perform pattern matching
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

//#define OUTPUT_BINARY_SEARCH_FOR_PATTERN_MATCH_INDEX_OF_BEGIN
//#define OUTPUT_BINARY_SEARCH_FOR_PATTERN_MATCH_INDEX_OF_END
#define OUTPUT_PATTERN_MATCH_INDEXES

using namespace std;
using Indexes = unordered_set< int >;
using Patterns = vector< string >;

/*
 * https://en.wikipedia.org/wiki/Suffix_array#Applications
 *

    n = len(S)
    def search(P):
        l = 0; r = n
        while l < r:
            mid = (l+r) / 2
            if P > suffixAt(A[mid]):
                l = mid + 1
            else:
                r = mid
        s = l; r = n
        while l < r:
            mid = (l+r) / 2
            if P < suffixAt(A[mid]): <- this comparison should be based on the first |P| characters of suffixAt(A[mid])
                r = mid
            else:
                l = mid + 1
        return (s, r)

 */

class SuffixArray {
public:
    using VI = vector< int >;
    static VI build( const string& S, const int N ){
        auto order = sortChars( S, N );
        auto classes = computeCharClasses( S, N, order );
        for( auto L{ 1 }; L < N; L *= 2 ){
            order = sortDoubled( S, N, L, order, classes );
            classes = updateClasses( N, L, order, classes );
        }
        return order;
    }
    static string to_string( const string& S, const VI& A,
                             const int L, const int M, const int R,
                             const string& pattern, const string& cur ){
        const auto N = static_cast< int >( A.size() );
        ostringstream os;
        os << "Pattern: " << pattern << endl
           << "Current: " << cur << endl << endl;
        for( auto i{ 0 }; i < N; ++i ){
            os << print_LMR( i, L, M, R )
               << "A[ " << setw( 2 ) << i << " ] = " << setw( 2 ) << A[ i ] << " -> " << S.substr( A[ i ] ) << endl;
        }
        os << print_LMR( N, L, M, R ) << "A[ " << setw( 2 ) << N << " ] = A.end()";
        return os.str();
    }
private:
    static string print_LMR( const int i, const int L, const int M, const int R ){
        ostringstream os{ " ", ostringstream::ate };
            os << ( ( i == L )? 'L' : ' ' ) << ' '
               << ( ( i == M )? 'M' : ' ' ) << ' '
               << ( ( i == R )? 'R' : ' ' ) << ' ';
        return os.str();
    }
    static VI sortChars( const string& S, const int N ){
        const int M = 'z' + 1; // alphabet size
        VI order( N ), cnt( M );
        for( auto i{ 0 }; i < N; ++i ){
            auto c = S[ i ];
            ++cnt[ c ];
        }
        for( auto j{ 1 }; j < M; ++j )
            cnt[ j ] += cnt[ j-1 ];
        for( auto i{ N-1 }; 0 <= i; --i ){
            auto c = S[ i ];
            --cnt[ c ];
            order[ cnt[ c ] ] = i;
        }
        return order;
    }
    static VI computeCharClasses( const string& S, const int N, const VI& order ){
        VI classes( N, 0 );
        for( auto i{ 1 }; i < N; ++i )
            if( S[ order[ i ] ] != S[ order[ i-1 ] ] )
                classes[ order[ i ] ] = classes[ order[ i-1 ] ] + 1;
            else
                classes[ order[ i ] ] = classes[ order[ i-1 ] ];
        return classes;
    }
    static VI sortDoubled( const string& S, const int N, const int L, const VI& order, const VI& classes ){
        VI next_order( N, 0 ), cnt( N, 0 );
        for( auto i{ 0 }; i < N; ++i ){
            auto cl = classes[ i ];
            ++cnt[ cl ];
        }
        for( auto j{ 1 }; j < N; ++j )
            cnt[ j ] += cnt[ j-1 ];
        for( auto i{ N-1 }; 0 <= i; --i ){
            auto start = ( order[ i ] - L + N ) % N; // start is the begin index of the doubled cyclic shift
            auto cl = classes[ start ];
            --cnt[ cl ];
            next_order[ cnt[ cl ] ] = start;
        }
        return next_order;
    }
    static VI updateClasses( const int N, const int L, const VI& order, const VI& classes ){
        VI next_classes( N, 0 );
        for( auto i{ 1 }; i < N; ++i ){
            auto pre = order[ i-1 ], preMid = ( pre + L ) % N,
                 cur = order[ i   ], curMid = ( cur + L ) % N;
            if( classes[ pre ] != classes[ cur ] || classes[ preMid ] != classes[ curMid ] )
                next_classes[ cur ] = next_classes[ pre ] + 1; // diff equivalence class
            else
                next_classes[ cur ] = next_classes[ pre ];     // same equivalence class
        }
        return next_classes;
    }
};

int main() {
    string S; cin >> S;
    S.append( "$" );
    const auto N = static_cast< int >( S.size() );
    const auto A = SuffixArray::build( S, N );
    auto K{ 0 }; cin >> K;
    Patterns P; copy_n( istream_iterator< string >( cin ), K, back_inserter( P ) );
    Indexes I; {
        for( const auto& pattern: P ){
            auto L{ 0 }, R{ N };
            while( L < R ){
                auto M = ( L + R ) / 2;
                auto cur = S.substr( A[ M ] );
#ifdef OUTPUT_BINARY_SEARCH_FOR_PATTERN_MATCH_INDEX_OF_BEGIN
                cout << SuffixArray::to_string( S, A, L, M, R, pattern, cur ) << endl << endl << endl;
#endif
                if( pattern > cur )
                    L = M + 1;
                else
                    R = M;
            }
            auto beg{ L };
            R = N;
            while( L < R ){
                auto M = ( L + R ) / 2;
                auto cur = S.substr( A[ M ], pattern.size() );
#ifdef OUTPUT_BINARY_SEARCH_FOR_PATTERN_MATCH_INDEX_OF_END
                cout << SuffixArray::to_string( S, A, L, M, R, pattern, cur ) << endl << endl << endl;
#endif
                if( pattern < cur )
                    R = M;
                else
                    L = M + 1;
            }
            auto end{ R };
            for(; beg < end; I.insert( A[ beg++ ] ) );
        }
    }
#ifdef OUTPUT_PATTERN_MATCH_INDEXES
    copy( I.begin(), I.end(), ostream_iterator< int >( cout, " " ) ); cout << endl;
#endif
    return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Problem: find all indexes of the pattern(s) in the genome


Pattern: CCT

Genome: TCCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC
        012345678901234567890123456789012345678901234567890
        0         1         2         3         4         5

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Use binary search to find the (beg)in index of the pattern in the genome's suffix array A
*

Pattern: CCT
Current: CTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$

 L     A[  0 ] = 50 -> $
       A[  1 ] = 37 -> AAAATTCTCCGGC$
       A[  2 ] = 24 -> AAACCTTCAGACCAAAATTCTCCGGC$
       A[  3 ] = 38 -> AAATTCTCCGGC$
       A[  4 ] = 25 -> AACCTTCAGACCAAAATTCTCCGGC$
       A[  5 ] = 39 -> AATTCTCCGGC$
       A[  6 ] = 34 -> ACCAAAATTCTCCGGC$
       A[  7 ] = 26 -> ACCTTCAGACCAAAATTCTCCGGC$
       A[  8 ] = 32 -> AGACCAAAATTCTCCGGC$
       A[  9 ] =  9 -> AGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 10 ] = 11 -> ATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 11 ] = 21 -> ATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 12 ] =  6 -> ATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 13 ] = 16 -> ATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 14 ] = 40 -> ATTCTCCGGC$
       A[ 15 ] = 49 -> C$
       A[ 16 ] = 36 -> CAAAATTCTCCGGC$
       A[ 17 ] = 31 -> CAGACCAAAATTCTCCGGC$
       A[ 18 ] = 35 -> CCAAAATTCTCCGGC$
       A[ 19 ] = 45 -> CCGGC$
       A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 21 ] =  1 -> CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 22 ] = 27 -> CCTTCAGACCAAAATTCTCCGGC$
       A[ 23 ] = 46 -> CGGC$
       A[ 24 ] = 19 -> CTATGAAACCTTCAGACCAAAATTCTCCGGC$
   M   A[ 25 ] =  4 -> CTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 26 ] = 14 -> CTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 27 ] = 43 -> CTCCGGC$
       A[ 28 ] =  2 -> CTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 29 ] = 28 -> CTTCAGACCAAAATTCTCCGGC$
       A[ 30 ] = 23 -> GAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 31 ] = 33 -> GACCAAAATTCTCCGGC$
       A[ 32 ] =  8 -> GAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 33 ] = 10 -> GATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 34 ] = 48 -> GC$
       A[ 35 ] = 47 -> GGC$
       A[ 36 ] = 20 -> TATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 37 ] =  5 -> TATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 38 ] = 15 -> TATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 39 ] = 30 -> TCAGACCAAAATTCTCCGGC$
       A[ 40 ] = 44 -> TCCGGC$
       A[ 41 ] = 12 -> TCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 42 ] =  0 -> TCCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 43 ] = 18 -> TCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 44 ] =  3 -> TCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 45 ] = 42 -> TCTCCGGC$
       A[ 46 ] = 22 -> TGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 47 ] =  7 -> TGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 48 ] = 29 -> TTCAGACCAAAATTCTCCGGC$
       A[ 49 ] = 17 -> TTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 50 ] = 41 -> TTCTCCGGC$
     R A[ 51 ] = A.end()


Pattern: CCT
Current: ATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$

 L     A[  0 ] = 50 -> $
       A[  1 ] = 37 -> AAAATTCTCCGGC$
       A[  2 ] = 24 -> AAACCTTCAGACCAAAATTCTCCGGC$
       A[  3 ] = 38 -> AAATTCTCCGGC$
       A[  4 ] = 25 -> AACCTTCAGACCAAAATTCTCCGGC$
       A[  5 ] = 39 -> AATTCTCCGGC$
       A[  6 ] = 34 -> ACCAAAATTCTCCGGC$
       A[  7 ] = 26 -> ACCTTCAGACCAAAATTCTCCGGC$
       A[  8 ] = 32 -> AGACCAAAATTCTCCGGC$
       A[  9 ] =  9 -> AGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 10 ] = 11 -> ATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 11 ] = 21 -> ATGAAACCTTCAGACCAAAATTCTCCGGC$
   M   A[ 12 ] =  6 -> ATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 13 ] = 16 -> ATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 14 ] = 40 -> ATTCTCCGGC$
       A[ 15 ] = 49 -> C$
       A[ 16 ] = 36 -> CAAAATTCTCCGGC$
       A[ 17 ] = 31 -> CAGACCAAAATTCTCCGGC$
       A[ 18 ] = 35 -> CCAAAATTCTCCGGC$
       A[ 19 ] = 45 -> CCGGC$
       A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 21 ] =  1 -> CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 22 ] = 27 -> CCTTCAGACCAAAATTCTCCGGC$
       A[ 23 ] = 46 -> CGGC$
       A[ 24 ] = 19 -> CTATGAAACCTTCAGACCAAAATTCTCCGGC$
     R A[ 25 ] =  4 -> CTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$


Pattern: CCT
Current: CCGGC$

 L     A[ 13 ] = 16 -> ATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 14 ] = 40 -> ATTCTCCGGC$
       A[ 15 ] = 49 -> C$
       A[ 16 ] = 36 -> CAAAATTCTCCGGC$
       A[ 17 ] = 31 -> CAGACCAAAATTCTCCGGC$
       A[ 18 ] = 35 -> CCAAAATTCTCCGGC$
   M   A[ 19 ] = 45 -> CCGGC$
       A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 21 ] =  1 -> CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 22 ] = 27 -> CCTTCAGACCAAAATTCTCCGGC$
       A[ 23 ] = 46 -> CGGC$
       A[ 24 ] = 19 -> CTATGAAACCTTCAGACCAAAATTCTCCGGC$
     R A[ 25 ] =  4 -> CTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$


Pattern: CCT
Current: CCTTCAGACCAAAATTCTCCGGC$

 L     A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 21 ] =  1 -> CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
   M   A[ 22 ] = 27 -> CCTTCAGACCAAAATTCTCCGGC$
       A[ 23 ] = 46 -> CGGC$
       A[ 24 ] = 19 -> CTATGAAACCTTCAGACCAAAATTCTCCGGC$
     R A[ 25 ] =  4 -> CTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$


Pattern: CCT
Current: CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$

 L     A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
   M   A[ 21 ] =  1 -> CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
     R A[ 22 ] = 27 -> CCTTCAGACCAAAATTCTCCGGC$


Pattern: CCT
Current: CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$

 L M   A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
     R A[ 21 ] =  1 -> CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$


 beg   A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$

*
* Found the (beg)in index of the pattern in the genome's suffix array A
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Use binary search to find the end index of the pattern in the genome's suffix array A
*
Pattern: CCT
Current: GGC

 L     A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 21 ] =  1 -> CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 22 ] = 27 -> CCTTCAGACCAAAATTCTCCGGC$
       A[ 23 ] = 46 -> CGGC$
       A[ 24 ] = 19 -> CTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 25 ] =  4 -> CTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 26 ] = 14 -> CTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 27 ] = 43 -> CTCCGGC$
       A[ 28 ] =  2 -> CTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 29 ] = 28 -> CTTCAGACCAAAATTCTCCGGC$
       A[ 30 ] = 23 -> GAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 31 ] = 33 -> GACCAAAATTCTCCGGC$
       A[ 32 ] =  8 -> GAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 33 ] = 10 -> GATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 34 ] = 48 -> GC$
   M   A[ 35 ] = 47 -> GGC$
       A[ 36 ] = 20 -> TATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 37 ] =  5 -> TATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 38 ] = 15 -> TATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 39 ] = 30 -> TCAGACCAAAATTCTCCGGC$
       A[ 40 ] = 44 -> TCCGGC$
       A[ 41 ] = 12 -> TCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 42 ] =  0 -> TCCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 43 ] = 18 -> TCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 44 ] =  3 -> TCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 45 ] = 42 -> TCTCCGGC$
       A[ 46 ] = 22 -> TGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 47 ] =  7 -> TGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 48 ] = 29 -> TTCAGACCAAAATTCTCCGGC$
       A[ 49 ] = 17 -> TTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 50 ] = 41 -> TTCTCCGGC$
     R A[ 51 ] = A.end()


Pattern: CCT
Current: CTC

 L     A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 21 ] =  1 -> CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 22 ] = 27 -> CCTTCAGACCAAAATTCTCCGGC$
       A[ 23 ] = 46 -> CGGC$
       A[ 24 ] = 19 -> CTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 25 ] =  4 -> CTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 26 ] = 14 -> CTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
   M   A[ 27 ] = 43 -> CTCCGGC$
       A[ 28 ] =  2 -> CTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 29 ] = 28 -> CTTCAGACCAAAATTCTCCGGC$
       A[ 30 ] = 23 -> GAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 31 ] = 33 -> GACCAAAATTCTCCGGC$
       A[ 32 ] =  8 -> GAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 33 ] = 10 -> GATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 34 ] = 48 -> GC$
     R A[ 35 ] = 47 -> GGC$


Pattern: CCT
Current: CGG

 L     A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 21 ] =  1 -> CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 22 ] = 27 -> CCTTCAGACCAAAATTCTCCGGC$
   M   A[ 23 ] = 46 -> CGGC$
       A[ 24 ] = 19 -> CTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 25 ] =  4 -> CTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 26 ] = 14 -> CTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
     R A[ 27 ] = 43 -> CTCCGGC$


Pattern: CCT
Current: CCT

 L     A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
   M   A[ 21 ] =  1 -> CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 22 ] = 27 -> CCTTCAGACCAAAATTCTCCGGC$
     R A[ 23 ] = 46 -> CGGC$


Pattern: CCT
Current: CCT

 L M   A[ 22 ] = 27 -> CCTTCAGACCAAAATTCTCCGGC$
     R A[ 23 ] = 46 -> CGGC$


 end   A[ 23 ] = 46 -> CGGC$

*
* Found the end index of the pattern in the genome's suffix array A
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* The pattern match indexes are the values in A[ beg : end )
*
* i.e. from A[ beg ] inclusive to A[ end ] non-inclusive
*

 Pattern: CCT

 beg   A[ 20 ] = 13 -> CCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 21 ] =  1 -> CCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC$
       A[ 22 ] = 27 -> CCTTCAGACCAAAATTCTCCGGC$
 end   A[ 23 ] = 46 -> CGGC$


 Indexes: 1 13 27

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *


* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Summary:

Problem: find all indexes of the pattern(s) in the genome

Pattern: CCT

         CCT         CCT           CCT
Genome: TCCTCTATGAGATCCTATTCTATGAAACCTTCAGACCAAAATTCTCCGGC
         ^^^         ^^^           ^^^
        012345678901234567890123456789012345678901234567890
        0         1         2         3         4         5

Indexes: 1 13 27

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
