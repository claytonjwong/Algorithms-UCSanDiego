# 4. Suffix Array
* [https://en.wikipedia.org/wiki/Suffix_array](https://en.wikipedia.org/wiki/Suffix_array)

## Contents
* [Memory Efficient Data Structure](#memory-efficient-data-structure)
* [General Strategy for Construction](#general-strategy-for-construction)
* [Initialization](#initialization)
* [Sort Doubled Cyclic Shifts](#sort-doubled-cyclic-shifts)
* [Updating Equivalence Classes](#updating-equivalence-classes)

## Lecture
### Memory Efficient Data Structure
![](docs/goal.png)
![](docs/alphabet.png)
![](docs/lexographic_order.png)
![](docs/lexographic_order_example.png)
![](docs/suffix_array_example.png)
![](docs/append_dollar_consistent_check.png)
![](docs/suffix_array_example_same_with_dollar.png)

#### Memory Storage Problem
![](docs/memory_storage_problem.png)

#### Quiz
![](docs/quiz1.png)

#### Memory Storage Solution
![](docs/memory_storage_solution.png)

#### Suffix Array Order
Use the [Burrows-Wheeler Transform Matrix](../2_week_suffix_arrays/1_burrows_wheeler_transform)
(i.e. the sorted Cyclic Rotations) to find and order all suffixes of the original string ```ababaa$```:

```
$ababaa
a$ababa
aa$abab
abaa$ab
ababaa$
baa$aba
babaa$a
```

Remove all characters after the ```$``` delimiter and only the ordered suffixes remain:

```
$
a$
aa$
abaa$
ababaa$
baa$
babaa$
```

The **Suffix Array Order** is the begin index of each of the ordered suffixes in the original string:

![](docs/order_example0.png)

```

ababaa$
01234567

order   suffix
-----   ------
        $
        a$
        aa$
        abaa$
        ababaa$
        baa$
        babaa$
```

![](docs/order_example1.png)

```
      v
ababaa$
01234567
      ^

order   suffix
-----   ------
    6   $
        a$
        aa$
        abaa$
        ababaa$
        baa$
        babaa$
```

![](docs/order_example2.png)

```
     vv
ababaa$
01234567
     ^^ 

order   suffix
-----   ------
    6   $
    5   a$
        aa$
        abaa$
        ababaa$
        baa$
        babaa$
```

![](docs/order_example3.png)

```
    vvv
ababaa$
01234567
    ^^^

order   suffix
-----   ------
    6   $
    5   a$
    4   aa$
        abaa$
        ababaa$
        baa$
        babaa$
```

![](docs/order_example4.png)

```
  vvvvv
ababaa$
01234567
  ^^^^^    

order   suffix
-----   ------
    6   $
    5   a$
    4   aa$
    2   abaa$
        ababaa$
        baa$
        babaa$
```

![](docs/order_example5.png)

```
vvvvvvv
ababaa$
01234567
^^^^^^^    

order   suffix
-----   ------
    6   $
    5   a$
    4   aa$
    2   abaa$
    0   ababaa$
        baa$
        babaa$
```

![](docs/order_example6.png)

```
   vvvv
ababaa$
01234567
   ^^^^    

order   suffix
-----   ------
    6   $
    5   a$
    4   aa$
    2   abaa$
    0   ababaa$
    3   baa$
        babaa$
```

![](docs/order_example7.png)

```
 vvvvvv
ababaa$
01234567
 ^^^^^^    

order   suffix
-----   ------
    6   $
    5   a$
    4   aa$
    2   abaa$
    0   ababaa$
    3   baa$
    1   babaa$
```

![](docs/order_example8.png)


### General Strategy for Construction
![](docs/sort_cyclic_shifts0.png)
![](docs/sort_cyclic_shifts1.png)
![](docs/sort_cyclic_shifts2.png)
![](docs/sort_cyclic_shifts3.png)
![](docs/sort_cyclic_shifts4.png)
![](docs/sort_cyclic_shifts_lemma.png)

#### Quiz
![](docs/quiz2.png)

#### Partial Cyclic Shifts
![](docs/partial_shift0.png)
![](docs/partial_shift1.png)
![](docs/partial_shift2.png)

#### Partial Cyclic Shift Strategy
![](docs/partial_shift_strategy.png)

#### Partial Cyclic Shift Example
![](docs/partial_shift_example1.png)
![](docs/partial_shift_example2.png)
![](docs/partial_shift_example3.png)
![](docs/partial_shift_example4.png)
![](docs/partial_shift_example5.png)
![](docs/partial_shift_example6.png)

### Initialization
#### Counting Sort
![](docs/count_sort1.png)
![](docs/count_sort2.png)
![](docs/count_sort3.png)

#### Equivalence Classes
![](docs/eq_class1.png)
![](docs/eq_class_pseudocode.png)
![](docs/eq_class_lemma.png)
![](docs/eq_class2.png)
![](docs/eq_class3.png)
![](docs/eq_class4.png)
![](docs/eq_class5.png)
![](docs/eq_class6.png)
![](docs/eq_class7.png)
![](docs/eq_class8.png)
![](docs/eq_class9.png)

### Sort Doubled Cyclic Shifts
![](docs/sort_dub_idea.png)
![](docs/sort_dub_example.png)
![](docs/stable_sort_pairs.png)

#### Example
![](docs/dub_cyclic_shift01.png)
![](docs/dub_cyclic_shift02.png)
![](docs/dub_cyclic_shift03.png)
![](docs/dub_cyclic_shift04.png)
![](docs/dub_cyclic_shift05.png)
![](docs/dub_cyclic_shift06.png)
![](docs/dub_cyclic_shift07.png)
![](docs/dub_cyclic_shift08.png)
![](docs/dub_cyclic_shift09.png)
![](docs/dub_cyclic_shift10.png)
![](docs/dub_cyclic_shift11.png)
![](docs/dub_cyclic_shift12.png)

The following slides appear to have incorrect values for ```C6'``` and ```C3'```.  I believe the values
in yellow are reversed:

```
Incorrect values?

C6' = $aba
C3' = baba

Correct values?

C6' = baba
C3' = $aba
```

![](docs/dub_cyclic_shift13.png)
![](docs/dub_cyclic_shift14.png)
![](docs/dub_cyclic_shift15.png)
![](docs/dub_cyclic_shift16.png)

#### Stable Sort
Required for ```C0'``` and ```C2'``` to remain in sorted order since we are only sorting my the first half
and the second half is already sorted:
![](docs/dub_cyclic_shift17.png)

#### Pseudocode
![](docs/dub_cyclic_shift_pseudo1.png)
![](docs/dub_cyclic_shift_pseudo2.png)
![](docs/dub_cyclic_shift_pseudo3.png)
![](docs/dub_cyclic_shift_pseudo4.png)
![](docs/dub_cyclic_shift_lemma.png)

#### Quiz
![](docs/quiz3_1.png)
![](docs/quiz3_2.png)
![](docs/quiz3_3.png)
```
    For this quiz, calculate start[ i ]:

    start <- ( order[ i ] - L + |S| ) mod |S|
    
    
    S = ababaa$
    
    ( recall: Suffix Array 'order' == begin index of the ordered suffixes of the original string S )
    
    order   suffix    
    -----   ------
        6   $
        5   a$
        4   aa$
        2   abaa$
        0   ababaa$
        3   baa$
        1   babaa$
    
      L = 2
    |S| = 7
    
    ( order[ 6 ] - L + |S| ) % |S| == ( 1 - 2 + 7 ) % 7 == 6
    ( order[ 5 ] - L + |S| ) % |S| == ( 3 - 2 + 7 ) % 7 == 1
    ( order[ 4 ] - L + |S| ) % |S| == ( 0 - 2 + 7 ) % 7 == 5
    ( order[ 3 ] - L + |S| ) % |S| == ( 2 - 2 + 7 ) % 7 == 0
    ( order[ 2 ] - L + |S| ) % |S| == ( 4 - 2 + 7 ) % 7 == 2
    ( order[ 1 ] - L + |S| ) % |S| == ( 5 - 2 + 7 ) % 7 == 3
    ( order[ 0 ] - L + |S| ) % |S| == ( 6 - 2 + 7 ) % 7 == 4
                                                           ^
                                                           ^
    start[ i ] = [6,1,5,0,2,3,4] > > > > > > > > > > > > > ^
             i =  6 5 4 3 2 1 0
    
    
    Next sort by the equivalence classes of the double cyclic shifts
    to derive the 'newOrder' 
    
    for i from |S| - 1 down to 0:
        cl <- class[ start ]
        count[ cl ] <- count[ cl ] - 1
        newOrder[ count[ cl ] ] <- start
    
    S = ababaa$
    C = 1212110  ( equivalence class )
    i = 01234567
    
    i   start   class   newOrder ( counting sort ordered by the first pair [ in-place for ties to be broken by second pair ] )
    -   -----   -----   --------
    0   6       1   
    1   1       2
    2   5       1
    3   0       2
    4   2       1
    5   3       1
    6   4       0 
    7
        
    i = 6
    cl = class[ 4 ] = 0
    count[ cl ] = count[ 0 ] =  
    
```

### Updating Equivalence Classes
![](docs/updating_classes.png)

#### Quiz
![](docs/num_eq_class_after_dub.png)



### FAQ
* [http://bioinformaticsalgorithms.com/faqs/bwt.html](http://bioinformaticsalgorithms.com/faqs/bwt.html)

## Problem
![](docs/2_problem.png)
![](docs/2_problem1.png)

## Solutions
* [C++](#cpp)

### CPP
```cpp

```
