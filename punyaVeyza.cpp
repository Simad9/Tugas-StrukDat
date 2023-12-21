#include <iostream>
#include <cstring>
using namespace std;

const int table_size = 10; // Ukuran tabel hash
const int max_deleted = 100; // Jumlah maksimal riwayat pasien yang dihapus

// Struktur data untuk informasi pasien
struct Patient {
    string name;
    int patientID;
    string roomCategory;
    int duration;
    Patient* next;

    Patient(const string& n, int id, const string& category, int d)
        : name(n), patientID(id), roomCategory(category), duration(d), next(nullptr) {}
};

// Struktur data untuk menyimpan data pasien yang dihapus
struct DeletedPatient {
    string name;
    int patientID;
    string roomCategory;
    int duration;
};

// Fungsi hash sederhana untuk ID pasien
int hashFunction(int patientID) {
    return patientID % table_size;
}

// Fungsi untuk menambahkan data pasien ke dalam tabel hash
void addPatient(Patient* table[], const string& name, int patientID, const string& roomCategory, int duration) {
    int index = hashFunction(patientID);
    Patient* newPatient = new Patient(name, patientID, roomCategory, duration);
    newPatient->next = table[index];
    table[index] = newPatient;
}

// Fungsi untuk menampilkan data pasien berdasarkan nama pasien
void displayPatientByName(Patient* table[], const string& name) {
    for (int i = 0; i < table_size; ++i) {
        Patient* current = table[i];
        while (current != nullptr) {
            if (current->name == name) {
                cout << "====================================\n";
                cout << "          DATA PASIEN\n";
                cout << "====================================\n";
                cout << "Nama            : " << current->name << endl;
                cout << "ID Pasien       : " << current->patientID << endl;
                cout << "Golongan Ruang  : " << current->roomCategory << endl;
                cout << "Lama Rawat Inap : " << current->duration << " hari" << endl;

                // Menghitung total biaya
                int harga;
                if (current->roomCategory == "A") {
                    harga = 150000;
                } else if (current->roomCategory == "B") {
                    harga = 200000;
                } else if (current->roomCategory == "C") {
                    harga = 250000;
                } else if (current->roomCategory == "D") {
                    harga = 300000;
                } else if (current->roomCategory == "E") {
                    harga = 350000;
                } else {
                    harga = 0; // Golongan ruang tidak valid
                }

                int totalBiaya = harga * current->duration;
                cout << "Total Biaya     : " << totalBiaya << endl;

                cout << "====================================\n";
                return; // Keluar dari fungsi setelah menemukan pasien
            }
            current = current->next;
        }
    }
    cout << "Pasien dengan nama '" << name << "' tidak ditemukan.\n";
}

// Fungsi untuk menghapus data pasien berdasarkan nama pasien
void removePatientByName(Patient* table[], DeletedPatient history[], int& deletedCount, const string& name) {
    for (int i = 0; i < table_size; ++i) {
        Patient* current = table[i];
        Patient* prev = nullptr;

        while (current != nullptr) {
            if (current->name == name) {
                // Simpan data pasien yang dihapus ke dalam history
                DeletedPatient deletedPatient = {current->name, current->patientID, current->roomCategory, current->duration};
                history[deletedCount++] = deletedPatient;

                if (prev == nullptr) {
                    // Pasien berada di awal linked list
                    table[i] = current->next;
                } else {
                    // Pasien berada di tengah atau akhir linked list
                    prev->next = current->next;
                }

                delete current; // Hapus data pasien
                cout << "Data pasien dengan nama '" << name << "' berhasil dihapus.\n";
                return;
            }

            prev = current;
            current = current->next;
        }
    }

    cout << "Pasien dengan nama '" << name << "' tidak ditemukan.\n";
}

// Fungsi untuk menampilkan data history pasien yang telah dihapus
void displayDeletedPatientHistory(DeletedPatient history[], int deletedCount) {
    cout << "====================================\n";
    cout << "      HISTORY DATA PASIEN DIHAPUS\n";
    cout << "====================================\n";

    for (int i = 0; i < deletedCount; ++i) {
        cout << "Nama            : " << history[i].name << endl;
        cout << "ID Pasien       : " << history[i].patientID << endl;
        cout << "Golongan Ruang  : " << history[i].roomCategory << endl;
        cout << "Lama Rawat Inap : " << history[i].duration << " hari" << endl;
        cout << "------------------------------------\n";
    }
}


struct TreeNode {
    Patient* patient;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Patient* p) : patient(p), left(nullptr), right(nullptr) {}
};

TreeNode* insertIntoBST(TreeNode* root, Patient* patient);

TreeNode* buildBinarySearchTree(Patient* table[]) {
    TreeNode* root = nullptr;

    for (int i = 0; i < table_size; ++i) {
        Patient* current = table[i];
        while (current != nullptr) {
            root = insertIntoBST(root, current);
            current = current->next;
        }
    }

    return root;
}

TreeNode* insertIntoBST(TreeNode* root, Patient* patient) {
    if (root == nullptr) {
        return new TreeNode(patient);
    }

    if (patient->name < root->patient->name) {
        root->left = insertIntoBST(root->left, patient);
    } else {
        root->right = insertIntoBST(root->right, patient);
    }

    return root;
}

