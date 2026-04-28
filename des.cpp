#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <sstream>
using namespace std;

// Helper function: Convert decimal to 4-bit binary string
string convert_decimal_to_binary(int decimal) {
    return bitset<4>(decimal).to_string();
}

// Helper function: Convert binary string to decimal
int convert_binary_to_decimal(const string& binary) {
    return stoi(binary, nullptr, 2);
}

// Helper function: XOR two binary strings
string Xor(const string& a, const string& b) {
    string result = "";
    for (size_t i = 0; i < b.size(); i++) {
        result += (a[i] != b[i]) ? '1' : '0';
    }
    return result;
}

// Initial Permutation (IP)
string initial_permutation(const string& input) {
    const int initial_permutation[64] = {
        58,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7
    };

    string permuted = "";
    for (int i = 0; i < 64; i++) {
        permuted += input[initial_permutation[i] - 1];
    }
    return permuted;
}

// Inverse Initial Permutation (IP^-1)
string inverse_initial_permutation(const string& input) {
    const int inverse_permutation[64] = {
        40,8,48,16,56,24,64,32,
        39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,
        37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,
        35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,
        33,1,41,9,49,17,57,25
    };

    string permuted = "";
    for (int i = 0; i < 64; i++) {
        permuted += input[inverse_permutation[i] - 1];
    }
    return permuted;
}

class KeyGenerator {
private:
    string key;
    vector<string> roundKeys;

    // PC1 Table
    const int pc1[56] = {
        57,49,41,33,25,17,9, 
        1,58,50,42,34,26,18, 
        10,2,59,51,43,35,27, 
        19,11,3,60,52,44,36,		 
        63,55,47,39,31,23,15, 
        7,62,54,46,38,30,22, 
        14,6,61,53,45,37,29, 
        21,13,5,28,20,12,4 
    };

    // PC2 Table
    const int pc2[48] = { 
        14,17,11,24,1,5, 
        3,28,15,6,21,10, 
        23,19,12,4,26,8, 
        16,7,27,20,13,2, 
        41,52,31,37,47,55, 
        30,40,51,45,33,48, 
        44,49,39,56,34,53, 
        46,42,50,36,29,32 
    };

    string shift_left_once(const string& key_chunk) {
        return key_chunk.substr(1) + key_chunk[0];
    }

    string shift_left_twice(string key_chunk) {
        key_chunk = shift_left_once(key_chunk);
        return shift_left_once(key_chunk);
    }

public:
    KeyGenerator(const string& input_key) : key(input_key) {}

    void generateRoundKeys(bool verbose = false) {
        roundKeys.clear();

        // 1. Apply PC1 permutation
        string permutedKey = "";
        for (int i = 0; i < 56; ++i) {
            permutedKey += key[pc1[i] - 1];
        }

        // 2. Split into left and right halves
        string left = permutedKey.substr(0, 28);
        string right = permutedKey.substr(28, 28);

        // 3. Generate 16 round keys
        for (int i = 0; i < 16; ++i) {
            if (i == 0 || i == 1 || i == 8 || i == 15) {
                left = shift_left_once(left);
                right = shift_left_once(right);
            } else {
                left = shift_left_twice(left);
                right = shift_left_twice(right);
            }

            // 4. Combine halves
            string combinedKey = left + right;

            // 5. Apply PC2 permutation
            string roundKey = "";
            for (int j = 0; j < 48; ++j) {
                roundKey += combinedKey[pc2[j] - 1];
            }

            roundKeys.push_back(roundKey);

            // Optional: print key
            if (verbose) {
                cout << "Key " << i + 1 << ": " << roundKey << endl;
            }
        }
    }

    const vector<string>& getRoundKeys() const {
        return roundKeys;
    }
};

// Class to perform DES Feistel rounds
class DES {
    private:
        // Expansion table to expand 32 bits to 48 bits
        const int expansion_table[48] = {
            32,1,2,3,4,5,4,5,
            6,7,8,9,8,9,10,11,
            12,13,12,13,14,15,16,17,
            16,17,18,19,20,21,20,21,
            22,23,24,25,24,25,26,27,
            28,29,28,29,30,31,32,1
        };
    
        // Permutation table after S-box substitution
        const int permutation_tab[32] = {
            16,7,20,21,29,12,28,17,
            1,15,23,26,5,18,31,10,
            2,8,24,14,32,27,3,9,
            19,13,30,6,22,11,4,25
        };
    
