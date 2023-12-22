#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;  // Tambahkan baris ini

// ===== STRUCT =====
struct Product {
  string name;
  double price;
  int code;
};

// Pohon Pencarian Biner (Binary Search Tree) untuk menyimpan produk berdasarkan
// nama produk
struct TreeNode {
  Product data;
  TreeNode* left;
  TreeNode* right;
};

// Tabel hash untuk menyimpan informasi produk
unordered_map<int, Product> productHash;
TreeNode* root = nullptr;  // Tambahkan baris ini

// ======= FUNGSI LOGIKA (BACK-END) ========

// Fungsi untuk memasukkan produk ke dalam Pohon Pencarian Biner
void insertProduct(TreeNode*& root, const Product& product) {
  if (root == nullptr) {
    root = new TreeNode{product, nullptr, nullptr};
  } else {
    if (product.name < root->data.name) {
      insertProduct(root->left, product);
    } else {
      insertProduct(root->right, product);
    }
  }
}

// Fungsi untuk melakukan traversal pasca pesanan untuk mengurutkan produk
// berdasarkan nama dalam urutan menurun
void postOrderTraversal(TreeNode* root) {
  if (root != nullptr) {
    postOrderTraversal(root->right);
    cout << "Product Name: " << root->data.name
         << ", Price: " << root->data.price << ", Code: " << root->data.code
         << endl;
    postOrderTraversal(root->left);
  }
}

// Fungsi untuk mencari produk berdasarkan rentang nama di Pohon Pencarian Biner
void searchByNameRange(TreeNode* root, const string& startName,
                       const string& endName, vector<Product>& result) {
  if (root != nullptr) {
    if (root->data.name >= startName && root->data.name <= endName) {
      result.push_back(root->data);
    }

    if (root->data.name >= startName) {
      searchByNameRange(root->left, startName, endName, result);
    }

    if (root->data.name <= endName) {
      searchByNameRange(root->right, startName, endName, result);
    }
  }
}

vector<Product> deletedProducts;  // Tambahkan baris ini sebelum main

