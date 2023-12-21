#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;  // Add this line

// ===== STRUCT =====
struct Product {
  string name;
  double price;
  int code;
};

// Binary Search Tree (Binary Search Tree) to store products based on product
// names
struct TreeNode {
  Product data;
  TreeNode* left;
  TreeNode* right;
};

// Hash table to store product information
unordered_map<int, Product> productHash;
TreeNode* root = nullptr;  // Add this line

// ======= FUNGSI LOGIKA (BACK-END) ========

// Function to insert product into Binary Search Tree
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

// Function to perform post-order traversal for sorting products by name in
// descending order
void postOrderTraversal(TreeNode* root) {
  if (root != nullptr) {
    postOrderTraversal(root->right);
    cout << "Product Name: " << root->data.name
         << ", Price: " << root->data.price << ", Code: " << root->data.code
         << endl;
    postOrderTraversal(root->left);
  }
}

// Function to search products based on name range in Binary Search Tree
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

vector<Product> deletedProducts;  // Add this line before main

// ======== FUNGSI TAMPILAN (FRONT-END) ========
void input() {
  Product newProduct;

  cout << "Masukan Data Produk : \n";
  cout << "Nama Produk  : ";
  cin >> newProduct.name;
  cout << "Harga Produk : ";
  cin >> newProduct.price;
  cout << "Kode Produk  : ";
  cin >> newProduct.code;

  // Insert into hash table
  productHash[newProduct.code] = newProduct;

  // Insert into binary search tree
  insertProduct(root, newProduct);
}
void output() {
  // Display products using hash table
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
  // View deleted products history
  if (!deletedProducts.empty()) {
    cout << "History Product Terhapus:\n";
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
    cout << "No deleted products history.\n";
  }
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
    cout << "+==================================+=========================+\n";
    cout
        << "| 1. Input Product                                           |\n";  // INPUT
    cout
        << "| 2. Display Products (using hash)                           |\n";  // OUTPUT
    cout
        << "| 3. Delete Product (using hash)                             |\n";  // DELETE
    cout
        << "| 4. Search Product by Code (using hash)                     |\n";  // SEARCH BY CODE
    cout
        << "| 5. Search Product by Name Range (using binary search tree) |\n";  // SEARCH BY NAME
    cout
        << "| 6. Sort Products by Name (Descending) (using binary search)|\n";  // SORT
    cout
        << "| 7. View Deleted Products History                           |\n";  // OUTPUT HISTORY
    cout
        << "| 8. Exit                                                    |\n";  // EXIT
    cout << "+============================================================+\n";
    cout << "Pilih menu : ";
    // Input Menu
    cin >> pilihMenu;
    cout << endl;
    switch (pilihMenu) {
      case 1: {
        input();
        break;
      }

      case 2: {

        output();
        break;
      }

      case 3: {
        // Delete product using hash table
        int deleteCode;
        cout << "Enter product code to delete: ";
        cin >> deleteCode;

        auto it = productHash.find(deleteCode);
        if (it != productHash.end()) {
          // Insert into binary search tree for history
          deletedProducts.push_back(it->second);

          // Erase from hash table
          productHash.erase(it);
          cout << "Product with code " << deleteCode << " deleted.\n";
        } else {
          cout << "Product with code " << deleteCode << " not found.\n";
        }

        break;
      }

      case 4: {
        // Search product by code using hash table
        int searchCode;
        cout << "Enter product code to search: ";
        cin >> searchCode;

        auto it = productHash.find(searchCode);
        if (it != productHash.end()) {
          const Product& product = it->second;
          cout << "Product found: " << product.name
               << ", Price: " << product.price << ", Code: " << product.code
               << endl;
        } else {
          cout << "Product with code " << searchCode << " not found.\n";
        }

        break;
      }

      case 5: {
        // Search product by name range using binary search tree
        string startName, endName;
        cout << "Enter start of name range: ";
        cin >> startName;
        cout << "Enter end of name range: ";
        cin >> endName;

        vector<Product> result;
        searchByNameRange(root, startName, endName, result);

        if (!result.empty()) {
          cout << "Products in the specified name range:\n";
          for (const auto& product : result) {
            cout << "Product Name: " << product.name
                 << ", Price: " << product.price << ", Code: " << product.code
                 << endl;
          }
        } else {
          cout << "No products found in the specified name range.\n";
        }

        break;
      }

      case 6: {
        // Sort products by name in descending order using binary search tree
        cout << "Products sorted by name (Descending):\n";
        postOrderTraversal(root);
        break;
      }

      case 7: {
        outputHistory();
        break;
      }

      case 8:
        cout << "Exiting program.\n";
        exit(1);
        break;

      default:
        cout << "Invalid option. Please try again.\n";
        break;
    }
    cout << "\nKembali ke menu? (y/n) = ";
    cin >> menu;
  } while (menu == 'y');
  return 0;
}
