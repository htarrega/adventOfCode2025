#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class GaussianXOR {
  vector<vector<int>> matrix;
  int nVars;
  int nEqs;
  vector<int> pivotCols;
  vector<int> freeCols;

 public:
  GaussianXOR(int vars, int equations) : nVars(vars), nEqs(equations) {
    matrix.resize(nEqs, vector<int>(vars + 1, 0));
  }

  void addEquation(int eqIdx, const vector<unsigned>& vars, bool result) {
    for (unsigned v : vars) {
      matrix[eqIdx][v] = 1;
    }
    matrix[eqIdx][nVars] = result ? 1 : 0;
  }

  int solve() {
    int row = 0;
    vector<bool> isPivot(nVars, false);

    for (int col = 0; col < nVars && row < nEqs; col++) {
      int pivot = -1;
      for (int r = row; r < nEqs; r++) {
        if (matrix[r][col] == 1) {
          pivot = r;
          break;
        }
      }

      if (pivot == -1) continue;

      if (pivot != row) {
        swap(matrix[row], matrix[pivot]);
      }

      for (int r = 0; r < nEqs; r++) {
        if (r != row && matrix[r][col] == 1) {
          for (int c = 0; c <= nVars; c++) {
            matrix[r][c] ^= matrix[row][c];
          }
        }
      }

      isPivot[col] = true;
      pivotCols.push_back(col);
      row++;
    }

    for (int i = 0; i < nVars; i++) {
      if (!isPivot[i]) {
        freeCols.push_back(i);
      }
    }

    int numFree = freeCols.size();
    int minPresses = nVars + 1;

    for (int mask = 0; mask < (1 << numFree); mask++) {
      vector<int> solution(nVars, 0);

      for (int i = 0; i < numFree; i++) {
        solution[freeCols[i]] = (mask >> i) & 1;
      }

      for (int r = 0; r < nEqs; r++) {
        int pivotCol = -1;
        for (int c = 0; c < nVars; c++) {
          if (matrix[r][c] == 1) {
            pivotCol = c;
            break;
          }
        }

        if (pivotCol != -1) {
          int val = matrix[r][nVars];
          for (int c = pivotCol + 1; c < nVars; c++) {
            if (matrix[r][c] == 1) {
              val ^= solution[c];
            }
          }
          solution[pivotCol] = val;
        }
      }

      int count = 0;
      for (int v : solution) {
        count += v;
      }
      minPresses = min(minPresses, count);
    }

    return minPresses;
  }
};

vector<int> parsePattern(const string& pattern) {
  vector<int> result;
  bool inBrackets = false;
  for (char c : pattern) {
    if (c == '[') {
      inBrackets = true;
    } else if (c == ']') {
      break;
    } else if (inBrackets) {
      result.push_back(c == '#' ? 1 : 0);
    }
  }
  return result;
}

vector<vector<unsigned>> parseButtons(const string& line) {
  vector<vector<unsigned>> buttons;
  size_t pos = 0;

  while ((pos = line.find('(', pos)) != string::npos) {
    size_t endPos = line.find(')', pos);
    if (endPos == string::npos) break;

    string content = line.substr(pos + 1, endPos - pos - 1);
    vector<unsigned> lights;

    stringstream ss(content);
    string num;
    while (getline(ss, num, ',')) {
      lights.push_back(stoi(num));
    }

    if (!lights.empty()) {
      buttons.push_back(lights);
    }

    pos = endPos + 1;
  }

  return buttons;
}

int solveMachine(const string& line) {
  auto targetPattern = parsePattern(line);
  auto buttons = parseButtons(line);

  if (targetPattern.empty() || buttons.empty()) {
    return 0;
  }

  int numLights = targetPattern.size();
  int numButtons = buttons.size();

  GaussianXOR solver(numButtons, numLights);

  for (int light = 0; light < numLights; light++) {
    vector<unsigned> buttonVars;
    for (int btn = 0; btn < numButtons; btn++) {
      for (unsigned toggledLight : buttons[btn]) {
        if (toggledLight == light) {
          buttonVars.push_back(btn);
          break;
        }
      }
    }

    bool targetValue = (targetPattern[light] == 1);
    solver.addEquation(light, buttonVars, targetValue);
  }

  return solver.solve();
}

vector<int> parseJoltage(const string& line) {
  vector<int> result;
  size_t pos = line.find('{');
  if (pos == string::npos) return result;

  size_t endPos = line.find('}', pos);
  if (endPos == string::npos) return result;

  string content = line.substr(pos + 1, endPos - pos - 1);
  stringstream ss(content);
  string num;
  while (getline(ss, num, ',')) {
    result.push_back(stoi(num));
  }

  return result;
}

class LinearSolver {
  vector<vector<int>> matrix;
  int nVars;
  int nEqs;
  vector<int> pivotCols;
  vector<int> freeCols;

