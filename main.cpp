#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

struct Product {
    std::string name;
    double price;
    int code;
};

// Hash table to store product information
std::unordered_map<int, Product> productHash;

// Binary Search Tree (Binary Search Tree) to store products based on product names
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

// Function to perform post-order traversal for sorting products by name in descending order
void postOrderTraversal(TreeNode* root) {
    if (root != nullptr) {
        postOrderTraversal(root->right);
        std::cout << "Product Name: " << root->data.name << ", Price: " << root->data.price << ", Code: " << root->data.code << std::endl;
        postOrderTraversal(root->left);
    }
}

// Function to search products based on name range in Binary Search Tree
void searchByNameRange(TreeNode* root, const std::string& startName, const std::string& endName, std::vector<Product>& result) {
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
std::vector<Product> deletedProducts;  // Add this line before main

int main() {
    int option;
    TreeNode* root = nullptr;  // Add this line

    do {
        std::cout << "\n=== Menu ===" << std::endl;
        std::cout << "1. Input Product\n";
        std::cout << "2. Display Products (using hash)\n";
        std::cout << "3. Delete Product (using hash)\n";
        std::cout << "4. Search Product by Code (using hash)\n";
        std::cout << "5. Search Product by Name Range (using binary search tree)\n";
        std::cout << "6. Sort Products by Name (Descending) (using binary search tree)\n";
        std::cout << "7. View Deleted Products History\n";
        std::cout << "8. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> option;

        switch (option) {
            case 1: {
                Product newProduct;
                std::cout << "Enter product name: ";
                std::cin >> newProduct.name;
                std::cout << "Enter product price: ";
                std::cin >> newProduct.price;
                std::cout << "Enter product code: ";
                std::cin >> newProduct.code;

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
                    std::cout << "Product Name: " << product.name << ", Price: " << product.price << ", Code: " << product.code << std::endl;
                }
                break;
            }

            case 3: {
                // Delete product using hash table
                int deleteCode;
                std::cout << "Enter product code to delete: ";
                std::cin >> deleteCode;

                auto it = productHash.find(deleteCode);
                if (it != productHash.end()) {
                    // Insert into binary search tree for history
                    deletedProducts.push_back(it->second);

                    // Erase from hash table
                    productHash.erase(it);
                    std::cout << "Product with code " << deleteCode << " deleted.\n";
                } else {
                    std::cout << "Product with code " << deleteCode << " not found.\n";
                }

                break;
            }

            case 4: {
                // Search product by code using hash table
                int searchCode;
                std::cout << "Enter product code to search: ";
                std::cin >> searchCode;

                auto it = productHash.find(searchCode);
                if (it != productHash.end()) {
                    const Product& product = it->second;
                    std::cout << "Product found: " << product.name << ", Price: " << product.price << ", Code: " << product.code << std::endl;
                } else {
                    std::cout << "Product with code " << searchCode << " not found.\n";
                }

                break;
            }

            case 5: {
                // Search product by name range using binary search tree
                std::string startName, endName;
                std::cout << "Enter start of name range: ";
                std::cin >> startName;
                std::cout << "Enter end of name range: ";
                std::cin >> endName;

                std::vector<Product> result;
                searchByNameRange(root, startName, endName, result);

                if (!result.empty()) {
                    std::cout << "Products in the specified name range:\n";
                    for (const auto& product : result) {
                        std::cout << "Product Name: " << product.name << ", Price: " << product.price << ", Code: " << product.code << std::endl;
                    }
                } else {
                    std::cout << "No products found in the specified name range.\n";
                }

                break;
            }

            case 6: {
                // Sort products by name in descending order using binary search tree
                std::cout << "Products sorted by name (Descending):\n";
                postOrderTraversal(root);
                break;
            }

            case 7: {
                // View deleted products history
                if (!deletedProducts.empty()) {
                    std::cout << "Deleted Products History:\n";
                    for (const auto& product : deletedProducts) {
                        std::cout << "Product Name: " << product.name << ", Price: " << product.price << ", Code: " << product.code << std::endl;
                    }
                } else {
                    std::cout << "No deleted products history.\n";
                }

                break;
            }

            case 8:
                std::cout << "Exiting program.\n";
                break;

            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
        }

    } while (option != 8);

    // Clean up memory for binary search tree (if needed)
    // ...

    return 0;
}