        // S-boxes (8 boxes)
        const int substition_boxes[8][4][16] = {{ 
            14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7, 
            0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8, 
            4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0, 
            15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
        }, 
        { 
            15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10, 
            3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5, 
            0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15, 
            13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 
        }, 
        { 
            10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8, 
            13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1, 
            13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7, 
            1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 
        }, 
        { 
            7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15, 
            13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9, 
            10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4, 
            3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 
        }, 
        { 
            2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9, 
            14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6, 
            4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14, 
            11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 
        }, 
        { 
            12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11, 
            10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8, 
            9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6, 
            4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 
        }, 
        { 
            4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1, 
            13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6, 
            1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2, 
            6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 
        }, 
        { 
            13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7, 
            1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2, 
            7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8, 
            2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 
        }};
    
        vector<string> round_keys;
    
    public:
        DES(const vector<string>& keys) : round_keys(keys) {}
    
        string encrypt(const string& input) {
            // Apply initial permutation
            string perm = initial_permutation(input);
    
            // Split into left and right parts
            string left = perm.substr(0, 32);
            string right = perm.substr(32, 32);
    
            // 16 Feistel rounds
            for (int i = 0; i < 16; i++) {
                // Expand right half to 48 bits
                string right_expanded = "";
                for (int j = 0; j < 48; j++) {
                    right_expanded += right[expansion_table[j] - 1];
                }
    
                // XOR with round key
                string xored = Xor(round_keys[i], right_expanded);
    
                // S-box substitution
                string res = "";
                for (int j = 0; j < 8; j++) {
                    string row1 = xored.substr(j * 6, 1) + xored.substr(j * 6 + 5, 1);
                    int row = convert_binary_to_decimal(row1);
    
                    string col1 = xored.substr(j * 6 + 1, 4);
                    int col = convert_binary_to_decimal(col1);
    
                    int val = substition_boxes[j][row][col];
                    res += convert_decimal_to_binary(val);
                }
    
                // Permutation after S-box
                string perm2 = "";
                for (int j = 0; j < 32; j++) {
                    perm2 += res[permutation_tab[j] - 1];
                }
    
                // XOR permuted result with left, then swap
                string new_right = Xor(perm2, left);
                left = right;
                right = new_right;
            }
    
            // Swap final halves
            string combined_text = right + left;
    
            // Apply inverse initial permutation
            string ciphertext = inverse_initial_permutation(combined_text);
    
            return ciphertext;
        }

        // Decrypt function - uses round keys in reverse order
        string decrypt(const string& input) {
            // Apply initial permutation
            string perm = initial_permutation(input);
    
            // Split into left and right parts
            string left = perm.substr(0, 32);
            string right = perm.substr(32, 32);
    
            // 16 Feistel rounds (using round keys in reverse order)
            for (int i = 0; i < 16; i++) {
                // Expand right half to 48 bits
                string right_expanded = "";
                for (int j = 0; j < 48; j++) {
                    right_expanded += right[expansion_table[j] - 1];
                }
    
                // XOR with round key (in reverse order for decryption)
                string xored = Xor(round_keys[15 - i], right_expanded);
    
                // S-box substitution
                string res = "";
                for (int j = 0; j < 8; j++) {
                    string row1 = xored.substr(j * 6, 1) + xored.substr(j * 6 + 5, 1);
                    int row = convert_binary_to_decimal(row1);
    
                    string col1 = xored.substr(j * 6 + 1, 4);
                    int col = convert_binary_to_decimal(col1);
    
                    int val = substition_boxes[j][row][col];
                    res += convert_decimal_to_binary(val);
                }
    
                // Permutation after S-box
                string perm2 = "";
                for (int j = 0; j < 32; j++) {
                    perm2 += res[permutation_tab[j] - 1];
                }
    
                // XOR permuted result with left, then swap
                string new_right = Xor(perm2, left);
                left = right;
                right = new_right;
            }
    
            // Swap final halves
            string combined_text = right + left;
    
            // Apply inverse initial permutation
            string plaintext = inverse_initial_permutation(combined_text);
    
            return plaintext;
        }
};

