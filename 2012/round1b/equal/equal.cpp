#include <cstdio>
#include <map>
#include <set>

using namespace std;

struct partition {
    set< int > one;
    set< int > two;
};

int t;
FILE* in = fopen( "equal.in", "r" );
FILE* out = fopen( "equal.out", "w" );

void solution( partition result ) {
    int cnt;
    
    fprintf( out, "Case #%i:\n", t );
    cnt = 0;
    for ( set< int >::iterator it = result.one.begin(); it != result.one.end(); ++it ) {
        fprintf( out, "%i", *it );
        ++cnt;
        if ( cnt < result.one.size() ) {
            fprintf( out, " " );
        }
    }
    fprintf( out, "\n" );
    cnt = 0;
    for ( set< int >::iterator it = result.two.begin(); it != result.two.end(); ++it ) {
        fprintf( out, "%i", *it );
        ++cnt;
        if ( cnt < result.two.size() ) {
            fprintf( out, " " );
        }
    }
    fprintf( out, "\n" );
}

void print( map< int, partition > B ) {
    for ( map< int, partition >::iterator it = B.begin(); it != B.end(); ++it ) {
        printf( "%i ", it->first );
    }
    printf( "\n" );
}

int main() {
    int T, N, i, j, a;
    map< int, partition > *A = new map< int, partition >(), *B, *C;

    printf( "Running...\n" );
    fscanf( in, "%i", &T );
    for ( t = 1; t <= T; ++t ) {
        printf( "Testcase %i: ", t );
        fscanf( in, "%i", &N );
        partition p;
        p.one = set< int >();
        p.two = set< int >();
        delete A;
        A = new map< int, partition >();
        ( *A )[ 0 ] = p;
        bool solved = false;
        for ( i = 0; i < N; ++i ) {
            printf( "%i ", i );
            fflush( stdout );
            fscanf( in, "%i", &a );
            if ( !solved ) {
                B = new map< int, partition >();
                for ( map< int, partition >::iterator it = A->begin(); it != A->end(); ++it ) {
                    ( *B )[ it->first + a ] = it->second; // group I
                    ( *B )[ it->first + a ].one.insert( a );

                    if ( it->first + a == 0 ) {
                        solution( ( *B )[ it->first + a ] );
                        solved = true;
                        break;
                    }

                    if ( it->first - a >= 0 ) {
                        ( *B )[ it->first - a ] = it->second; // group II
                        ( *B )[ it->first - a ].two.insert( a );

                        if ( it->first - a == 0 ) {
                            solution( ( *B )[ it->first - a ] );
                            solved = true;
                            break;
                        }
                    }

                    ( *B )[ it->first ] = it->second; // neither
                }
                C = A;
                A = B;
                delete C;
            }
        }
        printf( "\n" );
        if ( !solved ) {
            fprintf( out, "Case #%i:\nImpossible\n", t );
        }
    }
    fscanf( in, "%i", &N );
    return 0;
}
