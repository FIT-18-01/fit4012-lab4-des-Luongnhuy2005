#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Giả sử bạn đã có hàm mã hóa một khối 64-bit:
// string encryptDESBlock(string block, string key);

int main() {
    int mode;
    string full_plaintext, key;

    // 1. Đọc dữ liệu theo đúng "contract" của script test
    if (!(cin >> mode)) return 0;
    cin >> full_plaintext;
    cin >> key;

    if (mode == 1) {
        string final_ciphertext = "";

        // 2. Chia khối và thực hiện Zero Padding
        for (size_t i = 0; i < full_plaintext.length(); i += 64) {
            string block = full_plaintext.substr(i, 64);

            // Nếu khối cuối cùng thiếu bit, thêm '0' cho đủ 64 bit
            if (block.length() < 64) {
                block.append(64 - block.length(), '0');
            }

            // 3. Mã hóa từng khối và cộng dồn vào kết quả
            // Thay 'encryptDESBlock' bằng tên hàm mã hóa 64-bit thực tế của bạn
            string encrypted_block = encryptDESBlock(block, key); 
            final_ciphertext += encrypted_block;
        }

        // 4. In kết quả cuối cùng (Chỉ in chuỗi nhị phân, không kèm chữ)
        cout << final_ciphertext << endl;
    }

    return 0;
}