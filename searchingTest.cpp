#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

// Struktur data untuk merepresentasikan produk
struct Product {
    int productCode;
    std::string productName;

    // Konstruktor
    Product(int code, const std::string& name) : productCode(code), productName(name) {}
};

// Fungsi untuk pencarian produk berdasarkan kode produk menggunakan hash
std::unordered_map<int, Product> productHash;

void addProductToHash(const Product& product) {
    productHash[product.productCode] = product;
}

Product searchProductByCode(int code) {
    auto it = productHash.find(code);
    if (it != productHash.end()) {
        return it->second;
    } else {
        return Product(-1, "Product not found");
    }
}

// Struktur data untuk pohon telusur biner
struct BinarySearchTree {
    struct Node {
        Product product;
        Node* left;
        Node* right;

        // Konstruktor
        Node(const Product& p) : product(p), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Konstruktor
    BinarySearchTree() : root(nullptr) {}

    // Fungsi untuk menambahkan produk ke pohon telusur biner
    void addProductToTree(const Product& product) {
        root = insert(root, product);
    }

    // Fungsi rekursif untuk menambahkan node ke pohon telusur biner
    Node* insert(Node* node, const Product& product) {
        if (node == nullptr) {
            return new Node(product);
        }

        if (product.productName < node->product.productName) {
            node->left = insert(node->left, product);
        } else if (product.productName > node->product.productName) {
            node->right = insert(node->right, product);
        }

        return node;
    }

    // Fungsi untuk mencari produk berdasarkan rentang nama produk
    std::vector<Product> searchProductByNameRange(const std::string& startName, const std::string& endName) {
        std::vector<Product> result;
        searchByNameRange(root, startName, endName, result);
        return result;
    }

    // Fungsi rekursif untuk mencari produk berdasarkan rentang nama produk
    void searchByNameRange(Node* node, const std::string& startName, const std::string& endName, std::vector<Product>& result) {
        if (node == nullptr) {
            return;
        }

        if (node->product.productName >= startName) {
            searchByNameRange(node->left, startName, endName, result);
        }

        if (node->product.productName >= startName && node->product.productName <= endName) {
            result.push_back(node->product);
        }

        if (node->product.productName <= endName) {
            searchByNameRange(node->right, startName, endName, result);
        }
    }
};

int main() {
    // Contoh penggunaan

    // Pencarian berdasarkan kode produk menggunakan hash
    Product product1(101, "Apple");
    Product product2(202, "Banana");

    addProductToHash(product1);
    addProductToHash(product2);

    Product resultProduct = searchProductByCode(101);
    std::cout << "Search Result (by code): " << resultProduct.productName << std::endl;

    // Pencarian berdasarkan rentang nama produk menggunakan pohon telusur biner
    BinarySearchTree bst;
    bst.addProductToTree(product1);
    bst.addProductToTree(product2);

    std::vector<Product> resultProducts = bst.searchProductByNameRange("A", "B");
    std::cout << "Search Result (by name range):" << std::endl;
    for (const auto& product : resultProducts) {
        std::cout << product.productName << std::endl;
    }

    return 0;
}
