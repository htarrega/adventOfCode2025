# Complexity Analysis

## Part 1:
- **Time:** O(NM*L/2) = O(NML), where N is the number of ranges, M is the quantity of numbers per range and L is the length in characters of that number. 
- **Space:** O(L) - Where L is the length of the number as string

## Part 2: Count All Traversals Through 0
- **Time:** O(NML^2) - where N is the number of ranges, M is the quantity of numbers per range and L is the length in characters of that number. L is cubic since assuming worst case scenario of the regex backtracking.
- **Space:** O(L) - Where L is the length of the number as string
