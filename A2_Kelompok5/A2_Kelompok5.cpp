#include <iostream>
#include <cstring>
#include <conio.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Struktur data untuk menyimpan informasi bunga
struct Flower
{
    char nama[50];
    char warna[50];
    char asal[50];
    double harga;
    int stok;
    Flower *next;
};

// Struktur data untuk menyimpan informasi akun
struct Akun
{
    string username, password;
    Akun *next;
};

// Struktur data untuk menyimpan informasi keranjang
struct Cart
{
    string username;
    Flower *item;
    int jumlah;
    Cart *next;
};

// Struktur data untuk menyimpan informasi checkout
struct Checkout
{
    string username;
    Flower *item;
    int jumlah;
    double totalHarga;
    string status;
    Checkout *next;
};
// Inisialiasi nilai length
int length = 0;
// Inisialisasi linked list bunga
Flower *head = nullptr;
// Inisialisasi linked list pengguna
Akun *headAkun = nullptr;
// Inisialisasi linked list keranjang
Cart *headCart = nullptr;
// Inisialisasi linked list checkout
Checkout *headCheckout = nullptr;
// variabel global nama pemesan
string loggedInUsername = "";
// Pilihan user
int pilihan;
// variabel status login
bool statuslogin = false;
// Fitur login sederhana dengan nama dan NIM
string nama, nim;
// variabel inputan username dan password
string username, password;
// Variabel untuk menyimpan jumlah percobaan login
int login = 1;
int sisaLogin;

