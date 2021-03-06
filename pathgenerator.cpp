
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10;

vector<vector<pair<int, int> > > paths;//vector contains all paths
//each path is represented by a vector of coordinates
//each coordinate is two integer number (x, y)

int startx, starty; //x and y position of start point
int endx, endy; //x and y position of end point
int n, m; // n = number of rows, m = number of columns

bool isEmpty[MAX_N][MAX_N];
bool mark[MAX_N][MAX_N];
//we use mark to determine which cells we already visited in our algo.

vector<pair<int, int> > cur_path;
//this vector keep the current path generated by algo.


//this function checks if (x, y) is in the n*m table
//and we have not visited it already
bool valid(int x, int y) {
    if(x <= 0 or x > n or y <= 0 or y > m)
        return false;
    if(mark[x][y])
        return false;
    return true;
}

void go(int x, int y) {
    mark[x][y] = true;//determine this point is visited
    cur_path.push_back({x, y});//we add this point to our current path

    if(x == endx and y == endy) {//if this point is the end point
        paths.push_back(cur_path);//add this current path to paths
        return;
    }

    if(valid(x+1, y)) {
        go(x+1, y);
        cur_path.pop_back();
        mark[x+1][y] = false;
    }
    if(valid(x-1, y)) {
        go(x-1, y);
        cur_path.pop_back();
        mark[x-1][y] = false;
    }
    if(valid(x, y+1)) {
        go(x, y+1);
        cur_path.pop_back();
        mark[x][y+1] = false;
    }
    if(valid(x, y-1)) {
        go(x, y-1);
        cur_path.pop_back();
        mark[x][y-1] = false;
    }

}
/*bool isConflict(vector <pair <int,int>>){
}
void incrementalFormulation(vector <pair<int, int > > starts , vector <pair<int, int > > ends){
    for(int i = 0 ; i < starts.size();i++){
        for (int j = 0 ; j <  paths;j++){
            if (isConflict(paths[j]))
                continue;
            else
                break;
        }
    }

}*/
vector<vector<pair<int,int> > >
generator( int stx, int sty, int enx, int eny,int row,int column) {

    paths.clear();
    cur_path.clear();


    m = row-1 ;
    n = column-1;
    startx = stx;
    starty = sty;
    endx = enx;
    endy = eny;

    go(startx, starty);//call algorithm
    /*
    This algorithm is a recursive algorithm which generate all paths
    from start to end that do not meet itself in the middle
    it uses the fact that from each point we only have four direction to continue the path
    1-Up 2-Down 3-Right 4-Left
    */

    //this part of code shows all path from strat point to end point
    cout<<"Total Number of paths :"<< paths.size()<<endl;
    for(int i = 0 ; i < paths.size() ; i++) {
//       cout<<"Path "<<i+1<<": ";
        for(int j = 0 ; j < paths[i].size() ; j++)
             cout<<"("<<paths[i][j].first<<", "<<paths[i][j].second<<") ";
//        cout<<endl;
    }
    return paths;
}

