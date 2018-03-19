#include <iostream>
#include <vector>
#include <string>

#include <tclap/CmdLine.h>

#include "version.h"

using namespace std;

int main(int argc, char* argv[])
{
    try {

        TCLAP::CmdLine cmd("Simple Hello World", ' ', getProjectVersion());
        cmd.parse( argc, argv );

    } catch (TCLAP::ArgException &e) { 

        cerr << "error: " << e.error() << " for arg " << e.argId() << endl; 

    }


    cout << "Hello, World!" << endl;
    return 0;
}
