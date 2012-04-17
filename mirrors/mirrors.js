function assert( condition ) {
    if ( !condition ) {
        throw 'Assertion failed';
    }
}

var EPSILON = 0.0001;
var EPSILON_THETA = 0.0001;
var MARGINAL_THETA = 1 / 90;

function Vector( x, y ) {
    this.x = x;
    this.y = y;
}
Vector.prototype = {
    constructor: 'Vector',
    length: function() {
        return Math.sqrt( this.x * this.x + this.y * this.y );
    },
    angle: function() {
        return Math.atan2( this.y, this.x );
    },
    plus: function( operand ) {
        return new Vector( this.x + operand.x, this.y + operand.y );
    },
    minus: function( operand ) {
        return this.plus( operand.opposite() );
    },
    opposite: function() {
        return new Vector( -this.x, -this.y );
    },
    dot: function( operand ) {
        return this.x * operand.x + this.y * operand.y;
    },
    cross: function( operand ) {
        return this.x * operand.y - this.y * operand.x;
    },
    scale: function( factor ) {
        return new Vector( factor * this.x, factor * this.y );
    },
    unit: function() {
        var d = this.length();
        if ( d == 0 ) {
            return new Vector( 1, 0 );
        }
        return new Vector( this.x / d, this.y / d );
    },
    reflect: function( normal ) {
        return this.plus( normal.scale( -2 * this.dot( normal ) ) );
    },
    toString: function() {
        return '(' + this.x + ', ' + this.y + ')';
    },
    clone: function() {
        return new Vector( this.x, this.y );
    }
};
Vector.fromPolar = function( length, angle ) {
    var x = length * Math.cos( angle );
    var y = length * Math.sin( angle );
    return new Vector( x, y );
};

function Line( A, B ) {
    this.vertical = false;
    this.lambda = 0;
    this.alpha = 0;
    if ( A.x - B.x == 0 ) {
        this.vertical = true;
        this.alpha = A.x;
    }
    else { 
        this.lambda = ( A.y - B.y ) / ( A.x - B.x );
        this.alpha = A.y - this.lambda * A.x;
    }
}
Line.prototype = {
    constructor: 'Line',
    intersect: function( line ) {
        if ( line.vertical ) {
            if ( this.vertical ) {
                return false;
            }
            else {
                return line.intersect( this );
            }
        }
        else if ( this.vertical ) {
            return new Vector( this.alpha, line.eval( this.alpha ) );
        }
        if ( this.lambda == line.lambda ) {
            // parallel lines
            return false;
        }
        var x = ( line.alpha - this.alpha ) / ( this.lambda - line.lambda );
        var y = this.eval( x );

        return new Vector( x, y );
    },
    eval: function( x ) {
        return this.lambda * x + this.alpha;
    },
    toString: function() {
        return '[Line lambda = ' + this.lambda + '; alpha = ' + this.alpha + ']';
    }
};
var fs = require( 'fs' );
var lines = fs.readFileSync( '/dev/stdin' ).toString().split( "\n" );
var ln = 0;
var T = lines[ ln ];
var parents, current;
var W, H, D, A;

