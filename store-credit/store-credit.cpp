#include <cstdio>

using namespace std;

int main() {
    int N, I, C;
    int P[ 2002 ];

    scanf( "%i", &N );
    for ( int t = 1; t <= N; ++t ) {
        scanf( "%i", &C );
        scanf( "%i", &I );
        for ( int j = 1; j <= I; ++j ) {
            scanf( "%i", &P[ j ] );
        }
        for ( int j = 1; j <= I - 1; ++j ) {
            for ( int k = j + 1; k <= I; ++k ) {
                if ( P[ j ] + P[ k ] == C ) {
                    printf( "Case #%i: %i %i\n", t, j, k );
                }
            }
        }
    }
}
