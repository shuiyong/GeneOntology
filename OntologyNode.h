/* 
 * File:   OntologyNode.h
 * Author: yong
 *
 * Created on February 3, 2015, 7:09 PM
 */

#ifndef ONTOLOGYNODE_H
#define	ONTOLOGYNODE_H
#include<string>
#include<set>
#include<map>
#include<iostream>
#include<fstream>
using namespace std;

typedef string ID_TYPE;

class OntologyNode {
public:
    OntologyNode(ID_TYPE id);
    OntologyNode(const OntologyNode& orig);
    ID_TYPE getID();
    
    bool operator==(OntologyNode &other);
    
    void addParent(OntologyNode *par);
    
    void addChild(OntologyNode *child);
    
    OntologyNode* findParent(ID_TYPE id);
    
    OntologyNode* findChild(ID_TYPE id);
    
    size_t getNumOfAnnotation();
    
    set<OntologyNode *> getParents();
    
    void loadSubGraph(map<ID_TYPE, map<ID_TYPE, double> > &myList, set<ID_TYPE> &myAllNodes);
    
    void addAnnotation(string anno);
    
    void printNode(ofstream &out);
    
    virtual ~OntologyNode();
private:
    ID_TYPE ID;
    
    set<OntologyNode *> parent;
    set<OntologyNode *> children;
    set<string> proteins;
    
    bool compID(ID_TYPE id1, ID_TYPE id2){
        return id1.compare(id2) == 0;
    }
};



#endif	/* ONTOLOGYNODE_H */

