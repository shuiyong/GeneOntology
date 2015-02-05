/* 
 * File:   Parser.h
 * Author: yong
 *
 * Created on February 3, 2015, 7:06 PM
 */

#ifndef PARSER_H
#define	PARSER_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<cstring>
#include"Ontology.h"
using namespace std;
class Parser {
public:
    Parser();
    Parser(const Parser& orig);
    
    void parseOntology(Ontology &graph);
    
    void parseProtein(Ontology &graph);
    
    virtual ~Parser();
private:
    
};

#endif	/* PARSER_H */

