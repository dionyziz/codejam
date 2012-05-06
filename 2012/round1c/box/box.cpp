#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;

typedef pair< pair< int, int >, pair< int, int > > state;

FILE* in = fopen( "box.in", "r" );
FILE* out = fopen( "box.out", "w" );

map< state, int > memo;
int a[ 105 ], A[ 105 ], b[ 105 ], B[ 105 ];

int W( int i, int j, int n, int m ) {
    // printf( "W[ %i ][ %i ][ %i ][ %i ]\n", i, j, n, m );

    if ( i == 0 || j == 0 ) {
        return 0;
    }

    state key = make_pair( make_pair( i, j ), make_pair( n, m ) );
    map< state, int >::iterator f = memo.find( key );
    int ret;
    int ca = a[ i ] - n, cb = b[ j ] - m;

    if ( f != memo.end() ) {
        return f->second;
    }
    if ( A[ i ] == B[ j ] ) {
        if ( ca == cb ) {
            // printf( "Equal!\n" );
            ret = W( i - 1, j - 1, 0, 0 ) + ca;
        }
        if ( ca > cb ) {
            // printf( "More of a!\n" );
            ret = W( i, j - 1, ca - cb, 0 ) + cb;
        }
        else {
            // printf( "More of b!\n" );
            // cb > ca
            ret = W( i - 1, j, cb - ca, 0 ) + ca;
        }
    }
    else {
        // printf( "Mismatch!\n" );
        ret = max(
            W( i - 1, j, 0, m ), W( i, j - 1, n, 0 )
        );
    }

    return memo[ key ] = ret;
}

int main() {
    int T, M, N, t, i;

    fscanf( in, "%i", &T );
    for ( t = 1; t <= T; ++t ) {
        fprintf( out, "Case #%i: ", t );
        memo = map< state, int >();
        fscanf( in, "%i %i", &N, &M );
        for ( i = 1; i <= N; ++i ) {
            fscanf( in, "%i %i", &a[ i ], &A[ i ] );
        }
        for ( i = 1; i <= M; ++i ) {
            fscanf( in, "%i %i", &b[ i ], &B[ i ] );
        }
        fprintf( out, "%i\n", W( N, M, 0, 0 ) );
    }
    return 0;
}
