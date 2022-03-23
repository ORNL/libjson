// Unit test for libjson

#include <string>
#include <iostream>
#include <fstream>
#include <libjson.hpp>

using namespace std;
using namespace libjson;

string loadFile( const string & a_filename ){
    ifstream inf( a_filename.c_str() );

    if ( !inf.is_open() || !inf.good() ){
        throw runtime_error( string( "Could not open input file: " ) + a_filename );
    }

    string data{istreambuf_iterator<char>{inf}, {}};

    inf.close();

    return data;
}

void checkArray( const Value::Array & arr, bool nested = false ){

    if ( arr.size() != (nested?11:10) ){
        throw runtime_error("array is wrong size");
    }

    Value::Array::const_iterator i = arr.begin();

    if ( (i++)->asString() != "a" ){
        throw runtime_error("Array[0] wrong value");
    }

    if ( (i++)->asBool() != true ){
        throw runtime_error("Array[1] wrong value");
    }

    if ( (i++)->asBool() != false ){
        throw runtime_error("Array[2] wrong value");
    }

    if ( !(i++)->isNull() ){
        throw runtime_error("Array[3] wrong value");
    }

    if ( (i++)->asNumber() != -1 ){
        throw runtime_error("Array[4] wrong value");
    }

    if ( (i++)->asNumber() != 0 ){
        throw runtime_error("Array[5] wrong value");
    }

    if ( (i++)->asNumber() != 1 ){
        throw runtime_error("Array[6] wrong value");
    }

    if ( (i++)->asNumber() != -1.1e-5 ){
        throw runtime_error("Array[7] wrong value");
    }

    if ( (i++)->asNumber() != 0.001 ){
        throw runtime_error("Array[8] wrong value");
    }

    if ( (i++)->asNumber() != 1.1e5 ){
        throw runtime_error("Array[9] wrong value");
    }

    if ( nested ){
        checkArray( i->asArray() );
    }
}

void checkObject( const Value::Object & obj, int index ){

    if ( obj.getNumber("index") != index ){
        throw runtime_error("index key wrong value");
    }

    if ( obj.getString("v1") != "string" ){
        throw runtime_error("v1 key wrong value");
    }

    if ( obj.getBool("v2") != true ){
        throw runtime_error("v2 key wrong value");
    }

    if ( obj.getBool("v3") != false ){
        throw runtime_error("v3 key wrong value");
    }

    if ( !obj.getValue("v4").isNull() ){
        throw runtime_error("v4 key wrong value/type");
    }

    if ( obj.getNumber("v5") != -1 ){
        throw runtime_error("v5 key wrong value");
    }

    if ( obj.getNumber("v6") != 0 ){
        throw runtime_error("v7 key wrong value");
    }

    if ( obj.getNumber("v7") != 1 ){
        throw runtime_error("v7 key wrong value");
    }

    if ( obj.getNumber("v8") != -1.1e-5 ){
        throw runtime_error("v8 key wrong value");
    }

    if ( obj.getNumber("v9") != 0.001 ){
        throw runtime_error("v9 key wrong value");
    }

    if ( obj.getNumber("v10") != 1.1e5 ){
        throw runtime_error("v10 key wrong value");
    }

    checkArray( obj.getArray( "array1" ));
}

bool testParsing(){
    cout << "testParsing: ";

    try{
        string json_str = loadFile("library/test/test_basic.json");

        Value json;
        json.fromString( json_str );
        const Value::Object & obj = json.asObject();

        checkObject( obj, 0 );
        checkObject( obj.getObject( "object1" ), 1 );

        cout << "PASSED\n";
        return false;
    }catch( exception &e ){
        cout << "FAILED\n    exception:" << e.what() << endl;
        return true;
    }
}

bool testSerialization(){
    cout << "testSerialization: ";

    try{
        string json_str = loadFile("library/test/test_basic.json");
        Value orig, dup;

        orig.fromString( json_str );
        string orig_str = orig.toString();

        dup.fromString( orig_str );

        if ( orig_str != dup.toString() ){
            throw runtime_error("serializations do not match");
        }

        cout << "PASSED\n";
        return false;
    }catch( exception &e ){
        cout << "FAILED\n    exception:" << e.what() << endl;
        return true;
    }
}

void checkArrayComplex( const Value::Array & arr ){

    if ( arr.size() != 16 ){
        throw runtime_error("array is wrong size");
    }

    Value::Array::const_iterator i = arr.begin();

    checkObject( (i++)->asObject(), 0 );

    if ( (i++)->asString() != "a" ){
        throw runtime_error("Array[0] wrong value");
    }

    if ( (i++)->asBool() != true ){
        throw runtime_error("Array[1] wrong value");
    }

    if ( (i++)->asBool() != false ){
        throw runtime_error("Array[2] wrong value");
    }

    checkObject( (i++)->asObject(), 4 );

    if ( !(i++)->isNull() ){
        throw runtime_error("Array[3] wrong value");
    }

    if ( (i++)->asNumber() != -1 ){
        throw runtime_error("Array[4] wrong value");
    }

    if ( (i++)->asNumber() != 0 ){
        throw runtime_error("Array[5] wrong value");
    }

    if ( (i++)->asNumber() != 1 ){
        throw runtime_error("Array[6] wrong value");
    }

    checkObject( (i++)->asObject(), 9 );


    if ( (i++)->asNumber() != -1.1e-5 ){
        throw runtime_error("Array[7] wrong value");
    }

    if ( (i++)->asNumber() != 0.001 ){
        throw runtime_error("Array[8] wrong value");
    }

    if ( (i++)->asNumber() != 1.1e5 ){
        throw runtime_error("Array[9] wrong value");
    }

    checkObject( (i++)->asObject(), 13 );

    checkArray( (i++)->asArray() );
    checkArray( (i++)->asArray(), true );
}

bool testComplexArrays(){
    cout << "testComplexArrays: ";

    try{
        string json_str = loadFile("library/test/test_array_complex.json");
        Value json;

        json.fromString( json_str );
        checkArrayComplex( json.asArray() );

        cout << "PASSED\n";
        return false;
    }catch( exception &e ){
        cout << "FAILED\n    exception:" << e.what() << endl;
        return true;
    }
}

int main( int argc, char** argv ){
    bool fail = false;

    fail |= testParsing();          // Uses test_basic.json
    fail |= testSerialization();    // Uses test_basic.json
    fail |= testComplexArrays();    // Uses test_array_complex.json

    cout.flush();

    if ( fail ){
        abort();
    }

    return 0;
}
