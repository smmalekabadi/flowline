#ifndef OUTLET_H
#define OUTLET_H
#include "bits/stdc++.h"
using namespace std;
class outlet
{
public:
    outlet(int stax,int stay,int enx,int eny, int number ,int row , int column);
    int stax, stay;
    int enx, eny ;
    int row,column;
    int number;
    vector<vector<pair<int,int> > > Generator();
};

#endif // OUTLET_H
