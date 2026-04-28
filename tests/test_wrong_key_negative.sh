# #!/usr/bin/env bash
# # TODO_STUDENT: Hoàn thiện negative test cho wrong key / incorrect key / sai key.
# # Gợi ý: giải mã với khóa sai và chứng minh không khôi phục đúng plaintext.
# set -euo pipefail

# echo "TODO_STUDENT: implement wrong key negative test"
# exit 0

#!/usr/bin/env bash
# Negative test cho wrong key / incorrect key / sai key.
set -euo pipefail

echo "--- Đang chạy kiểm tra với Khóa Sai (Wrong Key Test) ---"

# 1. Biên dịch chương trình
g++ des.cpp -o des_tool

# 2. Thiết lập dữ liệu
PLAINTEXT="TOPSECRET"
CORRECT_KEY="12345678"
WRONG_KEY="87654321"

echo "Plaintext gốc: $PLAINTEXT"
echo "Khóa đúng: $CORRECT_KEY"
echo "Khóa sai:  $WRONG_KEY"

# 3. Mã hóa với khóa ĐÚNG
CIPHERTEXT=$(./des_tool encrypt "$PLAINTEXT" "$CORRECT_KEY")
echo "Ciphertext tạo ra: $CIPHERTEXT"

# 4. Giải mã với khóa SAI
# Kết quả mong đợi là một chuỗi ký tự không xác định, không giống bản gốc
DECRYPTED_WITH_WRONG_KEY=$(./des_tool decrypt "$CIPHERTEXT" "$WRONG_KEY")
echo "Kết quả sau khi giải mã bằng khóa sai: $DECRYPTED_WITH_WRONG_KEY"

# 5. Kiểm chứng
if [ "$DECRYPTED_WITH_WRONG_KEY" != "$PLAINTEXT" ]; then
    echo "------------------------------------------"
    echo "=> KẾT QUẢ: THÀNH CÔNG (Negative Test Pass)"
    echo "Xác nhận: Không thể khôi phục dữ liệu nếu dùng sai khóa."
    exit 0
else
    echo "------------------------------------------"
    echo "=> KẾT QUẢ: THẤT BẠI!"
    echo "CẢNH BÁO: Giải mã bằng khóa sai nhưng vẫn ra kết quả đúng. Kiểm tra lại code C++."
    exit 1
fi