// ======== FUNGSI TAMPILAN (FRONT-END) ========
void inputProduct() {
  Product newProduct;

  cout << "Masukan Data Produk : \n";
  cout << "Nama Produk  : ";
  cin >> newProduct.name;
  cout << "Harga Produk : ";
  cin >> newProduct.price;
  cout << "Kode Produk  : ";
  cin >> newProduct.code;

  // Masukkan ke dalam tabel hash
  productHash[newProduct.code] = newProduct;

  // Masukkan ke dalam pohon pencarian biner
  insertProduct(root, newProduct);
}
void outputProduct() {
  // Tampilkan produk menggunakan tabel hash
  int index = 1;
  cout << "List Produk : \n";
  for (const auto& entry : productHash) {
    const Product& product = entry.second;

    // Tampilan Output versi 1
    // cout << "+=====================+\n";
    // cout << "| Code | Nama | Harga |\n";
    // cout << "+------+------+-------+\n";
    // cout << "| " << product.code << " | " << product.name << " |  "
    //      << product.price << " |\n";
    // cout << "+=====================+\n";
    // cout << endl;

    // Tampilan Output versi 2
    cout << "Nama  : " << product.name << endl;
    cout << "Harga : " << product.price << endl;
    cout << "Code  : " << product.code << endl << endl;
  }
}
void outputHistory() {
  // Lihat riwayat produk yang dihapus
  if (!deletedProducts.empty()) {
    cout << "Lihat Riwayat Produk yang Dihapus :\n";
    for (const auto& product : deletedProducts) {
      // Tampilan Output versi 1
      // cout << "+=====================+\n";
      // cout << "| Code | Nama | Harga |\n";
      // cout << "+------+------+-------+\n";
      // cout << "| " << product.code << " | " << product.name << " |  "
      //      << product.price << " |\n";
      // cout << "+=====================+\n";
      // cout << endl;

      // Tampilan Output versi 2
      cout << "Nama  : " << product.name << endl;
      cout << "Harga : " << product.price << endl;
      cout << "Code  : " << product.code << endl << endl;
    }
  } else {
    cout << "Tidak ada riwayat produk yang dihapus.\n";
  }
}
void deleteProduct() {
  // Hapus produk menggunakan tabel hash
  int deleteCode;
  cout << "Masukkan kode produk yang akan dihapus : ";
  cin >> deleteCode;

  auto it = productHash.find(deleteCode);
  if (it != productHash.end()) {
    // Masukkan ke dalam pohon pencarian biner untuk sejarah
    deletedProducts.push_back(it->second);

    // Hapus dari tabel hash
    productHash.erase(it);
    cout << "Produk dengan kode " << deleteCode << " berhasil dihapus.\n";
  } else {
    cout << "Produk dengan kode " << deleteCode << " tidak ditemukan.\n";
  }
}
void searchByCode() {
  // Cari produk berdasarkan kode menggunakan tabel hash
  int searchCode;
  cout << "Masukkan kode produk untuk mencari : ";
  cin >> searchCode;

  auto it = productHash.find(searchCode);
  if (it != productHash.end()) {
    const Product& product = it->second;
    // Tampilan
    cout << "Product found: " << product.name << ", Price: " << product.price
         << ", Code: " << product.code << endl;
  } else {
    cout << "\nProduk dengan kode " << searchCode << " tidak ditemukan.\n";
  }
}
void searchByNameRange() {
  // Cari produk berdasarkan rentang nama menggunakan pohon pencarian
  // biner
  string startName, endName;
  cout << "Enter start of name range: ";
  cin >> startName;
  cout << "Enter end of name range: ";
  cin >> endName;

  cout << endl;

  vector<Product> result;
  searchByNameRange(root, startName, endName, result);

  if (!result.empty()) {
    cout << "Produk dalam rentang nama yang ditentukan :\n";
    for (const auto& product : result) {
      // Tampilan
      cout << "Product Name: " << product.name << ", Price: " << product.price
           << ", Code: " << product.code << endl;
    }
  } else {
    cout << "Tidak ada produk yang ditemukan dalam rentang nama yang "
            "ditentukan.\n";
  }
}
void sortingDescending() {
  // Urutkan produk berdasarkan nama dalam urutan menurun menggunakan
  // pohon pencarian biner
  cout << "Produk Ururt berdasarkan Nama (Descending):\n";
  postOrderTraversal(root);
}

int main() {
  // Deklarasi Variable
  int pilihMenu;
  char menu;

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
    cout << "+=================================================+\n";
    cout << "| 1. Produk Masukan                               |\n";  // INPUT
    cout << "| 2. Tampilkan Produk                             |\n";  // OUTPUT
    cout << "| 3. Hapus Produk                                 |\n";  // DELETE
    cout << "| 4. Cari Produk berdasarkan Kode                 |\n";  // SEARCH
                                                                      // BY CODE
    cout << "| 5. Cari Produk berdasarkan Rentang Nama         |\n";  // SEARCH
                                                                      // BY NAME
    cout << "| 6. Urutkan Produk berdasarkan Nama (Descending) |\n";  // SORT
    cout << "| 7. Lihat Riwayat Produk yang Dihapus            |\n";  // OUTPUT
                                                                      // HISTORY
    cout << "| 8. Keluar                                       |\n";  // EXIT
    cout << "+=================================================+\n";
    cout << "Pilih menu (1-8): ";
    // Input Menu
    cin >> pilihMenu;
    cout << endl;
    switch (pilihMenu) {
      case 1: {
        inputProduct();
        break;
      }
      case 2: {
        outputProduct();
        break;
      }
      case 3: {
        deleteProduct();
        break;
      }
      case 4: {
        searchByCode();
        break;
      }
      case 5: {
        searchByNameRange();
        break;
      }
      case 6: {
        sortingDescending();
        break;
      }
      case 7: {
        outputHistory();
        break;
      }
      case 8:
        cout << "Keluar dari Program.\n";
        exit(1);
        break;
      default:
        cout << "Opsi tidak valid. Silahkan coba lagi.\n";
        break;
    }
    cout << "\nKembali ke menu? (y/n) = ";
    cin >> menu;
  } while (menu == 'y');
  return 0;
}
