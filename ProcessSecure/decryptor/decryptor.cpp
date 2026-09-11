#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

#pragma comment(lib, "crypt32.lib")

int main() {
    std::ifstream fileRead("data.bin", std::ios::binary);
    std::ofstream fileWrite("data.txt", std::ios::app);

    if (!fileRead.is_open()) {
        std::cout << "[ERROR] Could not open data.bin!\n";
        return 1;
    }

    if (!fileWrite.is_open()) {
        std::cout << "[ERROR] Could not create data.txt!\n";
        fileRead.close();
        return 1;
    }

    DWORD dataSize = 0;

    while (fileRead.read((char*)&dataSize, sizeof(dataSize))) {
        std::string encryptedData;
        encryptedData.resize(dataSize);
        fileRead.read(encryptedData.data(), dataSize);

        DATA_BLOB fileBox;
        fileBox.pbData = (BYTE*)encryptedData.c_str();
        fileBox.cbData = dataSize;

        DATA_BLOB decryptedBox;

        BOOL isDecrypted = CryptUnprotectData(
            &fileBox,
            NULL, NULL, NULL, NULL, 0,
            &decryptedBox
        );

        if (isDecrypted) {
            std::cout << "Decrypted successfully\n";
            
            std::string finalText = (char*)decryptedBox.pbData;
            fileWrite << finalText << "\n";

            LocalFree(decryptedBox.pbData);
        } else {
            std::cout << "[ERROR] Decryption failed! Error Code: " << GetLastError() << "\n";
        }
    }

    fileRead.close();
    fileWrite.close();
    
    std::cout << "[SUCCESS] Decryption process complete. Data saved into 'data.txt'.\n";
    return 0;
}
