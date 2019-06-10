#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using Vertex = int;
using Graph = unordered_map< Vertex, unordered_set< Vertex > >;
using Seen = unordered_set< Vertex >;
using Components = vector< vector< Vertex > >;
using Sorted = vector< Vertex >;
using Stack = vector< Vertex >;
using Path = vector< Vertex >;

class Solution {
public:
    Components getSCC( Graph& G, int N, Components SCC={}, Stack S={}, Seen seen={} ){
        auto L = topo_sort( reverse( G ), N );
        for( auto vertex: L ){
            if( ! seen.insert( vertex ).second )
                continue;
            S.push_back( vertex );
            Path P;
            while( ! S.empty() ){
                auto u = S.back(); S.pop_back();
                P.push_back( u );
                for( auto v: G[ u ] )
                    if( seen.insert( v ).second )
                        S.push_back( v );
            }
            SCC.emplace_back( P );
        }
        return SCC;
    }
private:
    Graph reverse( Graph& G ){
        Graph R{ G };        // (R)eversed (G)raph: keep G's vertex keys ( pair.first ),
        for( auto& pair: R ) // but clear G's adjacency lists ( pair.second )
            pair.second = {};
        for( auto& pair: G ){
            auto u = pair.first;
            for( auto v: G[ u ] )   // u -> v
                R[ v ].insert( u ); // v -> u
        }
        return R;
    }

    Sorted topo_sort( Graph&& G, int N, Seen seen={} ){
        Sorted S( N );
        for( auto i{ 1 }, K{ N-1 }; i <= N; ++i ){
            if( seen.insert( i ).second )
                go( S, move( G ), i, K, seen );
        }
        return S;
    }

    void go( Sorted& S, Graph&& G, Vertex u, int& K, Seen& seen ){
        for( auto v: G[ u ] )
            if( seen.insert( v ).second )
                go( S, move( G ), v, K, seen );
        S[ K-- ] = u;
    }
};

int main() {
    Solution s;
    Graph G;
    auto N{ 0 }, M{ 0 }; cin >> N >> M;
    for( Vertex u{ 0 }, v{ 0 }; M-- && cin >> u >> v; G[ u ].insert( v ) );
    auto SCC = s.getSCC( G, N );
    cout << SCC.size() << endl;
    return 0;
}
