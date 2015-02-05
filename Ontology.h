/* 
 * File:   Ontology.h
 * Author: yong
 *
 * Created on February 3, 2015, 7:38 PM
 */

#ifndef ONTOLOGY_H
#define	ONTOLOGY_H
#include "OntologyNode.h"
#include <map>
#include <set>
#include <iostream>
using namespace std;

enum GO_TYPE {BP,MF,CC,ERR};
/*
 * BP = biological_process   p
 * MF = molecular_function   f
 * CC = cellular_component   c
 */

class Ontology {
public:
    Ontology();
    
    Ontology(GO_TYPE type){
        this->type = type;
    }
    
    Ontology(const Ontology& orig);
    
    void addNode(ID_TYPE id){
        if(graph.find(id) == graph.end()){
            OntologyNode *np = new OntologyNode(id);
            graph[id] = np;
        }
    }
    
    void addEdge(ID_TYPE parent, ID_TYPE child){
        addNode(parent);
        addNode(child);
        graph[parent]->addChild(graph[child]);
        graph[child]->addParent(graph[parent]);
    }
    
    void addAnnotation(ID_TYPE id, string anno){
        graph[id]->addAnnotation(anno);
    }
    
    void printGraph(ofstream &out){
        out<<"graph size() = "<<graph.size()<<endl;
        int i = 0;
        for(map<ID_TYPE, OntologyNode *>::iterator it = graph.begin(); it != graph.end() ; it++){
            out<<"["<<i++<<"]"<<endl;
            it->second->printNode(out);
            out<<endl;
        }
    }
    
    virtual ~Ontology();
    
    GO_TYPE getType(){
        return type;
    }
private:
    GO_TYPE type;
    map<ID_TYPE, OntologyNode *> graph;
};

GO_TYPE strToGoType(string tmp);
#endif	/* ONTOLOGY_H */

