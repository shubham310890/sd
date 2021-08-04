// https://www.interviewbit.com/problems/region-in-binarymatrix/
int x[] = {-1,-1,0,1,1,1,0,-1};
int y[] = {0,-1,-1, -1, 0, 1,1,1};
bool isInRange(vector<vector<int>> &A, int x, int y) {
    return x >= 0 && x < A[0].size() && y >= 0 && y < A.size();
}
void dfs(vector<vector<int>> & A, int & current, int a, int b) {
    A[a][b] = -1;
    current++;
    for(int i = 0; i < 8; i++) {
        int nx = a+y[i],  ny = b + x[i];
        if(isInRange(A,ny, nx) && A[nx][ny] == 1 ) {
            dfs(A,current, nx, ny);
        }
    }
}
int Solution::solve(vector<vector<int> > &A) {
    int result = 0, current = 0;
    for(int i = 0; i < A.size(); i++) {
        for(int j = 0; j < A[0].size(); j++) {
            if(A[i][j] == 1) {
                current = 0;
                dfs(A,current, i, j);
                result = current > result ? current : result;
            }
        }
    }
    return result;
}
