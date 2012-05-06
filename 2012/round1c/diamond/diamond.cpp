#include <cstdio>
#include <vector>
#include <list>
#include <stack>
#include <set>

using namespace std;

FILE* in = fopen( "diamond.in", "r" );
// FILE* out = fopen( "diamond.out", "w" );

vector< list< int > > E;
vector< int > numParents;
set< int > visited;

int main() {
    int T, N, M, t, i, j, u, v;

    fscanf( in, "%i", &T );
    for ( t = 1; t <= T; ++t ) {
        printf( "Case #%i: ", t );
        numParents = vector< int >();
        E = vector< list< int > >();
        fscanf( in, "%i", &N );
        for ( i = 0; i < N; ++i ) {
            numParents.push_back( 0 );
        }
        for ( u = 0; u < N; ++u ) {
            E.push_back( list< int >() );
            fscanf( in, "%i", &M );
            for ( j = 0; j < M; ++j ) {
                fscanf( in, "%i", &v );
                --v;
                E[ u ].push_back( v );
                ++numParents[ v ];
            }
        }
        bool diamond = false;
        for ( i = 0; i < N; ++i ) {
            if ( numParents[ i ] == 0 ) {
                // printf( "New dfs: %i\n", i + 1 );
                visited = set< int >();
                stack< int > s;

                s.push( i );
                while ( !s.empty() ) {
                    v = s.top();
                    s.pop();
                    for ( list< int >::iterator it = E[ v ].begin(); it != E[ v ].end(); ++it ) {
                        // printf( "Visiting %i\n", *it + 1 );
                        if ( visited.find( *it ) != visited.end() ) {
                            printf( "Yes\n" ); //, *it + 1, visited.size() );
                            diamond = true;
                            break;
                        }
                        visited.insert( *it );
                        s.push( *it );
                    }
                    if ( diamond ) {
                        break;
                    }
                }
            }
            if ( diamond ) {
                break;
            }
        }
        if ( !diamond ) {
            printf( "No\n" );
        }
    }
    return 0;
}