// mengecek string tidak boleh terdapat angka dan karakter
bool kata(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
bool karakter(char c)
{
    return c == ' ' || c == '-' || c == '_';
}
bool cek_inputan(const string &str)
{
    for (char c : str)
    {
        if (!kata(c) && !karakter(c))
        {
            return false;
        }
    }
    return true;
}

// Menampilkan header login
void header_login()
{
    system("cls");
    cout << "============================================" << endl;
    cout << "             * NARELLE FLORIST *             " << endl;
    cout << "--------------------------------------------" << endl;
    cout << "               Silahkan login :            " << endl;
    cout << "============================================" << endl;
}

// Menampilkan Header Tabel Bunga
void tabelBunga()
{
    cout << "============================================" << endl;
    cout << "                Data Bunga                  " << endl;
    cout << "          *** NARELLE FLORIST ***           " << endl;
    cout << "============================================" << endl;
}

// Mneampilkan Head Tabel Utama
void head_table()
{
    system("cls");
    cout << "============================================" << endl;
    cout << "           <<<<<<<   ***   >>>>>>>          " << endl;
    cout << "             - NARELLE FLORIST -            " << endl;
    cout << "           * Your Floral Paradise *         " << endl;
    cout << "============================================" << endl;
}

// Menampilkan Menu Awal
void menuAwal()
{
    head_table();
    cout << "  [1] Admin" << endl;
    cout << "  [2] Registrasi" << endl;
    cout << "  [3] Login" << endl;
    cout << "  [4] Exit" << endl;
    cout << endl;
}

// Fungsi untuk menampilkan menu admin
void tampilanAdmin()
{
    system("cls");
    cout << "============================================" << endl;
    cout << "                  Welcome to                " << endl;
    cout << "            *** NARELLE FLORIST ***         " << endl;
    cout << "               by kelompok 5 A2             " << endl;
    cout << "============================================" << endl;
    cout << "                Pilihan Menu  :             " << endl;
    cout << "============================================" << endl;
    cout << "[1]. Tambah data bunga" << endl;
    cout << "[2]. Tampilkan data bunga" << endl;
    cout << "[3]. Urutkan nama bunga" << endl;
    cout << "[4]. Searching nama bunga" << endl;
    cout << "[5]. Ubah data bunga" << endl;
    cout << "[6]. Hapus data bunga" << endl;
    cout << "[7]. Konfirmasi Pesanan" << endl;
    cout << "[8]. Riwayat Pesanan" << endl;
    cout << "[9]. Logout" << endl;
}

// Menampilkan menu user
void tampilanUser()
{
    system("cls");
    cout << "============================================" << endl;
    cout << "                  Welcome to                " << endl;
    cout << "            *** NARELLE FLORIST ***         " << endl;
    cout << "               by kelompok 5 A2             " << endl;
    cout << "============================================" << endl;
    cout << "                Pilihan Menu  :             " << endl;
    cout << "============================================" << endl;
    cout << "[1]. List bunga" << endl;
    cout << "[2]. Order Bunga" << endl;
    cout << "[3]. Keranjang Pesanan" << endl;
    cout << "[4]. Hapus Keranjang" << endl;
    cout << "[5]. Checkout" << endl;
    cout << "[6]. Riwayat Transaksi" << endl;
    cout << "[7]. Logout" << endl;
}

// Menampilkan akhir dari porgram
void end_program()
{
    cout << "============================================  " << endl;
    cout << "             * Terima Kasih *                 " << endl;
    cout << "   Ibnu Gilang Pradupta Cipta   2209106040    " << endl;
    cout << "   Raudhya Azzahra'             2209106034    " << endl;
    cout << "   Nadifa Salsabila Purnomo     2209106044    " << endl;
    cout << endl;
}

/////////////////////////// LOGIN DAN REGISTRASI  //////////////////////////////

// Fungsi untuk menambah akun ke linked list
void tambahAkun(Akun *&head, const string &username, const string &password)
{
    // Periksa apakah username sudah ada
    Akun *existingUser = head;
    while (existingUser)
    {
        if (existingUser->username == username)
        {
            cout << "Username sudah ada. Registrasi gagal.\n";
            return; // Keluar dari fungsi jika username sudah ada
        }
        existingUser = existingUser->next;
    }

    // Jika username belum ada, tambahkan akun baru
    Akun *newAkun = new Akun;
    newAkun->username = username;
    newAkun->password = password;
    newAkun->next = nullptr;

    if (!head)
    {
        head = newAkun;
    }
    else
    {
        Akun *current = head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newAkun;
    }
    cout << "Akun berhasil dibuat !!\n";
}

// Untuk mengecek login
bool loginUser(Akun *head, const string &username, const string &password)
{
    Akun *current = head;
    while (current)
    {
        if (current->username == username && current->password == password)
        {
            return true; // Login berhasil
        }
        current = current->next;
    }
    return false; // Login gagal
}
/////////////////////////// ADMIN //////////////////////////////
// Fungsi input data bunga
void inputFlowerData(Flower *newFlower)
{
    while (true)
    {
        cout << "Masukkan nama bunga        : ";
        cin >> newFlower->nama;
        if (!cek_inputan(newFlower->nama))
        {
            cout << "Inputan hanya dapat berupa huruf !" << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Masukkan warna bunga       : ";
        cin >> newFlower->warna;
        if (!cek_inputan(newFlower->warna))
        {
            cout << "Inputan hanya dapat berupa huruf !" << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Masukkan kota asal suplier : ";
        cin >> newFlower->asal;
        if (!cek_inputan(newFlower->asal))
        {
            cout << "Inputan hanya dapat berupa huruf !" << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Masukkan harga jual bunga  : ";
        cin >> newFlower->harga;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Jumlah harus berupa angka" << endl;
            continue;
        }
        if (newFlower->harga <= 0)
        {
            cout << "Harga bunga tidak dapat <= 0" << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Masukkan stok bunga        : ";
        cin >> newFlower->stok;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Jumlah harus berupa angka" << endl;
            continue;
        }
        if (newFlower->stok <= 0)
        {
            cout << "Jumlah minimal stok bunga adalah satu" << endl;
            continue;
        }
        break;
    }
}

// Fungsi untuk menambah data bunga di akhir linked list
void tambahDataAkhir(Flower *&head, int &length)
{
    Flower *newFlower = new Flower;
    system("cls");
    head_table();
    inputFlowerData(newFlower);

    newFlower->next = nullptr;

    if (!head)
    {
        head = newFlower;
    }
    else
    {
        Flower *current = head;
        while (current->next)
        {
            current = current->next;
        }
        current->next = newFlower;
    }
    length++;

    cout << "Data bunga berhasil ditambahkan di akhir!\n";
}

// Fungsi untuk menampilkan data bunga dari linked list
void tampilkanData(Flower *head)
{
    if (!head)
    {
        cout << "Data bunga kosong.\n";
        return;
    }
    system("cls");
    Flower *current = head;
    tabelBunga();
    int id = 1;
    while (current)
    {
        cout << "No Indeks  : " << id << endl;
        cout << "Nama       : " << current->nama << endl;
        cout << "Warna      : " << current->warna << endl;
        cout << "Asal       : " << current->asal << endl;
        cout << "Harga      : " << current->harga << endl;
        cout << "Stok       : " << current->stok << endl;
        cout << "--------------------------------------------\n";
        current = current->next;
        id++;
    }
}

// Fungsi untuk mengupdate data bunga dalam linked list berdasarkan indeks
void updateDataByIndex(Flower *head, int targetIndex)
{
    Flower *current = head;
    int currentIndex = 1;

    while (current)
    {
        if (currentIndex == targetIndex)
        {
            cout << "Nama   : " << current->nama << endl;
            cout << "Warna  : " << current->warna << endl;
            cout << "Asal   : " << current->asal << endl;
            cout << "Harga  : " << current->harga << endl;
            cout << "Stok   : " << current->stok << endl;
            cout << "--------------------------------------------\n";

            cout << "Masukkan data yang baru:\n";
            while (true)
            {
                cout << "Masukkan nama bunga        : ";
                cin >> current->nama;
                if (!cek_inputan(current->nama))
                {
                    cout << "Inputan hanya dapat berupa huruf !" << endl;
                    continue;
                }
                break;
            }
            while (true)
            {
                cout << "Masukkan warna bunga       : ";
                cin >> current->warna;
                if (!cek_inputan(current->warna))
                {
                    cout << "Inputan hanya dapat berupa huruf !" << endl;
                    continue;
                }
                break;
            }
            while (true)
            {
                cout << "Masukkan kota asal suplier : ";
                cin >> current->asal;
                if (!cek_inputan(current->asal))
                {
                    cout << "Inputan hanya dapat berupa huruf !" << endl;
                    continue;
                }
                break;
            }
            while (true)
            {
                cout << "Masukkan harga jual bunga  : ";
                cin >> current->harga;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Jumlah harus berupa angka" << endl;
                    continue;
                }
                if (current->harga <= 0)
                {
                    cout << "Harga bunga tidak dapat <= 0" << endl;
                    continue;
                }
                break;
            }
            while (true)
            {
                cout << "Masukkan stok bunga        : ";
                cin >> current->stok;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Jumlah harus berupa angka" << endl;
                    continue;
                }
                if (current->stok <= 0)
                {
                    cout << "Jumlah minimal tambah bunga adalah satu" << endl;
                    continue;
                }
                break;
            }
            cout << "Data bunga berhasil diperbarui!\n";
            return;
        }
        current = current->next;
        currentIndex++;
    }

    cout << "Indeks bunga '" << targetIndex << "' tidak ditemukan.\n";
}

// Fungsi untuk menghapus data bunga dalam linked list berdasarkan indeks
void hapusDataByIndex(Flower *&head, int targetIndex)
{
    if (!head)
    {
        cout << "List bunga kosong." << endl;
        return;
    }

    if (targetIndex == 1)
    {
        // Hapus elemen pertama
        Flower *temp = head;
        head = head->next;
        delete temp;
        cout << "Data bunga pada indeks " << targetIndex << " berhasil dihapus." << endl;
        return;
    }

    Flower *current = head;
    int currentIndex = 1;

    while (current && currentIndex < targetIndex - 1)
    {
        current = current->next;
        currentIndex++;
    }

    if (!current || !current->next)
    {
        cout << "Indeks bunga '" << targetIndex << "' tidak valid." << endl;
        return;
    }

    Flower *temp = current->next;
    current->next = temp->next;
    delete temp;

    cout << "Data bunga pada indeks " << targetIndex << " berhasil dihapus." << endl;
}

//////////////////////////// SORTING ////////////////////////////////////

// Deklarasi dari merge short
void mergeSort(Flower *&head);
void splitList(Flower *source, Flower *&front, Flower *&back);
Flower *mergeLists(Flower *a, Flower *b);

// Fungsi untuk membagi linked list menjadi dua bagian
void splitList(Flower *source, Flower *&front, Flower *&back)
{
    Flower *slow = source;
    Flower *fast = source->next;

    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    front = source;
    back = slow->next;
    slow->next = nullptr;
}

// Fungsi untuk menggabungkan dua linked list yang terurut
Flower *mergeLists(Flower *a, Flower *b)
{
    Flower *result = nullptr;

    if (!a)
        return b;
    else if (!b)
        return a;

    if (strcmp(a->nama, b->nama) <= 0)
    {
        result = a;
        result->next = mergeLists(a->next, b);
    }
    else
    {
        result = b;
        result->next = mergeLists(a, b->next);
    }

    return result;
}

// sorting MERGE SORT
void mergeSort(Flower *&head)
{
    Flower *current = head;
    Flower *front = nullptr;
    Flower *back = nullptr;

    if (!current || !current->next)
        return;

    splitList(current, front, back);

    mergeSort(front);
    mergeSort(back);

    head = mergeLists(front, back);
}
//////////////////////////////////// SEARCHING /////////////////////////////////////////

// Untuk deklarasi searching boyer moore
int boyer_moore_search(const char *text, const char *pattern)
{
    int text_len = strlen(text);
    int pattern_len = strlen(pattern);

    int skip_table[256];

    for (int i = 0; i < 256; i++)
    {
        skip_table[i] = pattern_len;
    }

    for (int i = 0; i < pattern_len - 1; i++)
    {
        skip_table[(unsigned char)pattern[i]] = pattern_len - 1 - i;
    }

    int i = pattern_len - 1;
    while (i < text_len)
    {
        int j = pattern_len - 1;
        while (j >= 0 && text[i] == pattern[j])
        {
            i--;
            j--;
        }

        if (j < 0)
        {
            return i + 1; // Pattern found
        }
        else
        {
            i += std::max(1, skip_table[(unsigned char)text[i]]);
        }
    }

    return -1; // Pattern not found
}

// Fungsi untuk menampilkan hasil searching
void searchAndPrintFlowers(const char *search_name)
{
    Flower *current = head;
    bool dataDitemukan = false; // Tambahkan variabel untuk melacak apakah data ditemukan

    while (current != nullptr)
    {
        if (boyer_moore_search(current->nama, search_name) != -1)
        {
            // Flower dengan nama yang cocok ditemukan
            cout << "Data Bunga ditemukan :" << endl;
            cout << "Nama   : " << current->nama << endl;
            cout << "Warna  : " << current->warna << endl;
            cout << "Asal   : " << current->asal << endl;
            cout << "Harga  : " << current->harga << endl;
            cout << "Stok   : " << current->stok << endl;
            dataDitemukan = true; // Setel flag dataDitemukan menjadi true
        }
        current = current->next;
    }

    if (!dataDitemukan)
    {
        cout << "Data tidak ditemukan." << endl; // Peringatan jika data tidak ditemukan
    }
}

////////////////////////////////////// FILE CSV ///////////////////////////////

// Fungsi untuk menyimpan akun ke file CSV
void simpanAkunKeCSV(const string &filename, Akun *head)
{
    ofstream file(filename);
    if (file.is_open())
    {
        Akun *current = head;
        while (current)
        {
            file << current->username << "," << current->password << "\n";
            current = current->next;
        }
        file.close();
    }
    else
    {
        cerr << "Gagal membuka file " << filename << " untuk penulisan." << endl;
    }
}
// Fungsi untuk memuat akun dari file CSV
void muatAkunDariCSV(const string &filename, Akun *&head)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username, password;
            getline(ss, username, ',');
            getline(ss, password);
            tambahAkun(head, username, password);
        }
        file.close();
    }
    else
    {
        cerr << "Gagal membuka file " << filename << " untuk pembacaan." << endl;
    }
}
// Fungsi untuk menyimpan data flower ke file csv
void StructKeCSV_flower(Flower *flwr)
{
    fstream fout;
    fout.open("flowers.csv", ios::out);
    fout << "Nama,Warna,Asal,Harga,Stok\n";
    Flower *current = flwr;
    while (current != NULL)
    {
        fout << current->nama << ","
             << current->warna << ","
             << current->asal << ","
             << current->harga << ","
             << current->stok << "\n";
        current = current->next;
    }
    fout.close();
}
// Fungsi untuk memuat data flower dari file csv
void CSVKeStruct_flower(Flower *flwr)
{
    fstream fin;
    fin.open("flowers.csv", ios::in);
    string line, nama_str, warna_str, asal_str, harga_str, stok_str;
    const char *nama_char;
    const char *warna_char;
    const char *asal_char;
    double harga_d;
    int stok_i;

    // Skip the header line
    getline(fin, line);

    if (fin.is_open())
    {
        while (getline(fin, line))
        {
            // Buat data struct baru
            Flower *newFlower = new Flower;

            // Buat object String Stream untuk mengambil tiap baris pada csv
            stringstream ss(line);

            // Ambil data setiap sebelum tanda koma
            getline(ss, nama_str, ',');
            getline(ss, warna_str, ',');
            getline(ss, asal_str, ',');
            getline(ss, harga_str, ',');
            getline(ss, stok_str, '\n');

            // Ambil variabel nama, warna, dan asal berjenis string, konversi ke Char
            nama_char = nama_str.c_str();
            warna_char = warna_str.c_str();
            asal_char = asal_str.c_str();

            // Salin variabel-variabel tersebut ke dalam member struct
            strncpy(newFlower->nama, nama_char, sizeof(newFlower->nama));
            strncpy(newFlower->warna, warna_char, sizeof(newFlower->warna));
            strncpy(newFlower->asal, asal_char, sizeof(newFlower->asal));

            // Pastikan akhiran array Char tersebut terdapat NULL, agar tidak error
            newFlower->nama[sizeof(newFlower->nama) - 1] = '\0';
            newFlower->warna[sizeof(newFlower->warna) - 1] = '\0';
            newFlower->asal[sizeof(newFlower->asal) - 1] = '\0';

            // Masukkan data-data tersebut menggunakan Single Linked List
            newFlower->harga = stod(harga_str);
            newFlower->stok = stoi(stok_str);
            newFlower->next = nullptr;

            if (!head)
                head = newFlower;
            else
            {
                Flower *current = head;
                while (current->next)
                    current = current->next;
                current->next = newFlower;
            }
            length++;
        }
        fin.close();
    }
    else
    {
        system("cls");
        cout << "ERROR: CSV tidak ditemukan." << endl;
        system("pause");
        return;
    }
}
// Fungsi untuk menyimpan data keranjang ke file csv
void buatCsvKeranjang()
{
    ofstream file("cart.csv"); // Buka file CSV, file lama akan ditimpa
    if (file.is_open())
    {
        file << "Username,Item Name,Quantity,Price,Total Price\n"; // Header kolom (opsional)

        Cart *current = headCart;
        while (current)
        {
            file << current->username << "," << current->item->nama << ","
                 << current->jumlah << "," << current->item->harga << ","
                 << current->jumlah * current->item->harga << "\n";
            current = current->next;
        }

        file.close();
    }
    else
    {
        cerr << "Gagal membuka file CSV untuk item keranjang.\n";
    }
}
// Fungsi untuk memuat data keranjang ke file csv
void muatCsvKeranjang(const string &loggedInUsername)
{
    ifstream file("cart.csv");
    if (file.is_open())
    {
        string line;
        int id = 1; // Deklarasikan variabel id di luar loop
        // getline(file, line); // Baca dan abaikan baris judul

        while (getline(file, line))
        {
            istringstream iss(line);
            string username, namaBunga;
            int jumlah;
            double hargaPerItem, subtotal;

            if (getline(iss, username, ',') &&
                getline(iss, namaBunga, ',') &&
                (iss >> jumlah) &&
                (iss.ignore(), iss >> hargaPerItem) &&
                (iss.ignore(), iss >> subtotal))
            {
                // Periksa apakah username di baris CSV sesuai dengan loggedInUsername
                if (username == loggedInUsername)
                {
                    cout << "No Indeks           : " << id << endl;
                    cout << "Username            : " << username << endl;
                    cout << "Nama Bunga          : " << namaBunga << endl;
                    cout << "Jumlah              : " << jumlah << endl;
                    cout << "Harga per item      : " << hargaPerItem << endl;
                    cout << "Total               : " << subtotal << endl;
                    cout << "--------------------------------------------\n";
                    id++; // Tingkatkan nilai id setiap kali mencetak baris
                }
            }
        }

        file.close();
    }
    else
    {
        cerr << "Gagal membuka file CSV keranjang untuk pembacaan.\n";
    }
}

