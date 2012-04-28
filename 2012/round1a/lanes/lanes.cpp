#include <cstdio>
#include <algorithm>

using namespace std;

const double EPSILON = 0.00000001;
const double INF = 987654321.0;

struct car {
    char lane;
    double x;
    double v;
};
car cars[ 52 ];
int T, N;
double m, total;

bool canMove( int i ) {
    for ( int k = 0; k < N; ++k ) {
        if ( k == i ) {
            continue;
        }
        if ( cars[ i ].lane == cars[ k ].lane ) {
            continue;
        }
        if ( cars[ k ].x > cars[ i ].x && cars[ k ].x < cars[ i ].x + 5
          || cars[ k ].x + 5 > cars[ i ].x && cars[ k ].x + 5 < cars[ i ].x + 5 ) {
            return true;
        }
    }
    return false;
}

void simulate() {
    do {
        m = INF;
        for ( int i = 0; i < N; ++i ) {
            for ( int j = 0; j < N; ++j ) {
                if ( i == j ) {
                    continue;
                }
                if ( cars[ i ].lane != cars[ j ].lane ) {
                    continue;
                }
                if ( cars[ i ].x + 5.0 < cars[ j ].x - EPSILON ) {
                    double x1 = cars[ i ].x + 5.0;
                    double x2 = cars[ j ].x;
                    double v1 = cars[ i ].v;
                    double v2 = cars[ j ].v;
                    if ( v1 == v1 ) {
                        continue;
                    }
                    double t = ( x1 - x2 ) / ( v2 - v1 );
                    if ( t < 0 ) {
                        continue;
                    }
                    if ( t < EPSILON ) {
                        if ( canMove( i ) ) {
                            cars[ i ].lane = cars[ i ].lane == 'L'? 'R': 'L';
                        }
                        else if ( canMove( j ) ) {
                            cars[ j ].lane = cars[ j ].lane == 'L'? 'R': 'L';
                        }
                        else {
                            return;
                        }
                    }
                    m = min( m, t );
                }
            }
        }
        if ( m == INF ) {
            break;
        }
        else {
            for ( int i = 0; i < N; ++i ) {
                cars[ i ].x += m * cars[ i ].v;
            }
            total += m;
        }
    } while ( m != INF );
}

int main() {
    scanf( "%i", &T );
    for ( int t = 1; t <= T; ++t ) {
        scanf( "%i", &N );
        for ( int i = 0; i < N; ++i ) {
            // printf( "Input car %i: ", i );
            scanf( "%c %f %f\n", &cars[ i ].lane, &cars[ i ].x, &cars[ i ].v );
        }
        total = 0;
        printf( "Case #%i: ", t );
        simulate();
        if ( m == INF ) {
            printf( "Possible\n" );
        }
        else {
            printf( "%2.6f\n", total );
        }
    }
    return 0;
}
