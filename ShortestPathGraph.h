/* 
 * File:   ShortestPathGraph.h
 * Author: yong
 *
 * Created on February 5, 2015, 3:50 PM
 */

#ifndef SHORTESTPATHGRAPH_H
#define	SHORTESTPATHGRAPH_H
#include<map>
#include<vector>
#include<cfloat>
#include<cmath>
#include"OntologyNode.h"
using namespace std;

class ShortestPathGraph {
public:
    ShortestPathGraph(map<ID_TYPE, map<ID_TYPE, double> > &myList, set<ID_TYPE> &myAllNodes);
    ShortestPathGraph(const ShortestPathGraph& orig);
    void addEdge(ID_TYPE par, ID_TYPE kid);
    void calculateShortestPath();
    void printPath(ofstream &out);
    friend double getGraphSim(ShortestPathGraph &g1,ShortestPathGraph &g2);
    double getLength();
    virtual ~ShortestPathGraph();
private:
    map<ID_TYPE, map<ID_TYPE, double> > list;
    set<ID_TYPE> allNodes;
};

#endif	/* SHORTESTPATHGRAPH_H */