//////////////////////////////////// FUNGSI MENAMBAH ORDER KE KERANJANG ////////////////////////////////////

// Fungsi untuk mengurangi stok bunga di file csv
void kurangiStokBungaCSV(const string &namaBunga, int jumlah)
{
    fstream file("flowers.csv", ios::in | ios::out);
    if (file.is_open())
    {
        string line;
        stringstream updatedCsvData;

        // Read and skip the header line
        getline(file, line);
        updatedCsvData << line << "\n";

        while (getline(file, line))
        {
            istringstream iss(line);
            string nama, warna, asal;
            int harga, stok;

            if (getline(iss, nama, ',') &&
                getline(iss, warna, ',') &&
                getline(iss, asal, ',') &&
                (iss >> harga) &&
                (iss.ignore(), iss >> stok))
            {
                if (nama == namaBunga)
                {
                    // Kurangi stok sesuai dengan jumlah pesanan
                    stok -= jumlah;
                }
                updatedCsvData << nama << "," << warna << ","
                               << asal << "," << harga << ","
                               << stok << "\n";
            }
        }

        // Menggantikan isi file CSV dengan data yang diperbarui
        file.clear();
        file.seekp(0);
        file << updatedCsvData.str();
        file.close();
    }
    else
    {
        cerr << "Gagal membuka file CSV bunga untuk pembaruan stok.\n";
    }
}
// Fungsi untuk menambah data flower ke keranjang
void tambahKeKeranjang(const string &loggedInUsername, Flower *bunga, int jumlah)
{
    // Cek apakah item yang sama sudah ada dalam keranjang
    Cart *current = headCart;
    bool itemFound = false;

    while (current)
    {
        // Periksa apakah pointer tidak null sebelum mengakses propertinya
        if (current->username == loggedInUsername && current->item && bunga && current->item->nama == bunga->nama)
        {
            // Item sudah ada, periksa apakah jumlah yang dipesan sebelumnya lebih besar dari nol
            if (current->jumlah > 0)
            {
                // Gantikan jumlah pesanan sebelumnya dengan yang baru
                current->jumlah = jumlah;
            }
            else
            {
                // Jika jumlah sebelumnya adalah nol, tambahkan jumlah pesanan yang baru
                current->jumlah += jumlah;
            }
            itemFound = true;
            break;
        }
        current = current->next;
    }

    // Jika item belum ada dalam keranjang, tambahkan item baru
    if (!itemFound)
    {
        Cart *newItem = new Cart;
        newItem->username = loggedInUsername;
        newItem->item = bunga;
        newItem->jumlah = jumlah;
        newItem->next = nullptr;

        if (!headCart)
        {
            headCart = newItem;
        }
        else
        {
            current = headCart;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newItem;
        }
    }

    // Kurangi stok bunga di CSV
    kurangiStokBungaCSV(bunga->nama, jumlah);

    // Buka file CSV, file lama akan ditimpa
    fstream file("cart.csv", ios::in | ios::out);
    if (file.is_open())
    {
        string line;
        stringstream updatedCsvData;

        // Baca dan simpan header kolom (opsional)
        getline(file, line);
        updatedCsvData << line << "\n";

        // Baca dan perbarui data yang sudah ada
        while (getline(file, line))
        {
            istringstream iss(line);
            string username, namaBunga;
            int jumlah, hargaPerItem, subtotal;

            if (getline(iss, username, ',') &&
                getline(iss, namaBunga, ',') &&
                (iss >> jumlah) &&
                (iss.ignore(), iss >> hargaPerItem) &&
                (iss.ignore(), iss >> subtotal))
            {
                if (username == loggedInUsername && bunga->nama == namaBunga)
                {
                    jumlah += current->jumlah; // Perbarui jumlah
                    subtotal = jumlah * hargaPerItem;
                    itemFound = true;
                }
                updatedCsvData << username << "," << namaBunga << ","
                               << jumlah << "," << hargaPerItem << ","
                               << subtotal << "\n";
            }
        }

        // Menambahkan item baru jika tidak ada dalam data yang ada
        if (!itemFound)
        {
            updatedCsvData << loggedInUsername << "," << bunga->nama << ","
                           << jumlah << "," << bunga->harga << ","
                           << jumlah * bunga->harga << "\n";
        }

        // Menggantikan isi file CSV dengan data yang diperbarui
        file.clear();
        file.seekp(0);
        file << updatedCsvData.str();
        file.close();
    }
    else
    {
        cerr << "Gagal membuka file CSV untuk item keranjang.\n";
    }
}
// Fungsi untuk mengorder bunga
void pesanBunga(Flower *head, const string &loggedInUsername)
{
    while (true)
    {
        int indeks, jumlahPesan;
        while (true)
        {
            system("cls");
            tampilkanData(head);
            cout << "*ketik 00 untuk kembali" << endl;
            cout << "Masukkan Indeks bunga        : ";
            cin >> indeks;
            if (indeks == 00)
                return; // Exit the function if the user enters "00"

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Indeks harus berupa angka" << endl;
                system("pause");
                continue;
            }
            if (indeks <= 0)
            {
                cout << "Indeks harus lebih besar dari nol" << endl;
                system("pause");
                continue;
            }
            break;
        }

        Flower *current = head;
        int currentIndeks = 1;

        while (current)
        {
            if (currentIndeks == indeks)
            {
                system("cls");
                cout << "Anda memesan bunga dengan detail berikut:\n";
                cout << "Nama   : " << current->nama << endl;
                cout << "Warna  : " << current->warna << endl;
                cout << "Asal   : " << current->asal << endl;
                cout << "Harga  : " << current->harga << endl;
                cout << "Stok   : " << current->stok << endl;

                while (true)
                {

                    cout << "Masukkan jumlah yang ingin dipesan: ";
                    cin >> jumlahPesan;
                    if (jumlahPesan == 00)
                        return; // Exit the function if the user enters "00"

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(100, '\n');
                        cout << "Jumlah harus berupa angka" << endl;
                        system("pause");
                        continue;
                    }
                    if (jumlahPesan <= 0)
                    {
                        cout << "Jumlah harus lebih besar dari nol" << endl;
                        system("pause");
                        continue;
                    }
                    break;
                }
                if (jumlahPesan > 0 && jumlahPesan <= current->stok)
                {
                    // Update stok bunga yang dipesan
                    current->stok -= jumlahPesan;
                    cout << "Pesanan Anda berhasil.\n";

                    // Tambah pesanan ke keranjang
                    tambahKeKeranjang(loggedInUsername, current, jumlahPesan);

                    // Tanyakan apakah pengguna ingin melanjutkan memesan
                    cout << "Apakah Anda ingin melanjutkan memesan? (y/n): ";
                    char pilihan;
                    cin >> pilihan;
                    if (pilihan == 'n' || pilihan == 'N')
                    {
                        return; // Keluar dari fungsi jika pengguna memilih 'n'
                    }
                }
                else if (jumlahPesan > current->stok)
                {
                    cout << "Maaf, stok tidak mencukupi untuk pesanan ini.\n";
                }
                else
                {
                    cout << "Jumlah pemesanan tidak valid.\n";
                }
                break;
            }
            current = current->next;
            currentIndeks++;
        }
        if (!current)
        {
            cout << "Bunga dengan indeks " << indeks << " tidak ditemukan.\n";
            system("pause");
        }
    }
}
// Fungsi untuk mengecek data di file csv
bool cekDataCSV(const string &fileName)
{
    ifstream file(fileName);

    if (file.is_open())
    {
        // Cek apakah ada karakter yang tersedia untuk dibaca
        if (file.peek() != ifstream::traits_type::eof())
        {
            file.close();
            return true; // File CSV tidak kosong
        }
        file.close();
    }

    return false; // File CSV kosong
}
// Fungsi untuk menampilkan keranjang
void tampilkanKeranjang(const string &loggedInUsername)
{
    if (cekDataCSV("cart.csv"))
    {
        system("cls");
        cout << "Pesanan atas nama   : " << loggedInUsername << endl;
        cout << "--------------------------------------------\n";
        muatCsvKeranjang(loggedInUsername); 
        // Panggil fungsi muatCsvKeranjang untuk menampilkan data keranjang
    }
    else
    {
        cout << "Keranjang kosong." << endl;
    }
}
// Fungsi untuk menghapus keranjang
void hapusDariKeranjang(const string &loggedInUsername, int indeks)
{
    fstream file("cart.csv", ios::in | ios::out);
    if (file.is_open())
    {
        string line;
        stringstream updatedCsvData;
        getline(file, line); // Baca dan abaikan baris judul

        updatedCsvData << line << "\n";

        int currentIndeks = 1;
        bool indeksDitemukan = false;

        while (getline(file, line))
        {
            istringstream iss(line);
            string username, namaBunga;
            int jumlah, hargaPerItem, subtotal;

            if (getline(iss, username, ',') &&
                getline(iss, namaBunga, ',') &&
                (iss >> jumlah) &&
                (iss.ignore(), iss >> hargaPerItem) &&
                (iss.ignore(), iss >> subtotal))
            {
                if (username == loggedInUsername)
                {
                    if (currentIndeks == indeks)
                    {
                        indeksDitemukan = true;
                        // Item yang sesuai dengan indeks ditemukan, jangan masukkan ke dalam data yang diperbarui
                        cout << "Item dihapus dari keranjang.\n";
                    }
                    else
                    {
                        // Item yang sesuai dengan indeks ditemukan, masukkan ke dalam data yang diperbarui
                        updatedCsvData << username << "," << namaBunga << ","
                                       << jumlah << "," << hargaPerItem << ","
                                       << subtotal << "\n";
                    }
                }
                currentIndeks++;
            }
        }

        if (!indeksDitemukan)
        {
            cout << "Indeks tidak ditemukan. Tidak ada item yang dihapus dari keranjang.\n";
        }

        // Menggantikan isi file CSV dengan data yang diperbarui
        file.close();                                 // Tutup file untuk menghindari masalah
        file.open("cart.csv", ios::out | ios::trunc); // Buka file dalam mode penulisan ulang
        file << updatedCsvData.str();
        file.close();
    }
    else
    {
        cerr << "Gagal membuka file CSV untuk item keranjang.\n";
    }
}

