<?php
    $source =
    'ejp mysljylc kd kxveddknmc re jsicpdrysi
    rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd
    de kr kd eoya kw aej tysr re ujdr lkgc jv';
    $target =
    'our language is impossible to understand
    there are twenty six factorial possibilities
    so it is okay if you want to just give up';
    $source = preg_replace( '#\W#', '', $source );
    $target = preg_replace( '#\W#', '', $target );
    $map = array();
    for ( $i = 0; $i < strlen( $source ); ++$i ) {
        $map[ $source[ $i ] ] = $target[ $i ];
    }
    $map[ 'q' ] = 'z';
    $map[ 'z' ] = 'q';
    ksort( $map );
    for ( $i = 0; $i < 26; ++$i ) {
        $c = chr( ord( 'a' ) + $i );
        if ( array_search( $c, $map ) === false ) {
            echo "Not found: " . $c . "\n";
        }
    }
    // var_dump( $map );
    $encrypted = file( 'tongues.in' );
    $t = ( int )$encrypted[ 0 ];
    for ( $i = 1; $i <= $t; ++$i ) {
        echo "Case #$i: ";
        echo strtr( $encrypted[ $i ], $map );
    }
?>
