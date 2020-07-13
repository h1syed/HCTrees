//Name: Hasan Syed
//Date: 02/09/2019
// HCTree.cpp
// CSE 100 Project 2
//
// Last modified by Hasan Syed on 02/09/2019
//
#include <stack>
#include <queue>

#include "HCTree.hpp"

/**
 * Delete all nodes for tree.
 */
void HCTree::deleteAll(HCNode* n) {
    if (n == NULL) return;
    deleteAll(n->c0);
    deleteAll(n->c1);
    delete n;
}

/**
 * Destructor for HCTree
 */
HCTree::~HCTree() {
    // TODO (checkpoint)
    deleteAll(this->root);
}

/** Use the Huffman algorithm to build a Huffman coding tree.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the tree,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs) {
    // TODO (checkpoint)
    if (this->root != nullptr) {
        this->~HCTree();
    }
    std::priority_queue<HCNode*,vector<HCNode*>,HCNodePtrComp> pq;

    for (int i = 0; i < 256; i++) {
        if (freqs[i] > 0) {
            HCNode* p = new HCNode(freqs[i], i);
            leaves[i] = p;
            pq.push(p);
        }
    }

    while (pq.size() > 1) {
        HCNode* a = pq.top();
        pq.pop();
        HCNode* b = pq.top();
        pq.pop();
        
        int newCount = a->count + b->count;
        
        HCNode* newNode = new HCNode(newCount, b->symbol, a, b);
        
        
        a->p = newNode;
        b->p = newNode;
        pq.push(newNode);
    }

    
        this->root = pq.top();
    
}

/** Write to the given ostream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, ostream& out) const {
    // TODO (checkpoint)
    if (this->root == nullptr) return;
    stack <int> coding;
    HCNode* start = this->leaves[symbol];
  

    while (start != root) {
        if (start == start->p->c0) {
            coding.push(0);
        }
        else {
            coding.push(1);
        }
        start = start->p;
    }

    while (!coding.empty()) {
        out << coding.top() << "";
        coding.pop();
    }
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the istream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(istream& in) const {
    char nextByte;
    HCNode* current = this->root;
    while(current->c0 != nullptr || current->c1 != nullptr){
        in.get(nextByte);
        if (nextByte == '0') {
            current = current->c0;
        }
        else  {
            current = current->c1;
        }
    }
    
    return current->symbol;  // TODO (checkpoint)
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    // TODO (final)
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
byte HCTree::decode(BitInputStream& in) const {
    return 0;  // TODO (final)
}

/**
 * Print the contents of a tree
 */
void HCTree::printTree() const {
    cout << "=== PRINT TREE BEGIN ===" << endl;
    printTreeHelper(root);
    cout << "=== PRINT TREE END =====" << endl;
}


/**
 * Recursive helper function for printTree
 */
void HCTree::printTreeHelper(HCNode * node, string indent) const {
    if (node == nullptr) {
        cout << indent << "nullptr" << endl;
        return;
    }

    cout << indent << *node << endl;
    if (node->c0 != nullptr || node->c1 != nullptr) {
        printTreeHelper(node->c0, indent + "  ");
        printTreeHelper(node->c1, indent + "  ");
    }

    
}