++ln;
for ( var t = 1; t <= T; ++t ) {
    // console.log( 'Testcase ' + t );
    parts = lines[ ln ].split( " " );
    ++ln;
    H = parts[ 0 ];
    W = parts[ 1 ];
    D = parts[ 2 ];
    A = [];
    for ( var y = 0; y < H; ++y ) {
        A[ y ] = lines[ ln ].split( '' );
        ++ln;
        for ( var x = 0; x < W; ++x ) {
            if ( A[ y ][ x ] == 'X' ) {
                current = new Vector( x + 0.5, y + 0.5 );
            }
        }
    }
    reflections = [];
    for ( var theta = -Math.PI; theta < Math.PI; theta += 0.001 ) {
        // console.log( 'Ray casting from ' + current + ' at an angle ' + theta );
        var simulation = simulate( current, theta, current, D );
        if ( simulation === true ) {
            // console.log( 'Detected reflection at angle ' + theta );
            reflections.push( theta );
        }
        else if ( simulation === false ) {
            // pass
        }
        else {
            // console.log( 'Detected reflection that can be turbulated to yield sample.' );
            function perturbate( deltaTheta ) {
                // console.log( 'Introducing turbulence of ' + deltaTheta );
                var turbSim = simulate( current, theta - deltaTheta, current, D );
                if ( turbSim === true ) {
                    // console.log( 'Turbulence introduction yielded positive sample.' );
                    reflections.push( theta - deltaTheta );
                }
                else {
                    if ( turbSim === false ) {
                        // console.log( 'Turbulence introduction yielded an impossibilty.' );
                    }
                    else {
                        // console.log( 'Turbulence introduction yielded an error of ' + turbSim );
                    }
                }
            }
            perturbate( simulation );
            perturbate( -simulation );
        }
        // return;
    }
    reflections.sort();
    var count = 0;
    if ( reflections.length ) {
        count = 1;
        for ( var i = 1; i < reflections.length; ++i ) {
            if ( Math.abs( reflections[ i + 1 ] - reflections[ i ] ) > EPSILON ) {
                ++count;
            }
        }
    }
    console.log( 'Case #' + t + ': ' + count );
}

