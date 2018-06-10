#include "satisfyer.h"
#include "outlet.h"
#include<bits/stdc++.h>
satisfyer::satisfyer(vector<outlet> allOutlet)
{
    this->allOutlet=allOutlet;
    initial();
}
void
satisfyer::IF(){
    int isPathfound = 0;
vector<vector<pair<int,int> > >   pathes;

    for (int i = 0 ; i < allOutlet.size() ; i++){
        pathes.clear();
        pathes  = allOutlet.at(i).Generator() ;
        for (int j = 0 ; j < pathes.size() ;j++){
                if (  !isConfilict(pathes[j])){
                    upgrade(pathes[j],1);
                    isPathfound = 1;
                    break;
                }
            }
    }
}
vector<vector<pair<int,int> > >
satisfyer::backTrack(vector<vector<pair<int,int> > > ans){

   if (ans.size() == allOutlet.size())
       return ans;
   vector<vector<pair<int,int> > >   pathes , resualt;
   resualt = ans;
   pathes  = allOutlet.at(ans.size()).Generator() ;
   for (int j = 0 ; j < pathes.size() ;j++){
       if (  ! isConfilict(pathes[j])){
           resualt.push_back(pathes[j]);
           upgrade(pathes[j],1);
           if ( !backTrack(resualt).empty())
                return resualt;
           resualt.pop_back();
           upgrade(pathes[j],0);
       }

   }
   vector<vector<pair<int,int> > > a ;
   return a;
}


vector<vector<pair<int,int> > >
satisfyer::backTrackMRVLCV(vector<vector<pair<int,int> > > ans){

    if (ans.size() == allOutlet.size())
        return ans;
    vector<vector<pair<int,int> > >   pathes , resualt;
    resualt = ans;
    //pathes  = outletlist.at(ans.size()).Generator() ;
    outlet n = chooseoutlet(satisfiedvarIndex);
    cout << " here =  " << n.number ;
    pathes = n.Generator();
    vector<pair<int,int> > indexes;
    indexes = sortcostrain(n, pathes);
    for (int j = indexes.size() - 1  ; j >= 0  ;j--){
        if (  ! isConfilict(pathes[indexes[j].second])){
            resualt.push_back(pathes[indexes[j].second]);
            upgrade(pathes[indexes[j].second],1);
            satisfiedvarIndex.push_back(n.number);
            if ( ! backTrackMRVLCV(resualt).empty())
                 return resualt;
            resualt.pop_back();
            upgrade(pathes[indexes[j].second],0);
            satisfiedvarIndex.erase(std::remove(satisfiedvarIndex.begin(),satisfiedvarIndex.end(), n.number),satisfiedvarIndex.end() );
        }

    }
    vector<vector<pair<int,int> > > a ;
    return a;
}
vector<pair<int,int> >
satisfyer::sortcostrain(outlet ol , vector<vector<pair<int,int> > >   pathes ){
     vector<pair<int,int> > pathindex;
    for(int i = 0 ; i  <  pathes.size() ; i++)
        pathindex.push_back(make_pair(countConstrains(ol , pathes[i]), i ));

    sort(pathindex.begin(),pathindex.end());
    for (int j = 0 ; j < pathindex.size() ; j++)

    return pathindex;
}


