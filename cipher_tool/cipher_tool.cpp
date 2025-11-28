#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib> // system("cls") ve exit() için

using namespace std;

// ==========================================
// RENK TANIMLAMALARI
// ==========================================
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string GOLD = "\033[33m";
const string WHITE = "\033[37m";
const string BLUE = "\033[34m"; // Yeni renk: Navigasyon icin mavi
const string BOLD = "\033[1m";

// ==========================================
// YARDIMCI ARAÇLAR
// ==========================================

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Ortak Çıkış Fonksiyonu (Her yerden çağrılabilir)
void exitApp() {
    cout << "\n" << RED << ">> Program güvenli bir şekilde kapatılıyor..." << RESET << "\n";
    cout << GOLD << ">> Murat Crypto'yu tercih ettiginiz icin tesekkurler!" << RESET << "\n\n";
    exit(0); // Programı anında sonlandırır
}

void pauseScreen() {
    cout << "\n" << BLUE << "Ana menuye donmek icin Enter'a basin..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void printLogo() {
    cout << GREEN << BOLD;
    cout << "  __  __ _   _ ____    _  _____   ____ ______   ______  _____ ___  \n";
    cout << " |  \\/  | | | |  _ \\  / \\|_   _| / ___|  _ \\ \\ / /  _ \\|_   _/ _ \\ \n";
    cout << " | |\\/| | | | | |_) |/ _ \\ | |  | |   | |_) \\ V /| |_) | | || | | |\n";
    cout << " | |  | | |_| |  _ <| ___ || |  | |___|  _ < | | |  __/  | || |_| |\n";
    cout << " |_|  |_|\\___/|_| \\_/_/   \\|_|   \\____|_| \\_\\|_| |_|     |_| \\___/ \n";
    cout << RESET;
    cout << "\n" << GOLD << "          >> GUVENLI ILETISIM ARACI v5.0 <<          " << RESET << "\n";
    cout << WHITE << "====================================================================" << RESET << "\n\n";
}

// ==========================================
// ALGORİTMALAR
// ==========================================

string caesarCipher(string text, int shift, bool encrypt) {
    string result = "";
    if (!encrypt) shift = -shift;
    while (shift < 0) shift += 26;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char(int(c - base + shift) % 26 + base);
        }
        else {
            result += c;
        }
    }
    return result;
}

string xorCipher(string text, char key) {
    string result = text;
    for (int i = 0; i < text.size(); i++) {
        result[i] = text[i] ^ key;
    }
    return result;
}

string atbashCipher(string text) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            if (isupper(c)) result += char('Z' - (c - 'A'));
            else result += char('z' - (c - 'a'));
        }
        else {
            result += c;
        }
    }
    return result;
}

string vigenereCipher(string text, string key, bool encrypt) {
    string result = "";
    int keyIndex = 0;
    for (auto& c : key) c = toupper(c);
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int shift = key[keyIndex % key.size()] - 'A';
            if (!encrypt) shift = -shift;
            while (shift < 0) shift += 26;
            result += char(int(c - base + shift) % 26 + base);
            keyIndex++;
        }
        else {
            result += c;
        }
    }
    return result;
}

// ==========================================
// SAYFA FONKSİYONLARI
// ==========================================

// 3. SAYFA: İŞLEM EKRANI
void performOperation(int method) {
    clearScreen();
    printLogo();

    string methodName = "";
    if (method == 1) methodName = "SEZAR SIFRELEME";
    else if (method == 2) methodName = "XOR SIFRELEME";
    else if (method == 3) methodName = "ATBASH SIFRELEME";
    else if (method == 4) methodName = "VIGENERE SIFRELEME";

    cout << WHITE << ">>> SECILEN YONTEM: " << GOLD << methodName << RESET << "\n";
    cout << "--------------------------------------\n";
    cout << GOLD << "[1]" << WHITE << " Sifre Olustur\n";
    cout << GOLD << "[2]" << WHITE << " Sifre Coz\n";
    cout << "--------------------------------------\n";
    cout << BLUE << "[9]" << WHITE << " Ana Menuye Don\n";
    cout << RED << "[0]" << WHITE << " PROGRAMI KAPAT\n"; // Doğrudan çıkış

    int action;
    cout << "\n" << GREEN << "Seciminiz >> " << RESET;
    if (!(cin >> action)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); return; }

    if (action == 0) exitApp(); // Buradan çıkış yapılırsa
    if (action == 9) return;    // Geri dönülürse

    cin.ignore();
    string inputText, resultText;

    cout << "\n" << WHITE << "Metni Girin: " << RESET;
    getline(cin, inputText);

    // Algoritmalar
    if (method == 1) {
        int key;
        cout << GOLD << "Anahtar Sayi Girin: " << RESET;
        cin >> key;
        resultText = caesarCipher(inputText, key, (action == 1));
    }
    else if (method == 2) {
        char key;
        cout << GOLD << "Anahtar Karakter Girin: " << RESET;
        cin >> key;
        resultText = xorCipher(inputText, key);
    }
    else if (method == 3) {
        resultText = atbashCipher(inputText);
    }
    else if (method == 4) {
        string key;
        cout << GOLD << "Anahtar Kelime Girin: " << RESET;
        cin >> key;
        resultText = vigenereCipher(inputText, key, (action == 1));
    }

    cout << "\n" << WHITE << "--------------------------------------------------" << RESET << "\n";
    if (action == 1) cout << ">>> " << RED << "SONUC: " << resultText << RESET << endl;
    else cout << ">>> " << GREEN << "SONUC: " << resultText << RESET << endl;
    cout << WHITE << "--------------------------------------------------" << RESET << "\n";

    pauseScreen();
}

// 2. SAYFA: ANA MENU
void showMainMenu() {
    while (true) {
        clearScreen();
        printLogo();

        cout << WHITE << "Lutfen bir sifreleme yontemi secin:\n\n" << RESET;
        cout << GOLD << "[1]" << WHITE << " Sezar Sifreleme\n";
        cout << GOLD << "[2]" << WHITE << " XOR Sifreleme\n";
        cout << GOLD << "[3]" << WHITE << " Atbash\n";
        cout << GOLD << "[4]" << WHITE << " Vigenere\n";
        cout << "---------------------------\n";
        cout << BLUE << "[9]" << WHITE << " Giris Ekranina Don\n"; // Geri butonu
        cout << RED << "[0]" << WHITE << " PROGRAMI KAPAT\n";     // Çıkış butonu

        int choice;
        cout << "\n" << GREEN << "Seciminiz >> " << RESET;
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) exitApp(); // Buradan çıkış
        if (choice == 9) break;     // Giriş ekranına döner

        if (choice >= 1 && choice <= 4) {
            performOperation(choice);
        }
    }
}

// 1. SAYFA: GİRİŞ EKRANI
int main() {
    while (true) {
        clearScreen();
        printLogo();

        cout << GOLD << "       HOŞGELDİNİZ       " << RESET << "\n";
        cout << "-------------------------\n";
        cout << GREEN << "[1]" << WHITE << " GIRIS YAP" << RESET << "\n";
        cout << RED << "[0]" << WHITE << " CIKIS YAP" << RESET << "\n";

        int loginChoice;
        cout << "\n" << WHITE << "Seciminiz >> " << RESET;

        if (!(cin >> loginChoice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (loginChoice == 1) {
            showMainMenu();
        }
        else if (loginChoice == 0) {
            exitApp(); // Buradan çıkış
        }
    }
    return 0;
}