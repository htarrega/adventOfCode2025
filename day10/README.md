# Complexity Analysis

**Implementation Note:** Both parts use custom-implemented Gaussian elimination algorithms. Only standard C++ library headers are included (`<algorithm>`, `<vector>`, `<string>`, etc.). No external linear algebra libraries are used - all matrix operations and equation solving are implemented from scratch in the solution.

## Part 1:
- **Time:** O(M × (L² × B + 2^F × B)) - where M is the number of machines, L is the number of indicator lights, B is the number of buttons, and F is the number of free variables. Gaussian elimination over GF(2) takes O(L² × B), and trying all 2^F combinations of free variables takes O(2^F × B).
- **Space:** O(L × B) - Storage for the augmented matrix representing the system of XOR equations.

## Part 2:
- **Time:** O(M × (C² × B + K^F × B)) - where M is the number of machines, C is the number of counters, B is the number of buttons, F is the number of free variables, and K is the maximum value tried for free variables (200). Gaussian elimination takes O(C² × B), and trying up to K^F combinations of free variables takes O(K^F × B).
- **Space:** O(C × B) - Storage for the augmented matrix representing the system of linear equations.
