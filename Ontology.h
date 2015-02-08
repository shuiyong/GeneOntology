/* 
 * File:   Ontology.h
 * Author: yong
 *
 * Created on February 3, 2015, 7:38 PM
 */

#ifndef ONTOLOGY_H
#define	ONTOLOGY_H
#include "OntologyNode.h"
#include "ShortestPathGraph.h"
#include <map>
#include <set>
#include <iostream>
#include <cmath>
#include <algorithm>
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
    
    Ontology(GO_TYPE type);
    
    Ontology(const Ontology& orig);
    
    void addNode(ID_TYPE id);
    
    void addEdge(ID_TYPE parent, ID_TYPE child);
    
    void addAnnotation(ID_TYPE id, string anno);
    
    size_t getNumOfAnnotation();
    
    size_t getNumOfAnnotation(ID_TYPE id);
    
    double getIC(ID_TYPE id); //return the Information Contest;
    
    double getOntologyNodeSim(ID_TYPE id1, ID_TYPE id2, string method);//return the similarity between to ontology node
    
    double getGeneSim(string g1, string g2, string method);// return the similarity between two gene product
    
    void printGraph(ofstream &out);
    
    ShortestPathGraph getSPG(string pro);
    
    virtual ~Ontology();
    
    GO_TYPE getType();
private:
    GO_TYPE type;
    map<ID_TYPE, OntologyNode *> graph;
    map<string, set<ID_TYPE> > annotation;
    map<ID_TYPE, double> infoCon;
};

GO_TYPE strToGoType(string tmp);
#endif	/* ONTOLOGY_H */

