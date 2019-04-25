/**
 *
 * C++ implementation of a max stack [ maximum stack value lookup in O(1) time ]
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

template< typename Type >
class Stack {
public:
    void push( Type val ){
        stack_.push_back( val );
        if( max_.empty() || max_.back() <= val )
            max_.push_back( val );
    }
    int pop(){
        auto result = stack_.back();
        stack_.pop_back();
        if( result == max_.back() )
            max_.pop_back();
        return result;
    }
    int max() const {
        return max_.back();
    }
private:
    vector< Type > stack_, max_;
};

int main() {
    using Type = int;
    auto N{ 0 }; cin >> N;
    Stack< Type > stack;
    for( string line, cmd; getline( cin, line ); ){
        istringstream parser{ line };
        parser >> cmd;
        if( cmd.find( "push" ) != string::npos )
            for( Type val{ 0 }; parser >> val; stack.push( val ));
        else
        if( cmd.find( "pop" ) != string::npos )
            stack.pop();
        else
        if( cmd.find( "max" ) != string::npos )
            cout << stack.max() << endl;
    }
    return 0;
}
