//Name: Hasan Syed
//Date: 02/09/2019
// HCNode.cpp
// CSE 100 Project 2
//
// Last modified by Hasan Syed on 02/09/2019
//
#include "HCNode.hpp"

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically.
 */
bool HCNode::operator<(const HCNode& other) {
    if (count != other.count) {
        return (count > other.count);
    }
    else {
        return (symbol > other.symbol);

    }
}
