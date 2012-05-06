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
vector< bool > visited;

int main() {
    int T, N, M, t, i, j, u, v;

    fscanf( in, "%i", &T );
    for ( t = 1; t <= T; ++t ) {
        printf( "Case #%i: ", t );
        numParents = vector< int >();
        visited = vector< bool >();
        E = vector< list< int > >();
        fscanf( in, "%i", &N );
        for ( i = 0; i < N; ++i ) {
            numParents.push_back( 0 );
            visited.push_back( false );
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
                stack< int > s;

                s.push( i );
                while ( !s.empty() ) {
                    v = s.top();
                    s.pop();
                    for ( list< int >::iterator it = E[ v ].begin(); it != E[ v ].end(); ++it ) {
                        if ( visited[ *it ] ) {
                            printf( "Yes\n" );
                            diamond = true;
                            break;
                        }
                        visited[ *it ] = true;
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
