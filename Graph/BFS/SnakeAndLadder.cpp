//https://www.interviewbit.com/problems/snake-ladder-problem/

int Solution::snakeLadder(vector<vector<int> > &A, vector<vector<int> > &B) {
    map<int, int> snake, ladder; 
    for(int i = 0 ; i < A.size(); i++) {
        ladder[A[i][0]] = A[i][1];
    }
    for(int i = 0 ; i < B.size(); i++) {
        snake[B[i][0]] = B[i][1];
    }
    int moves = 0;
    queue<int> q;
    q.push(1);
    q.push(-1);
    set<int> visited;
    while(!q.empty()) {
        int front = q.front();
        q.pop();
        if(front == -1) {
            if(q.empty() == false) {
                q.push(-1);
                moves++;
            }
        }
        else {
        
        for(int i = 1; i <= 6 ; i++) {
            int nextCell = front+i;
            int resultCell = nextCell;
                if(snake.find(nextCell) != snake.end()) {
                    resultCell = snake[nextCell];
                } else if(ladder.find(nextCell) != ladder.end()) {
                    resultCell = ladder[nextCell];
                } 
                if(resultCell == 100) {
                    return moves+1;
                }
                if(visited.find(resultCell) == visited.end()) {
                q.push(resultCell);
                visited.insert(resultCell);
                }
        }
        }
    }
    return -1;
}
