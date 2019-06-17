# 4. Suffix Array
* [https://en.wikipedia.org/wiki/Suffix_array](https://en.wikipedia.org/wiki/Suffix_array)

## Lecture
### Quiz
![](docs/quiz1.png)

The answer for this quiz is derived from the Burrows-Wheeler Transform Maxtrix of ```GAGAGAGA$```:
```
    $GAGAGAGA
    A$GAGAGAG
    AGA$GAGAG
    AGAGA$GAG
    AGAGAGA$G
    GA$GAGAGA
    GAGA$GAGA
    GAGAGA$GA
    GAGAGAGA$
```

![](docs/quiz2.png)

The answer for this quiz is derived from the Burrows-Wheeler Transform Maxtrix of ```ACGACA$```:
```
    Burrows-Wheeler Transform: ACG$AAC
    Original Genome:           ACGACA$
    
Pattern: ACA  ->  A"CA"  ->  A->C

    suffix  BWT      mismatch  first-
    array   matrix   count     last
    index
    6       $ACGACA 
    5       A$ACGAC  0         A1->C1
    3       ACA$ACG  1         A2->G1
    0       ACGACA$  1         A3->$1
    4       CA$ACGA
    1       CGACA$A
    2       GACA$AC

Pattern: AC  ->  "AC"  ->  C->A

    suffix  BWT      mismatch  first-
    array   matrix   count     last
    index
    6       $ACGACA  1         $1->A1
    5       A$ACGAC  
    3       ACA$ACG  
    0       ACGACA$  
    4       CA$ACGA  0         C1->A2
    1       CGACA$A  
    2       GACA$AC  2         N/A (more than 1 mismatch)

Pattern: C  ->  "A"  ->  A

    suffix  BWT      mismatch  first
    array   matrix   count     
    index
    6       $ACGACA
    5       A$ACGAC  1         A1      
    3       ACA$ACG  0         A2
    0       ACGACA$  
    4       CA$ACGA  
    1       CGACA$A  
    2       GACA$AC

Where is A1 and A2 in the original genome?

A1 exists at index 0 with 1 mismatch
A2 exists at index 3 with 0 mismatches

```

### FAQ
* [http://bioinformaticsalgorithms.com/faqs/bwt.html](http://bioinformaticsalgorithms.com/faqs/bwt.html)

### Pseudocode for Pattern Matching with Suffix Array
![](docs/suffix_array_pattern_match.png)

## Problem
![](docs/4_problem1.png)
![](docs/4_problem2.png)

## Solutions
* [C++](#cpp)

### CPP
```cpp

```
