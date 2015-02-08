/* 
 * File:   Parser.cpp
 * Author: yong
 * 
 * Created on February 3, 2015, 7:06 PM
 */

#include "Parser.h"


bool myComp(string s1, string s2){
    if(s1.size() < s2.size())
        return false;
    for(int j = 0; j < s2.size();j++)
        if(s2[j] != s1[j])
            return false;
    return true;
}

Parser::Parser() {
}

Parser::Parser(const Parser& orig) {
}

Parser::~Parser() {
}

void Parser::parseOntology(Ontology &graph){
    ifstream in("go.obo"); // file to gene ontology
    int count = 28;
    string tmp;
    
    while(count--)
        getline(in,tmp);
    getline(in,tmp);
    bool flag = true;
    string type;
    string ID;
    vector<string> kids; 
    count=0;
    while(getline(in,tmp)){
        
        if(myComp(tmp,"[Term]")){
            count++;
            if(count % 10000 == 0)
                cout<<count/10000<<endl;
            /*
            cout<<"ID = "<<ID<<endl;
            cout<<"Type = "<<type<<endl;
            cout<<"Flag = "<<flag<<endl;
            cout<<"kids = ";
            for(int i = 0; i < kids.size(); i++){
                cout<<kids[i]<<'\t';
            }
            cout<<endl<<endl;
            kids.clear();
            */
            if(flag == false){
                flag = true;
                kids.clear();
                continue;
            }
            if(strToGoType(type) != graph.getType())
                continue;
            graph.addNode(ID);
            for(int i = 0; i < kids.size(); i++)
                graph.addEdge(kids[i],ID);
            //graph.printGraph();
            kids.clear();
        }
        if(myComp(tmp, "id")){
            ID = tmp.substr(7,tmp.size() - 7);
        }
        if(myComp(tmp, "namespace")){
            type = tmp.substr(11,tmp.size() - 11);
        }else if(myComp(tmp, "is_a")){
            string t1 = tmp.substr(9,7);//assume the length of id is 7
            kids.push_back(t1);
        }else if(myComp(tmp, "is_obsolete")){
            //getline(in, tmp);
            string t2 = tmp.substr(13,tmp.size() - 13);
            if(t2.compare("true") == 0){
                flag = false;
            }
        }else if(tmp.find("part_of GO:") != string::npos){
            int beg = tmp.find("part_of GO:");
            kids.push_back(tmp.substr(beg + 11, 7));
            //cout<<"part of = "<<tmp.substr(beg + 11, 7)<<endl;
        }
    }
    cout<<"end"<<endl;
    in.close();
}
    
void Parser::parseProtein(Ontology &graph){
    ifstream in("gene_association.sgd");
    int count = 26;
    string tmp;
    while(count--){
        getline(in, tmp);
    }
    string type;
    string goid;
    string protein;
    count = 0;
    while(getline(in, tmp)){
        count++;
        if(count % 10000 == 0)
            cout<< count/10000<<endl;
        stringstream sin(tmp);
        int k = 0;
        string tmp1;
        while(k < 12){
            if(k == 4)
                getline(sin, goid, '\t');
            else if(k == 8)
                getline(sin, type,'\t');
            else if(k == 10)
                getline(sin, protein,'\t');
            else
                getline(sin, tmp1,'\t');
            k++;
        }
        
        if(protein[0] != 'Y' || strToGoType(type) != graph.getType())
            continue;
        goid = goid.substr(3,goid.size() - 3);
        protein = protein.substr(0,protein.find_first_of('|'));
        /*
        cout<<"id = "<<goid<<endl;
        cout<<"type = "<<type<<endl;
        cout<<"protein = "<<protein<<endl;
        */
        
        graph.addAnnotation(goid,protein);
        
    }
    in.close();
}