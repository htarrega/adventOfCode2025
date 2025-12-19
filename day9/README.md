# Complexity Analysis

## Part 1:
- **Time:** O(N log N + H²) - where N is the number of points and H is the number of hull points. Reading and sorting points takes O(N log N), building the convex hull using Andrew's monotone chain algorithm takes O(N log N), and checking all pairs of hull points takes O(H²) where H ≤ N.
- **Space:** O(N) - Storage for points and hull vertices.

## Part 2:
- **Time:** O(N²) - where N is the number of points. Creating coordinate compression and validating all grid points takes O(N²), building the prefix sum array takes O(N²), and checking all pairs of points takes O(N²) with O(1) rectangle validation using prefix sums.
- **Space:** O(N²) - Storage for the validity grid and prefix sum array, where the grid has at most N × N cells from coordinate compression.