TreeNode* searchByName(TreeNode* root, const string& name) {
    if (root == nullptr || root->patient->name == name) {
        return root;
    }

    if (name < root->patient->name) {
        return searchByName(root->left, name);
    } else {
        return searchByName(root->right, name);
    }
}

// Fungsi untuk menampilkan data pasien berdasarkan rentang abjad nama pasien
void displayPatientByAlphabetRange(Patient* table[], char startChar, char endChar) {
                cout << "====================================\n";
                cout << "          DATA PASIEN\n";
                cout << "====================================\n";
    for (int i = 0; i < table_size; ++i) {
        Patient* current = table[i];
        while (current != nullptr) {
            char firstChar = current->name[0];
            if (firstChar >= startChar && firstChar <= endChar) {
                cout << i+1 << ". " << current->name << endl;
            }
            current = current->next;
        }
    }
                cout << "Tidak ada pasien dalam rentang abjad tersebut.\n";
                cout << "====================================\n";
}


// Fungsi untuk menampilkan data pasien dengan metode InOrder pada PTB
void inOrderTraversal(TreeNode* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << "Nama            : " << root->patient->name << endl;
        cout << "ID Pasien       : " << root->patient->patientID << endl;
        cout << "Golongan Ruang  : " << root->patient->roomCategory << endl;
        cout << "Lama Rawat Inap : " << root->patient->duration << " hari" << endl;

        // Menghitung total biaya
        int hargaPerHari;
        if (root->patient->roomCategory == "A") {
            hargaPerHari = 150000;
        } else if (root->patient->roomCategory == "B") {
            hargaPerHari = 200000;
        } else if (root->patient->roomCategory == "C") {
            hargaPerHari = 250000;
        } else if (root->patient->roomCategory == "D") {
            hargaPerHari = 300000;
        } else if (root->patient->roomCategory == "E") {
            hargaPerHari = 350000;
        } else {
            hargaPerHari = 0; // Golongan ruang tidak valid
        }

        int totalBiaya = hargaPerHari * root->patient->duration;
        cout << "Total Biaya     : " << totalBiaya << endl;

        cout << "------------------------------------\n";
        inOrderTraversal(root->right);
    }
}

// Fungsi untuk menampilkan data pasien dengan metode PostOrder pada PTB
void postOrderTraversal(TreeNode* root) {
    if (root != nullptr) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        cout << "Nama            : " << root->patient->name << endl;
        cout << "ID Pasien       : " << root->patient->patientID << endl;
        cout << "Golongan Ruang  : " << root->patient->roomCategory << endl;
        cout << "Lama Rawat Inap : " << root->patient->duration << " hari" << endl;

        // Menghitung total biaya
        int hargaPerHari;
        if (root->patient->roomCategory == "A") {
            hargaPerHari = 150000;
        } else if (root->patient->roomCategory == "B") {
            hargaPerHari = 200000;
        } else if (root->patient->roomCategory == "C") {
            hargaPerHari = 250000;
        } else if (root->patient->roomCategory == "D") {
            hargaPerHari = 300000;
        } else if (root->patient->roomCategory == "E") {
            hargaPerHari = 350000;
        } else {
            hargaPerHari = 0; // Golongan ruang tidak valid
        }

        int totalBiaya = hargaPerHari * root->patient->duration;
        cout << "Total Biaya     : " << totalBiaya << endl;

        cout << "------------------------------------\n";
    }
}

