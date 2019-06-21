# 4. Suffix Array
* [https://en.wikipedia.org/wiki/Suffix_array](https://en.wikipedia.org/wiki/Suffix_array)

## Contents
* [Memory Efficient Data Structure](#memory-efficient-data-structure)
* [General Strategy for Construction](#general-strategy-for-construction)
* [Initialization](#initialization)
* [Sort Doubled Cyclic Shifts](#sort-doubled-cyclic-shifts)

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

### FAQ
* [http://bioinformaticsalgorithms.com/faqs/bwt.html](http://bioinformaticsalgorithms.com/faqs/bwt.html)



## Problem

## Solutions
* [C++](#cpp)

### CPP
```cpp

```
