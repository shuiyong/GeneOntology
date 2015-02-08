/* 
 * File:   ShortestPathGraph.cpp
 * Author: yong
 * 
 * Created on February 5, 2015, 3:50 PM
 */

#include "ShortestPathGraph.h"

ShortestPathGraph::ShortestPathGraph(map<ID_TYPE, map<ID_TYPE, double> > &myList, set<ID_TYPE> &myAllNodes) {
    list.insert(myList.begin(), myList.end());
    allNodes.insert(myAllNodes.begin(), myAllNodes.end());
    calculateShortestPath();
}

ShortestPathGraph::ShortestPathGraph(const ShortestPathGraph& orig) {
}

ShortestPathGraph::~ShortestPathGraph() {
}

void ShortestPathGraph::calculateShortestPath(){
    for(set<ID_TYPE>::iterator k = allNodes.begin(); k!= allNodes.end(); k++){
        for(set<ID_TYPE>::iterator i = allNodes.begin(); i != allNodes.end(); i++){
            for(set<ID_TYPE>::iterator j = allNodes.begin(); j != allNodes.end(); j++){
                if(list.find(*i) == list.end())
                    continue;
                if(list[*i].find(*k) == list[*i].end())
                    continue;
                if(list.find(*k) == list.end())
                    continue;
                if(list[*k].find(*j) == list[*k].end())
                    continue;
                if(list[*i].find(*j) == list[*i].end())
                    list[*i][*j] = DBL_MAX;
                if(list[*i][*j] > list[*i][*k] + list[*k][*j])
                    list[*i][*j] = list[*i][*k] + list[*k][*j];
            }
        }
    }
}

double getGraphSim(ShortestPathGraph &g1,ShortestPathGraph &g2){
    double res = 0;
    for(map<ID_TYPE, map<ID_TYPE, double> >::iterator i = g2.list.begin(); i != g2.list.end();i++){
        for(map<ID_TYPE, double>::iterator j = i->second.begin(); j != i->second.end();j++){
            if(g1.list.find(i->first) == g1.list.end())
                continue;
            if(g1.list[i->first].find(j->first) == g1.list[i->first].end())
                continue;
            res += g1.list[i->first][j->first] * j->second;
        }
    }
    return res / (g1.getLength() * g2.getLength());
}

double ShortestPathGraph::getLength(){
    double res = 0;
    for(map<ID_TYPE, map<ID_TYPE, double> >::iterator i = list.begin(); i != list.end();i++){
        for(map<ID_TYPE, double>::iterator j = i->second.begin(); j != i->second.end();j++){
            res += j->second * j->second;
        }
    }
    return sqrt(res);
}