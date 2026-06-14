/*

Minimum semesters to finish all courses

Given prerequisites, in one semester you can take all courses whose prerequisites are completed. Return minimum semesters.

Example:

1 -> 3
2 -> 3
3 -> 4
Let:

A = number of courses
P = number of prerequisite pairs

Time complexity:

O(A + P)

Because every course and every edge is processed once.

Space complexity:

O(A + P)

Because we store graph, indegree array, and queue.

I will model the courses as a directed graph. If course B[i] is a prerequisite for C[i], I add an edge B[i] -> C[i] and increase
indegree of C[i].

Now I use BFS topological sorting. All courses with indegree 0 have no pending prerequisites, so they can be taken in the first semester.
In each BFS level, I process all currently available courses. That entire level represents one semester.

After completing courses of the current semester, I reduce the indegree of their dependent courses. If any dependent course becomes 
indegree 0, it becomes available for the next semester.

At the end, if I completed all courses, I return the number of BFS levels as the minimum number of semesters. If not, there is a cycle,
so I return -1.
*/
int minimumSemesters(int A, vector<int> &B, vector<int> &C) {
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

    // Courses with no prerequisites can be taken in semester 1
    for (int course = 1; course <= A; course++) {
        if (indegree[course] == 0) {
            q.push(course);
        }
    }

    int completedCourses = 0;
    int semesters = 0;

    while (!q.empty()) {
        int size = q.size();

        // These courses belong to the current semester
        semesters++;

        for (int i = 0; i < size; i++) {
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
    }

    // If all courses are not completed, cycle exists
    if (completedCourses != A) {
        return -1;
    }

    return semesters;
}
