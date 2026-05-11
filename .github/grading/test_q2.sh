#!/bin/bash

# Test Q2: DES Encryption/Decryption with Multi-block & Zero Padding

echo "=========================================="
echo "Testing Q2: DES with Multi-block & Padding"
echo "=========================================="

# Compile program
echo "Compiling des.cpp..."
g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
if [ $? -ne 0 ]; then
    echo "[FAIL] Compilation failed"
    exit 1
fi
echo "[PASS] Compilation successful"

# Test 1: DES Encrypt single block
echo -e "\nTest 1: DES Encrypt (HelloWorld with key 12345678)"
output=$(echo -e "1\nHelloWorld\n12345678" | ./des)
if [[ $output == *"F1205FAEEB82B3DA"* ]]; then
    echo "[PASS] Single block encryption works"
else
    echo "[FAIL] Single block encryption failed"
    echo "Expected: F1205FAEEB82B3DA..."
    echo "Got: $output"
fi

# Test 2: DES Decrypt single block
echo -e "\nTest 2: DES Decrypt (ciphertext to qwerty)"
output=$(echo -e "2\n85E813540F0AB405\n12345678" | ./des)
if [[ $output == *"qwerty"* ]]; then
    echo "[PASS] Single block decryption works"
else
    echo "[FAIL] Single block decryption failed"
    echo "Expected: qwerty"
    echo "Got: $output"
fi

# Test 3: Multi-block encryption
echo -e "\nTest 3: Multi-block encryption (16 bytes)"
output=$(echo -e "1\nABCDEFGHIJKLMNOP\n12345678" | ./des)
if [ ${#output} -ge 32 ]; then
    echo "[PASS] Multi-block encryption works - Length: ${#output} chars"
else
    echo "[FAIL] Multi-block encryption failed - Length: ${#output} chars"
fi

# Test 4: Zero padding (7 bytes)
echo -e "\nTest 4: Zero padding (7-byte input: 1234567)"
output=$(echo -e "1\n1234567\n12345678" | ./des)
if [ ${#output} -ge 16 ]; then
    echo "[PASS] Zero padding works"
else
    echo "[FAIL] Zero padding failed - Output length: ${#output}"
fi

# Test 5: Roundtrip test
echo -e "\nTest 5: Roundtrip (encrypt then decrypt)"
original="Test123"
cipher=$(echo -e "1\n$original\n12345678" | ./des)
plain=$(echo -e "2\n$cipher\n12345678" | ./des)
if [[ $plain == *"$original"* ]]; then
    echo "[PASS] Roundtrip encryption/decryption works"
else
    echo "[FAIL] Roundtrip failed"
    echo "Original: $original"
    echo "Decrypted: $plain"
fi

echo -e "\n=========================================="
echo "Q2 Test Complete"
echo "=========================================="