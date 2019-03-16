# Sum of two digits
https://en.wikipedia.org/wiki/Digit_sum

## Problem
![](docs/sum_two_digits.png)

## Solutions
* [C++](#cpp)
* [Java](#java)
* [Python3](#python3)

### CPP
```cpp
#include <iostream>

using namespace std;

class Solution
{
public:

    int sum_of_two_digits( int first, int second )
    {
        return first + second;
    }

};

int main()
{
    Solution solution;

    auto a{ 0 }, b{ 0 };
    cin >> a >> b;
    cout << solution.sum_of_two_digits( a, b );

    return 0;
}
```

### Java
```java
import java.util.Scanner;

class APlusB {
    static int sumOfTwoDigits( int first, int second ){
        return first + second;
    }

    public static void main( String[] args ){
        Scanner s = new Scanner( System.in );
        int a = s.nextInt();
        int b = s.nextInt();
        System.out.println( sumOfTwoDigits( a, b ) );
    }
}
```

### Python3
```python
def sum_of_two_digits( first, second ):
    return first + second

if __name__ == '__main__':
    a, b = map( int, input().split() )
    print( sum_of_two_digits( a, b ) )
```