# 2. Inverse Burrows-Wheeler Transform
* [https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform](https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform)

## Lecture
* **Goal**
    * Reconstruct original genome from the Burrows-Wheeler Transform of the genome

| Algorithm                        | Memory    | Time           |
|:---------------------------------|:----------|:---------------|
| Trivial Implementation           | O( N^2 )  | O( N^3 log N ) |
| First-Last Property Optimization | O( 2N )   | O( N )         |

* **Summary**
    * We can go back from the Burrows-Wheeler Transform of the genome to the original genome:
    
### Trivial Implementation
![](docs/banana01.png)
---
![](docs/banana02.png)
---
![](docs/banana03.png)
---
![](docs/banana04.png)
---
![](docs/banana05.png)
---
![](docs/banana06.png)
---
![](docs/banana07.png)
---
![](docs/banana08.png)
---
![](docs/banana09.png)
---
![](docs/banana10.png)
---
![](docs/banana11.png)
---
![](docs/banana12.png)
---
![](docs/banana13.png)
---
![](docs/banana14.png)
---
![](docs/banana15.png)
---
![](docs/banana16.png)
---
![](docs/banana17.png)
---
![](docs/banana18.png)
---
![](docs/banana19.png)
---
![](docs/banana20.png)
---
![](docs/memory_issue.png)
---
![](docs/quiz1.png)
---

### First-Last Property Optimization
![](docs/observe01.png)
---
![](docs/observe02.png)
---
![](docs/observe03.png)
---
![](docs/observe05.png)
---
![](docs/observe06.png)
---
![](docs/observe07.png)
---
![](docs/observe08.png)
---
![](docs/observe09.png)
---
![](docs/observe10.png)
---
![](docs/observe11.png)
---
![](docs/observe12.png)
---
![](docs/observe13.png)
---
![](docs/observe14.png)
---
![](docs/inverting00.png)
---
![](docs/inverting01.png)
---
![](docs/inverting02.png)
---
![](docs/inverting03.png)
---
![](docs/inverting04.png)
---
![](docs/inverting05.png)
---
![](docs/inverting06.png)
---
![](docs/inverting07.png)
---
![](docs/inverting08.png)
---
![](docs/inverting09.png)
---
![](docs/inverting10.png)
---
![](docs/inverting11.png)
---
![](docs/inverting12.png)
---
![](docs/inverting13.png)
---
![](docs/inverting14.png)
---
![](docs/inverting15.png)
---
![](docs/inverting16.png)
---
![](docs/inverting17.png)
---
![](docs/inverting18.png)
---
![](docs/inverting19.png)
---
![](docs/inverting20.png)
---
![](docs/inverting21.png)
---
![](docs/inverting22.png)
---
![](docs/inverting23.png)
---
![](docs/inverting24.png)
---
![](docs/inverting25.png)
---
![](docs/inverting26.png)
---
![](docs/inverting27.png)
---
![](docs/inverting28.png)
---
![](docs/inverting29.png)
---
![](docs/inverting30.png)
---
![](docs/inverting31.png)

## Problem
![](docs/2_ibwt.png)

## Pseudocode (trivial implementation)
![](docs/pseudocode.png)

## Pseudocode (first-last property optimization)
The **path traversed** in **step 3** below is the **original genome** ( in reverse order ):
* **step 1:** create an **id counter** to track **unique char instances**
    * **i.e.** ```A(1,2,...,N-1,N), B(1,2,...,N-1,N), C..., D..., ...```

* **step 2:** use the **id counter** to create a **first-last path** which associates **first-last char instances**

* **step 3:** follow the **first-last path**, starting from ```$(1)``` and ending at ```$(1)```

## Solutions
* [C++](#cpp)

### CPP
```cpp
    #include <iostream>
    #include <sstream>
    #include <string>
    #include <queue>
    #include <algorithm>
    #include <unordered_map>
    
    //#define TRIVIAL_IMPLEMENTATION
    //#define OUTPUT_CYCLIC_ROTATIONS__THE_BURROWS_WHEELER_TRANSFORM_MATRIX
    #define OUTPUT_INVERSE_BURROWS_WHEELER_TRANSFORM__THE_ORIGINAL_GENOME
    
    using namespace std;
    
    #ifdef TRIVIAL_IMPLEMENTATION // Failed case #27/44: time limit exceeded (Time used: 4.05/2.00)
    using Deque = deque< char >;
    using Strings = vector< Deque >;
    int main() {
        Strings S;
        string str; cin >> str;
        const auto N = str.size();
        bool empty{ true };
        for( auto i{ 0 }; i < N; ++i ){
            if( empty )
                for( auto c: str )
                    S.push_back( Deque{ c } );
            else
                for( auto j{ 0 }; j < N; ++j )
                    S[ j ].push_front( str[ j ] );
            sort( S.begin(), S.end() );
            empty = false;
        }
    #ifdef OUTPUT_CYCLIC_ROTATIONS__THE_BURROWS_WHEELER_TRANSFORM_MATRIX
        for( auto i{ 0 }; i < N; ++i, cout << endl )
            for( auto j{ 0 }; j < S[ i ].size(); ++j )
                cout << S[ i ][ j ];
        cout << endl;
    #endif
    #ifdef OUTPUT_INVERSE_BURROWS_WHEELER_TRANSFORM__THE_ORIGINAL_GENOME
        auto it = find_if( S.begin(), S.end(), []( const auto& str ){ return str.back() == '$'; });
        string inverse{ it->begin(), it->end() };
        cout << inverse << endl;
    #endif
        return 0;
    }
    #else // First-Last Property Optimization
    using Counter = unordered_map< char, int >;
    using Path = unordered_map< string, string >;
    int main() {
    #ifdef OUTPUT_INVERSE_BURROWS_WHEELER_TRANSFORM__THE_ORIGINAL_GENOME
        Path path; {
            string transformed; cin >> transformed;
            auto sorted{ transformed }; sort( sorted.begin(), sorted.end() );
            const auto N = transformed.size();
            Counter begCnt, endCnt;
            for( auto i{ 0 }; i < N; ++i ){
                ostringstream first, last;
                auto beg = sorted[ i ],
                     end = transformed[ i ];
                first << beg << ++begCnt[ beg ];
                last  << end << ++endCnt[ end ];
                path[ first.str() ] = last.str();
            }
        }
        string inverse{ '$' }; {
            const auto sentinel{ "$1" };
            for( auto cur = path[ sentinel ]; cur != sentinel; cur = path[ cur ] )
                inverse.push_back( cur.front() );
        }
        cout << string{ inverse.rbegin(), inverse.rend() } << endl;
    #endif
        return 0;
    }
    #endif
```
