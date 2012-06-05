#include <cstdio>
#include <map>
#include <algorithm>
#include <cassert>

#define NDEBUG

using namespace std;

typedef unsigned long long int lli;
typedef pair< pair< int, int >, pair< lli, lli > > state;

FILE* in = fopen( "box.in", "r" );
FILE* out = fopen( "box.out", "w" );

map< state, lli > memo;
lli a[ 105 ], b[ 105 ];
int A[ 105 ], B[ 105 ];

lli W( int i, int j, lli n, lli m ) {
    assert( i >= 0 );
    assert( j >= 0 );
    assert( n >= 0 );
    assert( m >= 0 );

    if ( i == 0 || j == 0 ) {
        return 0;
    }

    state key = make_pair( make_pair( i, j ), make_pair( n, m ) );
    map< state, lli >::iterator f = memo.find( key );
    lli ret;
    lli ca = a[ i ] - n, cb = b[ j ] - m;

    if ( f != memo.end() ) {
        return f->second;
    }
    if ( A[ i ] == B[ j ] ) {
        if ( ca == cb ) {
            ret = W( i - 1, j - 1, 0, 0 ) + ca;
#ifndef NDEBUG
            printf(
                "By taking %lld from both A and B of kind %i and expanding on W[ %i ][ %i ][ %lld ][ %lld ]:\n",
                ca, A[ i ], i - 1, j - 1, ( lli )0, ( lli )0
            );
#endif
        }
        else if ( ca > cb ) {
            // printf( "More of a!\n" );
            ret = W( i, j - 1, n + cb, 0 ) + cb;
#ifndef NDEBUG
            printf(
                "By taking %lld from A of kind %i and %lld from B of kind %i and expanding on W[ %i ][ %i ][ %lld ][ %lld ]:\n",
                ca - cb, A[ i ], cb, B[ j ], i, j - 1, n + cb, ( lli )0
            );
#endif
        }
        else {
            // printf( "More of b!\n" );
            // cb > ca
            ret = W( i - 1, j, 0, m + ca ) + ca;
#ifndef NDEBUG
            printf(
                "By taking %lld from A of kind %i and %lld from B of kind %i and expanding on W[ %i ][ %i ][ %lld ][ %lld ]:\n",
                ca, A[ i ], cb - ca, B[ j ], i - 1, j, ( lli )0, m + ca
            );
#endif
        }
    }
    else {
        // printf( "Mismatch!\n" );
        lli W1 = W( i - 1, j, 0, m );
        lli W2 = W( i, j - 1, n, 0 );

        if ( W1 > W2 ) {
            ret = W1;
#ifndef NDEBUG
            printf(
                "By dropping %lld from A of kind %i and expanding on W[ %i ][ %i ][ %lld ][ %lld ]:\n",
                ca, A[ i ], i - 1, j, ( lli )0, m
            );
#endif
        }
        else {
            ret = W2;
#ifndef NDEBUG
            printf(
                "By dropping %lld from B of kind %i and expanding on W[ %i ][ %i ][ %lld ][ %lld ]:\n",
                cb, B[ j ], i, j - 1, n, ( lli )0
            );
#endif
        }
    }

#ifndef NDEBUG
    printf( "W[ %i ][ %i ][ %lld ][ %lld ] = %lld\n", i, j, n, m, ret );
#endif

    assert( ret >= 0 );

    return memo[ key ] = ret;
}

int main() {
    int T, M, N, t, i;

    fscanf( in, "%i", &T );
    for ( t = 1; t <= T; ++t ) {
        printf( "Case %i\n", t );
        fprintf( out, "Case #%i: ", t );
        memo = map< state, lli >();
        fscanf( in, "%i %i", &N, &M );
        for ( i = 1; i <= N; ++i ) {
            fscanf( in, "%lld %i", &a[ i ], &A[ i ] );
        }
        for ( i = 1; i <= M; ++i ) {
            fscanf( in, "%lld %i", &b[ i ], &B[ i ] );
        }
        // printf( "B[ 4 ] = %i\n", B[ 4 ] );
        fprintf( out, "%lld\n", W( N, M, 0, 0 ) );
    }
    return 0;
}
