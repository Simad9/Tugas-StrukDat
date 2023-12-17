#include <iostream>
#include <unordered_map>
using namespace std;

// STRUCT
struct Data {
  string namaProduk;
  int harga;
  int kodeProduk;

  Data* next;
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

void searchHash(int cariKodeProduk) {
  // Code
}

void searchPTB(string cariNamaProduk) {
  // Code
}

// FUNGSI TAMPILAN (FRONT-END)
// Kurang tau fungsinya
unordered_map<int, string> hashTable;

// INPUT DATA
void inputData() {
  // Testing doang ini
  cout << "\n~~ INPUT PRODUK ~~\n" << endl;
  cout << "Masukan Produk : " << endl;
  cout << "Nama : ";
  getline(cin >> ws, produk->namaProduk);
  cout << "Harga : ";
  cin >> produk->harga;

  // Untung hasing dari namanya
  int hashValue = simpleHash(produk->namaProduk);
  hashTable[hashValue] = produk->namaProduk;
}

// OUTPUT DATA
void outputData() {
  // Nampilin doang, buat testing
  cout << "\n~~ OUTPUT PRODUK ~~\n" << endl;
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

// SEARCH DATA
void searchData() {
  cout << "\n~~ Search ~~\n" << endl;
  cout << "Ingin mencari berdasarkan apa? : " << endl;
  cout << "1. Kode Produk" << endl;
  cout << "2. Nama Produk" << endl;
  cout << "Pilih : ";
  int pilihSearch;
  cin >> pilihSearch;
  if (pilihSearch == 1) {
    // Searching Hash
    cout << "Silahkan isi data yang akan dicari" << endl;
    cout << "Kode Produk = ";
    int cariKodeProduk;
    cin >> cariKodeProduk;
    searchHash(cariKodeProduk);
  } else if (pilihSearch == 2) {
    // Searching PTB
    cout << "Silahkan isi data yang akan dicari" << endl;
    cout << "Nama Produk = ";
    string cariNamaProduk;
    getline(cin >> ws, cariNamaProduk);
    searchPTB(cariNamaProduk);
  } else {
    cout << "Tidak Ada dipilihan" << endl << endl;
    return;
  }
}

// SORT DATA
void sortData() {
  // Note : Sorting PTB descending dari nama
  cout << "\n~~ SORTING ~~\n" << endl;
  cout << "Sorting berdasarkan nama secara Descending" << endl;
  
}

// DELETE DATA
void deleteData() {
  cout << "\n~~ DELETE ~~\n" << endl;
  // Logika codenya
  // 1. Pilih data mana yang akan dihapus
  // 2. Pindahkan data itu ke history
  // 3. Hapus datanya
}

void outputHistory() {
  cout << "\n~~ OUTPUT HISTORY ~~\n" << endl;
  // Logika codenya
  // 1. Cek historynya
  // 2. Jika kosong tampilkan kosong
  // 3. Jika ada maka tampilkan data yang ada di History
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