//////////////////////////////////// FUNGSI CHECKOUT ////////////////////////////////////

// Fungsi untuk memuat keranjang riwayat ke file csv
void muatCsvRiwayatKeranjangCheckout(const string &loggedInUsername)
{
    ifstream file("checkout.csv");
    if (file.is_open())
    {
        string line;
        int id = 1;
        int totalHarga = 0;

        while (getline(file, line))
        {
            istringstream iss(line);
            string username, namaBunga;
            int jumlah;
            double hargaPerItem, subtotal;

            if (getline(iss, username, ',') &&
                getline(iss, namaBunga, ',') &&
                (iss >> jumlah) &&
                (iss.ignore(), iss >> hargaPerItem) &&
                (iss.ignore(), iss >> subtotal))
            {
                // Periksa apakah username di baris CSV sesuai dengan loggedInUsername
                if (username == loggedInUsername)
                {
                    cout << "No Indeks           : " << id << endl;
                    cout << "Username            : " << username << endl;
                    cout << "Nama Bunga          : " << namaBunga << endl;
                    cout << "Jumlah              : " << jumlah << endl;
                    cout << "Harga per item      : " << hargaPerItem << endl;
                    cout << "Total               : " << subtotal << endl;
                    cout << "--------------------------------------------\n";
                    totalHarga += subtotal;
                    id++; // Tingkatkan nilai id setiap kali mencetak baris
                }
            }
        }
        file.close();
    }
    else
    {
        cerr << "Gagal membuka file CSV keranjang untuk pembacaan.\n";
    }
}
// Fungsi untuk memuat keranjang checkout ke file csv
void muatCsvKeranjangCheckout(const string &loggedInUsername)
{
    ifstream file("cart.csv");
    if (file.is_open())
    {
        string line;
        int id = 1;

        cout << "Keranjang atas nama   : " << loggedInUsername << endl;
        cout << "--------------------------------------------\n";

        while (getline(file, line))
        {
            istringstream iss(line);
            string username, namaBunga;
            int jumlah;
            double hargaPerItem, subtotal;
            // string waiting = "Menunggu";

            if (getline(iss, username, ',') &&
                getline(iss, namaBunga, ',') &&
                (iss >> jumlah) &&
                (iss.ignore(), iss >> hargaPerItem) &&
                (iss.ignore(), iss >> subtotal))
            {
                if (username == loggedInUsername)
                {
                    cout << "No Indeks           : " << id << endl;
                    cout << "Username            : " << username << endl;
                    cout << "Nama Bunga          : " << namaBunga << endl;
                    cout << "Jumlah              : " << jumlah << endl;
                    cout << "Harga per item      : " << hargaPerItem << endl;
                    cout << "Total               : " << subtotal << endl;
                    // cout << "Status              : " << waiting << endl;
                    cout << "--------------------------------------------\n";
                    id++;
                }
            }
        }
        file.close();
    }
    else
    {
        cerr << "Gagal membuka file CSV keranjang untuk pembacaan.\n";
    }
}

