//Name: Hasan Syed
//Date: 02/09/2019
// compress.cpp
// CSE 100 Project 2
//
// Last modified by Hasan Syed on 02/09/2019
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HCNode.hpp"
#include "HCTree.hpp"
#include "BitOutputStream.hpp"

using namespace std;

void print_usage(char ** argv) {
    cout << "Usage:" << endl;
    cout << "  " << argv[0] << " INFILE OUTFILE [-b]" << endl;
    cout << "Command-line flags:" << endl;
    cout << "  -b: switch to bitwise mode" << endl;
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * For debugging purposes, uses ASCII '0' and '1' rather than bitwise I/O.
 */
void compressAscii(const string & infile, const string & outfile) {
    // TODO (checkpoint)
    vector<int> freq(256,0);
    HCTree tree;
    ifstream inFile;
    ofstream outFile;
    inFile.open(infile,ios::binary);
    unsigned char next;
    int totalBytes;
    while (true) {
        if (inFile.is_open()) {
            next = inFile.get();
            if (inFile.eof()){
                break;
                }
           
            totalBytes++;
            for (int i = 0; i < 256; i++) {
                if (next == i) {
                    freq[i]++;
                }
            }
        }
    }
    inFile.close();
    
    tree.build(freq);
    
    
    outFile.open(outfile,ios::binary);

    if (outFile.is_open()) {
        for (int i = 0; i < 256; i++) {
            outFile << "" << freq[i];
        }
    }

    inFile.open(infile, ios::binary);
    BitOutputStream out = BitOutputStream(outFile);
    
    for (int i = 0; i < totalBytes; i++) {
        if (inFile.is_open()) {
            next = inFile.get();
            if (inFile.eof()) {
                break;
            }
        
            tree.encode(next, out);
        }
    }
    out.flush();
    inFile.close();
    outFile.close();
    
}

/**
 * Reads infile, constructs a Huffman coding tree based on its contents,
 * and produces a compressed version in outfile.
 * Uses bitwise I/O.
 */
void compressBitwise(const string & infile, const string & outfile) {
    // TODO (final)
    cerr << "TODO: compress '" << infile << "' -> '"
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
        compressBitwise(infile, outfile);
    } else {
        compressAscii(infile, outfile);
    }

    return 0;
}
