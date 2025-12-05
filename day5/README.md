# Complexity Analysis

## Part 1:
- **Time:** O(R log R + N × R) - where R is the number of ranges and N is the number of numbers to check. Sorting ranges takes O(R log R), and for each number, binary search takes O(log R) followed by worst-case O(R) linear scan.
- **Space:** O(R + N) - Storage for ranges and numbers lists.

## Part 2:
- **Time:** O(R log R + R) = O(R log R) - where R is the number of ranges. Sorting takes O(R log R) and merging ranges takes O(R).
- **Space:** O(R) - Storage for ranges and merged ranges list.