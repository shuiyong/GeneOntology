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