function adjacent( a, b ) {
    return ( a.x == b.x && Math.abs( a.x - b.x ) <= 1 )
        || ( a.y == b.y && Math.abs( a.y - b.y ) <= 1 );
}
function cell( location ) {
    return new Vector( Math.floor( location.x ), Math.floor( location.y ) );
}
function me( cell ) {
    assert( cell.x >= 0 && cell.x < W );
    assert( cell.y >= 0 && cell.y < H );
    return A[ cell.y ][ cell.x ] == 'X';
}
function empty( cell ) {
    assert( cell.x >= 0 && cell.x < W );
    assert( cell.y >= 0 && cell.y < H );
    return A[ cell.y ][ cell.x ] == '.';
}
function mirror( cell ) {
    assert( cell.x >= 0 && cell.x < W );
    assert( cell.y >= 0 && cell.y < H );
    return A[ cell.y ][ cell.x ] == '#';
}
function wall( a, b ) {
    assert( adjacent( a, b ) );
    if ( a.y == b.y ) {
        if ( a.x > b.x ) {
            var ret = wall( b, a );
            ret.normal = ret.normal.opposite();
            return ret;
        }
        return {
            line: new Line(
                new Vector( a.x + 1, a.y ),
                new Vector( a.x + 1, a.y + 1 )
            ),
            normal: new Vector( -1, 0 )
        };
    }
    else {
        // a.x == b.x
        if ( a.y > b.y ) {
            var ret = wall( b, a );
            ret.normal = ret.normal.opposite();
            return ret;
        }
        return {
            line: new Line(
                new Vector( a.x, a.y + 1 ),
                new Vector( a.x + 1, a.y + 1 )
            ),
            normal: new Vector( 0, -1 )
        };
    }
}
function same( a, b ) {
    return a.x == b.x && a.y == b.y;
}
function wrapAngle( theta ) {
    if ( theta < -Math.PI ) {
        return wrapAngle( theta + 2 * Math.PI );
    }
    if ( theta > Math.PI ) {
        return wrapAngle( theta - 2 * Math.PI );
    }
    return theta;
}
function simulate( source, angle, destination, fog ) {
    var dl, neighbour;

    console.log( 'Simulating from ' + source + ' with a fog of ' + fog );
    if ( fog < 0 ) {
        return false;
    }
    
    dl = 1;
    neighbour = source.clone();
    do {
        // console.log( 'At cell ' + neighbour + ' (dl = ' + dl + ')' );
        // console.log( 'Moving by ' + dl + ' at an angle of ' + angle );
        neighbour = neighbour.plus( Vector.fromPolar( dl, angle ) );
        if ( same( cell( source ), cell( neighbour ) ) ) {
            fog -= dl;
            // console.log( 'Same cell, continuing' );
            continue;
        }
        if ( !adjacent( cell( source ), cell( neighbour ) ) ) {
            // console.log( 'Cells are not adjacent; increasing resolution' );
            // not the same and not adjacent
            dl /= 2;
            neighbour = source.clone();
            if ( dl < EPSILON ) {
                break;
            }
        }
        else {
            break;
        }
    } while ( true );
    // console.log( 'Simulation step with neighbour ' + neighbour );
    if ( empty( cell( neighbour ) ) ) {
        // console.log( 'Neighbour cell is empty.' );
        console.log( 'Recursion with a fog of ' + ( fog - dl ) );
        return simulate( neighbour, angle, destination, fog - dl );
    }
    else if ( me( cell( neighbour ) ) ) {
        // console.log( 'Neighbour cell is destination.' );
        var travel = new Line( source, neighbour );
        var vertical = new Line(
            new Vector( cell( neighbour ).x + 0.5, cell( neighbour ) ),
            new Vector( cell( neighbour ).x + 0.5, cell( neighbour ) + 1 )
        );
        var horizontal = new Line(
            new Vector( cell( neighbour ).x, cell( neighbour ) ) + 0.5,
            new Vector( cell( neighbour ).x + 1, cell( neighbour ) + 0.5 )
        );
        var closeEnough = travel.intersect( vertical );
        if ( closeEnough === false ) {
            closeEnough = travel.intersect( horizontal );
        };
        // console.log( 'Actual intersection at ' + closeEnough );
        var deltaTheta = closeEnough.minus( source ).angle() - destination.minus( source ).angle();
        deltaTheta = wrapAngle( deltaTheta );
        if ( Math.abs( deltaTheta ) < EPSILON_THETA ) {
            // console.log( 'Detected reflection with an error of ' + deltaTheta );
            return true;
        }
        else if ( Math.abs( deltaTheta ) < MARGINAL_THETA ) {
            // console.log( 'Destination is off considerably by an angle error of ' + deltaTheta );
            return Math.abs( deltaTheta );
        }
        // console.log( 'Destination unreachable by ray. Error was ' + deltaTheta );
        console.log( 'Recursion with a fog of ' + ( fog - dl ) );
        return simulate( neighbour, angle, destination, fog - dl );
    }
    else if ( mirror( cell( neighbour ) ) ) {
        console.log( 'Neighbour cell is a mirror.' );
        function bump( w ) {
            var travel = new Line( source, neighbour );
            var collision = travel.intersect( w.line );
            var reflect = neighbour.minus( source ).reflect( w.normal );
            console.log( 'Collision detected at point ' + collision );
            fog -= source.minus( collision ).length();
            fog += 2 * EPSILON;
            angle = reflect.angle();
            source = collision.minus( Vector.fromPolar( 2 * EPSILON, angle ) );
            console.log( 'Recursion with a fog of ' + fog );
            return simulate( source, angle, destination, fog );
        }
        if ( adjacent( cell( source ), cell( neighbour ) ) ) {
            // console.log( 'Bumping off adjacent cell.' );
            var w = wall( cell( source ), cell( neighbour ) );
            return bump( w );
        }
        else {
            // console.log( 'Corner case.' );
            var n1 = new Vector( cell( source ).x, cell( neighbour ).y );
            var n2 = new Vector( cell( neighbour ).x, cell( source ).y );
            var corner = source.plus( cell( neighbour ).minus( cell( source ) ).scale( 0.5 ) );

            if ( empty( n1 ) && empty( n2 ) ) {
                return false;
            }
            else if ( mirror( n1 ) && mirror( n2 ) ) {
                angle -= Math.PI;
                var distance = 2 * corner.minus( source ).length();
                return simulate( source, angle, destination, fog - distance );
            }
            else if ( mirror( n1 ) && !mirror( n2 ) ) {
                var w = wall( source, n1 );
                return bump( w );
            }
            else if ( mirror( n2 ) && !mirror( n1 ) ) {
                var w = wall( source, n2 );
                return bump( w );
            }
        }
    }
}
