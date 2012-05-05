#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

int main() {
    float J[ 205 ];
    int k, T, N;

    printf( "Input:\n" );
    scanf( "%i", &T );
    for ( int t = 1; t <= T; ++t ) {
        printf( "Case #%i: ", t );
        scanf( "%i", &N );
        int X = 0, s;
        for ( int i = 0; i < N; ++i ) {
            scanf( "%f", &J[ i ] );
            X += J[ i ];
        }
        for ( int i = 0; i < N; ++i ) {
            float yi = 0, M = 987432100.0, M2 = 98765123.00;
            int Mi, M2i;

            while ( yi == 0 ) {
                for ( int j = 0; j < N; ++j ) {
                    if ( J[ j ] < M ) {
                        M2 = M;
                        M2i = Mi;
                        M = J[ j ];
                        Mi = j;
                    }
                    else if ( J[ j ] < M2 && J[ j ] != M ) { 
                        M2 = J[ j ];
                        M2i = j;
                    }
                }
                int cnt = 0;
                for ( int j = 0; j < N; ++j ) {
                    if ( J[ j ] == Mi ) {
                        ++cnt;
                    }
                }
                float d = M2 - M;
                float pos = min( d, ( 1 - yi ) * X / cnt );
                for ( int j = 0; j < N; ++j ) {
                    if ( j == Mi ) {
                        J[ j ] += pos;
                    }
                }
                yi += min( ( 1 - yi ) * X / cnt, cnt * d / X );
            }

            printf( "%2.7f", yi );
            if ( i < N - 1 ) {
                printf( " " );
            }
        }
        printf( "\n" );
    }
    return 0;
}
