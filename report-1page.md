# Report 1 page - Lab 4 DES / TripleDES

## Mục tiêu

- Hiểu và thực thi thuật toán mã hóa khối DES (Data Encryption Standard).
- Nắm vững các kỹ thuật xử lý bit: Hoán vị (Permutation), Mở rộng (Expansion), và Hàm S-Box.
- Xây dựng hệ thống kiểm thử tự động (Automation Test) để kiểm chứng tính đúng đắn của thuật toán trong nhiều điều kiện dữ liệu khác nhau.
## Cách làm / Method

- Hoàn thiện Code gốc:
  - Bổ sung hàm generateKeys() để tạo 16 khóa vòng từ khóa gốc 64-bit.
  - Xử lý hàm feistel() kết hợp mở rộng E, XOR khóa vòng và thay thế qua S-Boxes.
  - Cài đặt hàm decrypt() bằng cách đảo ngược thứ tự sử dụng khóa vòng (từ K16 về K1).
- Cấu trúc chương trình:
  - Phát triển theo dạng Modular: Mỗi bước trong DES (IP, FP, Expansion, S-Box) được viết thành các hàm riêng biệt để dễ dàng debug.
  - Sử dụng kiểu dữ liệu std::string để quản lý các bit dữ liệu.
- Xử lý dữ liệu: Áp dụng Zero Padding để đảm bảo bản tin luôn có độ dài là bội số của 8 bytes (64 bits).

## Kết quả / Result

Chương trình đã vượt qua các kịch bản kiểm thử sau:

- **Sample DES Test**: Khớp kết quả chuẩn với vector thử nghiệm quốc tế.
  - Input: 0123456789ABCDEF, Key: 133457799BBCDFF1
  - Result: 85E813540F0AB405

- **Round-trip Test**: Mã hóa một chuỗi văn bản và giải mã ngược lại thành công, bảo toàn 100% nội dung gốc.

- **Negative Tests**:
  - **Sai Key**: Kết quả giải mã ra dữ liệu rác, không thể đọc được.
  - **Tamper Test**: Thay đổi 1 bit trên Ciphertext dẫn đến sự thay đổi hoàn toàn của bản giải mã (Avalanche Effect).

- **Multi-block**: Xử lý tốt các chuỗi dài hơn 8 bytes bằng cách chia block và đệm bit.
## Kết luận / Conclusion

- **Học được**: Hiểu sâu về cấu trúc mạng Feistel và tầm quan trọng của việc quản lý các bảng hoán vị trong mật mã học. Biết cách sử dụng Shell Script để tự động hóa quy trình kiểm thử.

- **Hạn chế**: Tốc độ thực thi có thể tối ưu hơn nếu sử dụng bảng tra cứu (Lookup Table). Hiện tại mới chỉ hỗ trợ Zero Padding cơ bản, chưa áp dụng chuẩn PKCS#7.

- **Hướng mở rộng**: 
  - Phát triển lên TripleDES (3DES) bằng cách thực hiện chu trình Encrypt-Decrypt-Encrypt với các khóa khác nhau để tăng độ bảo mật.
  - Tối ưu hóa hiệu suất bằng cách sử dụng bitwise operations trực tiếp thay vì string manipulation.
  - Hỗ trợ thêm các chế độ mã hóa khối như CBC, CTR để tăng cường bảo mật.