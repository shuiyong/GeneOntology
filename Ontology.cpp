/* 
 * File:   Ontology.cpp
 * Author: yong
 * 
 * Created on February 3, 2015, 7:38 PM
 */

#include "Ontology.h"

Ontology::Ontology() {
}

Ontology::Ontology(const Ontology& orig) {
}

Ontology::~Ontology() {
    for(map<ID_TYPE, OntologyNode *>::iterator it = graph.begin(); it != graph.end() ; it++)
        delete it->second;
}

GO_TYPE strToGoType(string tmp){
    if(tmp.compare("biological_process") == 0 || tmp.compare("P") == 0)
        return BP;
    if(tmp.compare("molecular_function") == 0 || tmp.compare("F") == 0)
        return MF;
    if(tmp.compare("cellular_component") == 0 || tmp.compare("C") == 0)
        return CC;
    return ERR;
}


Ontology::Ontology(GO_TYPE type) {
    this->type = type;
}

void Ontology::addNode(ID_TYPE id) {
    if (graph.find(id) == graph.end()) {
        OntologyNode *np = new OntologyNode(id);
        graph[id] = np;
    }
}

void Ontology::addEdge(ID_TYPE parent, ID_TYPE child) {
    addNode(parent);
    addNode(child);
    graph[parent]->addChild(graph[child]);
    graph[child]->addParent(graph[parent]);
}

void Ontology::addAnnotation(ID_TYPE id, string anno) {
    graph[id]->addAnnotation(anno);
    annotation[anno].insert(id);
}

void Ontology::printGraph(ofstream &out) {
    out << "graph size() = " << graph.size() << endl;
    int i = 0;
    for (map<ID_TYPE, OntologyNode *>::iterator it = graph.begin(); it != graph.end(); it++) {
        out << "[" << i++ << "]" << endl;
        it->second->printNode(out);
        out << endl;
    }
}

double Ontology::getGeneSim(string g1, string g2, string method){
    
    if(method.compare("me") == 0){
        return getGraphSim(spg[g2],spg[g1]);
    }
    //cout<<"size = "<<annotation[g1].size()<<'\t'<<annotation[g2].size()<<endl;
    int count = 0;
    double res = 0;
    for(set<ID_TYPE>::iterator i = annotation[g1].begin(); i != annotation[g1].end(); i++){
        for(set<ID_TYPE>::iterator j = annotation[g2].begin(); j != annotation[g2].end(); j++){
            //cout<<"getGeneSim = "<<count++<<endl;
            res += getOntologyNodeSim(*i, *j, method);
        }
    }
    return res / (annotation[g1].size() * annotation[g2].size());
}

double Ontology::getOntologyNodeSim(ID_TYPE id1, ID_TYPE id2, string method){
    set<OntologyNode *> p1 = graph[id1]->getParents();
    set<OntologyNode *> p2 = graph[id2]->getParents();
    double ic1 = getIC(id1);
    double ic2 = getIC(id2);
    if(ic1 == -1 || ic2 == -1)
        return 0;
    double res = 0;
    for(set<OntologyNode *>::iterator i = p1.begin(); i != p1.end(); i++){
        if (p2.find(*i) == p2.end())
            continue;
        double tx = getIC((*i)->getID());
        if (method.compare("resnik") == 0 || method.compare("jiang") == 0) {
            res = max(res, tx);
        }
        if (method.compare("lin") == 0) {
            res = max(res, 2 * tx / (ic1 + ic2));
        }
        
    }
    if(method.compare("jiang") == 0){
        res = 1 / (1 + ic1 + ic2 - 2 * res);
    }
    return res;
}

size_t Ontology::getNumOfAnnotation(ID_TYPE id){
    return graph[id]->getNumOfAnnotation();
}

size_t Ontology::getNumOfAnnotation(){
    return annotation.size();
}

void Ontology::computeIC(){
    int count = 50;
    for(map<ID_TYPE,OntologyNode *>::iterator it = graph.begin(); it != graph.end();it++){
        if(getNumOfAnnotation(it->first) == 0)
            infoCon[it->first] = -1;
        else
            infoCon[it->first] = -log( (double)getNumOfAnnotation(it->first) / getNumOfAnnotation());
    }
}

double Ontology::getIC(ID_TYPE id){
    return infoCon[id];
}

void Ontology::getSPG(string pro){
    if(spg.find(pro) != spg.end())
        return;
    map<ID_TYPE, map<ID_TYPE, double> > myList;
    set<ID_TYPE> myAllNodes;
    
    //cout<<"size = "<<annotation[pro].size()<<endl;
    for(set<ID_TYPE>::iterator it = annotation[pro].begin(); it != annotation[pro].end(); it++){
        //cout<<*it<<endl;
        graph[*it]->loadSubGraph(myList,myAllNodes); // 0070816
    }
    //cout<<"size = "<<"end"<<endl;
    for(map<ID_TYPE, map<ID_TYPE, double> >::iterator i = myList.begin(); i != myList.end();i++){
        for(map<ID_TYPE, double>::iterator j = i->second.begin(); j!= i->second.end();j++){
            j->second = getIC(i->first) - getIC(j->first);
        }
    }
    //cout<<"Computing Shortest Path"<<endl;
    ShortestPathGraph sgp(myList,myAllNodes);
    spg[pro] = sgp;
}

GO_TYPE Ontology::getType() {
    return type;
}