#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;  // Add this line

struct Product {
  string name;
  double price;
  int code;
};

// Hash table to store product information
unordered_map<int, Product> productHash;

// Binary Search Tree (Binary Search Tree) to store products based on product
// names
struct TreeNode {
  Product data;
  TreeNode* left;
  TreeNode* right;
};

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

int main() {
  int option;
  TreeNode* root = nullptr;  // Add this line

  do {
    cout << "\n=== Menu ===" << endl;
    cout << "1. Input Product\n";
    cout << "2. Display Products (using hash)\n";
    cout << "3. Delete Product (using hash)\n";
    cout << "4. Search Product by Code (using hash)\n";
    cout << "5. Search Product by Name Range (using binary search tree)\n";
    cout
        << "6. Sort Products by Name (Descending) (using binary search tree)\n";
    cout << "7. View Deleted Products History\n";
    cout << "8. Exit\n";
    cout << "Choose an option: ";
    cin >> option;

    switch (option) {
      case 1: {
        Product newProduct;
        cout << "Enter product name: ";
        cin >> newProduct.name;
        cout << "Enter product price: ";
        cin >> newProduct.price;
        cout << "Enter product code: ";
        cin >> newProduct.code;

        // Insert into hash table
        productHash[newProduct.code] = newProduct;

        // Insert into binary search tree
        insertProduct(root, newProduct);

        break;
      }

      case 2: {
        // Display products using hash table
        for (const auto& entry : productHash) {
          const Product& product = entry.second;
          cout << "Product Name: " << product.name
               << ", Price: " << product.price << ", Code: " << product.code
               << endl;
        }
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
        // View deleted products history
        if (!deletedProducts.empty()) {
          cout << "Deleted Products History:\n";
          for (const auto& product : deletedProducts) {
            cout << "Product Name: " << product.name
                 << ", Price: " << product.price << ", Code: " << product.code
                 << endl;
          }
        } else {
          cout << "No deleted products history.\n";
        }

        break;
      }

      case 8:
        cout << "Exiting program.\n";
        break;

      default:
        cout << "Invalid option. Please try again.\n";
        break;
    }

  } while (option != 8);

  // Clean up memory for binary search tree (if needed)
  // ...

  return 0;
}
