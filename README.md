# Tugas Kecil 1 IF2211 - Strategi Algoritma

## LinkedIn Queens Game Solver (Iterative Brute Force)

**Identitas Pembuat:**

* **Nama:** Ega Luthfi Rais
* **NIM:** 13524115
* **Mata Kuliah:** IF2211 Strategi Algoritma

---

### Deskripsi Program

Program ini adalah solver untuk permainan logika "Queens" (yang populer di LinkedIn) yang diimplementasikan menggunakan bahasa C++ (Standard C++17).

Solusi menggunakan algoritma **Brute Force Murni** dengan pendekatan **Iteratif Odometer** (Base-N Counting). Pendekatan ini dipilih untuk melakukan enumerasi ruang solusi secara lengkap (exhaustive search) tanpa menggunakan rekursi, sehingga menghindari risiko stack overflow pada ukuran papan yang besar dan menjaga penggunaan memori tetap efisien.

### Fitur Utama

1. **Iterative Odometer Algorithm:** Menggunakan loop tunggal untuk enumerasi state dari `00...0` hingga `NN...N`.
2. **Efisiensi Memori:** Representasi papan menggunakan Array 1D.
3. **Validasi Input:** Modul Parser mendeteksi ketidakkonsistenan dimensi dan karakter ilegal.
4. **Visualisasi CLI:** Menampilkan proses pencarian dan solusi akhir di terminal.
5. **Telemetri Kinerja:** Menampilkan waktu eksekusi (ms) dan total iterasi.

---

### Persyaratan Sistem

* **Sistem Operasi:** Linux / WSL (Windows Subsystem for Linux) / macOS.
* **Compiler:** `g++` dengan dukungan C++17.
* **Build Tool:** `make`.

---

### Cara Kompilasi

Program dilengkapi dengan Makefile untuk mempermudah proses kompilasi. Pastikan Anda berada di direktori root proyek.

**1. Membangun Program (Build)**

```bash
make

```

Perintah ini akan mengompilasi seluruh source code dan menghasilkan file executable di folder `bin/solver`.

**2. Membersihkan Build (Clean)**

```bash
make clean

```

Perintah ini akan menghapus file objek (`.o`) dan file executable.

---

### Cara Menjalankan

Setelah proses kompilasi berhasil, jalankan program dengan perintah berikut:

```bash
./bin/solver

```

**Alur Penggunaan:**

1. Program akan memindai dan menampilkan daftar file `.txt` yang ada di dalam folder `test/`.
2. Masukkan nama file input (contoh: `tc_8x8_valid`).
3. Tentukan tingkat kecepatan visualisasi (input `1` untuk realtime, atau angka besar seperti `10000` untuk mode cepat).
4. Program akan memproses algoritma dan menampilkan hasil akhir beserta statistik waktu eksekusi.
5. Pengguna diberikan opsi untuk menyimpan solusi ke dalam file teks.

---

### Format File Input

File input harus berupa file teks (`.txt`) yang diletakkan di dalam folder `test/`. Format isi file merepresentasikan papan permainan :

* Setiap baris mewakili baris pada papan.
* Setiap karakter mewakili **Wilayah Warna**.
* Karakter yang diizinkan adalah huruf kapital `A` - `Z`.
* Jumlah baris harus sama dengan jumlah karakter per baris ().

**Contoh Input (4x4):**

```text
AABB
AABB
CCDD
CCDD

```

---

### Struktur Direktori

```text
.
├── Makefile            # Skrip kompilasi
├── README.md           # Dokumentasi proyek
├── bin/                # Direktori output executable
│   └── solver
├── src/                # Kode sumber implementasi (.cpp)
│   ├── main.cpp
│   ├── solver.cpp
│   ├── board.cpp
│   └── parser.cpp
├── include/            # File header (.hpp)
│   ├── solver.hpp
│   ├── board.hpp
│   ├── parser.hpp
│   └── globals.hpp
└── test/               # Kumpulan file uji (.txt)
    ├── tc_8x8_valid.txt
    ├── tc_3x3_impossible.txt
    ├── tc_not_square.txt
    └── tc_bad_char.txt

```

---

### Penjelasan Singkat Algoritma

Algoritma bekerja dengan memandang papan permainan sebagai sistem bilangan basis- dengan  digit (posisi ratu di setiap baris).

1. **Inisialisasi:** Semua ratu ditempatkan di kolom 0.
2. **Validasi:** Memeriksa apakah konfigurasi saat ini memenuhi aturan (satu ratu per warna, satu ratu per kolom, tidak bersentuhan).
3. **Increment:** Jika tidak valid, posisi ratu pada baris terakhir digeser ke kanan.
4. **Carry-Over:** Jika ratu di baris terakhir mencapai batas kanan, posisi di-reset ke 0 dan ratu di baris sebelumnya digeser (mekanisme odometer).
5. **Terminasi:** Jika proses carry-over mencapai baris pertama dan tidak bisa digeser lagi, maka seluruh ruang pencarian telah habis.