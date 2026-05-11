#!/bin/bash

# Test Q4: TripleDES Encryption/Decryption

echo "=========================================="
echo "Testing Q4: TripleDES"
echo "=========================================="

# Compile program
echo "Compiling des.cpp..."
g++ -std=c++17 -Wall -Wextra -pedantic des.cpp -o des
if [ $? -ne 0 ]; then
    echo "[FAIL] Compilation failed"
    exit 1
fi
echo "[PASS] Compilation successful"

# Test 1: TripleDES Encrypt
echo -e "\nTest 1: TripleDES Encrypt"
echo -e "3\nHelloWorld\nKey1\nKey2\nKey3" | ./des
if [ $? -eq 0 ]; then
    echo "[PASS] TripleDES encryption runs"
else
    echo "[FAIL] TripleDES encryption failed"
fi

# Test 2: TripleDES Decrypt
echo -e "\nTest 2: TripleDES Decrypt"
echo -e "4\n85E813540F0AB405\nKey1\nKey2\nKey3" | ./des
if [ $? -eq 0 ]; then
    echo "[PASS] TripleDES decryption runs"
else
    echo "[FAIL] TripleDES decryption failed"
fi

echo -e "\n=========================================="
echo "Q4 Test Complete"
echo "=========================================="