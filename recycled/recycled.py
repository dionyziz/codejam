import fileinput

lines = fileinput.input()
for t in range( 1, int( lines[ 0 ] ) + 1 ):
    ( A, _, B ) = lines[ t ].partition( ' ' )
    A, B = int( A ), int( B )
    c = 0
    for n in range( A, B + 1 ):
        nstr = str( n )
        l = len( nstr )
        seen = {}
        for j in range( 1, l ):
            m = int( nstr[ -j: ] + nstr[ :-j ] )
            if l == len( str( m ) ) and n < m <= B and not m in seen:
                seen[ m ] = True
                c = c + 1
    print "Case #%i: %i" % ( t, c )
