# #!/usr/bin/env bash
# # TODO_STUDENT: Hoàn thiện test cho trường hợp multi-block và padding.
# # Gợi ý: kiểm tra plaintext dài hơn 64 bit, chia block đúng và zero padding đúng.
# set -euo pipefail

# echo "TODO_STUDENT: implement multi-block padding test"
# exit 0

#!/usr/bin/env bash
# Test cho trường hợp multi-block và padding.
set -euo pipefail

echo "--- Đang chạy kiểm tra Multi-block và Zero Padding ---"

# 1. Biên dịch chương trình
g++ des.cpp -o des_tool
echo "1. Biên dịch thành công."

# 2. Dữ liệu thử nghiệm (Dài hơn 8 bytes để tạo ra ít nhất 2 blocks)
# "HelloWorld" = 10 bytes -> Phải chia làm 2 blocks (16 bytes)
PLAINTEXT="HelloWorld" 
KEY="MYSECRET"

echo "Dữ liệu đầu vào: '$PLAINTEXT' (${#PLAINTEXT} ký tự)"

# 3. Chạy mã hóa
ACTUAL_OUTPUT=$(./des_tool encrypt "$PLAINTEXT" "$KEY")
echo "Ciphertext: $ACTUAL_OUTPUT"

# 4. Kiểm tra độ dài output (2 blocks = 32 ký tự hex)
EXPECTED_MIN_LENGTH=32

if [ ${#ACTUAL_OUTPUT} -ge $EXPECTED_MIN_LENGTH ]; then
    echo "Độ dài ciphertext: ${#ACTUAL_OUTPUT} ký tự (hợp lệ)"
else
    echo "Lỗi: Độ dài Ciphertext không khớp với kỳ vọng của Multi-block."
    exit 1
fi

# 5. Giải mã và kiểm tra round-trip
DECRYPTED=$(./des_tool decrypt "$ACTUAL_OUTPUT" "$KEY")
echo "Giải mã: $DECRYPTED"

if [ "$DECRYPTED" == "$PLAINTEXT" ]; then
    echo "------------------------------------------"
    echo "=> KẾT QUẢ: THÀNH CÔNG!"
    echo "Chương trình đã xử lý được chuỗi dài và thực hiện padding đúng."
    exit 0
else
    echo "------------------------------------------"
    echo "=> KẾT QUẢ: THẤT BẠI!"
    echo "Lỗi: Round-trip thất bại với multi-block."
    exit 1
fi