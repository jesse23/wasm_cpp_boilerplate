const Module = require( '../public/example.js' );
const promise = new Promise( resolve => {
    Module.onRuntimeInitialized = resolve;
} )

describe( 'Test WASM example', () => {
    var squareVal;

    beforeEach( async () => {
        await promise;
        squareVal = Module.cwrap( 'squareVal', 'number', [ 'number' ] )
    } );

    it( 'Verify squareVal(12.5) === 156.25', () => {
        expect( squareVal( 12.5 ) ).toEqual( 156.25 );
    } );

    it( 'Verify squareVal(\'test\') === NaN (since type is number)', () => {
        expect( squareVal( 'test' ) ).toEqual( NaN );
    } );

    it( 'Verify squareVal() === NaN (since type is number)', () => {
        expect( squareVal() ).toEqual( NaN );
    } );
} );
