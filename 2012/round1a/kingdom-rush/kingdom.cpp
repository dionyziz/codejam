#include <cstdio>
#include <set>

using namespace std;

struct game {
    int star1;
    int star2;
    int score;
};

bool operator <( game a, game b ) {
    if ( a.score != b.score ) {
        if ( a.score == 2 ) {
            return 1;
        }
        else if ( b.score == 2 ) {
            return 0;
        }
    }
    return a.star2 < b.star2;
}

int main() {
    int T, N, a, b, stars, cnt;
    multiset< game > games;
    game current;
    bool win;

    // printf( "Input number of testcases: \n" );
    scanf( "%i", &T );
    // printf( "Running over %i testcases.\n", T );
    for ( int t = 1; t <= T; ++t ) {
        // printf( "Case #%i: ", t );
        scanf( "%i", &N );
        // printf( "Running over %i levels.\n", N );
        games = multiset< game >();
        for ( int i = 0; i < N; ++i ) {
            current.score = 0;
            scanf( "%i %i", &current.star1, &current.star2 );
            games.insert( current );
        }
        cnt = stars = 0;
        // printf( "Solving testcase %i.\n", t );
        do {
            // printf( "Iterating.\n" );
            win = false;
            for ( set< game >::iterator it = games.begin();
                  it != games.end(); ) {
                if ( it->star2 <= stars ) {
                    // printf( "Have %i stars.\n", stars );
                    // printf( "Picked game ( %i, %i ) for 2 stars with a score of %i.\n", it->star1, it->star2, it->score );
                    stars += 2 - it->score;
                    games.erase( it++ );
                    // printf( "Now have %i stars.\n", stars );
                    win = true;
                    ++cnt;
                }
                else {
                    break;
                }
            }
            int m = -1;
            set< game >::iterator mit;

            for ( set< game >::iterator it = games.begin();
                  it != games.end(); ++it ) {
                if ( it->score == 0 && it->star1 <= stars ) {
                    if ( it->star2 > m ) {
                        m = it->star2;
                        mit = it;
                    }
                }
            }
            if ( m > -1 ) {
                // printf( "Have %i stars.\n", stars );
                // printf( "Picked game ( %i, %i ) for 1 star.\n", mit->star1, mit->star2 );
                games.erase( mit );
                current.star1 = mit->star1;
                current.star2 = mit->star2;
                current.score = 1;
                games.insert( current );
                // printf( "Readded game. Have %i games to pick.\n", games.size() );
                ++stars;
                win = true;
                ++cnt;
            }
        } while ( win );
        printf( "Case #%i: ", t );
        if ( games.empty() ) {
            printf( "%i\n", cnt );
        }
        else {
            printf( "Too Bad\n" );
        }
    }
    return 0;
}
