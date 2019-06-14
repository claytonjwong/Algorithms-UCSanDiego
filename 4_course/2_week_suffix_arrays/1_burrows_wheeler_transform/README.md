# 1. Burrows-Wheeler Transform
* [https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform](https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform)

## Problem
![](docs/1_bwt1.png)
![](docs/1_bwt2.png)

## Solutions
* [C++](#cpp)

### CPP
```cpp
    #include <iostream>
    #include <sstream>
    #include <string>
    #include <algorithm>
    #include <queue>

    using namespace std;

    int main() {
        using Strings = vector< string >;
        Strings S;
        string str{ "AGACATA$" };
        for( auto N = str.size(); N--; ){
            rotate( str.begin(), str.begin()+1, str.end() );
            S.push_back({ str.begin(), str.end() });
        }
        sort( S.begin(), S.end() );
        copy( S.begin(), S.end(), ostream_iterator< string >( cout, "\n" ) );
        transform( S.begin(), S.end(), S.begin(), []( const auto& s ){ return s.back(); });
        ostringstream os;
        copy( S.begin(), S.end(), ostream_iterator< string >( os, "" ) );
        assert( os.str() == "ATG$CAAA" );
        cout << endl << os.str() << endl;
        return 0;
    }
```
