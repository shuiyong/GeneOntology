/* 
 * File:   OntologyNode.cpp
 * Author: yong
 * 
 * Created on February 3, 2015, 7:09 PM
 */

#include "OntologyNode.h"

OntologyNode::OntologyNode(ID_TYPE id) {
    ID = id;
}

OntologyNode::OntologyNode(const OntologyNode& orig) {
}

OntologyNode::~OntologyNode() {
}

ID_TYPE OntologyNode:: getID(){
    return ID;
}