#include "outlet.h"
#include "bits/stdc++.h"
#include <iostream>
#include <fstream>
#include <string>
#include "satisfyer.h"
#include "pathgenerator.cpp"
using namespace std ;
outlet::outlet(int stax,int stay,int enx,int eny, int number ,int row , int column){
    this->stax=stax;
    this->stay=stay;
    this->enx = enx;
    this->eny = eny;
    this->column=column;
    this->row=row;
    this->number=number;
}
vector<vector<pair<int,int> > >
outlet::Generator(){
  return generator(stax , stay, enx, eny,row  ,column);
}

int main(){
     vector<outlet> outletlist;
     outlet o(1,1,4,4,1,6,6);
     o.Generator();

     string line;
     int row ,col ;
     fstream myfile ("/home/morteza/csp/test.txt");
     int lineNumber = 0 ;
     int inputOutlet [5][5];
     char *c = new char[100];
     if (myfile.is_open())
     {
         getline(myfile,line);
         strcpy(c, line.c_str());
         row = c[0] - '0' + 1;
         col = c[2] - '0' + 1;

     while (getline(myfile,line)){
        for(int i= 0 ; i < line.size() ; i+=2 ){
             strcpy(c, line.c_str());
             inputOutlet[lineNumber][i/2]=c[i] - '0' ;
        }
        lineNumber++;

     }
     myfile.close();
     }
     int sw = 0 ;
     for (int i = 0 ; i < 5 ; i++ ){
         int tsx,tex,tsy,tey;
         for(int j = 0 ; j < 5 ; j++){
             for (int k = 0 ; k < 5 ; k++){
                 if(inputOutlet[j][k] == i+1){
                     if (sw == 0){
                          tsx = j+1;
                          tsy = k+1;
                          sw = 1;
                     }
                 else{
                         tex = j+1;
                         tey = k+1;
                         sw = 0;
                     }
                 }
             }
         }

               outlet ol(tsx,tsy,tex,tey,i + 1,row ,col);
               outletlist.push_back(ol);


     }
    cout<<outletlist.size()<<endl;
    vector<vector<pair<int,int> > > alaki;
    satisfyer s(outletlist);
            s.backTrackMRVFC(alaki);

}