// Fungsi untuk menghandle checkout keranjang
void handleCheckoutKeranjang(const string &loggedInUsername, int selectedIdx)
{
    fstream file("cart.csv", ios::in | ios::out);
    if (file.is_open())
    {
        string line;
        stringstream updatedCsvCart, insertCsvCheckout;
        getline(file, line); // Baca dan abaikan baris header

        updatedCsvCart << line << "\n";
        insertCsvCheckout << line << ",status\n"; // Tambahkan kolom 'status' pada header

        int currentIndex = 1;
        bool foundSelectedIdx = false; // Flag untuk menandai apakah indeks terpilih ditemukan

        while (getline(file, line))
        {
            istringstream iss(line);
            string username, namaBunga;
            int jumlah, hargaPerItem, subtotal;

            if (getline(iss, username, ',') &&
                getline(iss, namaBunga, ',') &&
                (iss >> jumlah) &&
                (iss.ignore(), iss >> hargaPerItem) &&
                (iss.ignore(), iss >> subtotal))
            {
                if (username == loggedInUsername)
                {
                    if (currentIndex == selectedIdx)
                    {
                        foundSelectedIdx = true; // Indeks terpilih ditemukan
                        // Pindahkan item terpilih ke checkout
                        insertCsvCheckout << username << "," << namaBunga << ","
                                          << jumlah << "," << hargaPerItem << ","
                                          << subtotal << ",menunggu\n"; // Setel status default menjadi "menunggu"
                    }
                    else
                    {
                        // Perbarui keranjang tanpa menghapus item non-terpilih
                        updatedCsvCart << username << "," << namaBunga << ","
                                       << jumlah << "," << hargaPerItem << ","
                                       << subtotal << "\n";
                    }

                    currentIndex++;
                }
            }
        }

        file.close();

        // Jika indeks terpilih tidak ditemukan, tampilkan pesan kesalahan
        if (!foundSelectedIdx)
        {
            cerr << "Indeks yang dipilih tidak ditemukan." << endl;
            return;
        }

        // Perbarui file keranjang
        file.open("cart.csv", ios::out | ios::trunc);
        file << updatedCsvCart.str();
        file.close();

        // Tambahkan item terpilih ke file checkout hanya jika itu item pertama
        file.open("checkout.csv", ios::out | ios::app);
        if (selectedIdx == 1)
        {
            file << insertCsvCheckout.str();
        }
        file.close();
    }
    else
    {
        cerr << "Gagal membuka file CSV untuk item keranjang." << endl;
    }
    cout << "Transaksi berhasil!" << endl;
}
// Fungsi untuk checkout keranjang
void checkoutKeranjang(const string &loggedInUsername)
{
    if (cekDataCSV("cart.csv"))
    {
        system("cls");
        cout << "--------------------------------------------\n";
        muatCsvKeranjangCheckout(loggedInUsername);

        cout << "Pilih No Indeks yang ingin di-checkout (0 untuk batal): ";
        int selectedIdx;
        cin >> selectedIdx;

        if (selectedIdx == 0)
        {
            cout << "Transaksi dibatalkan" << endl
                 << endl;
            return;
        }

        handleCheckoutKeranjang(loggedInUsername, selectedIdx);
    }
    else
    {
        cout << "Keranjang kosong." << endl;
    }
}
// Fungsi untuk menampilkan status checkout
void statusCheckout(const string &loggedInUsername)
{
    ifstream file("checkout.csv");
    if (file.is_open())
    {
        string line;
        int id = 1;
        system("cls");
        cout << "Status Checkout atas nama " << loggedInUsername << ":" << endl;
        cout << "--------------------------------------------\n";

        while (getline(file, line))
        {
            istringstream iss(line);
            string username, namaBunga, status;
            int jumlah;
            double hargaPerItem, subtotal;

            if (getline(iss, username, ',') &&
                getline(iss, namaBunga, ',') &&
                (iss >> jumlah) &&
                (iss.ignore(), iss >> hargaPerItem) &&
                (iss.ignore(), iss >> subtotal) &&
                (iss.ignore(), getline(iss, status, ',')))
            {
                if (username == loggedInUsername)
                {
                    cout << "No Indeks           : " << id << endl;
                    cout << "Username            : " << username << endl;
                    cout << "Nama Bunga          : " << namaBunga << endl;
                    cout << "Jumlah              : " << jumlah << endl;
                    cout << "Harga per item      : " << hargaPerItem << endl;
                    cout << "Total               : " << subtotal << endl;
                    cout << "Status              : " << status << endl;
                    cout << "--------------------------------------------\n";
                    id++;
                }
            }
        }

        file.close();
    }
    else
    {
        cerr << "Gagal membuka file CSV riwayat checkout untuk pembacaan.\n";
    }
}
// Fungsi untuk mengkonfirmasi pesanan
void konfirmasiPesananQueue()
{
    ifstream file("checkout.csv");
    if (file.is_open())
    {
        string line;
        stringstream updatedCsvData;
        int id = 1;
        bool confirmationNeeded = false; // Flag to check if confirmation is needed

        while (getline(file, line))
        {
            istringstream iss(line);
            string username, namaBunga, status;
            int jumlah;
            double hargaPerItem, subtotal;

            if (getline(iss, username, ',') &&
                getline(iss, namaBunga, ',') &&
                (iss >> jumlah) &&
                (iss.ignore(), iss >> hargaPerItem) &&
                (iss.ignore(), iss >> subtotal) &&
                (iss.ignore(), getline(iss, status, ',')))
            {
                system("cls");
                cout << "           List Pesanan Masuk              " << endl;
                cout << "--------------------------------------------\n";
                if (status == "menunggu") // Check if the status is "menunggu"
                {
                    confirmationNeeded = true; // Set the flag to true
                    cout << "Username            : " << username << endl;
                    cout << "Nama Bunga          : " << namaBunga << endl;
                    cout << "Jumlah              : " << jumlah << endl;
                    cout << "Harga per item      : " << hargaPerItem << endl;
                    cout << "Total               : " << subtotal << endl;
                    cout << "Status              : " << status << endl;
                    cout << "--------------------------------------------\n";

                    cout << "Konfirmasi pesanan untuk " << username << " (y/n): ";
                    char confirmation;
                    cin >> confirmation;

                    if (confirmation == 'y' || confirmation == 'Y')
                    {
                        // Update the status to "Diterima" for confirmed orders
                        status = "Diterima";
                    }
                    else if (confirmation == 'n' || confirmation == 'N')
                    {
                        // Update the status to "Ditolak" for rejected orders
                        status = "Ditolak";
                    }
                    else
                    {
                        cout << "Masukkan tidak dapat dipahami" << endl;
                    }
                }
            }

            // Append the updated entry to the stringstream
            updatedCsvData << username << "," << namaBunga << ","
                           << jumlah << "," << hargaPerItem << ","
                           << subtotal << "," << status << "\n";

            id++;
        }

        file.close();

        // Check if confirmation is needed before updating the file
        if (confirmationNeeded)
        {
            // Update the checkout.csv file with the modified data
            ofstream outFile("checkout.csv");
            outFile << updatedCsvData.str();
            outFile.close();
        }
        else
        {
            cout << "Tidak ada data yang perlu dikonfirmasi.\n";
        }
    }
    else
    {
        cerr << "Gagal membuka file CSV riwayat checkout untuk pembacaan.\n";
    }
}
// Fungsi untuk menampilkan isi checkout
void tampilkanIsiCheckout()
{
    ifstream file("checkout.csv");
    if (file.is_open())
    {
        string line;
        int id = 1;
        system("cls");
        cout << "    Data Riwayat Checkout Narelle Florist    " << endl;
        cout << "--------------------------------------------\n";

        while (getline(file, line))
        {
            istringstream iss(line);
            string username, namaBunga, status;
            int jumlah;
            double hargaPerItem, subtotal;

            if (getline(iss, username, ',') &&
                getline(iss, namaBunga, ',') &&
                (iss >> jumlah) &&
                (iss.ignore(), iss >> hargaPerItem) &&
                (iss.ignore(), iss >> subtotal) &&
                (iss.ignore(), getline(iss, status, ',')))
            {
                cout << "Username            : " << username << endl;
                cout << "Nama Bunga          : " << namaBunga << endl;
                cout << "Jumlah              : " << jumlah << endl;
                cout << "Harga per item      : " << hargaPerItem << endl;
                cout << "Total               : " << subtotal << endl;
                cout << "Status              : " << status << endl;
                cout << "--------------------------------------------\n";
                id++;
            }
        }

        file.close();
    }
    else
    {
        cerr << "Gagal membuka file CSV checkout untuk pembacaan.\n";
    }
}

