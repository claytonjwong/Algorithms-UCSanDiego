/**
 *
 * C++ implementation to find the maximum number of prizes
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <stdio.h>
#include <stdlib.h>

typedef int Type;
const Type INF = 1e9 + 1;

struct List_t {
    Type val;
    struct List_t* next;
};
typedef struct List_t List;
typedef List* HList;
HList createNode( Type val ) {
    HList node = malloc( sizeof( List ));
    node->val = val;
    node->next = NULL;
    return node;
}
HList appendNode( HList tail, Type val ){
    tail->next = malloc( sizeof( List ));
    tail = tail->next;
    tail->val = val;
    tail->next = NULL;
    return tail;
}

HList maxNumPrizes( Type N ){
    HList head = createNode( INF ),
          tail = head;
    size_t size = 0;
    for( Type i=1; i+1 <= N-i; N-=i, ++i, ++size )
        tail = appendNode( tail, i );
    if( 0 < N )
        tail = appendNode( tail, N ), ++size;
    printf( "%zu\n", size );
    return head;
}

int main() {
    Type N = 0, size = 0;
    scanf( "%d", &N );
    for( HList ans=maxNumPrizes( N )->next; ans; ans=ans->next ) // head is a sentinel, the (ans)wer is head->next
        printf( "%d ", ans->val );
    printf( "\n" );
    return 0;
}
