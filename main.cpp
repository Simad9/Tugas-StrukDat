#include <iostream>
using namespace std;

// DEKLARASI
// ...

// STRUCT
// ...

// FUNGSI LOGIKA (BACK-END)
// ...

// FUNGSI TAMPILAN (FRONT-END)
// ...

// MAIN PROGRAM
int main()
{
  // Deklarasi Variable
  int pilihMenu;
  do
  {
    // Tampilan Awal
    system("cls");
    cout << "+==================================+\n";
    cout << "|            1232200010            |\n";
    cout << "|            1232200019            |\n";
    cout << "|            1232200021            |\n";
    cout << "|            1232200031            |\n";
    cout << "+==================================+\n";
    cout << "| 1. Input Data                    |\n";
    cout << "| 2. Output Data                   |\n";
    cout << "| 3. Search Data                   |\n";
    cout << "| 4. Sort Data                     |\n";
    cout << "| 5. Delete Data                   |\n";
    cout << "| 6. Delete History                |\n";
    cout << "+==================================+\n";
    cout << "  Pilih menu : ";

    // Input Menu
    cin >> pilihMenu;

    // Error Handling Input Menu
    if (cin.fail() || pilihMenu < 1 || pilihMenu > 6)
    {
      cout << "  Inputan tidak terdeteksi!\n  ";
      cin.clear();
      cin.ignore();
      system("pause");
      continue;
    }

  } while (true);

  return 0;
}