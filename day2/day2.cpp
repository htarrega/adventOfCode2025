#include <fstream>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

string readLine(const string &path) {
  string line;
  ifstream file(path);
  if (!file.is_open()) {
    cerr << "Error: Could not open file: " << path << endl;
    return {};
  }
  getline(file, line);
  file.close();
  return line;
}

long long isInvalidID(const long long id) {
  const string num = to_string(id);
  if (num.size() % 2 != 0) {
    return 0;
  }
  const int range = num.size() / 2;
  for (int i = 0; i < range; i++) {
    if (num[i] != num[range + i]) {
      return 0;
    }
  }
  return id;
}

long long isInvalidID2(const long long id) {
  static const regex pattern(R"(^(\d+)\1+$)");
  if (regex_match(to_string(id), pattern)) {
    return id;
  }
  return 0;
}

long long getAllInvalidIDs(const string &line, int part) {
  long long total = 0;
  static const regex pattern(R"((\d+)-(\d+))");
  auto begin = sregex_iterator(line.begin(), line.end(), pattern);
  auto end = sregex_iterator();

  for (sregex_iterator i = begin; i != end; ++i) {
    smatch match = *i;
    long long num1 = stoll(match[1].str());
    long long num2 = stoll(match[2].str());
    long long iter = num1;
    while (iter <= num2) {
      if (part == 1) {
        total += isInvalidID(iter);
      } else {
        total += isInvalidID2(iter);
      }
      iter++;
    }
  }
  return total;
}

int main() {
  string path = "input.txt";
  const auto line = readLine(path);
  if (line.empty()) {
    cout << "No data to process." << endl;
    return 1;
  }
  auto sumIDs = getAllInvalidIDs(line, 1);
  cout << "Sum of invalid IDs (Part 1): " << sumIDs << endl;
  sumIDs = getAllInvalidIDs(line, 2);
  cout << "Sum of invalid IDs (Part 2): " << sumIDs << endl;
  return 0;
}