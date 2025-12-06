# Complexity Analysis

## Part 1:
- **Time:** O(MN+MN +N) = O(N(2M+1)) = O(MN), where M is the number of lines and N is the size of the line.
- **Space:** O(2N) = O(N), where N is the size of the line.

## Part 2:
- **Time:** O(M + MN + N) = O(MN), where M is the number of rows and N is the maximum number of columns. We iterate through all rows once to find max columns O(M), then iterate through all columns O(N) and for each column we read all rows O(M), giving O(MN).
- **Space:** O(MN + N + M) = O(MN), where M is the number of rows and N is the maximum number of columns. The matrix storage is O(MN), currentNumbers vector is O(N), and digits string is O(M).