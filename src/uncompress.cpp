//Name: Hasan Syed
//Date: 02/09/2019
// uncompress.cpp
// CSE 100 Project 2
//
// Last modified by Hasan Syed on 02/09/2019
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitInputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void uncompressAscii(const string & infile, const string & outfile) {
    // TODO (checkpoint)
    vector<int> freq(256, 0);
    int frequency, totalBytes;
    HCTree tree;
    ifstream inFile;
    ofstream outFile;
    inFile.open(infile, ios::binary);

    if (inFile.is_open()) {
        for (int i = 0; i < 256; i++) {
            inFile >> frequency;
            freq[i] = frequency;
            if (frequency > 0) {
                totalBytes += frequency;
            }
        }
    }
    
    tree.build(freq);
    
   
    outFile.open(outfile, ios::binary);
    BitInputStream input = BitInputStream(inFile);

    for (int i = 0; i < totalBytes; i++) {
        if (inFile.is_open()) {
            if (inFile.eof()) {
                break;
            }
            outFile << tree.decode(input);
        }
    }

    
    inFile.close();
    outFile.close();
}

/**
 * Reads infile, constructs a Huffman coding tree based on its header,
 * and produces an uncompressed version in outfile.
 * Uses bitwise I/O.
 */
void uncompressBitwise(const string & infile, const string & outfile) {
    // TODO (final)
    cerr << "TODO: uncompress '" << infile << "' -> '"
        << outfile << "' here (bitwise)" << endl;
}

int main(int argc, char ** argv) {
    string infile = "";
    string outfile = "";
    bool bitwise = false;
    for (int i = 1; i < argc; i++) {
        string currentArg = argv[i];
        if (currentArg == "-b") {
            bitwise = true;
        } else if (infile == "") {
            infile = currentArg;
        } else {
            outfile = currentArg;
        }
    }

    if (infile == "" || outfile == "") {
        cout << "ERROR: Must provide input and output files" << endl;
        print_usage(argv);
        return 1;
    }

    if (bitwise) {
        uncompressBitwise(infile, outfile);
    } else {
        uncompressAscii(infile, outfile);
    }

    return 0;
}
