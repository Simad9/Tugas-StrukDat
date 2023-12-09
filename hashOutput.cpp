#include <iostream>
#include <unordered_map>
using namespace std;

// Fungsi hash sederhana untuk menghasilkan nilai hash dari string
int simpleHash(const string& input) {
  int hash = 0;
  for (char c : input) {
    hash = hash * 31 + c;
  }
  return hash;
}

int main() {
  unordered_map<int, string> hashTable;
  string input;

  cout << "> ";
  getline(cin, input);

  int hashValue = simpleHash(input);
  hashTable[hashValue] = input;

  // Output data
  cout << "\nData yang dimasukkan:" << endl;
  for (const auto& entry : hashTable) {
    cout << "Hash: " << entry.first << ", Nilai: " << entry.second << endl;
  }
  return 0;
}