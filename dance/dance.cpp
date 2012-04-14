#include <cstdio>

using namespace std;

int main() {
    int T, N, S, p, b, a, m, A, M, c;

    scanf( "%i", &T );
    for ( int t = 1; t <= T; ++t ) {
        scanf( "%i", &N );
        scanf( "%i", &S );
        scanf( "%i", &p );
        c = 0;
        for ( int i = 0; i < N; ++i ) {
            scanf( "%i", &b );
            m = a = b / 3;
            if ( b % 3 == 1 || b % 3 == 2 ) {
                ++m;
            }
            A = b - 3;
            switch ( b % 3 ) {
                case 1:
                    --A;
                    break;
                case 2:
                    ++A;
                    break;
            }
            A /= 3;
            M = A + 2;
            if ( m >= p ) {
                ++c;
            }
            else if ( A >= 0 && S && M >= p ) {
                ++c;
                --S;
            }
        }
        printf( "Case #%i: %i\n", t, c );
    }
    return 0;
}
