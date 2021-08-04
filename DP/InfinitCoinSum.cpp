// https://www.interviewbit.com/problems/coin-sum-infinite/
int Solution::coinchange2(vector<int> &A, int B) {
    vector<int> count(B+1, 0);
    //for(int i = 0; i  < A.size(); i++) count[A[i]] = ;
    count[0] = 1;
    for(int i = 0; i < A.size(); i++) {
        for(int j = 1; j <= B; j++) {
            if(A[i] <= j) count[j] = (count[j] + count[j-A[i]])%1000007;
        }
    }
    return count[B];
}
