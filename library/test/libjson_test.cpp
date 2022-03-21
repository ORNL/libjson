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
        throw runtime_error( "Could not open input file: "s + a_filename );
    }
    string data((std::istreambuf_iterator<char>(inf)),
                 std::istreambuf_iterator<char>());

    inf.close();

    return data;
}

int main( int argc, char** argv ){
    cout << "Test 1\n";

    string json_str = loadFile("test1.json");

    Value result;

    try {
        result.fromString( json_str );

        cout << "Output: [" << result.toString() << endl;

        return 0;
    }catch( ParseError & e ){
        cout << e.toString();
    }
    return 1;
}