// Convert hex string to binary string
string hex_to_binary(const string& hex) {
    string binary = "";
    for (char c : hex) {
        int val;
        if (c >= '0' && c <= '9') val = c - '0';
        else if (c >= 'A' && c <= 'F') val = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') val = c - 'a' + 10;
        else continue;
        binary += bitset<4>(val).to_string();
    }
    return binary;
}

// Convert binary string to hex string
string binary_to_hex(const string& binary) {
    string hex = "";
    for (size_t i = 0; i < binary.size(); i += 4) {
        string nibble = binary.substr(i, 4);
        int val = stoi(nibble, nullptr, 2);
        hex += "0123456789ABCDEF"[val];
    }
    return hex;
}

// Convert string to binary (ASCII)
string string_to_binary(const string& str) {
    string binary = "";
    for (char c : str) {
        binary += bitset<8>(c).to_string();
    }
    return binary;
}

// Convert binary to string (ASCII)
string binary_to_string(const string& binary) {
    string str = "";
    for (size_t i = 0; i < binary.size(); i += 8) {
        string byte = binary.substr(i, 8);
        char c = static_cast<char>(stoi(byte, nullptr, 2));
        str += c;
    }
    return str;
}

// Zero padding - pad to multiple of 64 bits (8 bytes)
string zero_pad(const string& binary) {
    int remainder = binary.size() % 64;
    if (remainder == 0) return binary;
    int padding_needed = 64 - remainder;
    return binary + string(padding_needed, '0');
}

// Remove zero padding
string zero_unpad(const string& binary) {
    // Find the last '1' bit to determine actual data length
    int last_one = -1;
    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            last_one = i;
            break;
        }
    }
    
    if (last_one == -1) {
        return binary;
    }
    
    // Calculate actual data length (round up to nearest byte)
    int byte_pos = last_one / 8;
    return binary.substr(0, (byte_pos + 1) * 8);
}

// Process multiple blocks - encryption
string encrypt_multi_block(const string& plaintext, const string& key_str, bool verbose = false) {
    // Convert key to binary
    string key_binary;
    if (key_str.size() == 8) {
        key_binary = string_to_binary(key_str);
    } else if (key_str.size() == 16) {
        // TripleDES: use first 8 bytes for key generation
        key_binary = string_to_binary(key_str.substr(0, 8));
    } else if (key_str.size() == 64) {
        key_binary = key_str;
    } else {
        // Pad or truncate to 8 bytes
        string key_padded = key_str;
        while (key_padded.size() < 8) key_padded += '0';
        key_binary = string_to_binary(key_padded.substr(0, 8));
    }
    
    // Generate round keys
    KeyGenerator keygen(key_binary);
    keygen.generateRoundKeys(verbose);
    vector<string> roundKeys = keygen.getRoundKeys();
    
    // Create DES object
    DES des(roundKeys);
    
    // Convert plaintext to binary
    string plaintext_binary = string_to_binary(plaintext);
    
    // Apply zero padding
    string padded_plaintext = zero_pad(plaintext_binary);
    
    // Encrypt each block
    string ciphertext_binary = "";
    for (size_t i = 0; i < padded_plaintext.size(); i += 64) {
        string block = padded_plaintext.substr(i, 64);
        string encrypted_block = des.encrypt(block);
        ciphertext_binary += encrypted_block;
    }
    
    return binary_to_hex(ciphertext_binary);
}

// Process multiple blocks - decryption
string decrypt_multi_block(const string& ciphertext_hex, const string& key_str, bool verbose = false) {
    // Convert key to binary
    string key_binary;
    if (key_str.size() == 8) {
        key_binary = string_to_binary(key_str);
    } else if (key_str.size() == 16) {
        // TripleDES: use first 8 bytes for key generation
        key_binary = string_to_binary(key_str.substr(0, 8));
    } else if (key_str.size() == 64) {
        key_binary = key_str;
    } else {
        // Pad or truncate to 8 bytes
        string key_padded = key_str;
        while (key_padded.size() < 8) key_padded += '0';
        key_binary = string_to_binary(key_padded.substr(0, 8));
    }
    
    // Generate round keys
    KeyGenerator keygen(key_binary);
    keygen.generateRoundKeys(verbose);
    vector<string> roundKeys = keygen.getRoundKeys();
    
    // Create DES object
    DES des(roundKeys);
    
    // Convert ciphertext from hex to binary
    string ciphertext_binary = hex_to_binary(ciphertext_hex);
    
    // Decrypt each block
    string plaintext_binary = "";
    for (size_t i = 0; i < ciphertext_binary.size(); i += 64) {
        string block = ciphertext_binary.substr(i, 64);
        string decrypted_block = des.decrypt(block);
        plaintext_binary += decrypted_block;
    }
    
    // Remove zero padding
    string unpadded_plaintext = zero_unpad(plaintext_binary);
    
    return binary_to_string(unpadded_plaintext);
}

