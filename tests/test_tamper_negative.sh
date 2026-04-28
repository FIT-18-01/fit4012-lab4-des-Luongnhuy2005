# #!/usr/bin/env bash
## ...existing code...
# # Gợi ý: sửa 1 byte hoặc một số bit của ciphertext rồi quan sát kết quả giải mã / kiểm thử.
# set -euo pipefail

## ...existing code...
# exit 0

#!/usr/bin/env bash
# Negative test cho tamper / flip 1 byte / bit flip.
set -euo pipefail

echo "--- Đang chạy kiểm tra tính toàn vẹn (Tamper/Bit-flip Test) ---"

# 1. Biên dịch chương trình
g++ des.cpp -o des_tool

# 2. Chuẩn bị dữ liệu gốc
PLAINTEXT="SECURITY"
KEY="MYSECRET"

# 3. Mã hóa để lấy Ciphertext chuẩn
CIPHERTEXT=$(./des_tool encrypt "$PLAINTEXT" "$KEY")
echo "Ciphertext gốc: $CIPHERTEXT"

# 4. THỰC HIỆN TAMPER (Làm giả dữ liệu)
# Thay đổi ký tự đầu tiên của Ciphertext (Bit-flip/Byte-flip giả định)
TAMPERED_CIPHERTEXT="F${CIPHERTEXT:1}" 
echo "Ciphertext bị chỉnh sửa: $TAMPERED_CIPHERTEXT"

# 5. Giải mã Ciphertext đã bị chỉnh sửa
DECRYPTED_RESULT=$(./des_tool decrypt "$TAMPERED_CIPHERTEXT" "$KEY")
echo "Dữ liệu sau khi giải mã từ Ciphertext lỗi: $DECRYPTED_RESULT"

# 6. Đối chiếu kết quả (Kỳ vọng là PHẢI KHÁC NHAU)
if [ "$DECRYPTED_RESULT" != "$PLAINTEXT" ]; then
    echo "------------------------------------------"
    echo "=> KẾT QUẢ: THÀNH CÔNG (Negative Test Pass)"
    echo "Phát hiện: Khi bản mã bị thay đổi, dữ liệu giải mã không còn chính xác."
    exit 0
else
    echo "------------------------------------------"
    echo "=> KẾT QUẢ: THẤT BẠI!"
    echo "Lỗi: Bản mã bị sửa nhưng vẫn giải mã ra đúng dữ liệu gốc. Hãy kiểm tra lại logic thuật toán."
    exit 1
fi