// Fungsi untuk menampilkan data pasien dengan metode PreOrder pada PTB
void preOrderTraversal(TreeNode* root) {
    if (root != nullptr) {
        cout << "Nama            : " << root->patient->name << endl;
        cout << "ID Pasien       : " << root->patient->patientID << endl;
        cout << "Golongan Ruang  : " << root->patient->roomCategory << endl;
        cout << "Lama Rawat Inap : " << root->patient->duration << " hari" << endl;

        // Menghitung total biaya
        int hargaPerHari;
        if (root->patient->roomCategory == "A") {
            hargaPerHari = 150000;
        } else if (root->patient->roomCategory == "B") {
            hargaPerHari = 200000;
        } else if (root->patient->roomCategory == "C") {
            hargaPerHari = 250000;
        } else if (root->patient->roomCategory == "D") {
            hargaPerHari = 300000;
        } else if (root->patient->roomCategory == "E") {
            hargaPerHari = 350000;
        } else {
            hargaPerHari = 0; // Golongan ruang tidak valid
        }

        int totalBiaya = hargaPerHari * root->patient->duration;
        cout << "Total Biaya     : " << totalBiaya << endl;

        cout << "------------------------------------\n";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}


int main() {
    int pilih;
    Patient* patientTable[table_size];
    DeletedPatient deletedPatientHistory[max_deleted]; // Larik untuk menyimpan riwayat pasien yang dihapus
    int deletedCount = 0; // Menghitung jumlah riwayat pasien yang dihapus
    int numPatients;

    do {
        system("cls");
        cout << "====================================\n";
        cout << "      RUMAH SAKIT SAVV\n";
        cout << "====================================\n";
        cout << " 1. Lihat Data Semua Pasien\n";
        cout << " 2. Input Data Pasien\n";
        cout << " 3. Tampil Data Pasien\n";
        cout << " 4. Hapus Data Pasien\n";
        cout << " 5. Cari Pasien\n";
        cout << " 6. Lihat History Pasien\n";
        cout << " 0. Keluar\n";
        cout << "Pilih : "; cin >> pilih;
        cout << endl;

        switch(pilih) {
            case 1: {
                // Tambahkan logika untuk menampilkan semua data pasien
                system("cls");
                int pilih1;

    //             // Check if there are patients available
    // bool hasPatients = false;
    // for (int i = 0; i < table_size; ++i) {
    //     if (patientTable[i] != nullptr) {
    //         hasPatients = true;
    //         break;
    //     }
    // }

    // if (!hasPatients) {
    //     cout << "Tidak ada data pasien yang tersedia.\n";
    //     system("pause");
    //     break;
    // }

                cout << "--------- LIHAT DATA SEMUA PASIEN ----------\n";
                cout << " 1. InOrder\n";
                cout << " 2. PostOrder\n";
                cout << " 3. PreOrder\n";
                cout << "Pilih : "; cin >> pilih1;
                TreeNode* rootBST = buildBinarySearchTree(patientTable);
                switch(pilih1) {
                    case 1 : {
                            cout << "====================================\n";
                            cout << "   DATA SEMUA PASIEN (InOrder)\n";
                            cout << "====================================\n";
                            inOrderTraversal(rootBST);
                            break;
                    }
                    case 2 : {
                            cout << "====================================\n";
                            cout << "   DATA SEMUA PASIEN (PostOrder)\n";
                            cout << "====================================\n";
                            postOrderTraversal(rootBST);
                            break;
                    }
                    case 3 : {
                            cout << "====================================\n";
                            cout << "   DATA SEMUA PASIEN (PreOrder)\n";
                            cout << "====================================\n";
                            preOrderTraversal(rootBST);
                            break;
                    }
                    default : {
                            cout << "Mohon Maaf, silahkan inputkan kembali menu yang ada.\n";
                            break;
                    }
                }
                
                system("pause");
                break; }
            case 2: {
                system("cls");
                cout << "Masukkan jumlah data pasien yang ingin diinput: ";
                cin >> numPatients;
                cin.ignore(); // Membersihkan newline di buffer

                // Inisialisasi tabel pasien
                for (int i = 0; i < table_size; ++i) {
                    patientTable[i] = nullptr;
                }

                // Menambahkan data pasien
                string name;
                string roomCategory;
                int patientID, duration;

                cout << "Masukkan data pasien:" << endl;
                for (int i = 0; i < numPatients; ++i) {
                    cout << endl;
                    cout << "Data Pasien ke-" << i + 1 << ":" << endl;
                    cout << "Nama: ";
                    getline(cin, name);
                    cout << "ID Pasien: ";
                    cin >> patientID;
                    cin.ignore(); // Membersihkan newline di buffer
                    cout << "Golongan Ruang: ";
                    getline(cin, roomCategory);
                    cout << "Lama Rawat Inap (hari): ";
                    cin >> duration;
                    cin.ignore(); // Membersihkan newline di buffer

                    addPatient(patientTable, name, patientID, roomCategory, duration);
                }
                system("pause");
                break;
            }
            case 3: {
                string searchName;
                cout << "Masukkan nama pasien yang ingin dicari: ";
                cin.ignore(); // Membersihkan newline di buffer
                getline(cin, searchName);
                displayPatientByName(patientTable, searchName);
                system("pause");
                break;
            }
            case 4: {
                string removeName;
                cout << "Masukkan nama pasien yang ingin dihapus: ";
                cin.ignore(); // Membersihkan newline di buffer
                getline(cin, removeName);
                removePatientByName(patientTable, deletedPatientHistory, deletedCount, removeName);
                cin.ignore(); // Membersihkan newline di buffer setelah selesai mengambil input
                system("pause");
                break;
            }
            case 5: {
                char startChar, endChar;
                cout << "Masukkan rentang abjad pertama\t: "; cin >> startChar;
                cout << "Masukkan rentang abjad terakhir\t: "; cin >> endChar;
    
                if (startChar < 'A' || startChar > 'Z' || endChar < 'A' || endChar > 'Z' || startChar > endChar) {
                    cout << "Input rentang abjad tidak valid.\n";
                    break;
                }

                displayPatientByAlphabetRange(patientTable, startChar, endChar);

                system("pause");
                break;
            }
            case 6: {
                displayDeletedPatientHistory(deletedPatientHistory, deletedCount);
                system("pause");
                break;
            }
            case 0: {
                cout << " SEMOGA LEKAS SEMBUH KAWAN \n";
                break;
            }
            default: {
                cout << " Input Menu yang tersedia...\n";
                system("pause");
                break;
            }
        }
    } while(pilih != 0);
}