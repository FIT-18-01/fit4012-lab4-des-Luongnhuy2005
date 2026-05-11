# TODO - DES/TripleDES LAB4

- [ ] 1) Đọc kỹ toàn bộ `des.cpp` để xác định tất cả điểm sai (padding, unpad, TripleDES, output format, stdin contract).
- [ ] 2) Chuẩn hoá xử lý block 64-bit: plaintext/ciphertext -> binary/hex đúng 8 bytes/64 bits.
- [ ] 3) Sửa Zero padding/unpadding theo byte `0x00` (không unpad theo bit).
- [ ] 4) Implement DES đúng theo key schedule (nếu cần chỉnh lại PC1/PC2/shift thứ tự).
- [ ] 5) Implement TripleDES đúng E(K3, D(K2, E(K1, P))) và D ngược lại.
- [ ] 6) Sửa input/output theo contract stdin mode 1..4; không in prompt khi stdin contract hợp lệ.
- [ ] 7) Đảm bảo ciphertext output là hex uppercase, mỗi block 16 hex chars; multi-block nối liên tiếp.
- [ ] 8) Chạy các test hiện có để biết chính xác cái nào fail (thường CI/Q2/Q4 chỉ yêu cầu code đúng contract; nếu test script đã ổn thì không sửa).
- [ ] 9) Build và chạy toàn bộ tests trong `tests/`.
- [ ] 10) Chạy `.github/grading/test_q2.sh` nếu có.

