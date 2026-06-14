/*https://www.interviewbit.com/problems/possibility-of-finishing-all-courses-given-prerequisites/ 
1. Build graph using prerequisite pairs.
2. Calculate indegree for every course.
3. Put all courses with indegree 0 into queue.
4. Process queue:
   - Remove one course.
   - Count it as completed.
   - For every dependent course, reduce indegree by 1.
   - If any dependent course becomes indegree 0, add it to queue.
5. At the end:
   - If completed courses == A, return 1.
   - Else return 0.


A = number of courses
P = number of prerequisite pairs

time complexity: O(A + P)  Because we process every course and every prerequisite edge once.
space complexity: O(A + P) Because we store the graph, indegree array, and queue.

*/
int Solution::solve(int A, vector<int> &B, vector<int> &C) {
    vector<vector<int>> graph(A + 1);
    vector<int> indegree(A + 1, 0);

    // Build graph
    for (int i = 0; i < B.size(); i++) {
        int prerequisite = B[i];
        int course = C[i];

        graph[prerequisite].push_back(course);
        indegree[course]++;
    }

    queue<int> q;

    // Courses with no prerequisite can be taken first
    for (int course = 1; course <= A; course++) {
        if (indegree[course] == 0) {
            q.push(course);
        }
    }

    int completedCourses = 0;

    while (!q.empty()) {
        int currentCourse = q.front();
        q.pop();

        completedCourses++;

        for (int nextCourse : graph[currentCourse]) {
            indegree[nextCourse]--;

            if (indegree[nextCourse] == 0) {
                q.push(nextCourse);
            }
        }
    }

    return completedCourses == A ? 1 : 0;
}