 public:
  LinearSolver(int vars, int equations) : nVars(vars), nEqs(equations) {
    matrix.resize(nEqs, vector<int>(vars + 1, 0));
  }

  void addEquation(int eqIdx, const vector<unsigned>& vars, int result) {
    for (unsigned v : vars) {
      matrix[eqIdx][v] = 1;
    }
    matrix[eqIdx][nVars] = result;
  }

  int solve() {
    int row = 0;
    vector<bool> isPivot(nVars, false);

    for (int col = 0; col < nVars && row < nEqs; col++) {
      int pivot = -1;
      for (int r = row; r < nEqs; r++) {
        if (matrix[r][col] != 0) {
          pivot = r;
          break;
        }
      }

      if (pivot == -1) continue;

      if (pivot != row) {
        swap(matrix[row], matrix[pivot]);
      }

      for (int r = 0; r < nEqs; r++) {
        if (r != row && matrix[r][col] != 0) {
          int factor = matrix[r][col];
          int pivotVal = matrix[row][col];
          for (int c = 0; c <= nVars; c++) {
            matrix[r][c] = matrix[r][c] * pivotVal - matrix[row][c] * factor;
          }
        }
      }

      isPivot[col] = true;
      pivotCols.push_back(col);
      row++;
    }

    for (int i = 0; i < nVars; i++) {
      if (!isPivot[i]) {
        freeCols.push_back(i);
      }
    }

    int numFree = freeCols.size();
    int maxFreeVal = 200;
    int minPresses = INT_MAX;

    auto tryFreeValues = [&](auto& self, int idx, vector<int>& freeVals) -> void {
      if (idx == numFree) {
        vector<int> solution(nVars, 0);

        for (int i = 0; i < numFree; i++) {
          solution[freeCols[i]] = freeVals[i];
        }

        for (int r = nEqs - 1; r >= 0; r--) {
          int pivotCol = -1;
          int pivotVal = 0;
          for (int c = 0; c < nVars; c++) {
            if (matrix[r][c] != 0) {
              pivotCol = c;
              pivotVal = matrix[r][c];
              break;
            }
          }

          if (pivotCol != -1 && !isPivot[pivotCol]) continue;
          if (pivotCol == -1) continue;

          int val = matrix[r][nVars];
          for (int c = pivotCol + 1; c < nVars; c++) {
            if (matrix[r][c] != 0) {
              val -= matrix[r][c] * solution[c];
            }
          }

          if (val % pivotVal != 0) return;
          solution[pivotCol] = val / pivotVal;
          if (solution[pivotCol] < 0) return;
        }

        int count = 0;
        for (int v : solution) {
          if (v < 0) return;
          count += v;
        }
        minPresses = min(minPresses, count);
        return;
      }

      for (int val = 0; val <= maxFreeVal; val++) {
        freeVals[idx] = val;
        self(self, idx + 1, freeVals);
        if (minPresses < INT_MAX && val > minPresses) break;
      }
    };

    vector<int> freeVals(numFree, 0);
    tryFreeValues(tryFreeValues, 0, freeVals);

    return minPresses;
  }
};

int solveMachinePart2(const string& line) {
  auto targetJoltage = parseJoltage(line);
  auto buttons = parseButtons(line);

  if (targetJoltage.empty() || buttons.empty()) {
    return 0;
  }

  int numCounters = targetJoltage.size();
  int numButtons = buttons.size();

  LinearSolver solver(numButtons, numCounters);

  for (int counter = 0; counter < numCounters; counter++) {
    vector<unsigned> buttonVars;
    for (int btn = 0; btn < numButtons; btn++) {
      for (unsigned affectedCounter : buttons[btn]) {
        if (affectedCounter == counter) {
          buttonVars.push_back(btn);
          break;
        }
      }
    }

    solver.addEquation(counter, buttonVars, targetJoltage[counter]);
  }

  return solver.solve();
}

int solvePart1(const string& path) {
  int total = 0;
  ifstream file(path);
  string line;

  if (file.is_open()) {
    while (getline(file, line)) {
      if (line.empty()) continue;
      int presses = solveMachine(line);
      cout << "Line: " << presses << " presses\n";
      total += presses;
    }
    file.close();
  }

  return total;
}

int solvePart2(const string& path) {
  int total = 0;
  ifstream file(path);
  string line;

  if (file.is_open()) {
    while (getline(file, line)) {
      if (line.empty()) continue;
      int presses = solveMachinePart2(line);
      cout << "Line: " << presses << " presses\n";
      total += presses;
    }
    file.close();
  }

  return total;
}

int main() {
  const string path = "input.txt";
  const auto total1 = solvePart1(path);
  cout << "Total sum part 1: " << total1 << endl;

  const auto total2 = solvePart2(path);
  cout << "Total sum part 2: " << total2 << endl;
  return 0;
}