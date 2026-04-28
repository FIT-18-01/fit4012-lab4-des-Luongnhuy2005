# #!/usr/bin/env bash
## ...existing code...
# # Gợi ý: sau khi em viết thêm giải mã, cần kiểm tra decrypt(encrypt(plaintext)) = plaintext.
# set -euo pipefail

## ...existing code...
# exit 0
#!/usr/bin/env bash
# Test round-trip encrypt -> decrypt.
set -euo pipefail

echo "--- Đang chạy kiểm tra Round-trip (Encrypt -> Decrypt) ---"

# 1. Biên dịch chương trình
g++ des.cpp -o des_tool

# 2. Dữ liệu thử nghiệm
ORIGINAL_PLAINTEXT="HELLOWORLD12345"
KEY="MYSECRET"

echo "Plaintext gốc: $ORIGINAL_PLAINTEXT"

# 3. Thực hiện mã hóa
CIPHERTEXT=$(./des_tool encrypt "$ORIGINAL_PLAINTEXT" "$KEY")
echo "Ciphertext: $CIPHERTEXT"

# 4. Thực hiện giải mã từ ciphertext vừa tạo
DECRYPTED_TEXT=$(./des_tool decrypt "$CIPHERTEXT" "$KEY")
echo "Dữ liệu sau giải mã: $DECRYPTED_TEXT"

# 5. So sánh đối chiếu
if [ "$ORIGINAL_PLAINTEXT" == "$DECRYPTED_TEXT" ]; then
    echo "------------------------------------------"
    echo "=> KẾT QUẢ: THÀNH CÔNG!"
    echo "Giải mã (Mã hóa (P)) khớp hoàn toàn với P gốc."
    exit 0
else
    echo "------------------------------------------"
    echo "=> KẾT QUẢ: THẤT BẠI!"
    echo "Lỗi: Dữ liệu sau giải mã bị sai lệch."
    exit 1
fi