//////////////////////////////////// FUNGSI MAIN ////////////////////////////////////////

// Fungsi utama admin
void Admin()
{
    bool loop = true;
    int targetIndex;
    while (loop)
    {
        while (login <= 3)
        {
            system("cls");
            header_login();
            cout << "Username : ";
            cin >> username;
            cout << "Password : ";
            cin >> password;
            if (username == "admin" && password == "123")
            {
                bool loop = true;
                while (loop)
                {
                    tampilanAdmin();
                    cout << "Masukkan Pilihan anda: ";
                    cin >> pilihan;
                    while (!cin >> pilihan)
                    {
                        cin.clear();
                        cin.ignore(100, '\n');
                        break;
                    }

                    // Memproses pilihan menu
                    switch (pilihan)
                    {
                    case 1:
                        tambahDataAkhir(head, length);
                        system("pause");
                        break;
                    case 2:
                        tampilkanData(head);
                        system("pause");
                        break;
                    case 3:
                        if (length > 0)
                        {
                            mergeSort(head);
                            tampilkanData(head);
                            system("pause");
                        }
                        else
                        {
                            cout << "Data bunga kosong." << endl;
                            system("pause");
                        }
                        break;
                    case 4:
                        if (length > 0)
                        {
                            char search_name[50];
                            system("cls");
                            cout << "Masukkan nama yang akan dicari: ";
                            cin.ignore();
                            cin.getline(search_name, sizeof(search_name));

                            searchAndPrintFlowers(search_name);
                            system("pause");
                        }
                        else
                        {
                            cout << "Data bunga kosong." << endl;
                            system("pause");
                        }
                        break;
                    case 5:
                        if (length > 0)
                        {
                            tampilkanData(head);
                            cout << "Masukkan indeks bunga yang ingin diupdate: ";
                            cin >> targetIndex;
                            system("cls");
                            updateDataByIndex(head, targetIndex);
                            system("pause");
                            break;
                        }
                        else
                        {
                            cout << "Data bunga kosong." << endl;
                            system("pause");
                        }
                        break;
                    case 6:
                        if (length > 0)
                        {
                            while (true)
                            {   
                                tampilkanData(head);
                                cout << "*Ketik 00 untuk kembali" << endl;
                                cout << "Masukkan indeks item yang ingin dihapus: ";
                                cin >> targetIndex;
                                if (cin.fail())
                                {
                                    cin.clear();
                                    cin.ignore(100, '\n');
                                    cout << "Jumlah harus berupa angka" << endl;
                                    system("pause");
                                    continue;
                                }
                                break;
                            }
                            if (targetIndex == 00)
                            {
                                system("pause");
                                break;
                            }
                            hapusDataByIndex(head, targetIndex);
                            system("pause");
                            break;
                        }
                        else
                        {
                            cout << "Data bunga kosong." << endl;
                            system("pause");
                        }
                        break;
                    case 7:
                        konfirmasiPesananQueue();
                        system("pause");
                        break;
                    case 8:
                        tampilkanIsiCheckout();
                        system("pause");
                        break;
                    case 9:
                        loop = false;
                        break;
                    default:
                        cout << endl;
                        cout << "Mohon maaf pilihan tidak tersedia" << endl;
                        cout.flush();
                        sleep(1);
                        break;
                    }
                    // #Gading: Masukkan data struct yang dimodifikasi ke dalam CSV dg pilihan apapun,
                    // kecuali Lihat Data (4), Sorting (5), Searching (6), dan Exit(11)
                    if (pilihan != 2 && pilihan != 3 && pilihan != 4 && pilihan != 7)
                    {
                        StructKeCSV_flower(head);
                    }
                }
                login = 3;
                break;
            }
            else
            {
                login++;
                sisaLogin = 4 - login;
                cout << endl;
                cout << "Login tidak valid !" << endl; // user dan pass salah
                cout << "Anda memiliki sisa " << sisaLogin << " kesempatan tersisa" << endl;
                cout.flush();
                sleep(1);
            }
        }
        if (login > 3)
        {
            system("cls");
            cout << "Anda telah diblokir untuk menu admin !!" << endl;
            cout.flush();
            sleep(2);
            return;
        }
        return;
    }
}
// Fungsi utama user
void User(const string &loggedInUsername)
{
    int indeks;
    system("cls");
    bool loop = true;
    while (loop)
    {
        tampilanUser();
        cout << "Masukkan pilihan anda : ";
        cin >> pilihan;
        while (!cin >> pilihan)
        {
            cin.clear();
            cin.ignore(100, '\n');
            break;
        }

        switch (pilihan)
        {
        case 1:
            // list bunga
            tampilkanData(head);
            system("pause");
            break;
        case 2:
            // order bunga
            tampilkanKeranjang(loggedInUsername);
            pesanBunga(head, loggedInUsername);
            system("pause");
            break;
        case 3:
            // keranjang pesanan
            tampilkanKeranjang(loggedInUsername);
            system("pause");
            break;
        case 4:
            // hapus keranjang
            int indeksHapus;
            while (true)
            {
                tampilkanKeranjang(loggedInUsername);
                cout << "*Ketik 00 untuk kembali" << endl;
                cout << "Masukkan indeks item yang ingin dihapus: ";
                cin >> indeksHapus;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Jumlah harus berupa angka" << endl;
                    system("pause");
                    continue;
                }
                break;
            }
            if (indeksHapus == 00)
            {
                system("pause");
                break;
            }
            hapusDariKeranjang(loggedInUsername, indeksHapus);
            system("pause");
            break;
        case 5:
            // checkout
            checkoutKeranjang(loggedInUsername);
            system("pause");
            break;
        case 6:
            // status checkout
            // checkoutKeranjang(loggedInUsername);
            statusCheckout(loggedInUsername);
            system("pause");
            break;
        case 7:
            // logout
            loop = false;
            break;
        default:
            cout << endl;
            cout << "Mohon maaf pilihan tidak tersedia" << endl;
            cout.flush();
            sleep(1);
        }
        break;
    }
    muatCsvKeranjang(loggedInUsername);
}
// Fungsi menu utama
int main()
{
    CSVKeStruct_flower(head);
    muatAkunDariCSV("akun.csv", headAkun);

    bool loop = true;
    while (loop)
    {
        menuAwal();
        cout << "Masukkan pilihan [1-4]  : ";
        cin >> pilihan;
        while (!cin >> pilihan)
        {
            cin.clear();
            cin.ignore(100, '\n');
            break;
        }

        switch (pilihan)
        {
        case 1:
            Admin();
            break;
        case 2:
            // registrasi
            {
                string username, password, confirmPassword;
                head_table();
                cout << "Masukkan username    : ";
                cin >> username;

                cout << "Masukkan password    : ";
                cin >> password;

                cout << "Konfirmasi password  : "; 
                cin >> confirmPassword;

                if (password == confirmPassword)
                {
                    tambahAkun(headAkun, username, password);
                    simpanAkunKeCSV("akun.csv", headAkun);
                    cout << endl;
                    system("pause");
                }
                else
                {
                    cout << endl;
                    cout << "Kata sandi dan konfirmasi kata sandi tidak cocok. Registrasi gagal.\n";
                    system("pause");
                }
                break;
            }
        case 3:
            // login
            {
                string username, password;
                head_table();
                cout << "Masukkan username  : ";
                cin >> username;
                cout << "Masukkan password  : ";
                cin >> password;
                if (loginUser(headAkun, username, password))
                {
                    cout << endl;
                    cout << "Login berhasil !!\n";
                    string loggedInUsername = username;
                    // muatCsvKeranjang(loggedInUsername);
                    system("pause");
                    do
                    {
                        User(loggedInUsername);
                    } while (pilihan != 7);

                    // Logout pengguna dengan menghapus username yang sedang login
                    loggedInUsername = "";
                }
                else
                {
                    cout << endl;
                    cout << "Login gagal. Username atau password salah.\n";
                    system("pause");
                }
                break;
            }
        case 4:
            loop = false;
            end_program();
            break;
        default:
            cout << endl;
            cout << "Mohon maaf pilihan tidak tersedia" << endl;
            cout.flush();
            sleep(1);
            break;
        }
    }
    // Dealokasi memori untuk linked list akun
    Akun *current = headAkun;
    while (current)
    {
        Akun *temp = current;
        current = current->next;
        delete temp;
    }
    return 0;
}
