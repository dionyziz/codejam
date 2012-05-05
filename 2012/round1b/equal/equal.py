fi = open( 'equal.in', 'r' )
T = int( fi.readline() )
for t in xrange( 1, T + 1 ):
    line = ' '.split( fi.readline() )
    N = line[ 0 ]
    A = {}
    for n in xrange( 0, N ):
        A[ line[ n ] ] = True