// Print usage
void print_usage() {
    cout << "Usage: des <mode> <input> <key>" << endl;
    cout << "Modes:" << endl;
    cout << "  encrypt <plaintext> <key>   - Encrypt plaintext" << endl;
    cout << "  decrypt <ciphertext> <key>  - Decrypt ciphertext (hex)" << endl;
    cout << endl;
    cout << "Examples:" << endl;
    cout << "  des encrypt \"HelloWorld\" \"12345678\"" << endl;
    cout << "  des decrypt \"85E813540F0AB405\" \"12345678\"" << endl;
}

int main(int argc, char* argv[]) {
    // Check if we have command line arguments
    if (argc >= 2 && string(argv[1]) == "encrypt") {
        if (argc < 4) {
            cout << "Usage: des encrypt <plaintext> <key>" << endl;
            return 1;
        }
        string plaintext = argv[2];
        string key = argv[3];
        
        string ciphertext = encrypt_multi_block(plaintext, key, false);
        cout << ciphertext << endl;
        return 0;
    }
    else if (argc >= 2 && string(argv[1]) == "decrypt") {
        if (argc < 4) {
            cout << "Usage: des decrypt <ciphertext> <key>" << endl;
            return 1;
        }
        string ciphertext = argv[2];
        string key = argv[3];
        
        string plaintext = decrypt_multi_block(ciphertext, key, false);
        cout << plaintext << endl;
        return 0;
    }
    else if (argc >= 3) {
        // Backward compatibility: treat first arg as plaintext, second as key
        string plaintext = argv[1];
        string key = argv[2];
        
        string ciphertext = encrypt_multi_block(plaintext, key, false);
        cout << ciphertext << endl;
        return 0;
    }
    
    // Check if there's input from stdin (for CI)
    string mode, input, key;
    
    // Try to read from stdin
    if (!getline(cin, mode)) {
        print_usage();
        return 1;
    }
    
    // Check if mode is a number (1-4) for CI
    if (mode == "1" || mode == "2" || mode == "3" || mode == "4") {
        if (!getline(cin, input)) {
            cout << "Error: Missing input" << endl;
            return 1;
        }
        if (!getline(cin, key)) {
            cout << "Error: Missing key" << endl;
            return 1;
        }
        
        int mode_num = stoi(mode);
        if (mode_num == 1) {
            // DES encrypt
            string ciphertext = encrypt_multi_block(input, key, false);
            cout << ciphertext << endl;
        } else if (mode_num == 2) {
            // DES decrypt
            string plaintext = decrypt_multi_block(input, key, false);
            cout << plaintext << endl;
        } else if (mode_num == 3) {
            // TripleDES encrypt (currently same as DES)
            string ciphertext = encrypt_multi_block(input, key, false);
            cout << ciphertext << endl;
        } else if (mode_num == 4) {
            // TripleDES decrypt (currently same as DES)
            string plaintext = decrypt_multi_block(input, key, false);
            cout << plaintext << endl;
        }
        return 0;
    }
    
    // Interactive mode
    cout << "=== DES Encryption/Decryption Tool ===" << endl;
    cout << "Enter mode (encrypt/decrypt): ";
    getline(cin, mode);
    
    cout << "Enter input: ";
    getline(cin, input);
    
    cout << "Enter key (8 characters): ";
    getline(cin, key);
    
    if (mode == "encrypt" || mode == "1") {
        string ciphertext = encrypt_multi_block(input, key, false);
        cout << "Ciphertext (hex): " << ciphertext << endl;
    } else if (mode == "decrypt" || mode == "2") {
        string plaintext = decrypt_multi_block(input, key, false);
        cout << "Plaintext: " << plaintext << endl;
    } else {
        cout << "Invalid mode!" << endl;
        return 1;
    }
    
    return 0;
}

    






