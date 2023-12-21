#include <iostream>
#include <unordered_map>
using namespace std;

// STRUCT
struct Data {
  string namaProduk;
  int harga;
  int kodeProduk;
};

// DEKLARASI
// Data ada 10
Data produk[10];
// FUNGSI LOGIKA (BACK-END)
// Fungsi hash sederhana untuk menghasilkan nilai hash dari string (sting nama
// produk)
int simpleHash(const string& input) {
  int hash = 0;
  for (char c : input) {
    hash = hash * 31 + c;
  }
  return hash;
}

// FUNGSI TAMPILAN (FRONT-END)
// Kurang tau fungsinya
unordered_map<int, string> hashTable;
// output input
void inputData() {
  // Testing doang ini
  cout << "Masukan Produk : " << endl;
  cout << "Nama : ";
  getline(cin >> ws, produk->namaProduk);
  cout << "Harga : ";
  cin >> produk->harga;
  // Untung hasing dari namanya
  int hashValue = simpleHash(produk->namaProduk);
  hashTable[hashValue] = produk->namaProduk;
}

void outputData() {
  // Nampilin doang, buat testing
  cout << "Tampilan Produk" << endl;
  cout << "Nama : " << produk->namaProduk << endl;
  cout << "Harga : " << produk->harga << endl;
  //  --- hasingnya ---
  // Output data
  cout << "\nData yang dimasukkan:" << endl;
  for (const auto& entry : hashTable) {
    cout << "Hash: " << entry.first << ", Nilai: " << entry.second << endl;
  }
  // Biar gak ilang, soalnya cuman coba aja
  system("pause");
}

void searchData() {
  // Code...
}

void sortData() {
  // Code...
}

void deleteData() {
  // Code...
}

void outputHistory() {
  // Code...
}

// MAIN PROGRAM
int main() {
  // Deklarasi Variable
  int pilihMenu;
  do {
    // Tampilan Awal
    system("cls");
    cout << "+==================================+\n";
    cout << "|            1232200010            |\n";
    cout << "|            1232200019            |\n";
    cout << "|            1232200021            |\n";
    cout << "|            1232200031            |\n";
    cout << "+==================================+\n";
    cout << "|          Toko Serba Ada          |\n";
    cout << "+==================================+\n";
    cout << "| 1. Input Data                    |\n";
    cout << "| 2. Output Data                   |\n";
    cout << "| 3. Search Data                   |\n";
    cout << "| 4. Sort Data                     |\n";
    cout << "| 5. Delete Data                   |\n";
    cout << "| 6. Output History                |\n";
    cout << "+==================================+\n";
    cout << "  Pilih menu : ";
    // Input Menu
    cin >> pilihMenu;
    // Error Handling Input Menu
    if (cin.fail() || pilihMenu < 1 || pilihMenu > 6) {
      cout << "  Inputan tidak terdeteksi!\n  ";
      cin.clear();
      cin.ignore();
      system("pause");
      continue;
    }
    if (pilihMenu == 1) {  // 1. Input Data
      // perintah::input/penyisipan struktur hash
      inputData();
    } else if (pilihMenu == 2) {  // 2. Ouput Data
                                  // perintah::Tampilkan dengan struktur hash
      outputData();
    } else if (pilihMenu == 3) {  // 3. Search Data
      // perintah::struktur hash dengan kunci kode
      searchData();
    } else if (pilihMenu == 4) {  // 4. Sort Data
      // perintah::PTB post-order secara Descending(dsc)
      sortData();
    } else if (pilihMenu == 5) {  // 5. Delete Data
      // perintah::struktur hash dengan kunci kode
      deleteData();
    } else if (pilihMenu == 6) {  // 6. Output History
      // perintah::PTB in-order, post-order, pre-order
      outputHistory();
    }
  } while (true);
  return 0;
}