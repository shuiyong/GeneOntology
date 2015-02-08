/* 
 * File:   OntologyNode.cpp
 * Author: yong
 * 
 * Created on February 3, 2015, 7:09 PM
 */

#include <queue>

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

bool OntologyNode:: operator==(OntologyNode &other){
    return compID(other.getID(), ID); // the ID_TYPE is not string, rewrite the function;
}

void OntologyNode::addParent(OntologyNode *par) {
    // judge whether par is in list ???
    parent.insert(par);
}

void OntologyNode::addChild(OntologyNode *child) {
    // judge whether chi is in list ???
    children.insert(child);
}

set<OntologyNode *> OntologyNode::getParents(){
    set<OntologyNode *> tmp = parent;
    queue<OntologyNode *> list;
    for(set<OntologyNode *>::iterator it = parent.begin(); it != parent.end(); it++){
        list.push(*it);
    }
    
    while(!list.empty()){
        OntologyNode *pointer = list.front();
        list.pop();
        for(set<OntologyNode *>::iterator it = pointer->children.begin(); it != pointer->children.end(); it++){
            list.push(*it);
        }
        tmp.insert(pointer->parent.begin(),pointer->parent.end());
    }
    return tmp;
}

void OntologyNode::loadSubGraph(map<ID_TYPE, map<ID_TYPE, double> > &myList, set<ID_TYPE> &myAllNodes){
    myAllNodes.insert(getID());
    queue<OntologyNode *> list;
    for(set<OntologyNode *>::iterator it = parent.begin(); it != parent.end(); it++){
        list.push(*it);
    }
    
    for(set<OntologyNode *>::iterator i = parent.begin(); i != parent.end(); i++){
        myList[(*i)->getID()][getID()] = 1;
        myAllNodes.insert((*i)->getID());
    }
    
    while(!list.empty()){
        OntologyNode *pointer = list.front();
        list.pop();
        for(set<OntologyNode *>::iterator it = pointer->children.begin(); it != pointer->children.end(); it++){
            list.push(*it);
        }
        
        for(set<OntologyNode *>::iterator i = pointer->parent.begin(); i != pointer->parent.end(); i++){
            myList[(*i)->getID()][pointer->getID()] = 1;
            myAllNodes.insert((*i)->getID());
        }
    }
}

OntologyNode* OntologyNode::findParent(ID_TYPE id) {
    for (set<OntologyNode *>::iterator it = parent.begin(); it != parent.end(); it++) {
        if (compID((*it)->getID(), id))
            return *it;
    }
    return NULL;
}

OntologyNode* OntologyNode::findChild(ID_TYPE id) {
    for (set<OntologyNode *>::iterator it = children.begin(); it != children.end(); it++) {
        if (compID((*it)->getID(), id))
            return *it;
    }
    return NULL;
}

void OntologyNode::addAnnotation(string anno) {
    proteins.insert(anno);
}

size_t OntologyNode::getNumOfAnnotation(){
    set<string> tmp = proteins;
    queue<OntologyNode *> list;
    for(set<OntologyNode *>::iterator it = children.begin(); it != children.end(); it++){
        list.push(*it);
    }
    
    while(!list.empty()){
        OntologyNode *pointer = list.front();
        list.pop();
        for(set<OntologyNode *>::iterator it = pointer->children.begin(); it != pointer->children.end(); it++){
            list.push(*it);
        }
        tmp.insert(pointer->proteins.begin(),pointer->proteins.end());
    }
    return tmp.size();
}

void OntologyNode::printNode(ofstream &out) {
    out << "ID = " << ID << endl; //it may be wrong
    out << "Parent" << endl;
    for (set<OntologyNode *>::iterator it = parent.begin(); it != parent.end(); it++) {
        out << (*it)->getID() << '\t';
    }
    out << endl << "Children" << endl;
    for (set<OntologyNode *>::iterator it = children.begin(); it != children.end(); it++) {
        out << (*it)->getID() << '\t';
    }
    out << endl << "Annotations" << endl;

    for (set<string>::iterator it = proteins.begin(); it != proteins.end(); it++)
        out << *it << '\t';
    out << endl;
}