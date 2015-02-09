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
    Ontology g(tp);
    Parser parser;
    cout<<"parse Ontology"<<endl;
    parser.parseOntology(g);
    cout<<"parse Annotation"<<endl;
    parser.parseProtein(g);
    cout<<"Compute IC"<<endl;
    g.computeIC();
    cout<<"Computing Similarity"<<endl;
    
    
    ifstream infile("biogrid_ppi_cln.txt");
    ofstream of1("BP_me");
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
        g.getSPG(p1);
        g.getSPG(p2);
        of1<<p1<<'\t'<<p2<<'\t'<<g.getGeneSim(p1,p2,"me")<<endl;
    }
    
    
    of1.close();
    infile.close();
    
    
    
    
    /*
    GO_TYPE tp = BP;
    Ontology g(tp);
    Parser parser;
    cout<<"parse Ontology"<<endl;
    parser.parseOntology(g);
    cout<<"parse Annotation"<<endl;
    parser.parseProtein(g);
    cout<<"Compute IC"<<endl;
    g.computeIC();
    cout<<"Computing Similarity"<<endl;
    
    ifstream infile("biogrid_ppi_cln.txt");
    ofstream of1("BP_resnik");
    ofstream of2("BP_lin");
    ofstream of3("BP_jiang");
    string tmp,p1,p2;
    getline(infile, tmp);
    while(getline(infile, tmp)){
        int k = tmp.find_first_of('\t',0);
        int end = tmp.size(),j = tmp.size() - 1;
        while(tmp[j] > 'Z' ||tmp[j] <'A')
            j--;
        p1 = tmp.substr(0,k);
        p2 = tmp.substr(k + 1, j - k);
        of1<<p1<<'\t'<<p2<<'\t'<<g.getGeneSim(p1,p2,"resnik")<<endl;
        of2<<p1<<'\t'<<p2<<'\t'<<g.getGeneSim(p1,p2,"lin")<<endl;
        of3<<p1<<'\t'<<p2<<'\t'<<g.getGeneSim(p1,p2,"jiang")<<endl;
    }
    of1.close();
    of2.close();
    of3.close();
    infile.close();
    
    cout<<"Compute MF"<<endl;
    tp = MF;
    Ontology g1(tp);
    cout<<"parse Ontology"<<endl;
    parser.parseOntology(g1);
    cout<<"parse Annotation"<<endl;
    parser.parseProtein(g1);
    cout<<"Compute IC"<<endl;
    g1.computeIC();
    cout<<"Computing Similarity"<<endl;
    
    infile.open("biogrid_ppi_cln.txt");
    of1.open("MF_resnik");
    of2.open("MF_lin");
    of3.open("MF_jiang");
    getline(infile, tmp);
    
    while(getline(infile, tmp)){
        int k = tmp.find_first_of('\t',0);
        int end = tmp.size(),j = tmp.size() - 1;
        while(tmp[j] > 'Z' ||tmp[j] <'A')
            j--;
        
        p1 = tmp.substr(0,k);
        p2 = tmp.substr(k + 1, j - k);
        of1<<p1<<'\t'<<p2<<'\t'<<g1.getGeneSim(p1,p2,"resnik")<<endl;
        of2<<p1<<'\t'<<p2<<'\t'<<g1.getGeneSim(p1,p2,"lin")<<endl;
        of3<<p1<<'\t'<<p2<<'\t'<<g1.getGeneSim(p1,p2,"jiang")<<endl;
    }
    of1.close();
    of2.close();
    of3.close();
    infile.close();
    */
    return 0;
}

