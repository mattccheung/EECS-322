#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "ir.h"
#include "parser.h"


using namespace IR;
using namespace std;


int main(int argc, char **argv) {
    bool verbose;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " SOURCE [-v]" << endl;
        return 1;
    }
    int32_t opt;
    while ((opt = getopt(argc, argv, "v")) != -1) {
        switch (opt) {
            case 'v':
                verbose = true;
                break;
            default:
                cerr << "Usage: " << argv[0] << "[-v] SOURCE" << endl;
                return 1;
        }
    }

    ofstream output;
    output.open("prog.L3");
    Program p = IRParseFile(argv[optind]);
    output << p.toL3() << endl;
    output.close();
    return 0;
}