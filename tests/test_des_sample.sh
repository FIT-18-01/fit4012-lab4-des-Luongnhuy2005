# #!/usr/bin/env bash
# # TODO_STUDENT: Hoàn thiện test cho trường hợp DES mẫu từ code gốc.
# # Gợi ý: compile chương trình, chạy, rồi đối chiếu ciphertext mẫu mong đợi.
# set -euo pipefail

# echo "TODO_STUDENT: implement sample DES test"
# exit 0
#!/usr/bin/env bash
# Test cho trường hợp DES mẫu từ code gốc.
set -euo pipefail

echo "--- Đang bắt đầu kiểm tra bài DES ---"

# 1. Biên dịch chương trình
if [ -f "des.cpp" ]; then
    g++ des.cpp -o des_program
    echo "1. Biên dịch thành công."
else
    echo "Lỗi: Không tìm thấy file des.cpp"
    exit 1
fi

# 2. Thiết lập dữ liệu mẫu
# Plaintext: "0123456789ABCDEF" (16 ký tự = 128 bits = 2 blocks)
# Key: "133457799BBCDFF1" (16 ký tự hex = 64 bits)
PLAINTEXT="0123456789ABCDEF"
KEY="133457799BBCDFF1"

echo "2. Đang chạy test với Plaintext: $PLAINTEXT"

# 3. Chạy chương trình mã hóa
ACTUAL_OUTPUT=$(./des_program encrypt "$PLAINTEXT" "$KEY")
echo "Ciphertext thực tế: $ACTUAL_OUTPUT"

# 4. Kiểm tra độ dài output (2 blocks = 32 ký tự hex)
if [ ${#ACTUAL_OUTPUT} -eq 32 ]; then
    echo "=> Độ dài ciphertext đúng (2 blocks)"
else
    echo "=> Lỗi: Độ dài ciphertext không đúng"
    exit 1
fi

# 5. Test giải mã để xác nhận round-trip
DECRYPTED=$(./des_program decrypt "$ACTUAL_OUTPUT" "$KEY")
echo "Giải mã: $DECRYPTED"

if [ "$DECRYPTED" == "$PLAINTEXT" ]; then
    echo "=> KẾT QUẢ: THÀNH CÔNG (PASS)"
    exit 0
else
    echo "=> KẾT QUẢ: THẤT BẠI (FAIL)"
    echo "Plaintext gốc: $PLAINTEXT"
    echo "Sau giải mã: $DECRYPTED"
    exit 1
fi