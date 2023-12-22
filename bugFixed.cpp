#include <algorithm>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// Struktur Produk
struct Product
{
  string name;
  double price;
  int code;
};

// Node untuk Pohon Pencarian Biner (Binary Search Tree)
struct TreeNode
{
  Product data;
  TreeNode *left;
  TreeNode *right;
};

unordered_map<int, Product> productHash;
TreeNode *root = nullptr;

// Fungsi untuk memasukkan produk ke dalam Pohon Pencarian Biner
void insertProduct(TreeNode *&root, const Product &product)
{
  if (root == nullptr)
  {
    root = new TreeNode{product, nullptr, nullptr};
  }
  else
  {
    if (product.name < root->data.name)
    {
      insertProduct(root->left, product);
    }
    else
    {
      insertProduct(root->right, product);
    }
  }
}

// Fungsi untuk menghapus Pohon Pencarian Biner
void deleteTree(TreeNode *root)
{
  if (root != nullptr)
  {
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
  }
}

// Fungsi untuk melakukan traversal pasca pesanan untuk mengurutkan produk
// berdasarkan nama dalam urutan menurun
void postOrderTraversal(TreeNode *root)
{
  if (root != nullptr)
  {
    postOrderTraversal(root->right);
    cout << "+----------+----------+-----------+\n";
    cout << left << "| " << setw(8) << root->data.code << " | " << setw(8)
         << root->data.name << " | Rp." << setw(6) << root->data.price
         << " |\n";
    postOrderTraversal(root->left);
  }
}

// Fungsi untuk mencari produk berdasarkan rentang nama di Pohon Pencarian Biner
void searchByNameRange(TreeNode *root, const string &startName,
                       const string &endName, vector<Product> &result)
{
  if (root != nullptr)
  {
    if (root->data.name >= startName && root->data.name <= endName)
    {
      result.push_back(root->data);
    }

    if (root->data.name >= startName)
    {
      searchByNameRange(root->left, startName, endName, result);
    }

    if (root->data.name <= endName)
    {
      searchByNameRange(root->right, startName, endName, result);
    }
  }
}

vector<Product> deletedProducts;

// Fungsi untuk membersihkan memori dan keluar dari program
void cleanupAndExit()
{
  deleteTree(root);
  exit(0);
}

// Fungsi untuk menampilkan produk
void displayProduct(const Product &product)
{
  cout << "+----------+----------+-----------+\n";
  cout << left << "| " << setw(8) << product.code << " | " << setw(8)
       << product.name << " | Rp." << setw(6) << product.price << " |\n";
}

// ======= FUNGSI TAMPILAN (FRONT-END) ========

void inputProduct()
{
  Product newProduct;
  cout << "Masukkan Data Produk : \n";
  cout << "Nama Produk  : ";
  cin >> newProduct.name;
  cout << "Harga Produk : ";
  cin >> newProduct.price;
  cout << "Kode Produk  : ";
  cin >> newProduct.code;

  if (productHash.count(newProduct.code))
  {
    cout << "Kode sudah digunakan!\n";
  }
  else
  {
    productHash[newProduct.code] = newProduct;
    insertProduct(root, newProduct);
  }
}

void outputProduct()
{
  cout << "List Produk : \n";
  cout << "+==========+==========+===========+\n";
  cout << "|   Code   |   Nama   |   Harga   |\n";
  for (const auto &entry : productHash)
  {
    displayProduct(entry.second);
  }
  cout << "+==========+==========+===========+\n";
  cout << endl;
}

void outputHistory()
{
  if (!deletedProducts.empty())
  {
    cout << "Lihat Riwayat Produk yang Dihapus :\n";
    cout << "+==========+==========+===========+\n";
    cout << "|   Code   |   Nama   |   Harga   |\n";
    for (const auto &product : deletedProducts)
    {
      displayProduct(product);
    }
    cout << "+==========+==========+===========+\n";
    cout << endl;
  }
  else
  {
    cout << "Tidak ada riwayat produk yang dihapus.\n";
  }
}

void deleteProduct()
{
  int deleteCode;
  cout << "Masukkan kode produk yang akan dihapus : ";
  cin >> deleteCode;

  auto it = productHash.find(deleteCode);
  if (it != productHash.end())
  {
    deletedProducts.push_back(it->second);
    productHash.erase(it);
    cout << "Produk dengan kode " << deleteCode << " berhasil dihapus.\n";
  }
  else
  {
    cout << "Produk dengan kode " << deleteCode << " tidak ditemukan.\n";
  }
}

