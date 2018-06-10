#ifndef SATISFYER_H
#define SATISFYER_H
#include "outlet.h"
#include<bits/stdc++.h>
class satisfyer
{
public:
    satisfyer(vector<outlet> allOutlet);
    vector<outlet> allOutlet;
    void IF();
    void initial();
    void showMap();

    bool isConfilict(vector<pair<int,int> > path);
    bool upgrade(vector<pair<int,int> > path,int downOrup);

    bool FC();

    vector<vector<pair<int,int> > > backTrack(vector<vector<pair<int,int> > > ans);
    vector<vector<pair<int,int> > > backTrackMRVLCV(vector<vector<pair<int,int> > > ans);
    vector<vector<pair<int,int> > > backTrackMRVFC(vector<vector<pair<int,int> > > ans);


    vector<pair<int,int> > sortcostrain(outlet ol , vector<vector<pair<int,int> > >   pathlist );

    int countRemainings(outlet outlet);
    int countConstrains(outlet outlet,vector<pair<int,int> > path);

    outlet chooseoutlet(vector<int> satisfiedoutletsIndex);

    const static int size = 10 ;
    vector<int> satisfiedvarIndex;
    int map[size][size];
};

#endif // SATISFYER_H
