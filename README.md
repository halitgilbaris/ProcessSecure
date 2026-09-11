
<p align="center">
  <video src="https://github.com/user-attachments/assets/5b0584d1-40a3-44b8-8d3e-10fd098a93e0" autoplay muted loop playsinline width="100%" style="border-radius: 8px;">
  </video>
</p>






A lightweight, low-level **C++** security tool designed for Windows environments. **ProcCrypt** takes an active system snapshot of running processes, extracts their details, and securely serializes them into an encrypted binary file using enterprise-grade Windows Data Protection API (DPAPI). 

The repository also includes an independent decryption module to safely read, verify, and output the data.

---

## 🚀 Key Features

* **Active Process Auditing:** Utilizes the native Windows `Toolhelp32` API to capture active processes and their respective Process IDs (PID) in real-time.
* **Hardware-Bound Encryption:** Leverages **Windows DPAPI (`CryptProtectData`)** to encrypt process logs. The encrypted data is mathematically tied to the specific Windows user session, making it unreadable even if moved to another machine.
* **Safe Binary Serialization:** Instead of vulnerable plain-text logging, data is written using binary stream operations (`std::ios::binary`) to protect against tampering and file corruption.
* **Independent Decryption Module:** Features a dedicated module that decodes the `.bin` container, processes the raw bytes through `CryptUnprotectData`, and prints the verified system state.
* **ANSI & Compiler Optimization:** Tailored specifically for `g++` environments with explicit memory casting and safe byte-boundary checking.

---


## 🤖 AI Collaboration / Yapay Zeka Kullanımı

I utilized an AI assistant as a pair programmer and learning tool during this project. It helped me understand complex C++ low-level concepts, debug strict compiler type-mismatches (such as handling WCHAR/CHAR boundaries), and optimize binary file I/O operations while building my foundational skills in systems programming.

*Bu projeyi geliştirirken C++ kavramlarını daha iyi anlamak, Windows API yapısını öğrenmek, derleyici hatalarını çözmek ve mantıksal yapıyı kurmak adına bir yapay zeka asistanından destek aldım.*

---

## ⚙️ License & Copyright

* **Copyright:** Copyright (c) 2026 bhalitgil
* **License:** Licensed under the **MIT License**.

---

## ✉️ Contact & Feedback

If you have any questions, suggestions, or bug reports regarding this tool, feel free to reach out directly at: **bhalitgil250708@gmail.com**