void searchByCode()
{
  int searchCode;
  cout << "Masukkan kode produk untuk mencari : ";
  cin >> searchCode;
  cout << endl;

  auto it = productHash.find(searchCode);
  if (it != productHash.end())
  {
    const Product &product = it->second;
    // Tampilan versi 1
    cout << "Produk Ditemukan :\n";
    cout << "+==========+==========+===========+\n";
    cout << "|   Code   |   Nama   |   Harga   |\n";
    cout << "+----------+----------+-----------+\n";
    cout << left << "| " << setw(8) << product.code << " | " << setw(8) << product.name << " | Rp." << setw(6) << product.price << " |\n";
    cout << "+==========+==========+===========+\n";
    cout << endl;
    // Tampilan versi 2
    // cout << "Produk Ditemukan : \n";
    // cout << "Kode Produk  = " << product.code << endl;
    // cout << "Nama Produk  = " << product.name << endl;
    // cout << "Harga Produk = " << product.price << endl;
  }
  else
  {
    cout << "\nProduk dengan kode " << searchCode << " tidak ditemukan.\n";
  }
}

// Fungsi baru dengan nama yang berbeda untuk mengatasi bug pada menu 5
void searchByNameRangeMenu()
{
  string startName, endName;
  cout << "Masukkan awal rentang nama: ";
  cin >> startName;
  cout << "Masukkan akhir rentang nama: ";
  cin >> endName;
  cout << endl;

  vector<Product> result;
  searchByNameRange(root, startName, endName, result);

  if (!result.empty())
  {
    cout << "Produk dalam rentang nama yang ditentukan :\n";
    cout << "+==========+==========+===========+\n";
    cout << "|   Code   |   Nama   |   Harga   |\n";
    for (const auto &product : result)
    {
      displayProduct(product);
    }
    cout << "+==========+==========+===========+\n";
    cout << endl;
  }
  else
  {
    cout << "Tidak ada produk yang ditemukan dalam rentang nama yang "
            "ditentukan.\n";
  }
}

void sortingDescending()
{
  cout << "Produk Urut berdasarkan Nama (Descending):\n";
  cout << "+==========+==========+===========+\n";
  cout << "|   Code   |   Nama   |   Harga   |\n";
  postOrderTraversal(root);
  cout << "+==========+==========+===========+\n";
  cout << endl;
}

int main()
{
  int pilihMenu;
  char menu;

  do
  {
    system("cls");
    cout << "+==================================+\n";
    cout << "|            1232200010            |\n";
    cout << "|            1232200019            |\n";
    cout << "|            1232200021            |\n";
    cout << "|            1232200031            |\n";
    cout << "+==================================+\n";
    cout << "|          Toko Serba Ada          |\n";
    cout << "+=================================================+\n";
    cout << "| 1. Produk Masukan                               |\n";
    cout << "| 2. Tampilkan Produk                             |\n";
    cout << "| 3. Hapus Produk                                 |\n";
    cout << "| 4. Cari Produk berdasarkan Kode                 |\n";
    cout << "| 5. Cari Produk berdasarkan Rentang Nama         |\n";
    cout << "| 6. Urutkan Produk berdasarkan Nama (Descending) |\n";
    cout << "| 7. Lihat Riwayat Produk yang Dihapus            |\n";
    cout << "| 8. Keluar                                       |\n";
    cout << "+=================================================+\n";
    cout << "Pilih menu (1-8): ";
    cin >> pilihMenu;
    cout << endl;

    switch (pilihMenu)
    {
    case 1:
    {
      inputProduct();
      break;
    }
    case 2:
    {
      outputProduct();
      break;
    }
    case 3:
    {
      deleteProduct();
      break;
    }
    case 4:
    {
      searchByCode();
      break;
    }
    case 5:
    {
      searchByNameRangeMenu(); // Menggunakan fungsi yang berbeda
      break;
    }
    case 6:
    {
      sortingDescending();
      break;
    }
    case 7:
    {
      outputHistory();
      break;
    }
    case 8:
      cout << "Keluar dari Program.\n";
      cleanupAndExit();
      break;
    default:
      cout << "Opsi tidak valid. Silahkan coba lagi.\n";
      break;
    }

    cout << "\nKembali ke menu? (y/n) = ";
    cin >> menu;
  } while (menu == 'y');

  cleanupAndExit();
  return 0;
}
