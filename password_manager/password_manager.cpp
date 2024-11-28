#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;

// XOR encryption/decryption (simple demonstration, not for production use)
string encryptDecrypt(string data, char key = 'K') {
    string output = data;
    for (int i = 0; i < data.size(); i++) {
        output[i] = data[i] ^ key;
    }
    return output;
}

// Function to load passwords from file
map<string, string> loadPasswords(const string& filename) {
    map<string, string> passwords;
    ifstream file(filename);
    if (file.is_open()) {
        string service, encrypted_password;
        while (file >> service >> encrypted_password) {
            passwords[service] = encrypted_password;
        }
        file.close();
    }
    return passwords;
}

// Function to save passwords to file
void savePasswords(const map<string, string>& passwords, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : passwords) {
            file << entry.first << " " << entry.second << endl;
        }
        file.close();
    }
}

// Function to add a new password
void addPassword(map<string, string>& passwords) {
    string service, password;
    cout << "Enter service name: ";
    cin >> service;
    cout << "Enter password: ";
    cin >> password;
    passwords[service] = encryptDecrypt(password);
    cout << "Password added successfully!" << endl;
}

// Function to retrieve a password
void getPassword(const map<string, string>& passwords) {
    string service;
    cout << "Enter service name: ";
    cin >> service;
    auto it = passwords.find(service);
    if (it != passwords.end()) {
        cout << "Password for " << service << ": " << encryptDecrypt(it->second) << endl;
    } else {
        cout << "Service not found!" << endl;
    }
}

// Function to delete a password
void deletePassword(map<string, string>& passwords) {
    string service;
    cout << "Enter service name to delete: ";
    cin >> service;
    if (passwords.erase(service)) {
        cout << "Password deleted successfully!" << endl;
    } else {
        cout << "Service not found!" << endl;
    }
}

// Menu interface
void showMenu() {
    cout << "1. Add Password" << endl;
    cout << "2. Get Password" << endl;
    cout << "3. Delete Password" << endl;
    cout << "4. Exit" << endl;
}

int main() {
    const string filename = "passwords.txt";
    map<string, string> passwords = loadPasswords(filename);

    int choice;
    while (true) {
        showMenu();
        cout << "Choose an option: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addPassword(passwords);
                break;
            case 2:
                getPassword(passwords);
                break;
            case 3:
                deletePassword(passwords);
                break;
            case 4:
                savePasswords(passwords, filename);
                cout << "Goodbye!" << endl;
                exit(0);
            default:
                cout << "Invalid choice, try again." << endl;
        }
    }
    return 0;
}
