#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <fstream>
#include <string>

#pragma comment(lib, "crypt32.lib")

int main() {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cout << "[ERROR] Failed to retrieve system processes. Exiting safely.\n";
        return 1;
    }

    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(PROCESSENTRY32);

    std::ofstream logFile("data.bin", std::ios::binary);
    if (!logFile.is_open()) {
        std::cout << "[ERROR] Could not create log file.\n";
        CloseHandle(hSnapshot);
        return 1;
    }

    if (Process32First(hSnapshot, &processInfo)) {
        do {
            std::string cleanExe((char*)processInfo.szExeFile);
            std::string processLine = cleanExe + " | PID: " + std::to_string(processInfo.th32ProcessID);

            DATA_BLOB inputBox;
            inputBox.pbData = (BYTE*)processLine.c_str();
            inputBox.cbData = processLine.length() + 1;

            DATA_BLOB encryptedBox;

            BOOL isEncrypted = CryptProtectData(
                &inputBox,
                NULL,
                NULL, NULL, NULL, 0,
                &encryptedBox
            );

            if (isEncrypted) {
                logFile.write((char*)&encryptedBox.cbData, sizeof(encryptedBox.cbData));
                logFile.write((char*)encryptedBox.pbData, encryptedBox.cbData);
                LocalFree(encryptedBox.pbData);
            }

        } while (Process32Next(hSnapshot, &processInfo));
    }

    logFile.close();
    CloseHandle(hSnapshot);

    std::cout << "[SUCCESS] All running processes encrypted and secured into 'data.bin'.\n";

    std::ifstream fileRead("data.bin", std::ios::binary);
    std::cout << "\n--- Deserializing and Decrypting 'data.bin' ---\n";

    if (fileRead.is_open()) {
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
                NULL,
                NULL, NULL, NULL, 0,
                &decryptedBox
            );

            if (isDecrypted) {
                std::cout << "Decrypted Process: " << (char*)decryptedBox.pbData << "\n";
                LocalFree(decryptedBox.pbData);
            } else {
                std::cout << "[ERROR] Decryption failed for a record. Code: " << GetLastError() << "\n";
            }
        }
        fileRead.close();
    } else {
        std::cout << "[ERROR] Could not open data.bin for reading!\n";
    }

    return 0;
}
