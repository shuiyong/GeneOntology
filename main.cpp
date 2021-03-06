/* 
 * File:   main.cpp
 * Author: yong
 *
 * Created on February 3, 2015, 6:57 PM
 */

#include <cstdlib>
#include <cstring>
#include "Parser.h"
#include "Ontology.h"
using namespace std;

int main(int argc, char** argv) {
    if(argc != 3){
        cerr<<"./... type method"<<endl;
        return 0;
    }
    
    cout<<argv[1]<<" "<<argv[2]<<endl;
    string method;
    string output;
    GO_TYPE tp;
    if(strcmp(argv[1], "BP") == 0){
        tp = BP;
        output = "BP_";
    }
    else if(strcmp(argv[1], "MF") == 0){
        tp = MF;
        output = "MF_";
    }
    else{
        cerr<<"type is wrong"<<endl;
        return -1;
    }
    
    if(strcmp(argv[2], "me") == 0)
        method = "me";
    else if(strcmp(argv[2], "resnik") == 0)
        method = "resnik";
    else if(strcmp(argv[2], "lin") == 0)
        method = "lin";
    else if(strcmp(argv[2], "jiang") == 0)
        method = "jiang";
    else if(strcmp(argv[2], "ICND") == 0)
        method = "ICND";
    else{
        cerr<<"method is wrong"<<endl;
        return -2;
    }
    output = output + method;
    Ontology g(tp);
    Parser parser;
    cout<<"parse Ontology"<<endl;
    parser.parseOntology(g);
    cout<<"parse Annotation"<<endl;
    parser.parseProtein(g);
    cout<<"Compute IC"<<endl;
    g.computeIC();
    cout<<"Computing Similarity"<<endl;
    
    ifstream infile("./resource/biogrid_ppi_cln.txt");
    ofstream of1(output.c_str());
    string tmp,p1,p2;
    getline(infile, tmp);
    int count = 0;
    while(getline(infile, tmp)){
        count++;
        if(count % 1000 == 0)
            cout<<count<<endl;
        int k = tmp.find_first_of('\t',0);
        int end = tmp.size(),j = tmp.size() - 1;
        while(tmp[j] > 'Z' ||tmp[j] <'A')
            j--;
        p1 = tmp.substr(0,k);
        p2 = tmp.substr(k + 1, j - k);
        if(method.compare("me") == 0){
            g.getSPG(p1);
            g.getSPG(p2);
        }
        of1<<p1<<'\t'<<p2<<'\t'<<g.getGeneSim(p1,p2,method)<<endl;
    }
    
    of1.close();
    infile.close();
    return 0;
}

