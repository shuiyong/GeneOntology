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
#include<iostream>
#include<fstream>
using namespace std;

typedef string ID_TYPE;

class OntologyNode {
public:
    OntologyNode(ID_TYPE id);
    OntologyNode(const OntologyNode& orig);
    ID_TYPE getID();
    
    bool operator==(OntologyNode &other){
        return compID(other.getID(),ID);// the ID_TYPE is not string, rewrite the function;
    }
    
    void addParent(OntologyNode *par){
        // judge whether par is in list ???
        parent.insert(par);
    }
    
    void addChild(OntologyNode *child){
        // judge whether chi is in list ???
        children.insert(child);
    }
    
    OntologyNode* findParent(ID_TYPE id){
        for(set<OntologyNode *>::iterator it = parent.begin(); it != parent.end(); it++){
            if(compID((*it)->getID(),id))
                return *it;
        }
        return NULL;
    }
    
    OntologyNode* findChild(ID_TYPE id){
        for(set<OntologyNode *>::iterator it = children.begin(); it != children.end(); it++){
            if(compID((*it)->getID(),id))
                return *it;
        }
        return NULL;
    }
    
    void addAnnotation(string anno){
        proteins.insert(anno);
    }
    
    void printNode(ofstream &out){
        out<<"ID = "<<ID<<endl;//it may be wrong
        out<<"Parent"<<endl;
        for(set<OntologyNode *>::iterator it = parent.begin(); it != parent.end(); it++){
            out<<(*it)->getID()<<'\t';
        }
        out<<endl<<"Children"<<endl;
        for(set<OntologyNode *>::iterator it = children.begin(); it != children.end(); it++){
            out<<(*it)->getID()<<'\t';
        }
        out<<endl<<"Annotations"<<endl;
        
        for(set<string>::iterator it = proteins.begin(); it != proteins.end();it++)
            out<<*it<<'\t';
        out<<endl;
    }
    
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

