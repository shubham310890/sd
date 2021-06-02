

// [ 0  , 1 , 0,
//   1  , 0 , 0
//   0  , 0 , 0 ]
#include<iostream>
#include <vector>
#include <queue>
using namespace std;
int dr[] = {-1,0,1,0};
int dc[] = {0, 1, 0, -1};
bool isValid(int r, int c, int i, int j) {
    if(i < 0 || i >= r || j < 0 || j >= c) return false;
    return true;
}
int bfs(vector<vector<int>> & in, int r, int c, vector<vector<int>> & org)
{
    //cout << "Bfs" << endl;
    queue<pair<int, int>> q;
    q.push(make_pair(r,c));
    q.push(make_pair(-1,-1));
    vector<vector<bool>> visited(in.size(), vector<bool>(in[0].size(), false));
    int level = 1;
    while(q.empty() == false) {
        pair<int,int> front = q.front();
        q.pop();
        int x = front.first, y = front.second;
        if(x == -1 && y == -1) {
            //cout << "levle" << endl;
            level++;
            if(q.empty()==false) {
                q.push(make_pair(-1,-1));
            }
        } else {
            for(int i = 0; i < 4; i++) {
                int newX = x+dr[i], newY = y+dc[i];
                //cout << r << " " << c << " " << newX << " " << newY << endl;
                if(isValid(in.size(), in[0].size(), newX, newY) && visited[newX][newY] == false) {
                    if(org[newX][newY] == 1) return level;
                    q.push(make_pair(newX, newY));
                   // cout << newX << newY << endl;
                    visited[newX][newY] = true;
                }
            }
        }
    }
    return -1;
 }
 void bfs2(vector<vector<int>> & in, vector<vector<int>> & org) {
    queue<pair<int,int>> q;
    for(int i = 0; i < in.size(); i++) {
        for(int j = 0; j < in[0].size(); j++) {
            if(in[i][j] == 1) q.push(make_pair(i,j));
        }
    }
    q.push(make_pair(-1,-1));
    int level = 0;
    vector<vector<bool>> visited(in.size(), vector<bool>(in[0].size(), false));
    while(q.empty() == false) {
        pair<int,int> front = q.front();
        q.pop();
        int x = front.first, y = front.second;
        if(x == -1 && y == -1) {
            //cout << "levle" << endl;
            level++;
            if(q.empty()==false) {
                q.push(make_pair(-1,-1));
            }
        } else {
            for(int i = 0; i < 4; i++) {
                int newX = x+dr[i], newY = y+dc[i];
                //cout << r << " " << c << " " << newX << " " << newY << endl;
                if(isValid(in.size(), in[0].size(), newX, newY) && visited[newX][newY] == false) {
                    org[newX][newY] = org[x][y]+1;
                    q.push(make_pair(newX, newY));
                   // cout << newX << newY << endl;
                    visited[newX][newY] = true;
                }
            }
        }
    }
}
void findNearestATM(vector<vector<int>> & in)
{
    int row = in.size(), col = in[0].size();
    vector<vector<int>> org(in.size(),vector<int>(in[0].size(), 0));
    
    bfs2(in,org);

    cout << endl;
    for(int i = 0; i < in.size(); i++) {
        for(int j = 0; j < in[0].size(); j++){
            in[i][j] = in[i][j] == 1 ? 1: org[i][j] ;
        }
    }
    for(int i = 0; i < in.size(); i++)
    {
        for(int j = 0; j < in[0].size(); j++) {
            cout << in[i][j] << " ";
        }
        cout << endl;
    }
}

int main() 
{
    vector<vector<int>> in(3, vector<int>(4,0));
    in[0][1] = 1, in[1][0] = 1, in[2][3] = 1;
    for(int i = 0; i < in.size(); i++)
    {
        for(int j = 0; j < in[0].size(); j++) {
            cout << in[i][j] << " ";
        }
        cout << endl;
    }
    findNearestATM(in);
    //
    
    return 0;
}
