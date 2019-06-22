# Counting Sort (modern C++)
* [https://en.wikipedia.org/wiki/Counting_sort](https://en.wikipedia.org/wiki/Counting_sort)

```cpp
    #include <iostream>
    #include <vector>
    #include <unordered_map>
    #include <algorithm>
    #include <iterator>
    
    using namespace std;
    using Count = unordered_map< char, size_t >;
    using Collection = vector< char >;
    
    int main() {
        const string alpha{ "ACGT" };
        string S; cin >> S;
        Count C; {
            for( auto ch: S )
                ++C[ ch ];
        }
        Collection A; {
            const auto N = S.size();
            A.reserve( N );
            for( auto ch: alpha )
                generate_n( back_inserter( A ), C[ ch ], [=](){ return ch; });
        }
        copy( A.begin(), A.end(), ostream_iterator< char >( cout, ""  ) );
        return 0;
    }
```
