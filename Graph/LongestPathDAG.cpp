/*
Longest path in DAG

Given course durations and prerequisites, find minimum time to complete all courses.

Example:

1 takes 2 months
2 takes 3 months
3 depends on 1 and 2, takes 4 months

Minimum finish time:

max(time[1], time[2]) + time[3]
= max(2, 3) + 4
= 7

Pattern:

Topological sort + DP on DAG


I will model the courses as a directed graph. If course B is a prerequisite of course C, I add an edge B -> C.

Since prerequisites form dependency ordering, I first apply topological sorting using indegree. Along with that, I maintain 
finishTime[course], which represents the earliest time by which that course can be completed.

For courses with no prerequisites, finishTime is simply their own duration. When I process a course, I try to relax 
]all dependent courses. If currentCourse finishes at time T, then nextCourse can finish at T + duration[nextCourse].
Since a course may have multiple prerequisites, I take the maximum over all prerequisite paths.

At the end, the answer is the maximum finish time among all courses. If I cannot process all courses, that means there is a cycle,
so completion is impossible.



Core idea

Use topological sort + DP.

Maintain:

finishTime[course] = earliest time by which this course can be completed

For a course with no prerequisites:

finishTime[course] = duration[course]

For a dependent course:

finishTime[nextCourse] = max(
    finishTime[nextCourse],
    finishTime[currentCourse] + duration[nextCourse]
)

Why max?

Because if a course has multiple prerequisites, it can start only after the slowest prerequisite chain finishes.

Complexity

Let:

A = number of courses
P = number of prerequisite pairs

Time complexity:

O(A + P)

Space complexity:

O(A + P)

Because we process every course and every edge once.
*/

int minimumCompletionTime(
    int A,
    vector<int> &B,
    vector<int> &C,
    vector<int> &duration
) {
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
    vector<int> finishTime(A + 1, 0);

    // Courses with no prerequisites can start immediately
    for (int course = 1; course <= A; course++) {
        if (indegree[course] == 0) {
            q.push(course);
            finishTime[course] = duration[course];
        }
    }

    int completedCourses = 0;
    int answer = 0;

    while (!q.empty()) {
        int currentCourse = q.front();
        q.pop();

        completedCourses++;
        answer = max(answer, finishTime[currentCourse]);

        for (int nextCourse : graph[currentCourse]) {
            // If we complete currentCourse first, then nextCourse can finish at:
            // finishTime[currentCourse] + duration[nextCourse]
            finishTime[nextCourse] = max(
                finishTime[nextCourse],
                finishTime[currentCourse] + duration[nextCourse]
            );

            indegree[nextCourse]--;

            if (indegree[nextCourse] == 0) {
                q.push(nextCourse);
            }
        }
    }

    // Cycle exists
    if (completedCourses != A) {
        return -1;
    }

    return answer;
}
