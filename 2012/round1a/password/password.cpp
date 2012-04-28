#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int T, A, B, pi;
    float strategy;

    scanf( "%i", &T );
    // printf( "Solving %i instances.\n", T );
    for ( int t = 1; t <= T; ++t ) {
        scanf( "%i %i", &A, &B );
        // printf( "A = %i, B = %i\n", A, B );
        float pk, p = 1;
        strategy = min( B + 2, A + B + 1 );
        // printf( "Expected with immediate enter: %i\n", B + 2 );
        // printf( "Expected with full backspace: %i\n", A + B + 1 );
        for ( int i = 1; i <= A; ++i ) {
            // printf( "Input %i-th probability: ", i );
            scanf( "%f", &pk );
            p *= pk;
            int goodkeystrokes = A - 2 * i + B + 1;
            int badkeystrokes = goodkeystrokes + B + 1;
            // printf( "Good keystrokes: %i\n", goodkeystrokes );
            // printf( "Bad keystrokes: %i\n", badkeystrokes );
            // printf( "Probability: %2.6f\n", p );
            // printf(
            //     "Expected with %i backspaces: %2.6f\n",
            //     A - i, 
            //     goodkeystrokes * p + badkeystrokes * ( 1 - p )
            // );
            strategy = min(
                strategy,
                goodkeystrokes * p + badkeystrokes * ( 1 - p )
            );
        }
        printf( "Case #%i: %2.6f\n", t, strategy );
    }

    return 0;
}
