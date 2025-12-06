#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> getOperationsVector(const string &path) {
  std::ifstream file(path);
  std::string line, lastLine;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      lastLine = line;
    }
  }
  vector<string> stripped;
  std::istringstream iss(lastLine);
  std::string word;
  while (iss >> word) {
    stripped.push_back(word);
  }
  return stripped;
}

long long int getTotal(const vector<string> &signs, const string &path) {
  long long int sum = 0;
  ifstream file(path);
  string line;
  vector<string> words;
  std::vector<long long int> nums;
  nums.assign(signs.size(), 1);
  while (std::getline(file, line)) {
    vector<string> words;
    istringstream iss(line);
    string word;
    while (iss >> word) {
      words.push_back(word);
    }
    if (words[0] == "*" || words[0] == "+") {
      break;
    }
    for (int i = 0; i < signs.size(); i++) {
      if (signs[i] == "+") {
        sum += stoll(words[i]);
      } else {
        nums[i] *= stoll(words[i]);
      }
    }
    words.clear();
  }
  for (const auto num : nums) {
    if (num != 1) {
      sum += num;
    }
  }
  return sum;
}

long long int part1(const string &path) {
  const auto signs = getOperationsVector(path);
  return getTotal(signs, path);
}

std::vector<std::string> loadMatrixFromFile(const std::string &filename) {
  std::vector<std::string> matrix;
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return matrix;
  }
  std::string line;
  while (std::getline(file, line)) {
    matrix.push_back(line);
  }
  file.close();
  return matrix;
}

long long int calculateTotal(const std::vector<std::string> &matrix) {
  if (matrix.empty()) return 0;

  int signRow = matrix.size() - 1;
  int maxColumns = 0;
  for (const auto &row : matrix) {
    if (row.length() > maxColumns) {
      maxColumns = row.length();
    }
  }

  long long int total = 0;
  vector<long long int> currentNumbers;
  char currentSign = ' ';

  for (int col = maxColumns - 1; col >= 0; col--) {
    bool emptyColumn = true;
    string digits = "";

    for (int row = 0; row < signRow; row++) {
      if (col < matrix[row].length() && matrix[row][col] != ' ') {
        digits += matrix[row][col];
        emptyColumn = false;
      }
    }

    if (col < matrix[signRow].length() && matrix[signRow][col] != ' ') {
      currentSign = matrix[signRow][col];
      emptyColumn = false;
    }

    if (!digits.empty()) {
      long long int num = stoll(digits);
      currentNumbers.push_back(num);
    }

    if (emptyColumn && !currentNumbers.empty()) {
      long long int result = (currentSign == '*') ? 1 : 0;
      for (long long int n : currentNumbers) {
        if (currentSign == '*') {
          result *= n;
        } else {
          result += n;
        }
      }
      total += result;
      currentNumbers.clear();
      currentSign = ' ';
    }
  }

  if (!currentNumbers.empty()) {
    long long int result = (currentSign == '*') ? 1 : 0;
    for (long long int n : currentNumbers) {
      if (currentSign == '*') {
        result *= n;
      } else {
        result += n;
      }
    }
    total += result;
  }

  return total;
}

long long int part2(const string &path) {
  const auto matrix = loadMatrixFromFile(path);
  return calculateTotal(matrix);
}

int main() {
  const string path = "input.txt";
  const auto total = to_string(part1(path));
  cout << "Total sum part 1: " << string(total) << endl;
  const auto total2 = to_string(part2(path));
  cout << "Total sum part 2: " << string(total2) << endl;
  return 0;
}