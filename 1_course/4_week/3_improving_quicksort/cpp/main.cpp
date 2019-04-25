/**
 *
 * Modern C++ implementation of Quick Sort algorithm to sort a collection using 3-way partition
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

template< typename Type >
class Solution
{
public:
    using Collection = vector< Type >;
    using Iter = typename Collection::iterator;
    void quickSort( Collection& A ){
        go( A, A.begin(), A.end() );
    }
private:
    void go( Collection& A, Iter L, Iter R ){   // go() sorts from [ L : R ), that is, from L (inclusive) to R (non-inclusive)
        if( L >= R )
            return;
        iter_swap( L, random( L, R ));          // set pivot as first element
        auto[ M1, M2 ] = partition3( A, L, R );
        go( A, L, M1 );
        go( A, M2, R );
    }
    Iter partition( Collection& A, Iter L, Iter R ){
        auto threshold{ L }, less{ L+1 };
        for( auto more{ less }; more != R; ++more )
            if( *more < *threshold )
                iter_swap( less++, more );
        auto pivot{ less-1 };
        iter_swap( L, pivot );
        return pivot;
    }
    pair< Iter, Iter > partition3( Collection& A, Iter L, Iter R ){
        auto P = partition( A, L, R ),
             M1{ P },
             M2{ P };
        for( auto i{ R-1 }; M2 <= i; )
            if( *i == *P )
                iter_swap( i, M2++ );
            else
                --i;
        return{ M1, M2 };

    }
    using RandomDevice = random_device;
    using Generator = mt19937;
    using Distribution = uniform_int_distribution< int >;
    Iter random( Iter L, Iter R, RandomDevice randomDevice=RandomDevice() ){
        Generator randomGenerator{ randomDevice() };
        int size = distance( L, R-1 );        // R-1 since R is non-inclusive
        Distribution distribution{ 0, size }; // distribution from [ 0 : size ], that is 0 ( inclusive ) to size ( inclusive )
        return L + distribution( randomGenerator );
    }
};

int main() {
    using Type = size_t;
    Solution< Type > solution;
    Solution< Type >::Collection A;
    auto N{ 0 }; cin >> N;
    copy_n( istream_iterator< Type >( cin ), N, back_inserter( A ));
    solution.quickSort( A );
    copy( A.begin(), A.end(), ostream_iterator< Type >( cout, " " ));
    return 0;
}
