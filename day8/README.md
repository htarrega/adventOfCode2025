# Complexity Analysis

## Part 1:
- **Time:** O(N² log N) - where N is the number of points. Creating all edges takes O(N²), sorting edges takes O(N² log N), and performing Union-Find operations takes O(K × α(N)) where K=1000 connections and α is the inverse Ackermann function (effectively constant).
- **Space:** O(N²) - Storage for all edges between points, plus O(N) for the Union-Find data structure.

## Part 2:
- **Time:** O(N² log N) - where N is the number of points. Creating all edges takes O(N²), sorting edges takes O(N² log N), and performing Union-Find operations until all points are connected takes O(N × α(N)) which is dominated by the sorting step.
- **Space:** O(N²) - Storage for all edges between points, plus O(N) for the Union-Find data structure.