int
satisfyer::countRemainings(outlet ol){
    vector<vector<pair<int,int> > >   pathlist;
    int count = 0 ;
    pathlist  = ol.Generator();
    for (int j = 0 ; j < pathlist.size() ;j++){
        if (  ! isConfilict(pathlist[j])){
            count++;
        }
    }

    return count;
}
int
satisfyer::countConstrains(outlet o,vector<pair<int,int> > path){
    vector<vector<pair<int,int> > >   pathlist;
    pathlist  = o.Generator();
    int sw = 0, count = 0;

        if (!isConfilict(path)){
           upgrade(path,1);
           for (int i = 0  ; i< allOutlet.size();i++){

               if(allOutlet[i].number != o.number ){
               for (int k = 0 ; k  <  satisfiedvarIndex.size() ; k++){
                    if (satisfiedvarIndex[k]== allOutlet[i].number)
                        sw = 1;
                    }
               if (sw == 0)
                   count += countRemainings(allOutlet[i]);

               }
           }
           //countMRV() for nodes which does not satisfy
           upgrade(path,0);
}
        else
            return INT_MAX;


return count;
}
outlet
satisfyer::chooseoutlet(vector<int> satisfiedvarIndex){

    vector<pair<int,int> > outletindex;
    for (int i = 0 ; i < allOutlet.size() ; i++)
        outletindex.push_back(make_pair( countRemainings(allOutlet[i]), i ));

    sort(outletindex.begin(),outletindex.end());

    int sw = 0 ;
    for (int i = 0 ; i < outletindex.size();i++ ){
       for (int j = 0 ; j  <  satisfiedvarIndex.size() ; j++){
            if (satisfiedvarIndex[j] == outletindex[i].second +1  )
                sw = 1;

        }
       if(sw == 0)
           return allOutlet[outletindex[i].second];
       sw=0;
     }

}


vector<vector<pair<int,int> > >
satisfyer::backTrackMRVFC(vector<vector<pair<int,int> > > ans){

    if (ans.size() == allOutlet.size())
        return ans;
    vector<vector<pair<int,int> > >   pathlist , resualt ,a;

    resualt = ans;
    //pathlist  = nodelist.at(ans.size()).getPath() ;
    outlet ol = chooseoutlet(satisfiedvarIndex);
    cout << " here =  " << ol.number ;
    pathlist = ol.Generator();
    for (int j = 0 ; j < pathlist.size() ;j++){
        if (  ! isConfilict(pathlist[j])){
            resualt.push_back(pathlist[j]);
            upgrade(pathlist[j],1);
            satisfiedvarIndex.push_back(ol.number);
            if (FC()){
            if ( ! backTrackMRVFC(resualt).empty())
                 return resualt;
            }
            resualt.pop_back();
            upgrade(pathlist[j],0);
            satisfiedvarIndex.erase(std::remove(satisfiedvarIndex.begin(),satisfiedvarIndex.end(), ol.number),satisfiedvarIndex.end() );
        }

    }

    return a;
}
bool
satisfyer::FC(){
    int count = 0 , sw =0;

        for (int i = 0  ; i< allOutlet.size();i++){
            for (int k = 0 ; k  <  satisfiedvarIndex.size() ; k++){
                 if (satisfiedvarIndex[k] == allOutlet[i].number)
                     sw = 1;
                 }
        if (sw == 0){
            count = countRemainings(allOutlet[i]);
            if(!count)
                return false;
             }

        }


        return true;

}









void
satisfyer::showMap(){
    for(int i = 1 ; i <= 5 ; i++){
        for(int j = 1 ; j <= 5  ; j++){
           cout<< map[i][j]<<"  ";
        }
        cout << endl;
    }
}

void
satisfyer::initial(){
    for(int i =0 ; i< satisfyer::size;i++)
                for(int j =0 ; j < satisfyer::size ; j++)
            map[i][j]=0;
    for(int i = 0 ; i < allOutlet.size();i++){
        map[allOutlet.at(i).stax][allOutlet.at(i).stay] = i+1;/// one means that cell is full
        map[allOutlet.at(i).enx][allOutlet.at(i).eny] = i+1;

    }

    for(int i = 0 ; i <= 5 ; i++){
        for(int j = 0 ; j <= 5  ; j++){
           cout<< map[i][j]<<"  ";
        }
        cout << endl;
}
}
bool
satisfyer::isConfilict(vector<pair<int,int> > path){
    for (int i = 1 ; i < path.size() - 1 ;i++ )// from 1 cell after begin and 1 cell before path
        if(map[path[i].first][path[i].second] != 0)
            return true;
    return false;
}
bool
satisfyer::upgrade(vector<pair<int,int> > path,int downOrup){
    for (int i = 1 ; i < path.size() - 1 ;i++ ){
        if(downOrup)
            map[path[i].first][path[i].second] = map[path[0].first][path[0].second];
        else
             map[path[i].first][path[i].second] = 0;
    }
    showMap();
}


