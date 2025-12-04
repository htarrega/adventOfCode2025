# Complexity Analysis

## Part 1:
- **Time:** O(8MN) = O(MN), where M is the number of lines and N is the line length, assuming all lines have equal length.
- **Space:** O(3N) = O(N) - Where N is the length of every line, assuming all have equal length.

## Part 2:
- **Time:** O(8MN × min(M, N)) = O(MN × min(M, N)) = O(M³) ,  where M is the number of rows and N is the number of columns, assuming they are equal. This is due to iterative layer-peeling requiring up to O(min(M, N)) passes through the grid.
- **Space:** O(MN) = O(M²) - Stores the entire grid in memory plus a vector for coordinates to remove per iteration.