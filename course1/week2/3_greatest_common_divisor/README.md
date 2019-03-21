# 3. Greatest Common Divisor
https://en.wikipedia.org/wiki/Euclidean_algorithm

## Problem
![](docs/3_greatest_common_divisor.png)

## Solutions
* [C](#c)
* [C++](#cpp)
* [Java](#java)
* [Python3](#python3)

### C
```c
    #include <stdio.h>

    typedef size_t Type;

    Type gcd( Type a, Type b ){
        for( Type t = 0; b != 0; ){
            t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    int main(){
        Type a = 0,
             b = 0;
        scanf( "%ld %ld", &a, &b );
        Type ans = gcd( a, b );
        printf( "%ld\n", ans );
        return 0;
    }
```

### CPP
```cpp
    #include <iostream>

    using namespace std;

    template< typename Type >
    class Solution {
    public:
        Type gcd( Type a, Type b ){
            for( auto t{ b }; b != 0; ){
                t = b;
                b = a % b;
                a = t;
            }
            return a;
        }
    };

    int main(){
        using Type = size_t;
        Solution< Type > solution;
        Type a = 0,
             b = 0;
        cin >> a >> b;
        Type ans = solution.gcd( a, b );
        cout << ans << endl;
        return 0;
    }
```

### Java
```java
    import java.util.Scanner;

    public class Main {

        private static int gcd( int a, int b ){
            for( int t = 0; b != 0; ){
                t = b;
                b = a % b;
                a = t;
            }
            return a;
        }

        public static void main(String[] args){
            Scanner input = new Scanner( System.in );
            int a = input.nextInt(),
                b = input.nextInt(),
                ans = gcd( a, b );
            System.out.println( ans );
        }
    }
```

### Python3
```python
    def gcd( a, b ):
        while b != 0:
            t = b
            b = a % b
            a = t
        return a

    if __name__ == '__main__':
        a, b = map( int, input().split() )
        ans = gcd( a, b )
        print( ans )
```
