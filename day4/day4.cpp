#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void processLine(const string &topLine, const string &midLine,
                 const string &lowLine, int &forkable) {
  if (midLine.empty()) return;
  int lineSize = midLine.size();
  for (int i = 0; i < lineSize; i++) {
    if (midLine[i] != '@') continue;
    int adjacents = 0;
    if (topLine.size() > 0 && i < topLine.size()) {
      adjacents += i > 0 && topLine[i - 1] == '@' ? 1 : 0;
      adjacents += topLine[i] == '@' ? 1 : 0;
      adjacents += i < lineSize - 1 && topLine[i + 1] == '@' ? 1 : 0;
    }
    adjacents += i > 0 && midLine[i - 1] == '@' ? 1 : 0;
    adjacents += i < lineSize - 1 && midLine[i + 1] == '@' ? 1 : 0;
    if (lowLine.size() > 0 && i < lowLine.size()) {
      adjacents += i > 0 && lowLine[i - 1] == '@' ? 1 : 0;
      adjacents += lowLine[i] == '@' ? 1 : 0;
      adjacents += i < lineSize - 1 && lowLine[i + 1] == '@' ? 1 : 0;
    }
    forkable += adjacents < 4 ? 1 : 0;
  }
}

int forkableRolls(const string &path) {
  ifstream file(path);
  string line;
  int forkable = 0;
  if (file.is_open()) {
    string topLine = "";
    string midLine = "";
    string lowLine = "";

    while (getline(file, line)) {
      topLine = midLine;
      midLine = lowLine;
      lowLine = line;
      processLine(topLine, midLine, lowLine, forkable);
    }

    topLine = midLine;
    midLine = lowLine;
    lowLine = "";
    processLine(topLine, midLine, lowLine, forkable);

    file.close();
  }
  return forkable;
}

int removableRolls(const string &path) {
  ifstream file(path);
  vector<string> grid;
  string line;

  if (file.is_open()) {
    while (getline(file, line)) {
      grid.push_back(line);
    }
    file.close();
  }

  int totalRemoved = 0;

  while (true) {
    vector<pair<int, int>> toRemove;

    for (int row = 0; row < grid.size(); row++) {
      for (int col = 0; col < grid[row].size(); col++) {
        if (grid[row][col] != '@') continue;

        int adjacents = 0;
        for (int dr = -1; dr <= 1; dr++) {
          for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int newRow = row + dr;
            int newCol = col + dc;
            if (newRow >= 0 && newRow < grid.size() && newCol >= 0 &&
                newCol < grid[newRow].size() && grid[newRow][newCol] == '@') {
              adjacents++;
            }
          }
        }

        if (adjacents < 4) {
          toRemove.push_back({row, col});
        }
      }
    }

    if (toRemove.empty()) break;

    for (auto [row, col] : toRemove) {
      grid[row][col] = 'X';
    }

    totalRemoved += toRemove.size();
  }

  return totalRemoved;
}

int main() {
  string path = "input.txt";
  const auto total = to_string(forkableRolls(path));
  cout << "Total accesible rolls: " << string(total) << endl;
  const auto removables = to_string(removableRolls(path));
  cout << "Total removable rolls: " << removables << endl;

  return 0;
}