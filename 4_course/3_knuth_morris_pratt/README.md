# 1. Knuth-Morris-Pratt
* [https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm](https://en.wikipedia.org/wiki/Knuth–Morris–Pratt_algorithm)

## Lecture
### Exact Pattern Matching
![](docs/exact_pattern_matching.png)

### Brute Force
![](docs/brute_force1.png)
![](docs/brute_force2.png)
![](docs/brute_force3.png)
![](docs/brute_force4.png)

### Skipping Positions
![](docs/border.png)
![](docs/shift1.png)
![](docs/shift2.png)

#### Example 1
![](docs/skip1_1.png)
![](docs/skip1_2.png)
![](docs/skip1_3.png)
![](docs/skip1_4.png)
![](docs/skip1_5.png)

#### Example 2
![](docs/skip2_1.png)
![](docs/skip2_2.png)
![](docs/skip2_3.png)
![](docs/skip2_4.png)
![](docs/skip2_5.png)
![](docs/skip2_6.png)
![](docs/skip2_7.png)
![](docs/skip2_8.png)

### Is Skipping Safe?
![](docs/suffix_notation.png)
![](docs/safe1.png)
![](docs/safe2.png)
![](docs/safe3.png)
![](docs/safe4.png)
![](docs/safe5.png)
![](docs/safe6.png)
![](docs/safe7.png)
![](docs/safe8.png)
![](docs/safe9.png)

### Quiz 1
![](docs/quiz1.png)
```
Before shift:    ??abcdabc??????
                   abcdabcef
                   1234
                   
After shift:     ??abcdabc??????
                   ->  abcdabcef
                   1234
```

### Quiz 2
![](docs/quiz2.png)

### Prefix Function
```s[ 0 ]``` is always ```0``` since a string *cannot* be a prefix of itself.
![](docs/prefix01.png)
![](docs/prefix02.png)
![](docs/prefix03.png)
![](docs/prefix04.png)
![](docs/prefix05.png)
![](docs/prefix06.png)
![](docs/prefix07.png)
![](docs/prefix08.png)
![](docs/prefix09.png)
![](docs/prefix10.png)
![](docs/prefix11.png)

### Lemma
![](docs/prefix_function_lemma1.png)
![](docs/prefix_function_lemma2.png)

### Corollary
The border can "grow" at most 1-character at at time when computing ```s( i + 1 )```
from ```s( i )```

![](docs/corollary.png)

### Enumerating Borders
![](docs/enum1.png)
![](docs/enum2.png)
![](docs/enum3.png)

#### Example
Enumerating borders is similiar to the concept of Matryoshka dolls (i.e. one fits inside the other
until there's nothing left)
![](docs/matryoshka_doll.png)

### Quiz 3
![](docs/quiz3.png)

### Computing s( i + 1 )
![](docs/compute_s_i_plus_one_01.png)
![](docs/compute_s_i_plus_one_02.png)
![](docs/compute_s_i_plus_one_03.png)
![](docs/compute_s_i_plus_one_04.png)
![](docs/compute_s_i_plus_one_05.png)
![](docs/compute_s_i_plus_one_06.png)
![](docs/compute_s_i_plus_one_07.png)
![](docs/compute_s_i_plus_one_08.png)
![](docs/compute_s_i_plus_one_09.png)

### Quiz 4
![](docs/quiz4.png)
```
    P = ababcababac
    i = 012345678901
 s(i) = 00220123430
                ^
                i=8
```
### Pseudocode
![](docs/pseudo_prefix_func.png)

### Example
![](docs/example_s_i_computations.png)

### Lemma and Proof
![](docs/prefix_function_lemma3.png)
![](docs/prefix_func_linear_proof1.png)
![](docs/graph.png)

![](docs/prefix_func_linear_proof2.png)

### Knuth-Morris-Pratt Algorithm
![](docs/kmp1.png)
![](docs/kmp2.png)

## Problem
![](docs/3_problem.png)

## Solutions
* [C++](#cpp)

### CPP
```cpp
    #include <algorithm>
    #include <iostream>
    #include <iterator>
    #include <sstream>
    #include <vector>
    
    //#define BRUTE_FORCE_SEARCH
    //#define OUTPUT_PREFIX_FUNCTION
    #define OUTPUT_INDEXES_OF_NEEDLE_IN_HAYSTACK
    
    using namespace std;
    
    #ifdef BRUTE_FORCE_SEARCH // Failed case #57/64: time limit exceeded (Time used: 1.98/1.00, memory used: 72019968/536870912.)
    using Indexes = vector< int >;
    int main() {
        string needle, haystack; cin >> needle >> haystack;
        auto M = needle.size(),
             N = haystack.size();
        Indexes I; {
            for( auto i{ 0 }, j{ 0 }; i + M <= N; ++i ){
                for( j = 0; j < M && needle[ j ] == haystack[ i+j ]; ++j );
                if( j == M )
                    I.push_back( i );
            }
        }
    #ifdef OUTPUT_INDEXES_OF_NEEDLE_IN_HAYSTACK
        copy( I.begin(), I.end(), ostream_iterator< int >( cout, " " ) ); cout << endl;
    #endif
    }
    #else // Knuth-Morris-Pratt
    using PrefixFunction = vector< int >;
    using Indexes = vector< int >;
    int main() {
        string needle, haystack; cin >> needle >> haystack;
        string S; {
            ostringstream os; os << needle << '$' << haystack;
            S = os.str();
        }
        auto M = needle.size(),
             N = S.size();
        PrefixFunction P( N, 0 ); {
            for( auto i{ 1 }, j{ 0 }; i < N; ++i ){ // let j denote the "border" of the string
                while( 0 < j && S[ i ] != S[ j ] )
                    j = P[ j-1 ];
                P[ i ] = j = ( S[ i ] == S[ j ] )? j+1 : 0;
            }
        }
    #ifdef OUTPUT_PREFIX_FUNCTION
        cout << S << endl;
        copy( P.begin(), P.end(), ostream_iterator< int >( cout, "" ) ); cout << endl;
    #endif
        Indexes I; {
            auto offset = 2 * M;
            for( auto i{ offset }; i < S.size(); ++i )
                if( P[ i ] == M )
                    I.push_back( i - offset );
        }
    #ifdef OUTPUT_INDEXES_OF_NEEDLE_IN_HAYSTACK
        copy( I.begin(), I.end(), ostream_iterator< int >( cout, " " ) ); cout << endl;
    #endif
        return 0;
    }
    #endif
```
