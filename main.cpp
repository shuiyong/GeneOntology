/* 
 * File:   main.cpp
 * Author: yong
 *
 * Created on February 3, 2015, 6:57 PM
 */

#include <cstdlib>
#include "Parser.h"
#include "Ontology.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    GO_TYPE tp = BP;
    Ontology g(BP);
    Parser parser;
    cout<<"parse Ontology"<<endl;
    parser.parseOntology(g);
    cout<<"parse Annotation"<<endl;
    parser.parseProtein(g);
    ofstream out("graph");
    g.printGraph(out);
    out.close();
    return 0;
}

