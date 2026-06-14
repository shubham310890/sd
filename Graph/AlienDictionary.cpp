/*

Given a sorted list of words from an alien language, find the order of characters in that alien language.

Example:

words = ["baa", "abcd", "abca", "cab", "cad"]

These words are already sorted according to the alien dictionary. We have to infer character order.

Explaination: 
I will model this problem as a directed graph of characters. Since the given words are already sorted according to the alien dictionary,
I can compare every adjacent pair of words. The first position where the two words differ tells me the relative ordering of two characters.
For example, if word1 has character x and word2 has character y at the first differing position, then x must come before y, so I add a directed
edge x -> y.
After building all such constraints, the problem becomes finding a valid ordering of characters that satisfies all directed edges. This is a
topological sort problem. I use BFS topological sort with indegree. Characters with indegree 0 have no character required before them, so they 
can be placed first. Whenever I place a character in the answer, I reduce the indegree of its neighbors. If a neighbor becomes indegree 0,
I add it to the queue.
If I process all characters, the generated order is valid. If not, there is a cycle, so no valid alien dictionary order exists.
There is also one invalid prefix case: if a longer word appears before its own prefix, like "abc" before "ab", then the ordering is
impossible and I return empty string.

Complexity
N = number of words
L = average length of each word
K = number of unique characters
Building graph: O(N * L)

Topological sort: O(K + E)

Where E is number of ordering edges.

Overall:
Time Complexity: O(N * L + K + E)

Usually simplified as: O(total characters in all words)

Space Complexity: O(K + E)

For lowercase English letters, K <= 26, so it is almost constant.
*/

class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>> graph;
        unordered_map<char, int> indegree;

        // Step 1: Initialize all unique characters
        for (string &word : words) {
            for (char ch : word) {
                if (indegree.find(ch) == indegree.end()) {
                    indegree[ch] = 0;
                }
            }
        }

        // Step 2: Build graph by comparing adjacent words
        for (int i = 0; i < words.size() - 1; i++) {
            string word1 = words[i];
            string word2 = words[i + 1];

            int len = min(word1.size(), word2.size());
            bool foundDifference = false;

            for (int j = 0; j < len; j++) {
                char c1 = word1[j];
                char c2 = word2[j];

                if (c1 != c2) {
                    // c1 must come before c2
                    if (graph[c1].find(c2) == graph[c1].end()) {
                        graph[c1].insert(c2);
                        indegree[c2]++;
                    }

                    foundDifference = true;
                    break;
                }
            }

            // Invalid case:
            // "abc" comes before "ab", but "abc" is longer.
            // This is impossible in lexicographical order.
            if (!foundDifference && word1.size() > word2.size()) {
                return "";
            }
        }

        // Step 3: Push all characters with indegree 0
        queue<char> q;

        for (auto &entry : indegree) {
            if (entry.second == 0) {
                q.push(entry.first);
            }
        }

        // Step 4: BFS Topological Sort
        string order;

        while (!q.empty()) {
            char current = q.front();
            q.pop();

            order.push_back(current);

            for (char next : graph[current]) {
                indegree[next]--;

                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        // Step 5: If all characters are not processed, cycle exists
        if (order.size() != indegree.size()) {
            return "";
        }

        return order;
    }
};
