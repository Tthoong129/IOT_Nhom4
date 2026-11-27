# BÁO CÁO TIỂU LUẬN HỌC PHẦN INTERNET OF THINGS (IOT)

**ĐỀ TÀI: HỆ THỐNG BÃI GIỮ XE MÁY TỰ QUẢN SỬ DỤNG RFID**

---

## PHẦN ĐẦU

### TRANG BÌA

* **Trường:** Trường Đại học Công Thương Thành phố Hồ Chí Minh (HUIT)
* **Khoa:** Khoa Công nghệ Thông tin
* **Học phần:** Internet of Things (IoT)
* **Đề tài:** Hệ thống bãi giữ xe máy tự quản sử dụng RFID (Mô phỏng 4 tầng IoT)
* **Nhóm thực hiện:** Nhóm 4

| STT | Họ và tên thành viên | Mã số sinh viên |
| :---: | :--- | :--- |
| 1 | Nguyễn Lê Duy Cương | 2001230069 |
| 2 | Đinh Tấn Thành | 2001230894 |
| 3 | Bùi Tấn Thông | 2001230938 |

* **Giảng viên hướng dẫn:** Võ Hoàng Hải
* **Địa điểm, thời gian:** TP. Hồ Chí Minh, tháng 11 năm 2026

---

### MỤC LỤC *(Trong bản Word `.docx` được cấu hình tự động cập nhật số trang)*

* Phần đầu: Danh mục hình, Danh mục bảng, Danh mục từ viết tắt, Tóm tắt
* Chương 1: Giới thiệu đề tài
* Chương 2: Cơ sở lý thuyết
* Chương 3: Phân tích và thiết kế hệ thống
* Chương 4: Triển khai
* Chương 5: Kiểm thử và đánh giá
* Chương 6: Kết luận và hướng phát triển
* Tài liệu tham khảo
* Phụ lục A – F

---

### DANH MỤC HÌNH

* **Hình 3.1:** Sơ đồ Use Case tổng quát của hệ thống bãi giữ xe RFID *(Sơ đồ Mermaid)*
* **Hình 3.2:** Sơ đồ kiến trúc 4 tầng IoT và luồng dữ liệu hai chiều *(Sơ đồ Mermaid)*
* **Hình 3.3:** Lưu đồ thuật toán xử lý quẹt thẻ RFID tại cổng ESP32 *(Sơ đồ Mermaid)*
* **Hình 3.4:** Lưu đồ chống kẹp xe (HC-SR04) và máy trạng thái Barie *(Sơ đồ Mermaid)*
* **Hình 3.5:** Lưu đồ xử lý sự kiện, đồng bộ và 4 rule trên Node-RED *(Sơ đồ Mermaid)*
* **Hình 4.1:** Mạch mô phỏng Wokwi khi xe ra tính phí và kích hoạt chống kẹp xe (`minh_chung_anti_pinch_wokwi.png`)
* **Hình 4.2:** Giao diện luồng xử lý Node-RED thực tế chia theo 4 cụm và cụm khởi động (`nodered_flow.png`)
* **Hình 4.3:** Giao diện Web Dashboard Tab 1 giám sát bãi xe và điều khiển barie (`dashboard_demo.png`)
* **Hình 4.4:** Giao diện đăng nhập xác thực quản trị Node-RED và cơ chế `httpNodeAuth` (`nodered_admin_login.png`)
* **Hình 4.5:** Giao diện mở rộng Tab 2 quản lý thẻ RFID và bảng giá động (`dashboard_cards_pricing.png`)
* **Hình 4.6:** Giao diện mở rộng Tab 3 tra cứu lịch sử giao dịch và xuất CSV (`dashboard_history.png`)
* **Hình 5.1:** Kết quả kiểm thử mất kết nối đột ngột kích hoạt LWT trên Dashboard (`test_ch5_lwt_offline.png`)
* **Hình 5.2:** Kết quả kiểm thử kích hoạt đồng thời Rule 1, Rule 2 và Rule 3 trên Dashboard (`test_ch5_rules_alerts.png`)
* **Hình 5.3:** Dashboard sau khi khởi động lại container Docker khôi phục doanh thu và giao dịch (`test_ch5_restart_recovery.png`)

---

### DANH MỤC BẢNG

* **Bảng 1.1:** Kế hoạch thực hiện đề tài trong 10 tuần và các mốc rubric
* **Bảng 2.1:** So sánh ngắn giữa chuẩn RFID 13,56 MHz (MFRC522) và NFC
* **Bảng 2.2:** So sánh giao thức MQTT với HTTP và AMQP trong bối cảnh đề tài
* **Bảng 3.1:** Bảng đặc tả yêu cầu chức năng và phi chức năng
* **Bảng 3.2:** Sơ đồ đấu nối chân linh kiện phần cứng trên ESP32
* **Bảng 3.3:** Danh mục 6 topic MQTT nghiệp vụ và cấu trúc thông điệp
* **Bảng 3.4:** Đặc tả các trường dữ liệu trong mô hình trạng thái tập trung của bãi xe
* **Bảng 3.5:** Bộ 4 quy tắc tự động hóa trên Node-RED (ngưỡng demo và ngưỡng thực tế)
* **Bảng 4.1:** Môi trường công cụ và phiên bản sử dụng khi triển khai
* **Bảng 5.1:** Bộ dữ liệu 4 thẻ RFID mẫu sử dụng trong kiểm thử
* **Bảng 5.2:** Kết quả kiểm thử Tầng 1 (Firmware và mạch mô phỏng Wokwi)
* **Bảng 5.3:** Kết quả kiểm thử Tầng 2 (Truyền thông MQTT hai chiều, LWT và xác thực)
* **Bảng 5.4:** Kết quả kiểm thử Tầng 3 (4 rule tự động và lưu trữ bền vững)
* **Bảng 5.5:** Kết quả kiểm thử đầu-cuối (End-to-End) theo 9 phân cảnh demo
* **Bảng 5.6:** Bảng đối chiếu kết quả với các mốc yêu cầu học phần (M1–M4 và điều kiện Pass)
* **Bảng 5.7:** Số liệu đo kiểm tài nguyên Firmware ESP32 và thời gian phản hồi quan sát
* **Bảng C.1:** Danh sách thẻ RFID mẫu sử dụng trong mô phỏng Wokwi

---

### DANH MỤC TỪ VIẾT TẮT

| Từ viết tắt | Tên đầy đủ tiếng Anh | Nghĩa tiếng Việt |
| :--- | :--- | :--- |
| **IoT** | Internet of Things | Mạng lưới vạn vật kết nối |
| **RFID** | Radio Frequency Identification | Nhận dạng qua tần số vô tuyến |
| **UID** | Unique Identifier | Mã định danh duy nhất của thẻ từ |
| **MQTT** | Message Queuing Telemetry Transport | Giao thức truyền thông điệp nhẹ publish/subscribe |
| **QoS** | Quality of Service | Mức chất lượng dịch vụ truyền tin MQTT |
| **JSON** | JavaScript Object Notation | Định dạng dữ liệu văn bản có cấu trúc cặp khóa–giá trị |
| **SPI** | Serial Peripheral Interface | Giao tiếp nối tiếp đồng bộ 4 dây cho ngoại vi tốc độ cao |
| **I2C** | Inter-Integrated Circuit | Giao tiếp nối tiếp đồng bộ 2 dây (`SDA`, `SCL`) |
| **PWM** | Pulse Width Modulation | Điều chế độ rộng xung điều khiển động cơ servo và âm thanh |
| **LWT** | Last Will and Testament | Thông điệp di chúc thông báo mất kết nối đột ngột trong MQTT |

---

### TÓM TẮT

Quản lý bãi giữ xe máy theo cách ghi vé giấy dễ gây ùn tắc giờ cao điểm, barie đóng cố định tiềm ẩn va chạm xe và thiếu dữ liệu giám sát từ xa. Đề tài mô phỏng hệ thống bãi giữ xe máy tự quản theo kiến trúc IoT 4 tầng. Tầng 1 dùng ESP32 trên Wokwi kết nối đầu đọc RFID-RC522, cảm biến HC-SR04 chống kẹp dưới 15 cm, servo SG90, LED Đỏ/Xanh, LCD 1602 I2C và buzzer; mọi quyết định vào/ra xử lý tại cổng kể cả khi mất mạng. Tầng 2 truyền dữ liệu hai chiều qua Wi-Fi và MQTT (`broker.hivemq.com:1883`, tiền tố `parking_n4/`). Tầng 3 chạy Node-RED đồng bộ trạng thái, thực thi bốn rule tự động và lưu tệp `parking_log.txt`, `parking_database.json`. Tầng 4 cung cấp Web Dashboard có xác thực đăng nhập (`httpNodeAuth`), điều khiển barie cùng phần mở rộng quản lý thẻ, bảng giá động và xuất CSV. Firmware tiêu thụ 62,7% Flash, 14,3% RAM; kiểm thử qua MQTT và Chrome xác nhận bốn rule và đồng bộ hai chiều hoạt động ổn định.

---

## CHƯƠNG 1. GIỚI THIỆU ĐỀ TÀI

### 1.1. Đặt vấn đề
Tại nhiều bãi giữ xe máy quy mô vừa và nhỏ như ký túc xá, trường học hoặc tòa nhà văn phòng, việc soát vé giấy thủ công bộc lộ ba hạn chế rõ rệt trong quá trình vận hành:
1. **Ùn tắc tại cổng vào/ra:** Bảo vệ phải ghi vé, kiểm tra biển số bằng tay và thu tiền trực tiếp, làm kéo dài thời gian xử lý mỗi lượt xe vào giờ cao điểm.
2. **Rủi ro va chạm thanh chắn barie:** Các cổng tự động đóng cứng sau một khoảng thời gian cố định không nhận biết được phương tiện hay người đi bộ vẫn đang ở bên dưới, dễ gây va chạm.
3. **Khó giám sát và thiếu dữ liệu truy vết:** Người quản lý không biết được bãi còn bao nhiêu chỗ trống theo thời gian thực, không phát hiện được xe gửi quá hạn hay hành vi thử thẻ lạ liên tiếp, và thiếu nhật ký chi tiết khi cần đối soát sự cố.

### 1.2. Mục tiêu

#### 1.2.1. Mục tiêu tổng quát
Xây dựng hoàn chỉnh hệ thống mô phỏng bãi giữ xe máy tự quản theo kiến trúc IoT 4 tầng, bảo đảm truyền thông hai chiều ổn định giữa thiết bị cổng và ứng dụng giám sát.

#### 1.2.2. Mục tiêu cụ thể
1. Thiết kế mạch mô phỏng Tầng 1 trên Wokwi với ESP32, đầu đọc RFID-RC522, cảm biến siêu âm HC-SR04, servo SG90, đèn LED Đỏ/Xanh, màn hình LCD 1602 I2C và còi báo.
2. Xây dựng firmware xử lý quẹt thẻ vào/ra, chống đọc trùng thẻ (debounce), tính thời gian gửi và cước phí ngay tại cổng không phụ thuộc kết nối mạng.
3. Cài đặt cơ chế an toàn chống kẹp xe: tự động hoãn hạ thanh chắn khi phát hiện vật cản dưới 15 cm và kiểm tra lại mỗi 0,3 giây đến khi thông thoáng.
4. Triển khai truyền thông MQTT hai chiều (Uplink dữ liệu cảm biến/trạng thái và Downlink lệnh điều khiển/cấu hình) có tự kết nối lại sau 5 giây và Last Will thông báo mất kết nối.
5. Xây dựng 4 quy tắc tự động hóa trên Node-RED và lưu trữ lịch sử, trạng thái bền vững qua khởi động lại.
6. Thiết kế Web Dashboard có xác thực đăng nhập, hiển thị số xe, trạng thái từng ô, nhật ký sự kiện, nút điều khiển barie từ xa và các công cụ quản trị mở rộng.

### 1.3. Phạm vi và giới hạn

#### 1.3.1. Phạm vi mô phỏng và hạ tầng
* **Mô phỏng phần cứng:** Toàn bộ Tầng 1 chạy trên nền tảng mô phỏng Wokwi kết hợp biên dịch firmware bằng PlatformIO, chưa lắp ráp trên mạch vật lý thật.
* **Hạ tầng mạng:** Sử dụng Wi-Fi giả lập `Wokwi-GUEST` kết nối tới HiveMQ public broker (`broker.hivemq.com:1883`), sử dụng tiền tố topic riêng (`parking_n4/`) để tránh lẫn dữ liệu với người dùng khác.

#### 1.3.2. Giới hạn quy mô thực nghiệm
* Bãi xe mô phỏng có sức chứa 2 ô đỗ (`PARKING_CAPACITY = 2`); các ngưỡng thời gian kiểm tra (giữ mở barie 3 giây, quá giờ 30 giây, barie mở quá lâu 10 giây) được thu ngắn để thuận tiện trình bày và kiểm thử trong thời lượng demo.

### 1.4. Phương pháp thực hiện
Nhóm áp dụng phương pháp thiết kế theo mô hình IoT 4 tầng từ dưới lên, tách biệt từng lớp phần cứng mô phỏng, truyền thông mạng, xử lý trung gian và giao diện ứng dụng:
* **Tầng thiết bị:** Viết firmware C++ theo hướng mô-đun trên VS Code + PlatformIO, mô phỏng trên Wokwi.
* **Tầng mạng và trung gian:** Sử dụng HiveMQ public broker (`broker.hivemq.com:1883`) và Node-RED (`v5.0.10` đóng gói trong Docker Compose cùng `eclipse-mosquitto:2.0` và `nodered/node-red:latest`).
* **Kiểm thử:** Kết hợp kiểm thử tương tác Tầng 1 trên Wokwi Simulator với bộ kịch bản Node.js giả lập bản tin ESP32 qua MQTT, kiểm tra HTTP Auth và kiểm tra giao diện trên Chrome headless.
* **Phân chia tiến độ:** Chia khối lượng công việc thành 10 tuần gắn với 4 mốc nghiệm thu M1–M4 của học phần.

### 1.5. Kế hoạch 10 tuần

| Tuần | Nội dung công việc thực hiện (đối chiếu báo cáo tuần) | Mốc Rubric |
| :---: | :--- | :---: |
| **1** | Phân tích bài toán, xác định use case, thiết kế kiến trúc 4 tầng, phân công thành viên | |
| **2** | Dựng mô phỏng Tầng 1 bản đầu trên Wokwi gồm ESP32, RFID-RC522, Servo SG90 và Buzzer (chưa triển khai Wi-Fi/MQTT) | |
| **3** | Ổn định firmware: tái cấu trúc theo State Machine 4 trạng thái (`IDLE` → `SCANNING` → `OPENING` → `CLOSING`), phân biệt vào/ra theo UID, lọc đọc trùng (debounce) và kiểm thử nhiều UID | **M1** |
| **4** | Tích hợp kết nối Wi-Fi và giao thức MQTT hai chiều (`publish` sự kiện Uplink, `subscribe` lệnh barie Downlink, cơ chế tự kết nối lại) | **M2** |
| **5** | Xây dựng flow Node-RED trung gian (`Check Card`), ghi nhật ký sự kiện ra tệp và gửi lệnh điều khiển barie | |
| **6** | Xây dựng Web Dashboard (`/ui`) hiển thị số xe, trạng thái barie, 8 sự kiện, biên nhận, cảnh báo, nút Mở/Đóng và bật xác thực đăng nhập (`httpNodeAuth` trong `settings.js`) | **M3** |
| **7** | Hoàn thiện 4 quy tắc tự động hóa trên Node-RED và xử lý các kịch bản bất thường | |
| **8** | Tích hợp đầu-cuối (End-to-End); bổ sung cảm biến siêu âm HC-SR04 chống kẹp xe, màn hình LCD 1602 I2C (dời chân `RST` RFID sang GPIO 4), cụm LED Đỏ/Xanh, khai báo LWT và snapshot `retained` | **M4** |
| **9** | Đóng gói Docker Compose, triển khai các tính năng mở rộng (quản lý 16 thẻ động, bảng giá động, lịch sử ghép cặp & xuất CSV), chạy kịch bản kiểm thử tự động MQTT/Chrome và hoàn thiện báo cáo, slide | |
| **10** | Thực hiện chạy liên hoàn 9 bước trên Wokwi thật kết hợp Dashboard, quay video minh chứng và nghiệm thu cuối kỳ | |

*Bảng 1.1: Kế hoạch thực hiện đề tài trong 10 tuần và các mốc rubric.*

### 1.6. Bố cục tiểu luận
Báo cáo gồm 6 chương và phần phụ lục:
* **Chương 1 (Giới thiệu đề tài):** Trình bày bài toán thực tế, mục tiêu, phạm vi mô phỏng, phương pháp và kế hoạch 10 tuần.
* **Chương 2 (Cơ sở lý thuyết):** Tóm tắt các công nghệ thực tế sử dụng trong dự án gồm kiến trúc IoT 4 tầng, RFID 13,56 MHz, ngoại vi ESP32, giao thức MQTT, Node-RED và mô phỏng Wokwi.
* **Chương 3 (Phân tích và thiết kế hệ thống):** Trình bày đặc tả yêu cầu, sơ đồ Use Case, kiến trúc 4 tầng, thiết kế phần cứng, thuật toán và nguyên lý xử lý từng tầng, cây topic MQTT, 4 rule tự động, giao diện Dashboard và mô hình lưu trữ.
* **Chương 4 (Triển khai):** Trình bày môi trường phiên bản, tổ chức mô-đun mã nguồn, cấu hình cụ thể, trích đoạn xử lý tiêu biểu, ảnh chụp vận hành thực tế và các tính năng mở rộng.
* **Chương 5 (Kiểm thử và đánh giá):** Trình bày kết quả kiểm thử từng tầng, kiểm thử đầu-cuối 9 phân cảnh, đối chiếu rubric và số đo tài nguyên thật.
* **Chương 6 (Kết luận và hướng phát triển):** Tổng kết kết quả đạt được, các hạn chế hiện có và định hướng nâng cấp.

---

## CHƯƠNG 2. CƠ SỞ LÝ THUYẾT

### 2.1. IoT và kiến trúc phân tầng
Hệ thống Internet of Things (IoT) là tập hợp các thiết bị vật lý được gắn cảm biến, bộ xử lý và khả năng kết nối mạng để thu thập, trao đổi dữ liệu và tác động trở lại môi trường tự động. Để dễ bảo trì và mở rộng, dự án tổ chức theo kiến trúc phân tầng gồm 4 lớp:
1. **Tầng Cảm biến và Chấp hành (Sensing & Actuation):** Đọc thông tin đầu vào từ môi trường và thực thi tác động cơ học hoặc tín hiệu hiển thị tại chỗ.
2. **Tầng Mạng (Network):** Đảm bảo kết nối không dây và định tuyến thông điệp giữa thiết bị biên với máy chủ thông qua giao thức chuẩn.
3. **Tầng Xử lý trung gian (Middleware):** Tiếp nhận luồng dữ liệu, lưu trữ trạng thái, đánh giá điều kiện nghiệp vụ theo quy tắc tự động và phát cảnh báo.
4. **Tầng Ứng dụng (Application):** Cung cấp giao diện trực quan cho người vận hành giám sát số liệu và gửi lệnh điều khiển.

Trong kiến trúc này, dữ liệu đi theo hai chiều: **luồng Uplink** (từ Tầng 1 qua Tầng 2, Tầng 3 lên Tầng 4 để cập nhật trạng thái) và **luồng Downlink** (từ Tầng 4 hoặc Tầng 3 truyền ngược xuống Tầng 1 để thay đổi trạng thái chấp hành hoặc cấu hình).

### 2.2. RFID
Công nghệ RFID (Radio Frequency Identification) nhận dạng đối tượng không tiếp xúc bằng sóng vô tuyến giữa đầu đọc (Reader) và thẻ từ (Tag). Trong đề tài, nhóm sử dụng thẻ thụ động MIFARE Classic hoạt động ở băng tần cao **HF 13,56 MHz** theo chuẩn **ISO/IEC 14443A**:
* Khi thẻ đi vào vùng từ trường của cuộn anten trên module **MFRC522**, năng lượng cảm ứng cấp nguồn cho vi mạch trong thẻ phản hồi lại chuỗi định danh duy nhất **UID** (4 byte, viết dưới dạng 4 cặp số thập lục phân như `01 02 03 04`).
* Module MFRC522 truyền dữ liệu UID vừa đọc về vi điều khiển ESP32 thông qua giao tiếp **SPI** ở mức điện áp logic 3,3V.

| Tiêu chí | RFID HF 13,56 MHz (MFRC522) | NFC (Near Field Communication) |
| :--- | :--- | :--- |
| Tần số hoạt động | 13,56 MHz | 13,56 MHz (tương thích chuẩn ISO 14443) |
| Chế độ giao tiếp | Một chiều đọc/ghi từ đầu đọc xuống thẻ | Hai chiều (ngang hàng P2P, giả lập thẻ, đọc/ghi) |
| Khoảng cách đọc | Tối đa khoảng 3–5 cm (với anten RC522) | Thường dưới 4 cm |
| Ứng dụng điển hình | Thẻ giữ xe, thẻ nhân viên, kiểm soát ra vào | Thanh toán di động, ghép nối nhanh trên điện thoại |

*Bảng 2.1: So sánh ngắn giữa chuẩn RFID 13,56 MHz (MFRC522) và NFC.*

### 2.3. ESP32 và thiết bị ngoại vi
Vi điều khiển **ESP32 DevKit V1** (nhân Xtensa dual-core 32-bit, tích hợp sẵn Wi-Fi 802.11 b/g/n) làm bộ điều khiển trung tâm tại cổng với ba nhóm giao tiếp chính:

#### 2.3.1. Giao tiếp SPI và I2C
* **Giao tiếp SPI (Serial Peripheral Interface):** Chuẩn nối tiếp đồng bộ 4 dây (`SCK` xung nhịp, `MOSI` truyền đi, `MISO` nhận về, `SDA/SS` chọn chip) dùng để ESP32 đọc dữ liệu từ module RFID-RC522 ở tốc độ cao.
* **Giao tiếp I2C (Inter-Integrated Circuit):** Chuẩn 2 dây gồm đường dữ liệu `SDA` và đường xung nhịp `SCL`, dùng để điều khiển màn hình ký tự **LCD 1602** (2 dòng x 16 cột) qua mạch mở rộng PCF8574 tại địa chỉ `0x27`.

#### 2.3.2. Điều chế độ rộng xung PWM cho Servo và Buzzer
Bộ định thời LEDC trong ESP32 xuất xung tần số **50 Hz** (chu kỳ 20 ms, độ rộng xung 500–2400 $\mu$s) để điều khiển góc quay $0^\circ$ đến $90^\circ$ cho động cơ **Servo SG90** thông qua thư viện `ESP32Servo`. Để còi **Active Buzzer** phát âm thanh ở tần số 2000 Hz mà không xung đột bộ định thời với servo, dự án cấp riêng cho buzzer kênh LEDC số 15.

#### 2.3.3. Nguyên lý đo khoảng cách của cảm biến siêu âm HC-SR04
ESP32 kích một xung mức cao tối thiểu 10 $\mu$s vào chân `TRIG`, cảm biến phát chùm sóng siêu âm 40 kHz và kéo chân `ECHO` lên mức cao trong thời gian $t$ ($\mu$s) bằng tổng thời gian sóng đi và phản xạ về. Khoảng cách $d$ (cm) tính theo tốc độ âm thanh trong không khí ($343\text{ m/s} = 0{,}0343\text{ cm/}\mu\text{s}$):
$$d = \frac{t \times 0{,}0343}{2}$$

### 2.4. Giao thức MQTT

#### 2.4.1. Mô hình Publish/Subscribe và cây Topic
MQTT (Message Queuing Telemetry Transport) là giao thức truyền thông điệp nhẹ hoạt động trên nền TCP/IP theo mô hình **Publish / Subscribe** thông qua một máy chủ trung gian (**Broker**). Thiết bị phát (Publisher) và thiết bị nhận (Subscriber) không kết nối trực tiếp với nhau mà phân loại dữ liệu theo cấu trúc cây **Topic** (ví dụ `parking_n4/rfid/scan`).

#### 2.4.2. Chất lượng dịch vụ (QoS) sử dụng thực tế trong đề tài
Chuẩn MQTT quy định ba mức chất lượng truyền tin: `QoS 0` (*At most once* — gửi một lần không xác nhận), `QoS 1` (*At least once* — gửi ít nhất một lần có gói `PUBACK` xác nhận) và `QoS 2` (*Exactly once* — bắt tay bốn bước đảm bảo nhận đúng một lần, ít dùng trên vi điều khiển do tốn tài nguyên). Trong mã nguồn dự án:
* **Chiều Uplink (ESP32 $\rightarrow$ Broker):** Thư viện `PubSubClient 2.8.0` chỉ hỗ trợ hàm `publish()` ở **`QoS 0`**, do đó mọi bản tin quẹt thẻ, barie, cảnh báo và snapshot từ ESP32 đều phát ở `QoS 0`. Riêng bản tin di chúc **LWT** do Broker tự phát khi ESP32 đứt kết nối được khai báo mức `willQos = 1`.
* **Chiều Broker $\rightarrow$ Node-RED:** Bốn node `mqtt in` đăng ký nhận ở `QoS 1` (theo đặc tả MQTT, Broker chuyển phát theo giá trị nhỏ hơn giữa QoS lúc gửi và QoS đăng ký, nên bản tin Uplink từ ESP32 tới Node-RED chạy ở `QoS 0`, còn LWT từ Broker chạy ở `QoS 1`).
* **Chiều Downlink (Node-RED $\rightarrow$ Broker $\rightarrow$ ESP32):** Hai node `mqtt out` trên Node-RED (`barie/cmd` và `config`) phát lên Broker ở **`QoS 1`**; ở đầu thiết bị, hàm `_mqttClient.subscribe(topic)` của `PubSubClient` đăng ký nhận theo mặc định **`QoS 0`**.

#### 2.4.3. Cơ chế Retained, LWT và so sánh với HTTP, AMQP
* **Retained Message:** Broker lưu giữ bản tin cuối cùng có cờ `retain = true` của một topic để bất kỳ client nào vừa `subscribe` sau đó đều nhận ngay trạng thái mới nhất (dùng cho trạng thái barie, snapshot và cấu hình thẻ).
* **LWT (Last Will and Testament):** Khi kết nối tới broker, ESP32 khai báo trước một thông điệp di chúc (`{"online":false}` trên `parking_n4/status`). Nếu thiết bị mất nguồn hoặc đứt mạng đột ngột quá thời gian `keepAlive`, broker tự động phát thông điệp này báo ngoại tuyến lên Dashboard.

| Tiêu chí | MQTT | HTTP | AMQP |
| :--- | :--- | :--- | :--- |
| Mô hình giao tiếp | Publish / Subscribe qua Broker | Request / Response (Client – Server) | Publish / Subscribe & Queue phức tạp |
| Kích thước phần đầu | Nhỏ gọn (tối thiểu 2 bytes) | Lớn (header dạng văn bản ASCII) | Trung bình đến lớn |
| Đẩy lệnh Downlink | Tức thời qua kết nối TCP duy trì sẵn | Phải polling định kỳ hoặc thêm WebSocket | Tức thời qua broker |
| Phù hợp cho ESP32 | Rất phù hợp cho vi điều khiển tài nguyên hạn chế | Tốn tài nguyên phân tích header và mở lại kết nối | Nặng hơn, phù hợp hạ tầng máy chủ doanh nghiệp |

*Bảng 2.2: So sánh giao thức MQTT với HTTP và AMQP trong bối cảnh đề tài.*

### 2.5. Node-RED và Dashboard
**Node-RED** là công cụ lập trình trực quan theo luồng (Flow-Based Programming) chạy trên nền Node.js:
* **Node `function`:** Cho phép viết mã JavaScript xử lý dữ liệu JSON từ thông điệp `msg.payload` và lưu giữ trạng thái dùng chung trong luồng thông qua biến ngữ cảnh `flow` (`flow.get()`, `flow.set()`) hoặc nội bộ node (`context`).
* **Node-RED Dashboard (`node-red-dashboard`):** Gói mở rộng tự động dựng giao diện web tại đường dẫn `/ui` dựa trên AngularJS 1.x và Socket.IO, cung cấp các thành phần dựng sẵn như nút bấm (`ui_button`), biểu đồ (`ui_chart`), thông báo nổi (`ui_toast`) và khung mẫu tùy biến (`ui_template`).

### 2.6. Nền tảng Wokwi
**Wokwi** là trình mô phỏng phần cứng nhúng trực tuyến và tích hợp sẵn trong VS Code. Nền tảng hỗ trợ giả lập vi điều khiển ESP32, thực thi trực tiếp tệp nhị phân `.bin` biên dịch từ PlatformIO, mô phỏng tương tác các linh kiện như đầu đọc thẻ MFRC522 (chọn thẻ mẫu có sẵn hoặc tùy chỉnh UID), thanh trượt khoảng cách HC-SR04, góc quay Servo SG90, màn hình LCD I2C và cung cấp mạng Wi-Fi ảo `Wokwi-GUEST` cho phép kết nối tới MQTT broker công cộng ngoài Internet.

*Giới hạn:* Vì chạy trên môi trường ảo hóa đám mây của Wokwi nên độ trễ truyền gói tin qua mạng Internet tới public broker phụ thuộc băng thông thực tế tại thời điểm chạy, tốc độ mô phỏng CPU có thể chậm hơn nhẹ so với phần cứng thực khi tải cao, và không mô phỏng được nhiễu điện từ hay sai số cơ học ngoài đời thực.

---

## CHƯƠNG 3. PHÂN TÍCH VÀ THIẾT KẾ HỆ THỐNG

### 3.1. Phân tích yêu cầu bài toán

#### 3.1.1. Khảo sát thực tế và bài toán cần giải quyết
Tại các bãi giữ xe máy truyền thống (ở trường học, bệnh viện hay khu chung cư), mô hình vận hành chủ yếu dựa vào bảo vệ ghi vé giấy hoặc quẹt thẻ từ thủ công kết hợp camera chụp biển số. Qua quan sát thực tế, mô hình này bộc lộ ba vấn đề lớn:
1. **Ùn tắc giờ cao điểm:** Thao tác ghi vé giấy hoặc nhập liệu thủ công mất từ 5 đến 10 giây mỗi xe. Vào đầu giờ học hoặc giờ tan tầm, lượng xe đổ về lớn dễ gây dồn ứ kéo dài từ cổng bãi xe ra tới lòng đường.
2. **Nguy cơ barie kẹp xe và người:** Các cổng barie tự động thông thường hoạt động theo thời gian cố định (mở lên, đếm 3–5 giây rồi tự hạ xuống). Nếu xe phía trước gặp sự cố chết máy, tài xế lúng túng hoặc có người đi sát phía sau, thanh chắn hạ xuống bất ngờ rất dễ va quẹt gây hư hỏng phương tiện và mất an toàn cho người gửi.
3. **Phụ thuộc hoàn toàn vào máy chủ trung tâm:** Đa số các hệ thống thương mại hiện nay đẩy toàn bộ dữ liệu thẻ về máy chủ trung tâm để kiểm tra rồi mới phát lệnh mở barie. Khi đường truyền mạng gặp sự cố hoặc máy chủ bị quá tải/treo, toàn bộ bãi xe lập tức bị tê liệt, barie không thể mở được khiến khách bị kẹt lại.

Từ những hạn chế trên, mục tiêu của đồ án là thiết kế một hệ thống bãi giữ xe máy thông minh thu nhỏ, ứng dụng công nghệ nhận dạng RFID kết hợp cảm biến siêu âm chống kẹp xe, ứng dụng giao thức MQTT để truyền thông hai chiều và Node-RED để giám sát, đồng thời áp dụng nguyên lý **xử lý tại biên (Edge Computing)** nhằm đảm bảo cổng vào/ra vẫn hoạt động bình thường khi mất kết nối mạng.

#### 3.1.2. Phân tích các nhóm tác nhân sử dụng hệ thống
Hệ thống được thiết kế phục vụ ba đối tượng tương tác chính:
* **Người gửi xe (Tài xế):** Thực hiện quẹt thẻ tại cổng vào và cổng ra; quan sát hướng dẫn trên màn hình LCD và đèn tín hiệu LED Đỏ/Xanh; nghe âm thanh còi báo phản hồi để biết lượt quẹt có hợp lệ hay không; di chuyển qua cổng an toàn dưới sự bảo vệ của cảm biến chống kẹp.
* **Người vận hành / Nhân viên bảo vệ:** Đăng nhập vào giao diện Web Dashboard để theo dõi trực quan hiện trạng bãi xe (số chỗ trống, thông tin xe trong từng ô); bấm nút đóng/mở barie từ xa trong các tình huống khẩn cấp; tiếp nhận các cảnh báo an ninh tức thời (xe gửi quá giờ, bãi đầy, quẹt thẻ lạ); quản lý danh sách thẻ xe, thay đổi bảng giá và tra cứu lịch sử giao dịch.
* **Hệ thống tự động hóa (ESP32 & Node-RED):** Vi điều khiển ESP32 tại cổng tự động đo cảm biến siêu âm mỗi 300 ms để hoãn đóng barie khi có vật cản; Node-RED tại tầng trung gian định kỳ mỗi giây quét và thực thi 4 luật cảnh báo tự động chạy ngầm.

#### 3.1.3. Bảng tổng hợp yêu cầu chức năng và phi chức năng

| Nhóm | Mã | Yêu cầu chi tiết |
| :--- | :---: | :--- |
| **Nghiệp vụ tại cổng** | FR1 | Đọc và chuẩn hóa UID thẻ RFID 13,56 MHz; tự động nhận diện lượt vào/ra; cấp ô đỗ trống (1 hoặc 2) và từ chối khi bãi đã đầy (2/2) hoặc thẻ chưa đăng ký |
| | FR2 | Tính thời gian lưu bãi và cước phí khi xe ra; hiển thị cước phí, biển số lên LCD 1602; phát âm còi bíp phân biệt và điều khiển đèn LED chỉ dẫn |
| | FR3 | Giám sát an toàn bằng cảm biến siêu âm HC-SR04: tạm hoãn hạ barie khi khoảng cách vật cản dưới 15 cm (áp dụng cho cả tự đóng và lệnh điều khiển từ xa) |
| **Quản trị & Giám sát** | FR4 | Truyền dữ liệu hai chiều qua MQTT; hiển thị trạng thái lên Web Dashboard có bảo mật đăng nhập; hỗ trợ bấm mở/đóng barie thủ công từ xa |
| | FR5 | Thực thi 4 luật tự động hóa trên Node-RED (cảnh báo xe quá giờ > 30s, cảnh báo bãi đầy 2/2, phát hiện dò thẻ lạ $\ge$ 3 lần/60s, tự đóng barie kẹt mở > 10s) |
| **Chức năng mở rộng** | ER1 | Quản lý danh sách tối đa 16 thẻ động (thêm, sửa, khóa/mở, xóa thẻ, phân loại vé lượt/vé tháng) và cho phép chỉnh bảng giá trực tiếp từ giao diện web |
| | ER2 | Tra cứu lịch sử giao dịch ghép cặp vào–ra hoàn chỉnh; hỗ trợ tìm kiếm, lọc theo biển số/thời gian và xuất dữ liệu ra tệp CSV để đối soát trên Excel |
| **Yêu cầu phi chức năng** | NFR1 | **Tính tự chủ tại biên (Edge Autonomy):** Cổng vào/ra vận hành độc lập bình thường khi mất kết nối Wi-Fi/MQTT; tự động đồng bộ lại số liệu khi có mạng |
| | NFR2 | **Xử lý không chặn (Non-blocking):** Không sử dụng các hàm dừng chương trình kéo dài (`delay`) làm gián đoạn việc quét thẻ, đo cảm biến hoặc nhận lệnh mạng |

*Bảng 3.1: Bảng tổng hợp yêu cầu chức năng và phi chức năng của hệ thống.*

*Phạm vi thiết kế mô phỏng:* Để phù hợp với điều kiện thực nghiệm trên môi trường Wokwi và thiết bị nhúng, đồ án thiết lập quy mô mô phỏng gồm: sức chứa 2 ô đỗ xe, quản lý tối đa 16 thẻ RFID và 1 cổng barie điều khiển bằng động cơ Servo.

---

### 3.2. Thiết kế kiến trúc tổng thể 4 tầng IoT

#### 3.2.1. Phân tầng kiến trúc và vai trò từng thành phần
Hệ thống được thiết kế theo kiến trúc IoT 4 tầng hoàn chỉnh, phân định rành mạch trách nhiệm của từng tầng nhằm đảm bảo tính ổn định và khả năng mở rộng:
1. **Tầng 1 – Thiết bị cảm biến và chấp hành (Edge / Device Layer):** Đặt trực tiếp tại cổng vào/ra, sử dụng vi điều khiển ESP32 kết nối với đầu đọc RFID-RC522, cảm biến siêu âm HC-SR04, động cơ Servo SG90, màn hình LCD 1602 I2C, còi báo và đèn LED Đỏ/Xanh. Tầng này chịu trách nhiệm thu thập tín hiệu ngoại vi và thực thi điều khiển cơ học tại hiện trường.
2. **Tầng 2 – Mạng và truyền thông (Network Layer):** Sử dụng kết nối mạng không dây Wi-Fi kết hợp giao thức truyền thông MQTT thông qua broker HiveMQ (`broker.hivemq.com:1883`). Đóng vai trò là kênh trung chuyển dữ liệu hai chiều giữa thiết bị tại cổng và máy chủ quản trị.
3. **Tầng 3 – Xử lý trung gian và tự động hóa (Middleware Layer):** Triển khai bằng nền tảng Node-RED đóng gói trong môi trường container Docker. Đóng vai trò là bộ não điều phối trung tâm: tiếp nhận các sự kiện từ MQTT, chuẩn hóa dữ liệu vào mô hình trạng thái duy nhất, thực thi 4 quy tắc tự động hóa và quản lý lưu trữ tệp dữ liệu bền vững.
4. **Tầng 4 – Ứng dụng quản trị (Application Layer):** Cung cấp giao diện Web Dashboard trực quan chia làm 3 tab trên nền tối, hỗ trợ nhân viên bảo vệ và người quản lý theo dõi số lượng xe, điều khiển barie từ xa, chỉnh sửa thẻ, cập nhật giá và xuất báo cáo đối soát.

![Hình 3.1: Sơ đồ kiến trúc tổng thể 4 tầng và luồng dữ liệu hai chiều](figures/fig_3_1_arch_4layer.png)
*Hình 3.1: Sơ đồ kiến trúc tổng thể 4 tầng và luồng dữ liệu hai chiều.*

#### 3.2.2. Triết lý thiết kế cốt lõi: Xử lý tại biên (Edge Computing)
Điểm khác biệt quan trọng nhất trong thiết kế của nhóm là **không để cổng phụ thuộc vào máy chủ trung tâm**:
* **Hạn chế của mô hình tập trung truyền thống:** Khi xe quẹt thẻ, nếu thiết bị phải gửi mã thẻ lên server và chờ phản hồi qua Internet thì sẽ gặp độ trễ mạng từ 0,5 đến 2 giây. Nguy hiểm hơn, nếu đường truyền mạng đứt hoặc máy chủ bảo trì, toàn bộ bãi xe bị tê liệt hoàn toàn.
* **Giải pháp của đồ án:** ESP32 được thiết kế như một nút xử lý biên thông minh (Edge Node). Toàn bộ danh sách 16 thẻ xe, trạng thái 2 ô đỗ và bảng giá được lưu trực tiếp trong bộ nhớ RAM của ESP32. Khi khách quẹt thẻ, vi điều khiển tự đối chiếu mã UID, tự phân luồng vào/ra, tự tính cước phí và quyết định mở barie trong vòng chưa đầy 50 mili-giây. Sau khi hoàn tất thao tác mở cửa, ESP32 mới phát bản tin báo cáo lên tầng trên qua MQTT.
* Nhờ nguyên lý này, kể cả khi rớt mạng Wi-Fi hoặc tắt máy chủ Node-RED, xe cộ tại cổng vẫn vào/ra bình thường. Khi kết nối mạng phục hồi, dữ liệu hiện trường sẽ được đồng bộ ngược trở lại lên web.

#### 3.2.3. Thiết kế luồng dữ liệu hai chiều (Uplink và Downlink)
Dữ liệu luân chuyển trong hệ thống theo hai hướng tách biệt:
* **Luồng dữ liệu đi lên (Uplink):** Xuất phát từ ESP32 tại Tầng 1 gửi lên MQTT Broker để Tầng 3 và Tầng 4 tiếp nhận. Gồm 4 luồng chính:
  1. *Sự kiện quẹt thẻ (`rfid/scan`):* Bắn lên ngay khi có lượt xe vào hoặc ra hợp lệ (kèm biển số, mã thẻ, ô đỗ, cước phí).
  2. *Trạng thái thanh chắn (`barie/status`):* Cập nhật tức thời góc mở Servo, trạng thái đóng/mở và nguồn phát lệnh.
  3. *Cảnh báo bất thường (`alert`):* Báo động ngay các sự cố như quẹt thẻ chưa đăng ký, quẹt thẻ bị khóa, bãi đã đầy hoặc có vật cản dưới cần barie.
  4. *Ảnh chụp toàn bãi (`status`):* Cung cấp snapshot toàn diện gồm trạng thái online, số xe đang đỗ, chi tiết từng ô và độ mạnh Wi-Fi.
* **Luồng dữ liệu đi xuống (Downlink):** Xuất phát từ thao tác của người quản trị trên Web Dashboard (Tầng 4) hoặc từ các luật tự động của Node-RED (Tầng 3) truyền xuống cổng:
  1. *Lệnh điều khiển barie (`barie/cmd`):* Truyền các lệnh mở khẩn cấp, giữ mở hoặc hạ barie xuống ESP32.
  2. *Cấu hình hệ thống (`config`):* Đẩy toàn bộ danh sách thẻ mới và bảng giá vừa chỉnh sửa trên web xuống ESP32 dạng tin nhắn `retained` để vi điều khiển cập nhật ngay mà không cần nạp lại code.

---

### 3.3. Thiết kế Tầng 1 – Lựa chọn phần cứng và sơ đồ kết nối

#### 3.3.1. Phân tích lựa chọn linh kiện phần cứng
Việc lựa chọn linh kiện cho Tầng 1 dựa trên sự cân bằng giữa tính năng kỹ thuật, độ tin cậy và khả năng mô phỏng sát với thực tế:
* **Bộ điều khiển trung tâm (ESP32 DevKit V1):** Sở hữu vi xử lý 32-bit lõi kép tốc độ 240 MHz, bộ nhớ SRAM 520 KB và tích hợp sẵn Wi-Fi chuẩn 802.11 b/g/n. Cấu hình này hoàn toàn vượt trội so với các dòng vi điều khiển 8-bit (như Arduino Uno), đủ khả năng quản lý mảng thẻ nhớ, xử lý chuỗi JSON, điều khiển đa ngoại vi và duy trì kết nối mạng thời gian thực mà không bị quá tải.
* **Mô-đun đọc thẻ RFID-RC522:** Hoạt động ở tần số sóng vô tuyến 13,56 MHz (chuẩn ISO/IEC 14443A), tương thích với hầu hết các loại thẻ từ và thẻ Mifare thông dụng trên thị trường. Mô-đun sử dụng giao thức SPI tốc độ cao giúp đọc mã thẻ định danh UID 4 byte gần như tức thời khi thẻ đến gần mắt đọc.
* **Cảm biến siêu âm HC-SR04:** Sử dụng sóng siêu âm tần số 40 kHz để đo khoảng cách vật thể trong phạm vi từ 2 cm đến 400 cm. Linh kiện này được lựa chọn để giám sát vùng không gian ngay bên dưới thanh chắn barie nhằm chống kẹp xe và người, với độ chính xác cao và không bị ảnh hưởng bởi màu sắc phương tiện.
* **Động cơ Servo SG90:** Động cơ điều khiển góc quay bằng tín hiệu xung PWM (chu kỳ 20 ms / 50 Hz), góc quay linh hoạt từ 0° (đóng thanh chắn ngang) đến 90° (nâng thanh chắn thẳng đứng), phù hợp cho mô hình cổng barie thu nhỏ.
* **Màn hình LCD 1602 kèm mạch I2C:** Màn hình 2 dòng, mỗi dòng 16 ký tự, dùng hiển thị trực quan thông tin biển số xe, số ô đỗ, cước phí và lý do từ chối ngay tại cổng. Việc tích hợp chip chuyển đổi I2C (địa chỉ mặc định `0x27`) giúp thu gọn giao tiếp từ 16 chân song song xuống chỉ còn 2 chân tín hiệu (SDA và SCL), tiết kiệm tài nguyên chân GPIO cho ESP32.
* **Còi báo (Active Buzzer) và Đèn LED 2 màu:** Còi chip chủ động tạo âm thanh phản hồi nhanh theo nhịp; đèn LED Đỏ báo hiệu dừng (cổng đóng hoặc từ chối) và đèn LED Xanh báo hiệu cho phép xe di chuyển qua cổng.

#### 3.3.2. Sơ đồ phân bổ chân GPIO và giải pháp chống xung đột phần cứng
Tất cả 7 linh kiện ngoại vi được đấu nối vào các chân GPIO chuyên dụng của ESP32 như tổng hợp tại Bảng 3.2:

| Linh kiện ngoại vi | Chân linh kiện | Chân ESP32 (GPIO) | Chuẩn giao tiếp | Nguồn cấp | Chức năng chi tiết trong hệ thống |
| :--- | :--- | :---: | :---: | :---: | :--- |
| **RFID-RC522** | `SDA(SS)`, `SCK`, `MOSI`, `MISO`, `RST` | `5`, `18`, `23`, `19`, `4` | SPI | 3,3V | Đọc mã UID thẻ từ tần số 13,56 MHz qua bus SPI |
| **HC-SR04** | `TRIG`, `ECHO` | `27`, `32` | Digital I/O | 5V | Phát xung và đo thời gian dội sóng để tính khoảng cách vật cản |
| **Servo SG90** | `PWM` | `13` | PWM (50 Hz) | 5V | Nâng/hạ thanh chắn barie (góc 0° khi đóng, 90° khi mở) |
| **LED Đỏ / Xanh** | `Anode (+)` | `25` / `26` | Digital Output | 3,3V | Đèn tín hiệu giao thông (Đỏ = Dừng lại, Xanh = Mời đi) |
| **Active Buzzer** | `Signal` | `14` | LEDC Channel 15 | 3,3V | Phát âm thanh bíp phản hồi thao tác và báo động an ninh |
| **LCD 1602 I2C** | `SDA`, `SCL` | `21`, `22` | I2C (`0x27`) | 5V | Hiển thị biển số xe, số ô đỗ, số tiền thu và lý do từ chối |

*Bảng 3.2: Sơ đồ đấu nối chân linh kiện phần cứng trên ESP32.*

> **Phân tích giải pháp kỹ thuật chống xung đột Timer:** Trên vi điều khiển ESP32, thư viện Servo (`ESP32Servo`) và hàm phát âm thanh thông thường (`tone()`) đều cần sử dụng các bộ định thời phần cứng (Hardware Timer). Nếu cấu hình không cẩn thận, tín hiệu điều khiển còi sẽ chiếm dụng timer của Servo, dẫn đến hiện tượng thanh chắn barie bị rung giật hoặc mất kiểm soát góc quay. Nhóm giải quyết triệt để vấn đề này bằng cách cấu hình còi Buzzer chạy trên **kênh LEDC 15 độc lập** (sử dụng Timer 3 riêng biệt), hoàn toàn tách rời khỏi các timer điều khiển góc xoay của Servo.

#### 3.3.3. Phân tích các lưu ý kỹ thuật khi chuyển từ mô phỏng sang mạch thật
Mô hình hiện được kiểm thử hoàn chỉnh trên trình giả lập Wokwi. Để hệ thống hoạt động ổn định và an toàn khi lắp ráp mạch phần cứng thực tế ngoài đời, nhóm phân tích và đề xuất 3 giải pháp kỹ thuật bắt buộc:
1. **Nối chung đường mass (Common Ground):** Nguồn cấp cho vi điều khiển (3,3V) và nguồn cấp cho các linh kiện tải lớn (5V) phải được nối chung đường GND với nhau. Nếu không chung mass, mức logic 0V giữa các linh kiện sẽ bị lệch, làm cho đầu đọc RFID đọc sai dữ liệu và cảm biến siêu âm phát tín hiệu chập chờn.
2. **Tách nguồn cấp công suất riêng cho Servo SG90:** Khi động cơ servo khởi động hoặc xoay cần gạt gập góc, dòng tiêu thụ tức thời có thể vọt lên 500mA – 1A. Nếu lấy nguồn 5V trực tiếp từ chân `VIN` của board ESP32, hiện tượng sụt áp nguồn cấp sẽ xảy ra ngay lập tức, kích hoạt mạch bảo vệ brown-out làm ESP32 bị reset liên tục. Do đó, mạch thật bắt buộc phải dùng nguồn 5V rời (adapter hoặc nguồn xung riêng) cấp trực tiếp cho chân dương của Servo, đồng thời gắn thêm tụ hóa lọc nguồn 100µF – 470µF để gánh dòng khởi động.
3. **Cầu phân áp điện áp bảo vệ chân ECHO của HC-SR04:** Cảm biến siêu âm HC-SR04 dùng nguồn nuôi 5V nên tín hiệu xung trả về ở chân `ECHO` có mức điện áp 5V logic. Trong khi đó, các chân GPIO của vi điều khiển ESP32 chỉ chịu được mức điện áp tối đa là 3,3V. Nếu nối trực tiếp chân ECHO vào GPIO 32 trong thời gian dài sẽ làm cháy cổng đầu vào của chip. Mạch thật cần lắp thêm cầu phân áp gồm hai điện trở (điện trở 1 kΩ nối tiếp và điện trở 2 kΩ kéo xuống mass) để hạ mức điện áp từ 5V xuống mức an toàn xấp xỉ 3,3V.

---

### 3.4. Thiết kế giải thuật xử lý tại cổng và Máy trạng thái Barie

#### 3.4.1. Giải thuật xử lý quẹt thẻ RFID và phân luồng nghiệp vụ
Quy trình nghiệp vụ tại cổng được tổ chức thành một chuỗi logic chặt chẽ, chia làm 3 giai đoạn độc lập:

![Hình 3.2: Lưu đồ xử lý thẻ RFID và kiểm tra chống kẹp barie tại cổng](figures/fig_3_2_flow_rfid.png)
*Hình 3.2: Lưu đồ thuật toán xử lý quẹt thẻ RFID và kiểm tra chống kẹp barie tại cổng.*

* **Giai đoạn 1 – Tiếp nhận và Xác thực thẻ:**
  1. *Đọc và Chuẩn hóa UID:* Khi khách đưa thẻ vào phạm vi quét của đầu đọc RC522, vi điều khiển thu nhận 4 byte định danh và chuẩn hóa thành chuỗi ký tự lục phân viết hoa cách nhau bằng khoảng trắng (ví dụ: `01 02 03 04`). Việc chuẩn hóa giúp việc tìm kiếm trong danh sách không bị nhầm lẫn giữa chữ hoa và chữ thường.
  2. *Cơ chế chống đọc lặp (Card Debounce 1.500 ms):* Trong thực tế, người gửi xe thường có thói quen cầm giữ thẻ trước đầu đọc vài giây hoặc tay bị run. Nếu không xử lý, đầu đọc sẽ quét liên tục 5–10 lần trong một giây, làm hệ thống hiểu nhầm khách vừa vào xong lập tức quẹt ra ngay. Nhóm thiết lập cơ chế so sánh mốc thời gian: nếu cùng một mã UID được quẹt liên tiếp trong khoảng thời gian dưới 1,5 giây (khi thanh chắn đang đóng), lần quét đó sẽ bị bỏ qua hoàn toàn.
  3. *Kiểm tra tính hợp lệ:* Hệ thống đối chiếu UID với danh sách 16 thẻ nội bộ. Nếu thẻ chưa được đăng ký trong hệ thống, cổng lập tức từ chối, còi kêu 3 tiếng bíp ngắn, LCD hiển thị thông báo từ chối (`THE CHUA DKY`) và gửi cảnh báo thẻ lạ lên mạng. Nếu thẻ có trong danh sách nhưng đang ở trạng thái bị khóa (do quản trị viên khóa thẻ trên web), cổng từ chối mở và LCD báo `THE BI KHOA`.

* **Giai đoạn 2 – Phân luồng Vào / Ra và Quản lý vị trí đỗ:**
  1. *Phân biệt lượt Vào hay Ra:* Hệ thống kiểm tra trạng thái lưu trú hiện tại của thẻ: nếu thẻ chưa được gán vị trí ô đỗ trong bãi (trạng thái ô bằng 0), hệ thống xác định đây là **Lượt vào**. Nếu thẻ đang được ghi nhận nằm tại Ô 1 hoặc Ô 2, hệ thống xác định đây là **Lượt ra**.
  2. *Xử lý Lượt vào và Kiểm soát sức chứa:* Khi là lượt vào, hệ thống quét tìm ô trống đầu tiên (ưu tiên Ô 1 rồi tới Ô 2). Nếu cả hai ô đều đã có xe (`2/2`), cổng từ chối mở barie, giữ nguyên đèn đỏ, còi bíp cảnh báo và LCD thông báo `BAI DA DAY`. Nếu còn ô trống, hệ thống gán ô đỗ cho thẻ, lưu lại mốc thời gian vào bãi theo bộ đếm thời gian hệ thống và chuyển sang bước mở barie.
  3. *Xử lý Lượt ra và Tính cước phí:* Khi là lượt ra, hệ thống lấy thời điểm hiện tại trừ đi thời điểm vào xe để tính ra tổng số thời gian lưu bãi. Thẻ được xóa ghi nhận vị trí ô đỗ để giải phóng ô cho xe tiếp theo.
     - *Vé tháng:* Cước phí được tính cố định là `0 đồng`.
     - *Vé lượt:* Áp dụng biểu phí bậc thang cấu hình. Để phục vụ kiểm thử và trình diễn trên mô hình mô phỏng, thang thời gian được rút gọn theo giây: đỗ dưới 10 giây tính 3.000đ; từ 10 đến 30 giây tính 5.000đ; trên 30 giây tính 9.000đ. Người quản trị có thể thay đổi các mức giá này từ xa bất kỳ lúc nào. Màn hình LCD hiển thị số tiền thu để tài xế và bảo vệ cùng đối chiếu, còi phát 2 tiếng bíp xác nhận.

* **Giai đoạn 3 – Chấp hành mở cổng và Cơ chế chống kẹp xe an toàn:**
  - Sau khi xác thực vào hoặc ra thành công, Servo kích hoạt xoay cần gạt lên góc 90°, đèn LED chuyển sang Xanh và ESP32 gửi bản tin MQTT Uplink (`rfid/scan`) báo cáo lên hệ thống.
  - Thanh chắn được giữ mở trong khoảng thời gian an toàn thiết kế là **3 giây** để xe bắt đầu di chuyển qua cổng.

#### 3.4.2. Phân tích nguyên lý cảm biến siêu âm chống kẹp xe
Đây là tính năng an toàn cốt lõi giúp hệ thống vượt trội so với các loại barie hẹn giờ thông thường:
* Khi hết thời gian giữ mở 3 giây, vi điều khiển **tuyệt đối không hạ cần ngay**. Hệ thống chuyển sang trạng thái chờ đóng và kích hoạt cảm biến siêu âm HC-SR04 đo khoảng cách vật thể phía dưới cần chắn theo chu kỳ định kỳ mỗi **300 mili-giây**.
* **Trường hợp có vật cản (Khoảng cách đo được $d < 15\text{ cm}$):** Nghĩa là đuôi xe hoặc người vẫn chưa ra khỏi phạm vi thanh chắn. Firmware lập tức tạm hoãn thao tác đóng, tiếp tục giữ Servo ở góc mở 90°, màn hình LCD hiện thông báo hoãn đóng và phát bản tin cảnh báo vật cản lên Dashboard để bảo vệ nắm tình hình. Quá trình kiểm tra lặp lại liên tục sau mỗi 300 ms.
* **Trường hợp an toàn (Khoảng cách $d \ge 15\text{ cm}$):** Khi vùng dưới thanh chắn đã hoàn toàn thông thoáng, Servo mới thực hiện hạ cần từ từ về góc 0°, đèn LED chuyển sang Đỏ và cập nhật trạng thái cổng đã đóng hoàn tất (`barie/status`).

#### 3.4.3. Thiết kế Máy trạng thái Barie (Finite State Machine)
Hoạt động của cổng barie được mô hình hóa bằng máy 3 trạng thái hữu hạn (FSM) chặt chẽ:
1. **`GATE_CLOSED` (Trạng thái Đóng):** Servo ở góc 0°, đèn LED Đỏ sáng. Cổng ở trạng thái nghỉ, sẵn sàng tiếp nhận quẹt thẻ hoặc lệnh mở từ xa.
2. **`GATE_OPEN_TIMED` (Trạng thái Mở có thời hạn):** Kích hoạt khi có lượt quẹt thẻ hợp lệ. Servo quay lên 90°, đèn LED Xanh sáng. Hệ thống đếm đủ 3 giây, sau đó chuyển sang chế độ quét cảm biến siêu âm để hạ cần an toàn về `GATE_CLOSED`.
3. **`GATE_OPEN_HOLD` (Trạng thái Giữ mở thủ công):** Kích hoạt khi nhân viên bảo vệ bấm nút "Mở Barie" trên Dashboard (ví dụ trong các tình huống khẩn cấp như xe cứu hỏa, sự cố mất điện hoặc cần mở thông làn liên tục). Barie sẽ giữ nguyên ở góc 90° vô thời hạn cho tới khi bảo vệ chủ động bấm nút "Đóng Barie" từ xa hoặc có lệnh tự động từ Rule 4; khi hạ xuống, hệ thống vẫn bắt buộc phải kiểm tra qua cảm biến siêu âm chống kẹp.

---

### 3.5. Thiết kế Tầng 2 – Giao thức truyền thông MQTT

#### 3.5.1. Lý do lựa chọn giao thức MQTT
Thay vì sử dụng giao thức HTTP REST API truyền thống, hệ thống chọn giao thức **MQTT (Message Queuing Telemetry Transport)** làm cầu nối liên lạc nhờ các ưu điểm vượt trội trong môi trường IoT:
* **Mô hình Xuất bản / Đăng ký (Publish / Subscribe):** Tách rời hoàn toàn bên gửi và bên nhận. Thiết bị ESP32 không cần biết địa chỉ IP của máy chủ Node-RED và ngược lại, cả hai chỉ cần kết nối tới Broker chung. Điều này cho phép hệ thống mở rộng thêm nhiều cổng vào/ra hoặc nhiều màn hình theo dõi mà không cần cấu hình lại mã nguồn.
* **Nhẹ và tiết kiệm băng thông:** Gói tin MQTT có tiêu đề (header) chỉ từ 2 byte, tiêu thụ ít tài nguyên mạng và tiết kiệm pin/RAM tối đa cho vi điều khiển nhúng.
* **Hỗ trợ truyền thông hai chiều thời gian thực:** Cho phép máy chủ phát lệnh điều khiển tức thì xuống thiết bị mà thiết bị không cần phải liên tục gửi request thăm dò (polling) gây lãng phí tài nguyên mạng.

#### 3.5.2. Thiết kế danh mục 6 Topic nghiệp vụ
Hệ thống quy hoạch không gian topic thống nhất dưới tiền tố `parking_n4/` để tránh xung đột với các nhóm khác trên broker công cộng:

| Topic MQTT | Hướng truyền | Chế độ bản tin | Dữ liệu trao đổi (JSON) | Mục đích sử dụng |
| :--- | :---: | :---: | :--- | :--- |
| `parking_n4/rfid/scan` | Uplink | QoS 0, Không Retained | `type`, `uid`, `plate`, `owner`, `slot`, `duration`, `fee` | Báo cáo chi tiết sự kiện xe quẹt thẻ vào/ra hợp lệ |
| `parking_n4/barie/status` | Uplink | QoS 0, **Retained** | `state` (open/closed), `angle`, `mode`, `src` | Đồng bộ trạng thái thực tế của cần barie lên web |
| `parking_n4/alert` | Uplink | QoS 0, Không Retained | `type` (INVALID_CARD, LOT_FULL, ANTI_PINCH...), `msg` | Báo động tức thời các sự cố an ninh và vật cản |
| `parking_n4/status` | Uplink | QoS 0, **Retained + LWT** | `online`, `total`, `capacity`, `slots` (thông tin 2 ô), `rssi` | Snapshot toàn diện bãi xe; tự báo ngoại tuyến khi mất nguồn |
| `parking_n4/barie/cmd` | Downlink | QoS 1, Không Retained | `cmd` (open, close, open_hold, sync), `src` | Truyền lệnh điều khiển thanh chắn barie từ xa |
| `parking_n4/config` | Downlink | QoS 1, **Retained** | `v`, `p` (bảng giá 3 bậc), `c` (danh sách 16 thẻ xe) | Cập nhật thẻ và giá từ xa xuống ESP32 không cần nạp code |

*Bảng 3.3: Danh mục 6 topic MQTT nghiệp vụ và thông tin trao đổi.*

#### 3.5.3. Phân tích hai cơ chế đặc thù: Retained Messages và Last Will (LWT)
Đồ án khai thác triệt để hai cơ chế cao cấp của MQTT để giải quyết triệt để bài toán đồng bộ trạng thái khi kết nối mạng chập chờn:
1. **Cơ chế Lưu giữ bản tin (Retained Message):**
   - *Nguyên lý:* Khi một bản tin được gửi kèm cờ `retained = true`, Broker sẽ lưu giữ lại bản tin mới nhất của topic đó. Bất kỳ khi nào có một thiết bị mới kết nối vào và đăng ký (subscribe) topic này, Broker lập tức gửi ngay bản tin lưu giữ đó mà không cần đợi người phát gửi lại.
   - *Ứng dụng trong đồ án:* Nhóm áp dụng cờ retained cho topic trạng thái barie (`barie/status`), snapshot toàn bãi (`status`) và cấu hình hệ thống (`config`). Nhờ đó, mỗi khi nhân viên mở trình duyệt web lên, Dashboard lập tức hiển thị chính xác số xe đang đỗ và góc mở barie ngoài cổng mà không phải chờ một lượt quẹt xe kế tiếp. Tương tự, mỗi khi ESP32 bị mất mạng rồi có lại, vi điều khiển nhận ngay cấu hình thẻ và bảng giá mới nhất từ máy chủ.
2. **Cơ chế Di chúc (Last Will and Testament - LWT):**
   - *Nguyên lý:* Khi ESP32 thiết lập kết nối tới Broker, nó gửi kèm một bản tin "di chúc" dự phòng đăng ký trên topic `parking_n4/status` với nội dung `{"online":false}` có cờ retained. Trong quá trình vận hành bình thường, bản tin này nằm im ở Broker.
   - *Ứng dụng trong đồ án:* Nếu ESP32 bị rút phích cắm nguồn đột ngột, đứt dây mạng hoặc sập nguồn, Broker sẽ phát hiện kết nối TCP bị ngắt mà không qua thủ tục ngắt kết nối chuẩn. Broker lập tức tự động phát bản tin di chúc đó tới Node-RED. Nhờ cơ chế này, Dashboard lập tức chuyển trạng thái cổng sang **Mất kết nối (Offline)** kèm đèn đỏ cảnh báo, giúp bảo vệ phát hiện sự cố phần cứng ngay lập tức.

#### 3.5.4. Lựa chọn Broker mô phỏng và kế hoạch triển khai thực tế
* **Giai đoạn thử nghiệm hiện tại:** Đồ án sử dụng public broker của HiveMQ (`broker.hivemq.com:1883`). HiveMQ là nhà cung cấp giải pháp MQTT hàng đầu thế giới, broker công cộng của họ có độ ổn định cao, hỗ trợ kiểm thử từ nhiều máy tính khác nhau và chạy trực tiếp trên máy ảo Wokwi mà không đòi hỏi thiết lập mạng phức tạp.
* **Giai đoạn triển khai thực tế:** Trong tệp `docker-compose.yml`, nhóm đã cấu hình sẵn một dịch vụ Broker mã nguồn mở `eclipse-mosquitto:2.0` chạy độc lập trong mạng nội bộ. Khi đưa vào hoạt động thực tế tại một bãi xe cụ thể, hệ thống sẽ trỏ toàn bộ kết nối về Mosquitto cục bộ này, đồng thời kích hoạt chứng thực tài khoản (Username/Password), phân quyền truy cập ACL và mã hóa đường truyền bằng chứng chỉ bảo mật TLS/SSL qua cổng 8883 để đảm bảo an ninh thông tin tuyệt đối.

---

### 3.6. Thiết kế Tầng 3 – Tầng trung gian và Bộ 4 quy tắc tự động hóa Node-RED

#### 3.6.1. Vai trò của Tầng xử lý trung gian (Middleware)
Tầng trung gian Node-RED đóng vai trò làm cầu nối giữa luồng dữ liệu thô từ cổng và giao diện hiển thị cho người dùng:
* **Không can thiệp vào nghiệp vụ thời gian thực tại cổng:** Node-RED không đưa ra quyết định xe được vào hay không được vào, nhằm giữ đúng nguyên tắc xử lý tại biên của ESP32.
* **Hợp nhất dữ liệu và duy trì trạng thái:** Tiếp nhận các thông điệp JSON rời rạc từ các topic MQTT, phân tích và gom chung vào một cấu trúc dữ liệu toàn cục duy nhất.
* **Bộ máy thực thi luật tự động (Rule Engine):** Giám sát các điều kiện bất thường và tự động phát cảnh báo hoặc gửi lệnh can thiệp.

![Hình 3.3: Luồng xử lý dữ liệu và 4 quy tắc tự động trong Node-RED](figures/fig_3_3_flow_nodered.png)
*Hình 3.3: Luồng xử lý dữ liệu và 4 quy tắc tự động trong Node-RED.*

#### 3.6.2. Thiết kế mô hình dữ liệu và trạng thái tập trung của bãi xe
Trong các hệ thống IoT thời gian thực, dữ liệu gửi đến máy chủ từ nhiều nguồn bất đồng bộ (sự kiện quẹt thẻ, snapshot định kỳ, cảnh báo an ninh, lệnh điều khiển từ người dùng, gói tin Last Will khi mất kết nối). Nếu hệ thống lưu trữ trạng thái phân tán ở từng khối xử lý giao diện riêng biệt sẽ dẫn đến hiện tượng bất đồng bộ dữ liệu (Data Inconsistency) — ví dụ một tab hiển thị còn chỗ nhưng tab khác lại hiển thị đã đầy.

Để giải quyết triệt để vấn đề này, kiến trúc Tầng 3 áp dụng nguyên lý **Kho dữ liệu trạng thái duy nhất (Single Source of Truth)** kết hợp mẫu thiết kế **Bộ điều phối tập trung (Centralized Dispatcher)**. Mọi luồng dữ liệu đi vào (từ MQTT Uplink) hoặc thao tác từ giao diện người dùng (Dashboard) đều được dẫn về một khối điều phối duy nhất. Khối này thực hiện chuẩn hóa, cập nhật vào một mô hình trạng thái bãi xe tập trung duy nhất, sau đó mới phân phối đồng bộ tới các thành phần hiển thị và module lưu trữ bền vững.

Cấu trúc mô hình trạng thái bãi xe được chuẩn hóa gồm 7 nhóm trường dữ liệu cốt lõi (Bảng 3.4):

| Nhóm dữ liệu | Tên thuộc tính | Kiểu dữ liệu logic | Ý nghĩa thiết kế và vai trò trong hệ thống |
| :--- | :--- | :---: | :--- |
| **Kết nối mạng** | `online` | Boolean | Ghi nhận trạng thái trực tuyến hoặc ngoại tuyến của vi điều khiển ESP32 tại cổng (cập nhật qua LWT và snapshot) |
| **Sức chứa bãi** | `capacity`, `total` | Số nguyên (Integer) | Sức chứa tối đa của bãi xe (thiết kế 2 ô) và tổng số phương tiện đang lưu bãi tại thời điểm hiện tại |
| **Chi tiết ô đỗ** | `slots` | Đối tượng bản ghi | Trạng thái chiếm dụng (`occupied`), biển số xe, tên chủ xe và mốc thời gian vào bãi của từng vị trí ô (Ô 1 và Ô 2) |
| **Trạng thái cổng** | `gate` | Đối tượng bản ghi | Trạng thái thanh chắn (`state`: đóng/mở), góc quay hiện tại của động cơ servo (0°–90°) và thời điểm chuyển trạng thái gần nhất |
| **Biểu phí gửi xe** | `pricing` | Đối tượng cấu hình | Chế độ tính cước (tính phí hoặc miễn phí), các mốc thời gian bậc thang và định mức tiền thu tương ứng |
| **Danh mục thẻ xe**| `cards` | Danh sách bản ghi | Quản lý danh sách tối đa 16 thẻ RFID (mã UID, tên chủ xe, biển số, phân loại vé lượt/vé tháng, cờ khóa thẻ) |
| **Lịch sử giao dịch**| `history`| Danh sách bản ghi | Lưu trữ danh sách 100 giao dịch ghép cặp vào–ra gần nhất phục vụ việc tra cứu, đối soát doanh thu và xuất báo cáo CSV |

*Bảng 3.4: Đặc tả các trường dữ liệu trong mô hình trạng thái tập trung của bãi xe.*

Nguyên tắc thiết kế này giúp tách biệt hoàn toàn giữa **dữ liệu trạng thái (State)** và **giao diện hiển thị (Presentation)**: các khối giao diện chỉ đóng vai trò đọc dữ liệu và vẽ lại thành phần trực quan, không được tự ý sửa đổi biến trạng thái độc lập. Khi có bất kỳ thay đổi nào, toàn bộ giao diện của cả 3 tab đều được cập nhật tức thời và đồng nhất.

#### 3.6.3. Thiết kế Bộ 4 quy tắc tự động hóa (Automated Rules Engine)
Hệ thống thiết lập một nhịp quét định kỳ mỗi giây một lần (kích hoạt bằng node Inject) để kiểm tra 4 quy tắc tự động hóa vận hành liên tục (Bảng 3.5):

| Quy tắc | Điều kiện kích hoạt | Ngưỡng demo | Ngưỡng thực tế đề xuất | Hành động xử lý của hệ thống |
| :--- | :--- | :---: | :---: | :--- |
| **Rule 1: Xe gửi quá giờ** | Thời gian xe đỗ trong ô vượt quá ngưỡng cài đặt | 30 giây | 4–12 giờ tùy ca | Đổi viền ô đỗ sang vàng nhấp nháy, gắn nhãn `QUÁ GIỜ`, hiện thông báo nhắc nhở |
| **Rule 2: Bãi xe đã đầy** | Cả 2 ô đỗ đều đã có xe hoặc nhận cảnh báo `LOT_FULL` từ cổng | 2/2 xe | 50–500 xe | Đổi thẻ KPI Tổng quan sang màu đỏ cảnh báo; việc chặn xe ngoài cổng do ESP32 tự làm |
| **Rule 3: Dò thẻ lạ liên tục** | Phát hiện quẹt thẻ không hợp lệ nhiều lần trong cửa sổ thời gian | $\ge$ 3 lần / 60s | $\ge$ 5 lần / 120s | Nâng cấp mức an ninh lên cảnh báo đỏ (`Rule 3 · Nghi vấn dò thẻ`), phát chuông báo động |
| **Rule 4: Kẹt barie mở quá lâu** | Thanh chắn giữ mở liên tục vượt quá thời gian khi ESP32 trực tuyến | 10 giây | 30–60 giây | Node-RED tự động phát lệnh `close` qua MQTT (cổng vẫn kích hoạt siêu âm chống kẹp) |

*Bảng 3.5: Bộ 4 quy tắc tự động hóa trên Node-RED.*

---

### 3.7. Thiết kế Tầng 4 – Giao diện Web Dashboard và An ninh hệ thống

#### 3.7.1. Phân tích nhu cầu người dùng và bố cục giao diện 3 Tab
Giao diện quản trị được xây dựng trên bộ thư viện `node-red-dashboard`, thiết kế theo chủ đề nền tối (Dark Theme) để giảm mỏi mắt cho nhân viên trực ban vào ban đêm, bố cục chia làm 3 tab chức năng riêng biệt:
* **Tab 1 – Giám sát trực ban (Dành cho nhân viên bảo vệ tại cổng):**
  - *Hàng thẻ KPI tổng quan:* 4 thẻ hiển thị nhanh số xe đang đỗ kèm thanh đo lấp đầy phần trăm, trạng thái barie (Đóng/Mở), tình trạng kết nối thiết bị (Online/Offline) và tổng doanh thu thu được trong ca trực.
  - *Sơ đồ trực quan 2 ô đỗ xe:* Ô trống hiển thị màu xanh nhạt; ô có xe hiển thị biển số, tên chủ xe, mốc giờ vào và bộ đếm thời gian đỗ theo thời gian thực. Nếu xe đỗ quá giờ quy định, ô tự động đổi viền sang màu vàng cảnh báo.
  - *Bảng điều khiển barie và Cảnh báo an ninh:* Thanh giả lập góc quay barie (0°–90°) kèm hai nút bấm điều khiển khẩn cấp `MỞ BARIE` và `ĐÓNG BARIE`. Banner cảnh báo phía trên tự động đổi màu và hiện chi tiết nội dung sự cố khi các quy tắc tự động bị kích hoạt.
  - *Bảng nhật ký sự kiện:* Hiển thị danh sách 12 sự kiện gần nhất cùng biểu đồ thống kê thời gian lưu bãi.
* **Tab 2 – Quản lý Thẻ và Bảng giá (Dành cho người quản lý bãi xe):**
  - *Biểu mẫu cấu hình thẻ:* Cho phép thêm thẻ mới, sửa thông tin chủ xe/biển số, chuyển đổi giữa vé lượt và vé tháng (vé tháng được miễn phí cước 0đ), bật/tắt công tắc khóa thẻ (khi phát hiện thẻ bị mất) và xóa thẻ khỏi danh sách.
  - *Nút tiện ích "Lấy UID này":* Khi một người lạ quẹt thẻ chưa đăng ký tại cổng, hệ thống bắt được mã UID và kích hoạt nút `Lấy UID này` trên web. Quản lý chỉ cần nhấp một nút là mã thẻ tự động điền vào ô đăng ký, không cần phải gõ thủ công từng ký tự mã thẻ hex phức tạp.
  - *Biểu mẫu điều chỉnh bảng giá:* Chuyển đổi giữa chế độ tính phí và miễn phí toàn bãi; điều chỉnh 3 khung thời gian và số tiền tương ứng; thay đổi ngưỡng cảnh báo quá giờ của Rule 1.
* **Tab 3 – Lịch sử Giao dịch và Đối soát (Dành cho kế toán và quản lý):**
  - *Bảng ghép cặp giao dịch:* Tự động ghép nối lượt vào và lượt ra của cùng một thẻ xe thành một dòng giao dịch hoàn chỉnh gồm: Mã giao dịch, Biển số, Chủ xe, Vị trí ô, Thời điểm vào, Thời điểm ra, Tổng thời gian gửi, Số tiền đã thu và Trạng thái hoàn tất.
  - *Bộ lọc tìm kiếm:* Tìm kiếm tức thời theo biển số xe hoặc mã thẻ; lọc danh sách theo xe đang gửi hay xe đã thanh toán rời bãi.
  - *Xuất báo cáo CSV:* Cung cấp nút `Tải file CSV` để xuất toàn bộ danh sách giao dịch về máy tính. Dữ liệu được mã hóa chuẩn UTF-8 có chèn ký tự BOM (`\uFEFF`) để khi mở trực tiếp bằng phần mềm Microsoft Excel không bị lỗi phông chữ tiếng Việt có dấu.

#### 3.7.2. Thiết kế cơ chế an ninh và phân quyền truy cập
Để bảo vệ hệ thống khỏi các can thiệp trái phép qua mạng nội bộ, thiết kế an ninh áp dụng mô hình xác thực hai lớp:
* **Bảo vệ bề mặt vận hành Dashboard (`/ui`):** Sử dụng phương thức xác thực chuẩn HTTP Basic Auth (`httpNodeAuth`). Mọi trình duyệt truy cập vào đường dẫn điều khiển bắt buộc phải đăng nhập tài khoản quản trị viên (`admin:Nhom4@2026`). Mật khẩu không lưu dạng văn bản thô mà được băm một chiều bằng thuật toán mã hóa công nghiệp `bcrypt` trong tệp cấu hình `settings.js`. Các truy cập không có thông tin xác thực đều bị máy chủ từ chối với mã lỗi `401 Unauthorized`.
* **Bảo vệ trình soạn thảo luồng Node-RED Editor (`/`):** Cấu hình tính năng `adminAuth` mã hóa bcrypt để khóa hoàn toàn giao diện lập trình luồng. Nhân viên trực ban chỉ được phép thao tác trên giao diện Dashboard, không thể tự ý thay đổi sơ đồ khối hoặc cấu hình logic của hệ thống.

---

### 3.8. Thiết kế cấu trúc dữ liệu và Cơ chế lưu trữ bền vững

#### 3.8.1. Phân tích lý do chọn lưu trữ dạng tệp thay cho hệ quản trị CSDL rời
Trong quá trình thiết kế hệ thống, nhóm cân nhắc giữa hai phương án: cài đặt một hệ quản trị cơ sở dữ liệu độc lập (như MySQL, PostgreSQL, MongoDB) hoặc sử dụng giải pháp lưu trữ dạng tệp trực tiếp trong Node-RED:
* **Hạn chế của phương án dùng CSDL rời:** Việc chạy thêm một máy chủ database độc lập sẽ làm tăng đáng kể lượng RAM tiêu thụ của container Docker (thường tốn thêm 200MB – 500MB RAM), đòi hỏi cấu hình mạng phức tạp và làm chậm thời gian khởi động hệ thống. Nếu CSDL bị treo, toàn bộ luồng xử lý của Node-RED cũng bị nghẽn theo.
* **Hiệu quả của giải pháp tệp phẳng kết hợp (Flat-file Storage):** Với quy mô bãi xe mô phỏng quản lý tối đa 16 thẻ và lưu trữ lịch sử 100 giao dịch gần nhất, dữ liệu có dung lượng chỉ vài chục kilobyte. Nhóm quyết định sử dụng mô hình kết hợp hai tệp lưu trữ nội bộ:
  1. *Tệp nhật ký nối tiếp (`parking_log.txt`):* Ghi bổ sung (append-only) từng dòng văn bản theo thời gian thực mọi sự kiện phát sinh (xe vào, xe ra, cảnh báo chống kẹp, thẻ lạ, kích hoạt rule, lỗi mạng). Tệp này giúp lập trình viên và người quản trị có thể mở đọc kiểm tra trực tiếp bằng các công cụ văn bản đơn giản mà không cần cài phần mềm chuyên dụng.
  2. *Tệp cơ sở dữ liệu cấu trúc (`parking_database.json`):* Lưu trữ ảnh chụp có cấu trúc JSON của toàn bộ hệ thống gồm cấu hình bảng giá, danh sách 16 thẻ xe, trạng thái xe trong 2 ô đỗ, thống kê doanh thu và mảng 100 giao dịch ghép cặp gần nhất.

#### 3.8.2. Thiết kế vùng lưu trữ Docker Volume và Cơ chế khôi phục sau sự cố
Để đảm bảo dữ liệu không bị biến mất khi tắt máy hoặc cập nhật container Docker, nhóm cấu hình cơ chế liên kết thư mục (bind mount):
* Thư mục vật lý `data/` trên máy tính chủ được ánh xạ thẳng vào đường dẫn `/data/storage` bên trong container Node-RED thông qua biến môi trường `PARKING_DATA_DIR` trong tệp `docker-compose.yml`. Mọi thao tác ghi tệp của Node-RED đều được lưu trực tiếp xuống ổ cứng của máy tính chủ.
* **Cơ chế khôi phục trạng thái tức thì sau sự cố (`docker restart`):**
  - Khi dịch vụ Node-RED bị khởi động lại hoặc container bị tắt đột ngột, trong sự kiện khởi động ban đầu (On Start), hệ thống tự động đọc lại tệp `parking_database.json` từ đĩa cứng và nạp ngược trở lại vào mô hình trạng thái bãi xe trong bộ nhớ. Toàn bộ danh sách thẻ, bảng giá và lịch sử giao dịch trước đó được khôi phục 100%.
  - Đồng thời, Node-RED kết nối lại Broker và nhận ngay bản tin snapshot (retained) do ESP32 ngoài cổng phát ra trên topic `parking_n4/status`. Dữ liệu snapshot này được đối chiếu với thông tin trong tệp JSON để tái lập chính xác tình trạng 2 ô đỗ ngoài cổng mà không làm mất mát hay sai lệch số liệu.

---

## CHƯƠNG 4. TRIỂN KHAI

### 4.1. Môi trường triển khai
Hệ thống được phát triển, biên dịch và kiểm thử trên hệ điều hành Windows; Node-RED Runtime có thể chạy trực tiếp bằng Node.js hoặc đóng gói một lệnh qua Docker Compose. Bảng 4.1 tổng hợp các công cụ và phiên bản thực tế trích từ nhật ký biên dịch và hạ tầng kiểm thử.

| Thành phần | Công cụ / Thư viện | Phiên bản thực tế | Vai trò |
| :--- | :--- | :--- | :--- |
| Biên dịch nhúng | PlatformIO Core / Platform | Core `6.2.0` (`pio --version`) / `espressif32 (7.1.3)` | Biên dịch firmware cho board `esp32dev` |
| Framework & Toolchain | Arduino-ESP32 / GCC / esptool | `framework-arduinoespressif32 @ 4.20017.260907+sha.dcc1105b` (nhánh 2.0.17), `toolchain-xtensa-esp32 @ 8.4.0+2021r2-patch5`, `esptool.py v4.11.0` | Lõi Arduino-ESP32, trình biên dịch và đóng gói `.bin` |
| Thư viện ESP32 | `MFRC522`, `ESP32Servo`, `LiquidCrystal_I2C`, `PubSubClient`, `ArduinoJson` | `1.4.12`, `3.2.1`, `1.1.4`, `2.8.0`, `7.4.3` | Giao tiếp ngoại vi, JSON và MQTT |
| Mô phỏng phần cứng | Wokwi Simulator (VS Code ext.) | `wokwi-vscode 4.1.0` (nạp `firmware.bin`) | Mô phỏng mạch ESP32 và cảm biến |
| Middleware & UI (Docker) | Node-RED / Node.js / Dashboard | `Node-RED v5.0.10` / `Node.js v24.22.3` / `node-red-dashboard 3.6.6` (`docker logs`) | Xử lý luồng, 4 rule, xác thực và giao diện web |
| Hạ tầng container & Host | Docker Engine / Node.js Host | `Docker 29.5.3` (`docker --version`) / `Node.js v24.22.0` (`node -v`) | Đóng gói `nodered/node-red:latest`, `eclipse-mosquitto:2.0` và chạy script kiểm thử |
| MQTT Broker | HiveMQ Public Broker | `broker.hivemq.com:1883` | Trung chuyển gói tin giữa Wokwi và Node-RED |

*Bảng 4.1: Môi trường công cụ và phiên bản sử dụng khi triển khai.*

**Quy trình khởi chạy lại hệ thống:** (1) Chạy `docker compose up -d --build` (hoặc nhấp đúp `start_docker.bat`) để khởi động Node-RED tại cổng `1880` (tệp `docker-compose.yml` cũng khai báo sẵn dịch vụ `eclipse-mosquitto:2.0` dự phòng, còn luồng hiện tại trỏ thẳng tới `broker.hivemq.com:1883`); (2) Chạy `pio run` để biên dịch `.pio/build/esp32dev/firmware.bin`; (3) Mở `diagram.json` trên VS Code Wokwi và bấm **Play**; (4) Truy cập `http://localhost:1880/ui` và đăng nhập theo cấu hình `settings.js`.

### 4.2. Triển khai Tầng 1 – Thiết bị

#### 4.2.1. Đấu nối mô phỏng trên Wokwi và xử lý xung đột phần cứng
Mạch mô phỏng Tầng 1 khai báo trong `diagram.json` với vi điều khiển `board-esp32-devkit-c-v4` và 7 linh kiện đấu nối theo đúng Bảng 3.2, sử dụng màn hình LCD I2C tại địa chỉ `0x27`. Để còi báo không xung đột bộ định thời PWM với động cơ Servo SG90 trên ESP32, firmware cấp riêng cho còi **kênh LEDC 15** và điều khiển âm thanh hoàn toàn không chặn vòng quét chính.

Ảnh chụp thực tế ở Hình 4.1 ghi nhận tình huống xe `29A-123.45` quẹt thẻ ra bãi (LCD hiển thị `RA: 29A-123.45` / `T:35s 9000d`), đồng thời cảm biến siêu âm HC-SR04 ở cự ly `10,0 cm` nên hệ thống tạm hoãn hạ barie và in log `[GATE] Anti-pinch triggered (dist=10.0cm). Holding barrier open.` trên cửa sổ Terminal.

![Hình 4.1: Mạch mô phỏng Wokwi khi xe ra tính phí và kích hoạt chống kẹp xe](minh_chung_anti_pinch_wokwi.png)
*Hình 4.1: Mạch mô phỏng Wokwi khi xe ra tính phí và kích hoạt chống kẹp xe.*

#### 4.2.2. Tổ chức 4 mô-đun mã nguồn và trích đoạn chống kẹp xe
Mã nguồn firmware phân chia thành 4 mô-đun theo trách nhiệm trong `include/` và `src/`:
* **`Config.h`:** Khai báo chân GPIO, hằng số thời gian (`GATE_HOLD_MS = 3000`, `CARD_DEBOUNCE_MS = 1500`, `ANTI_PINCH_DIST_CM = 15.0`, `ANTI_PINCH_RECHECK = 300`), biểu phí mặc định và 6 topic MQTT.
* **`ParkingSystem`:** Quản lý mảng `_cards` (tối đa 16 thẻ), chuẩn hóa UID dạng thập lục phân viết hoa, cấp phát ô `1..2`, tính cước phí và cập nhật bảng giá/thẻ động thông qua hàm `applyConfig()` (bảo toàn thông tin `slot` và `entryTime` của xe đang gửi trong bãi kể cả khi cấu hình từ web chỉnh sửa hoặc xóa thẻ).
* **`GateController`:** Triển khai máy trạng thái barie (`GATE_CLOSED`, `GATE_OPEN_TIMED`, `GATE_OPEN_HOLD`) và điều khiển Servo SG90 cùng đèn LED Đỏ/Xanh.
* **`MqttService` & `main.cpp`:** Quản lý kết nối Wi-Fi/MQTT và vòng lặp không chặn `loop()` (kèm các lệnh kiểm thử qua Serial như `1`–`4`, `scan`, `open`, `close`, `sonar`, `cards`, `price`, `status`).

Khi barie chuẩn bị đóng, cờ `_closePending = true` kích hoạt chu kỳ đo siêu âm mỗi `300 ms` trong `GateController::update()` (`src/GateController.cpp`, chi tiết đầy đủ tại Phụ lục A):

```cpp
if (!_closePending) return EVT_NONE;
if (_lastCheck != 0 && now - _lastCheck < ANTI_PINCH_RECHECK) return EVT_NONE;
_lastCheck = now;
if (readDistanceCm() < ANTI_PINCH_DIST_CM) {
    if (!_blocked) { _blocked = true; return EVT_OBSTACLE; }
    return EVT_NONE;
}
doClose();
return EVT_CLOSED;
```

### 4.3. Triển khai Tầng 2 – Truyền thông MQTT

#### 4.3.1. Cấu hình kết nối, bộ đệm và LWT
Lớp `MqttService` (`src/MqttService.cpp`) tạo Client ID duy nhất từ mã eFuse của ESP32, thiết lập Wi-Fi `WIFI_STA` với `setAutoReconnect(true)` (chỉ chờ tối đa 10 giây lúc khởi động để không chặn cổng nếu chưa có Wi-Fi). Thư viện `PubSubClient` cấu hình bộ đệm `2560 bytes` (đủ truyền tải trọn gói cấu hình JSON chứa tối đa 16 thẻ), `keepAlive = 15s` và `socketTimeout = 4s`. Khi kết nối tới `broker.hivemq.com:1883`, ESP32 khai báo sẵn gói LWT `{"online":false}` trên topic `parking_n4/status` với `willQos = 1`, `willRetain = true`. Ở phía phát bản tin, ESP32 dùng `QoS 0` cho 4 topic Uplink, còn các node `mqtt out` trên Node-RED phát lệnh và cấu hình Downlink ở `QoS 1`.

#### 4.3.2. Tự kết nối lại và đồng bộ cấu hình
Khi mất mạng, hàm `mqtt.update()` không chặn vòng lặp xử lý tại cổng và gọi `connectMqtt()` thử lại mỗi `5 giây` (`MQTT_RETRY_MS = 5000`). Ngay sau khi phục hồi kết nối, thiết bị đăng ký 2 topic Downlink (`parking_n4/barie/cmd` nhận `open`, `open_hold`, `close`, `sync` và `parking_n4/config` nhận payload cấu hình `{"v":2,"p":{...},"c":[...]}`), đồng thời gọi `onMqttConnected()` phát lại trạng thái barie và bản tin snapshot gồm sức chứa, xe đang gửi trong 2 ô, `uptime` và `RSSI`.

### 4.4. Triển khai Tầng 3 – Xử lý và tự động hóa

#### 4.4.1. Tổ chức luồng Node-RED và trạng thái tập trung
Node-RED thực thi tệp `nodered_flow.json` gồm **69 phần tử JSON** (`50` node xử lý và hiển thị UI, `13` node cấu hình dùng chung gồm `broker_hivemq`, `cfg_ui_base`, 3 tab và 8 group UI, kèm `1` tab flow và `5` khung nhóm trực quan trên Editor). Luồng xử lý bố trí từ trái sang phải theo 4 cụm Uplink, Middleware, Application, Downlink và cụm Khởi động ở phía dưới (Hình 4.2).

![Hình 4.2: Giao diện luồng xử lý Node-RED thực tế chia theo 4 cụm và cụm khởi động](nodered_flow.png)
*Hình 4.2: Giao diện luồng xử lý Node-RED thực tế chia theo 4 cụm và cụm khởi động.*

#### 4.4.2. Bộ điều phối trung tâm và mã xử lý 4 quy tắc
Mọi nhánh đầu vào hội tụ về nút `DISPATCH` để cập nhật đối tượng ngữ cảnh `flow.get('park')`, lưu tối đa 12 nhật ký gần nhất, ghi đồng bộ ra tệp và chuyển qua nút `RENDER` (chỉ phát bản tin cho từng widget UI khi chuỗi JSON đầu ra thay đổi).

Trên xung quét `1 giây`: `RULE1` đối chiếu thời gian lưu bãi của từng ô với ngưỡng `overstaySec` động; `RULE2` theo dõi đủ `2/2` xe và cờ từ chối `LOT_FULL`; `RULE3` đếm `INVALID_CARD` trong cửa sổ 60 giây và nâng mức cảnh báo từ lần thứ 3; `RULE4` kiểm tra barie mở giữ quá 10 giây theo trích đoạn JavaScript cốt lõi dưới đây trước khi phát lệnh đóng tự động xuống ESP32 (mã đầy đủ của luồng đặt tại Phụ lục B):

```javascript
if (g.state === 'open' && now - g.since > 10000 && park.online) {
    if (!park.rule4.sentAt || now - park.rule4.sentAt > 10000) {
        park.rule4.sentAt = now;
        cmd = { payload: { cmd: 'close', src: 'rule4' } };
        flow.set('park', park);
    }
}
```

### 4.5. Triển khai Tầng 4 – Web Dashboard và xác thực

#### 4.5.1. Giao diện giám sát chính Tab 1
Tab 1 (`Giám sát bãi xe`, Hình 4.3) sắp xếp thành hai cột cân đối ở độ phân giải `1440x1080` để người trực theo dõi trọn vẹn trên một màn hình mà không phải cuộn trang: cột trái gồm 4 thẻ KPI tổng quan (`overview`) và bảng 12 nhật ký sự kiện (`park.events`); cột phải gồm sơ đồ 2 ô đỗ (`slots`), khu vực điều khiển barie (`control`) kèm 2 nút `MỞ BARIE` / `ĐÓNG BARIE` (có cảnh báo nếu gửi lệnh lúc ESP32 đang ngoại tuyến), phía dưới là 4 chỉ số vận hành và 2 biểu đồ step thời gian thực (`stats`, `rev`, `occ`).

![Hình 4.3: Giao diện Web Dashboard Tab 1 giám sát bãi xe và điều khiển barie](dashboard_demo.png)
*Hình 4.3: Giao diện Web Dashboard Tab 1 giám sát bãi xe và điều khiển barie.*

#### 4.5.2. Cấu hình xác thực truy cập (`httpNodeAuth` và `adminAuth`)
Tệp `docker/nodered/settings.js` bật đồng thời `httpNodeAuth` (HTTP Basic Auth cho `/ui`, trả mã `401 Unauthorized` kèm header `WWW-Authenticate` khi thiếu hoặc sai mật khẩu) và `adminAuth` (hộp thoại đăng nhập cho Node-RED Editor `/`, Hình 4.4). Mật khẩu được lưu hoàn toàn dưới dạng chuỗi băm `bcrypt` (`$2b$08$...`) hoặc nạp qua hai biến môi trường `NODERED_UI_PASS_HASH` và `NODERED_ADMIN_PASS_HASH`, không chứa mật khẩu dạng văn bản thuần trong mã nguồn.

![Hình 4.4: Giao diện hộp thoại đăng nhập xác thực quản trị Node-RED (`adminAuth`)](nodered_admin_login.png)
*Hình 4.4: Giao diện hộp thoại đăng nhập xác thực quản trị Node-RED (`adminAuth`), đồng thời `/ui` áp dụng `httpNodeAuth` kiểm tra mã `401`/`200`.*

### 4.6. Tính năng mở rộng và đóng gói lưu trữ *(Mở rộng)*
Ngoài 4 tầng IoT và 4 quy tắc tự động cốt lõi của học phần, hệ thống triển khai thêm các phần mở rộng quản trị, đối soát và đóng gói hạ tầng sau:

#### 4.6.1. Quản lý danh sách thẻ động (16 thẻ) và bảng giá động *(Mở rộng)*
Tab 2 (Hình 4.5) cho phép thêm thẻ mới, chỉnh sửa biển số/chủ xe, chuyển `Vé lượt` / `Vé tháng` (`0đ`), `Khóa/Mở khóa` thẻ (`LOCKED_CARD`) và xóa thẻ (tự vô hiệu nút xóa nếu xe của thẻ đó đang gửi trong bãi). Khi vừa quẹt một thẻ lạ trên Wokwi, biểu mẫu tự hiện nút `Lấy UID này` để điền nhanh UID mới; các thay đổi chế độ thu phí, 3 khung giá và ngưỡng Rule 1 được lưu xuống `parking_database.json` và đẩy `retained` qua `parking_n4/config` để `applyConfig()` trên ESP32 cập nhật ngay không cần nạp lại firmware.

![Hình 4.5: Giao diện mở rộng Tab 2 quản lý thẻ RFID và bảng giá động](dashboard_cards_pricing.png)
*Hình 4.5: Giao diện mở rộng Tab 2 quản lý thẻ RFID và bảng giá động.*

#### 4.6.2. Đối soát lịch sử giao dịch và xuất tệp CSV *(Mở rộng)*
Tab 3 (Hình 4.6) ghép cặp từng lượt `check_in` và `check_out` thành dòng giao dịch hoàn chỉnh (`Mã GD`, `Biển số`, `Chủ xe`, `UID`, `Loại vé`, `Ô`, `Giờ vào`, `Giờ ra`, `Thời lượng`, `Cước phí`, `Trạng thái`), hỗ trợ tìm kiếm, lọc trạng thái và nút `Xuất CSV (Excel)` xuất tệp `lich_su_bai_xe.csv` kèm chữ ký UTF-8 BOM giúp Excel hiển thị đúng tiếng Việt.

![Hình 4.6: Giao diện mở rộng Tab 3 tra cứu lịch sử giao dịch và xuất CSV](dashboard_history.png)
*Hình 4.6: Giao diện mở rộng Tab 3 tra cứu lịch sử giao dịch và xuất CSV.*

#### 4.6.3. Lưu trữ bền vững và đóng gói triển khai Docker Compose *(Mở rộng)*
Dữ liệu vận hành được Node-RED ghi đồng thời vào hai tệp trong thư mục `data/` (gắn qua biến `PARKING_DATA_DIR` vào `/data/storage` trong container Docker):
1. **`data/parking_log.txt`:** Ghi nối tiếp mỗi sự kiện một dòng theo định dạng `Ngày Giờ | Loại sự kiện | Biển số/UID | Chi tiết`, ví dụ:
   ```text
   23/11/2026 18:11:41 | Xe vào | 29A-123.45 | Ô 1 · Nguyễn Văn A
   ```
2. **`data/parking_database.json`:** Ghi đè cấu trúc gồm `updated_at`, `capacity`, `pricing`, `cards`, `vehicles_inside`, `stats`, `events` (12 sự kiện gần nhất) và `transactions` (tối đa 100 giao dịch) để nạp lại nguyên vẹn khi dịch vụ khởi động lại.

Cấu hình `docker-compose.yml`, `docker/nodered/Dockerfile` và script `start_docker.bat` tự động cài sẵn `node-red-dashboard@^3.6.6`, nạp `settings.js`, gắn volume dữ liệu và cho phép dựng lại toàn bộ hệ thống trên máy khác chỉ bằng một lệnh `docker compose up -d --build`.

---

## CHƯƠNG 5. KIỂM THỬ VÀ ĐÁNH GIÁ

### 5.1. Phương pháp kiểm thử

#### 5.1.1. Môi trường kiểm thử và bộ dữ liệu thẻ mẫu
Kiểm thử được thực hiện trên Windows, sử dụng Wokwi Simulator để mô phỏng phần cứng ESP32 và Docker để triển khai Node-RED `v5.0.10`. Hệ thống truyền thông qua HiveMQ Public Broker tại `broker.hivemq.com:1883`. Thông tin phiên bản công cụ và sơ đồ chân kết nối đã được trình bày tại Chương 3, Chương 4 và Phụ lục. Bộ dữ liệu đầu vào gồm 4 thẻ RFID mẫu trong Bảng 5.1.

| STT | Ký hiệu / phím Wokwi | Mã UID | Biển số | Chủ xe | Trạng thái ban đầu |
| :---: | :--- | :--- | :--- | :--- | :--- |
| 1 | Thẻ 1 (Blue / `1`) | `01 02 03 04` | `29A-123.45` | Nguyễn Văn A | Đã đăng ký, vé lượt |
| 2 | Thẻ 2 (Green / `2`) | `11 22 33 44` | `51F-999.88` | Trần Thị B | Đã đăng ký, vé lượt |
| 3 | Thẻ 3 (Yellow / `3`) | `55 66 77 88` | `43C-678.90` | Lê Văn C | Đã đăng ký, vé lượt |
| 4 | Thẻ 4 (Red / `4`) | `AA BB CC DD` | *(Chưa gán)* | *(Chưa gán)* | Chưa đăng ký |

*Bảng 5.1: Bộ dữ liệu thẻ RFID mẫu sử dụng trong kiểm thử.*

#### 5.1.2. Cách thức kiểm thử
Nhóm thực hiện kiểm thử theo ba nhóm thao tác:
1. **Kiểm thử firmware trên Wokwi:** Quẹt thẻ mẫu, thay đổi khoảng cách cảm biến siêu âm và đối chiếu phản hồi của Servo, LED, Buzzer, LCD và Serial Monitor.
2. **Kiểm thử MQTT, HTTP Auth và Dashboard:** Sử dụng kịch bản Node.js giả lập bản tin Uplink của ESP32, theo dõi bản tin Downlink và kiểm tra truy cập Dashboard với thông tin xác thực khác nhau.
3. **Kiểm tra Node-RED và dữ liệu lưu trữ:** Kiểm tra cấu hình luồng, giao diện ba tab trên trình duyệt tự động (chi tiết trình bày tại Phụ lục D) và đối chiếu dữ liệu trong thư mục `data/`.

#### 5.1.3. Quy trình ghi nhận kết quả
Một ca kiểm thử được đánh dấu **Đạt** khi kết quả quan sát khớp với yêu cầu và dữ liệu tương ứng được cập nhật đúng. Các ca sử dụng script Node.js giả lập ESP32 được ghi rõ **Đạt (script)** để phân biệt với các ca thao tác trực tiếp trên Wokwi.

### 5.2. Kiểm thử Tầng 1 – Thiết bị
Các ca kiểm thử Tầng 1 tập trung vào nghiệp vụ vào/ra, xử lý bãi đầy, thẻ chưa đăng ký, chống đọc trùng và chống kẹp xe với sức chứa mô phỏng `2` xe, thời gian giữ mở barie `3 giây` và khoảng chống đọc trùng `1,5 giây`. Ca `T1-03` kiểm tra cảm biến siêu âm khi barie chuẩn bị đóng: nếu khoảng cách dưới `15 cm`, thanh chắn giữ mở `90°` và chỉ hạ xuống `0°` khi thông thoáng (kết quả trên Wokwi đã được minh chứng tại Hình 4.1 ở Chương 4).

| Mã | Trường hợp kiểm thử | Phương thức và đầu vào | Kết quả quan sát | Trạng thái |
| :--- | :--- | :--- | :--- | :---: |
| **T1-01** | Xe vào hợp lệ | Wokwi; quẹt thẻ Blue khi bãi `0/2` | Barie mở `90°`, LED xanh, còi 1 tiếng; LCD hiển thị biển số và ô đỗ. Serial ghi nhận UID và ô được cấp | Đạt |
| **T1-02** | Xe ra và tính cước | Wokwi; quẹt lại thẻ Blue sau `35 giây` | Barie mở `90°`, còi 2 tiếng; LCD hiển thị `T:35s` và phí `9000d` (Hình 4.1) | Đạt |
| **T1-03** | Chống kẹp xe | Wokwi; đặt cảm biến ở `10,0 cm` lúc hết giờ giữ mở | Barie tiếp tục mở, LCD báo tạm hoãn đóng; khi khoảng cách `> 15 cm`, barie hạ xuống `0°` (Hình 4.1) | Đạt |
| **T1-04** | Bãi đầy | Wokwi; bãi đã có 2 xe, quẹt thẻ Yellow | ESP32 từ chối xe vào, barie giữ đóng, LED đỏ và LCD báo `BAI XE DA DAY!` | Đạt |
| **T1-05** | Thẻ chưa đăng ký | Wokwi; quẹt thẻ Red (`AA BB CC DD`) | Cổng từ chối, còi 3 tiếng và LCD hiển thị thẻ chưa đăng ký cùng UID | Đạt |
| **T1-06** | Chống đọc trùng | Wokwi; quẹt lặp cùng thẻ trong `< 1,5 giây` | Lần đọc lặp bị bỏ qua, không ghi nhận nhầm thành lượt ra | Đạt |

*Bảng 5.2: Kết quả kiểm thử Tầng 1 trên Wokwi.*

### 5.3. Kiểm thử Tầng 2 – Truyền thông
Các ca kiểm thử Tầng 2 đánh giá truyền thông MQTT hai chiều, đồng bộ cấu hình `retained`, cơ chế LWT và xác thực truy cập Dashboard (Bảng 5.3).

| Mã | Trường hợp kiểm thử | Phương thức và kịch bản | Kết quả quan sát | Trạng thái |
| :--- | :--- | :--- | :--- | :---: |
| **T2-01** | Uplink sự kiện và trạng thái | Script MQTT giả lập ESP32 gửi sự kiện vào/ra, trạng thái barie và cảnh báo | Node-RED nhận đủ bản tin trên các topic Uplink; trạng thái Dashboard khớp kịch bản | Đạt *(script)* |
| **T2-02** | Downlink điều khiển | Nhấn nút mở và đóng barie trên Dashboard | Broker nhận lệnh `open` và `close` trên topic `parking_n4/barie/cmd` | Đạt *(script)* |
| **T2-03** | Downlink cấu hình `retained` | Thay đổi bảng giá và thêm thẻ trên Tab 2 | Bản tin cấu hình JSON được gửi lên `parking_n4/config` với cờ `retain = true` | Đạt *(script)* |
| **T2-04** | Ngắt kết nối và LWT | Ngắt đột ngột kết nối TCP của client mô phỏng mà không gửi gói thoát | Broker phát LWT `{"online":false}`; Dashboard chuyển `NGOẠI TUYẾN` và ghi nhật ký (Hình 5.1) | Đạt *(script)* |
| **T2-05** | Xác thực Dashboard | Gửi yêu cầu `GET /ui/` bằng `curl` khi thiếu, sai và đúng thông tin Basic Auth | Kết quả đo thực tế: `NO_AUTH=401`, `BAD_AUTH=401`, `VALID_AUTH=200` | Đạt |

*Bảng 5.3: Kết quả kiểm thử MQTT, LWT và xác thực truy cập.*

Hình 5.1 ghi nhận kết quả thực nghiệm ca `T2-04` trên Dashboard đang chạy Docker khi client mô phỏng bị ngắt kết nối TCP đột ngột: Broker tự phát thông điệp Last Will `{"online":false}`, thẻ `THIẾT BỊ ESP32` chuyển sang cảnh báo đỏ `NGOẠI TUYẾN` kèm thông báo nổi và dòng log `Mất kết nối thiết bị` lúc `13:51:07` (đồng thời nhật ký sự kiện cũng ghi nhận ca `Rule 4` tự đóng barie trước đó lúc `13:50:50`–`13:50:52` và xe ra `5.000 đ`).

![Hình 5.1: Kết quả kiểm thử mất kết nối đột ngột kích hoạt LWT trên Dashboard](test_ch5_lwt_offline.png)
*Hình 5.1: Kết quả kiểm thử mất kết nối đột ngột kích hoạt LWT trên Dashboard (`T2-04`), kèm nhật ký `Rule 4` và xe ra thu phí.*

### 5.4. Kiểm thử Tầng 3 – Xử lý và tự động hóa
Các ca kiểm thử Tầng 3 đánh giá bốn quy tắc tự động và khả năng khôi phục dữ liệu sau khi Node-RED khởi động lại. Ngưỡng demo gồm `30 giây` quá giờ, `10 giây` barie mở lâu, sức chứa `2` xe và `3 lần` quẹt thẻ không hợp lệ trong `60 giây` (Bảng 5.4).

| Mã | Trường hợp kiểm thử | Điều kiện kiểm thử | Kết quả quan sát | Trạng thái |
| :--- | :--- | :--- | :--- | :---: |
| **T3-01** | Rule 1 – Xe quá giờ | Giữ trạng thái xe gửi quá `30 giây` | Ở giây `31`, Node-RED phát cảnh báo quá giờ, gắn nhãn `QUÁ GIỜ` trên ô đỗ và ghi log (Hình 5.2) | Đạt *(script)* |
| **T3-02** | Rule 2 – Bãi đầy | Gửi `2` lượt check-in (`2/2`) và thêm sự kiện từ chối xe thứ 3 | Tổng quan chuyển cảnh báo đỏ `Bãi đã đầy`; log ghi cảnh báo và sự kiện từ chối (Hình 5.2) | Đạt *(script)* |
| **T3-03** | Rule 3 – Dò thẻ lạ | Gửi `3` sự kiện thẻ không hợp lệ trong cửa sổ `60 giây` (`< 3 giây`) | Lần thứ 3 kích hoạt banner và toast đỏ `Rule 3 · Nghi vấn dò thẻ` (Hình 5.2) | Đạt *(script)* |
| **T3-04** | Rule 4 – Barie mở lâu | Gửi trạng thái barie mở chế độ `hold` và chờ `11,5 giây` | Sau ngưỡng `10 giây`, Node-RED gửi lệnh `{"cmd":"close","src":"rule4"}` và ghi log (Hình 5.1) | Đạt *(script)* |
| **T3-05** | Khởi động lại Node-RED | Chạy `docker restart iot_parking_middleware` khi có doanh thu `5.000đ` và `2` giao dịch | Dashboard nạp lại nguyên `5.000đ`, `2` giao dịch và `12` nhật ký từ `parking_database.json` (Hình 5.3) | Đạt |

*Bảng 5.4: Kết quả kiểm thử các quy tắc tự động và lưu trữ dữ liệu.*

Hình 5.2 minh họa đồng thời kết quả các ca `T3-01`, `T3-02` và `T3-03` trên giao diện Web Dashboard: hai ô đỗ đồng loạt bật viền vàng `QUÁ GIỜ` (`34 giây` và `33 giây`), thẻ Tổng quan chuyển cảnh báo đỏ `2 / 2 · Bãi đã đầy`, và khu vực điều khiển bật banner đỏ `Rule 3 · Nghi vấn dò thẻ` cùng hộp thoại thông báo nổi.

![Hình 5.2: Kết quả kiểm thử kích hoạt đồng thời Rule 1, Rule 2 và Rule 3 trên Dashboard](test_ch5_rules_alerts.png)
*Hình 5.2: Kết quả kiểm thử kích hoạt đồng thời `Rule 1` (Quá giờ), `Rule 2` (Bãi đầy `2/2`) và `Rule 3` (Dò thẻ lạ) trên Dashboard.*

Hình 5.3 ghi nhận giao diện ngay sau khi thực thi lệnh `docker restart iot_parking_middleware`: toàn bộ số liệu `DOANH THU: 5.000đ`, `THỜI GIAN GỬI TB: 15 giây`, `PHÍ TB / LƯỢT: 5.000 đ`, `GIAO DỊCH ĐÃ LƯU: 2` và bảng 12 sự kiện được khôi phục từ `parking_database.json` (tại thời điểm chụp `13:51:17`, container vừa khởi động lại nên thẻ trạng thái hiển thị đang chờ kết nối lại tới broker). Ngoài ra, kiểm tra tự động toàn luồng sau khi bật xác thực xác nhận `69` phần tử luồng hợp lệ và cả `3` tab hiển thị đúng ở `1440 × 1080`, không có lỗi JavaScript hay tràn khung ngang (chi tiết tại Phụ lục D).

![Hình 5.3: Dashboard sau khi khởi động lại container Docker khôi phục doanh thu và giao dịch](test_ch5_restart_recovery.png)
*Hình 5.3: Giao diện sau `docker restart iot_parking_middleware` (`T3-05`) khôi phục doanh thu `5.000đ`, `2` giao dịch và `12` sự kiện.*

### 5.5. Kiểm thử đầu-cuối

#### 5.5.1. Kịch bản kiểm thử qua bốn tầng
Kịch bản đầu-cuối gồm chín bước, từ đăng nhập Dashboard, thao tác tại cổng, phát sinh cảnh báo đến kiểm tra lịch sử giao dịch (Bảng 5.5). Cột kết quả bằng script thể hiện quá trình kiểm chứng bằng kịch bản MQTT kết hợp Node-RED thực tế; cột Wokwi ghi nhận tiến độ chạy trực tiếp và quay video.

| Bước | Thao tác | Kết quả kiểm chứng bằng script và Node-RED | Chạy trực tiếp Wokwi |
| :---: | :--- | :--- | :---: |
| 1 | Đăng nhập Dashboard và mở Wokwi | Đạt *(script + HTTP `401/200`)* | Chưa quay E2E |
| 2 | Quẹt thẻ xe 1 (`29A-123.45`) | Đạt *(script)*; đã kiểm chứng riêng ở `T1-01` | Đã kiểm thử riêng; chưa quay E2E |
| 3 | Mô phỏng vật cản dưới `15 cm` | Đạt *(script)*; có ảnh minh chứng tại Hình 4.1 | Đã kiểm thử riêng; chưa quay E2E |
| 4 | Để xe quá `30 giây` | Đạt *(script)* (Hình 5.2) | Chưa chạy và quay E2E |
| 5 | Đưa xe thứ 2 vào và thử xe thứ 3 | Đạt *(script)* (Hình 5.2) | Chưa chạy và quay E2E |
| 6 | Quẹt thẻ chưa đăng ký `3` lần | Đạt *(script)* (Hình 5.2) | Chưa chạy và quay E2E |
| 7 | Thêm thẻ, khóa thẻ và đổi giá trên Tab 2 | Đạt *(script)* | Chưa chạy và quay E2E |
| 8 | Mở barie quá `10 giây` | Đạt *(script)* (Hình 5.1) | Chưa chạy và quay E2E |
| 9 | Cho xe ra và kiểm tra Tab 3, tệp log | Đạt *(script)* (Hình 5.1, Hình 5.3) | Chưa chạy và quay E2E |

*Bảng 5.5: Tiến độ kiểm thử đầu-cuối theo chín bước.*

Như vậy, toàn bộ chín bước đã được kiểm chứng bằng script MQTT kết hợp Node-RED thực tế. Việc chạy liên hoàn trực tiếp trên Wokwi và quay video minh chứng vẫn cần hoàn tất trước khi nghiệm thu.

### 5.6. Đối chiếu yêu cầu học phần

| Yêu cầu | Minh chứng | Vị trí tham chiếu |
| :--- | :--- | :--- |
| **Có mô phỏng hoạt động** | Wokwi mô phỏng ESP32, RFID, HC-SR04, Servo, LCD, LED và Buzzer | Mục 4.2, Hình 4.1, Bảng 5.2 |
| **Đủ kiến trúc IoT 4 tầng** | Thiết bị, MQTT, Node-RED và Dashboard | Mục 3.2, Hình 3.2 |
| **Có Uplink và Downlink** | Sự kiện gửi lên; lệnh điều khiển và cấu hình gửi xuống | Mục 5.3, Bảng 5.3, Hình 5.1 |
| **M1 – Device Prototype** | Thuật toán vào/ra, chống đọc trùng và chống kẹp `< 15 cm` | Mục 3.4, Bảng 5.2 |
| **M2 – Connected Device** | MQTT, tự kết nối lại, LWT và `retained` | Mục 4.3, Bảng 5.3, Hình 5.1 |
| **M3 – Full 4-Layer IoT** | Dashboard, điều khiển từ xa và xác thực truy cập (`401`/`200`) | Mục 4.5, Hình 4.3, 4.4, `T2-05` |
| **M4 – End-to-End** | Chín bước kiểm chứng bằng script và Node-RED; E2E trực tiếp Wokwi đang hoàn thiện | Mục 5.5, Bảng 5.5, Phụ lục E |
| **Tự động hóa và bất thường** | Bốn rule tự động, xử lý bãi đầy và thẻ không hợp lệ | Mục 3.6, Bảng 5.4, Hình 5.2, 5.3 |

*Bảng 5.6: Đối chiếu kết quả với các yêu cầu và mốc học phần.*

### 5.7. Số liệu đo và đánh giá
Các số liệu trong Bảng 5.7 được ghi nhận từ kết quả biên dịch PlatformIO thực tế (`[SUCCESS] 13,19 giây`) và các phép đo trong môi trường thử nghiệm. Độ trễ MQTT là phép đo vòng mạng từ Node.js đến Broker, không đại diện cho độ trễ toàn tuyến từ Wokwi đến Dashboard.

| Đại lượng | Giá trị ghi nhận | Công cụ và phương pháp |
| :--- | :--- | :--- |
| **Flash sử dụng** | `821.629 / 1.310.720 bytes` (**62,7%**) | Kết quả biên dịch PlatformIO (`pio run`) |
| **RAM tĩnh (DRAM)** | `46.764 / 327.680 bytes` (**14,3%**) | Kết quả biên dịch PlatformIO (`pio run`) |
| **Chu kỳ kiểm tra Rule** | `1 giây` | Chu kỳ inject kiểm tra trong Node-RED |
| **Chu kỳ kiểm tra chống kẹp** | `300 ms` | Chu kỳ đo lại cảm biến HC-SR04 |
| **Độ trễ vòng MQTT đến Broker** | `167–172 ms` (qua 5 mẫu đo) | Node.js gửi/nhận echo QoS 0 qua HiveMQ |
| **Độ phân giải nhật ký** | `1 giây` (`HH:MM:SS`) | Tệp `data/parking_log.txt` |

*Bảng 5.7: Số liệu tài nguyên firmware và thời gian phản hồi quan sát.*

Kết quả kiểm thử cho thấy các chức năng chính đã được kiểm chứng trong môi trường mô phỏng và qua script kết hợp Node-RED. Tuy nhiên, độ trễ toàn tuyến, độ ổn định của phần cứng thật và khả năng vận hành trong điều kiện bãi xe thực tế chưa được đánh giá đầy đủ.

---

## CHƯƠNG 6. KẾT LUẬN VÀ HƯỚNG PHÁT TRIỂN

### 6.1. Kết quả đạt được

#### 6.1.1. Hoàn thiện mô hình IoT bốn tầng
Nhóm đã xây dựng mô hình bãi giữ xe máy tự quản sử dụng RFID theo kiến trúc IoT bốn tầng. Mô hình gồm ESP32 và các thiết bị ngoại vi được mô phỏng trên Wokwi, truyền thông MQTT qua HiveMQ, xử lý trung gian bằng Node-RED và giao diện Web Dashboard. Firmware thực hiện các nghiệp vụ nhận diện thẻ, xử lý xe vào/ra, phân ô đỗ, điều khiển barie và chống kẹp; Node-RED đảm nhiệm đồng bộ trạng thái, lưu trữ dữ liệu và thực hiện bốn quy tắc tự động.

#### 6.1.2. Hoàn thiện truyền thông và giao diện quản lý
Hệ thống hỗ trợ truyền thông MQTT hai chiều, sử dụng `retained message` để đồng bộ trạng thái và cấu hình, đồng thời áp dụng LWT để cập nhật tình trạng ngoại tuyến. Dashboard cung cấp chức năng giám sát, điều khiển barie, quản lý thẻ, điều chỉnh bảng giá, tra cứu giao dịch và xuất CSV. Giao diện Dashboard (`/ui`) và Node-RED Editor (`/`) được cấu hình xác thực bằng mật khẩu lưu dưới dạng mã băm `bcrypt`.

#### 6.1.3. Bổ sung chức năng mở rộng và lưu trữ
Hệ thống hỗ trợ quản lý tối đa 16 thẻ RFID, vé tháng, khóa thẻ, bảng giá động và lịch sử giao dịch. Dữ liệu được lưu trong `parking_database.json` và `parking_log.txt`; kết quả kiểm thử ghi nhận doanh thu và giao dịch được khôi phục sau khi container Node-RED khởi động lại.

### 6.2. Hạn chế

#### 6.2.1. Giới hạn của môi trường mô phỏng
Hệ thống hiện được kiểm thử chủ yếu trên Wokwi, chưa được đánh giá đầy đủ với phần cứng thực tế. Do đó, độ chính xác của cảm biến, độ ổn định cơ khí của barie và ảnh hưởng của môi trường bên ngoài vẫn cần được kiểm tra thêm.

#### 6.2.2. Bảo mật và phụ thuộc dịch vụ
Hệ thống sử dụng HiveMQ Public Broker qua cổng `1883` và chưa triển khai TLS. Dashboard hiện sử dụng Basic Auth trên HTTP cục bộ; nếu triển khai qua Internet cần bổ sung HTTPS, cơ chế phân quyền và Broker có xác thực.

#### 6.2.3. Quy mô và tiến độ kiểm thử
Mô hình hiện giới hạn ở hai ô đỗ và sử dụng các ngưỡng thời gian rút gọn để phục vụ demo. Chín bước kiểm thử đầu-cuối đã được kiểm chứng bằng script MQTT kết hợp Node-RED; việc chạy liên hoàn trực tiếp trên Wokwi và quay video minh chứng vẫn cần hoàn tất.

### 6.3. Hướng phát triển

#### 6.3.1. Tích hợp camera nhận diện biển số
Bổ sung camera nhận diện biển số để đối chiếu với UID RFID, tăng độ chính xác trong quản lý phương tiện và hạn chế nguy cơ sử dụng hoặc tráo thẻ không đúng chủ.

#### 6.3.2. Tích hợp thanh toán điện tử
Tích hợp VietQR hoặc phương thức thanh toán điện tử phù hợp, cho phép hệ thống tạo mã thanh toán theo cước phí và cập nhật trạng thái giao dịch trước khi mở barie cho xe ra.

#### 6.3.3. Bổ sung cảm biến tại từng ô đỗ
Lắp cảm biến phát hiện phương tiện tại mỗi vị trí đỗ để xác định tình trạng chiếm chỗ thực tế, thay vì chỉ suy luận trạng thái ô đỗ từ sự kiện quẹt thẻ tại cổng.

#### 6.3.4. Mở rộng cảnh báo và lưu trữ
Bổ sung kênh thông báo từ xa như Telegram khi phát sinh cảnh báo hoặc thiết bị mất kết nối. Đồng thời, có thể chuyển dữ liệu từ tệp JSON sang hệ quản trị cơ sở dữ liệu và triển khai MQTT Broker riêng có xác thực, mã hóa khi mở rộng quy mô.

### 6.4. Lời kết và cảm ơn
Sau 10 tuần tìm hiểu và triển khai đồ án học phần Internet of Things, Nhóm 4 đã xây dựng mô hình mô phỏng hệ thống bãi giữ xe máy tự quản sử dụng RFID theo kiến trúc IoT bốn tầng. Đề tài giúp nhóm củng cố kiến thức về hệ thống nhúng, giao thức MQTT, tự động hóa và phát triển ứng dụng IoT; đồng thời rèn luyện kỹ năng lập trình, kiểm thử, quản lý mã nguồn và làm việc nhóm.

Mặc dù hệ thống còn hạn chế về kiểm thử phần cứng thực tế và bảo mật truyền thông, kết quả đạt được là nền tảng để nhóm tiếp tục hoàn thiện và mở rộng trong tương lai.

Nhóm 4 xin chân thành cảm ơn **Thầy Võ Hoàng Hải** đã tận tình hướng dẫn, góp ý và hỗ trợ nhóm trong suốt quá trình thực hiện đồ án. Nhóm cũng xin cảm ơn quý **Thầy Cô Khoa Công nghệ Thông tin – Trường Đại học Công Thương TP. Hồ Chí Minh** đã trang bị kiến thức và tạo điều kiện để nhóm hoàn thành đề tài.

---

## TÀI LIỆU THAM KHẢO

1. OASIS Standard, *MQTT Version 3.1.1 & Version 5.0 Protocol Specification*, https://docs.oasis-open.org/mqtt/mqtt/
2. OpenJS Foundation, *Node-RED Documentation & Function/Context Guides*, https://nodered.org/docs/
3. Node-RED FlowForge / Dashboard Project, *node-red-dashboard Documentation*, https://github.com/node-red/node-red-dashboard
4. Wokwi Ltd., *Wokwi Simulator Documentation (ESP32, MFRC522, HC-SR04, WiFi)*, https://docs.wokwi.com/
5. NXP Semiconductors, *MFRC522 Standard performance MIFARE and NTAG frontend Datasheet*, Rev. 3.9.
6. Espressif Systems, *ESP32 Series Datasheet & ESP-IDF Technical Reference Manual*, https://www.espressif.com/
7. ElecFreaks, *Ultrasonic Ranging Module HC-SR04 User Guide & Timing Diagram*.
8. Nick O'Leary, *PubSubClient — Arduino Client for MQTT*, https://pubsubclient.knolleary.net/
9. Benoit Blanchon, *ArduinoJson v7 Documentation*, https://arduinojson.org/
10. PlatformIO Labs, *PlatformIO Core & Espressif 32 Platform Documentation*, https://docs.platformio.org/
11. Bộ môn Internet of Things, *Slide bài giảng và Rubric đánh giá đồ án môn học IoT (M1–M4)*.

---

## PHỤ LỤC

### Phụ lục A. Mã nguồn Firmware ESP32
* **Kho mã nguồn (GitHub công khai):** https://github.com/Tthoong129/IOT_Nhom4.git (nhánh `main`, commit mã nguồn vận hành: `c7b4b0b`; đã rà soát toàn bộ tệp theo dõi không chứa token hay mật khẩu thô).
* **Cấu trúc tệp mã nguồn:**
  * `include/Config.h` (53 dòng): Khai báo chân GPIO, thông số thời gian/phí mặc định và 6 topic MQTT.
  * `include/GateController.h`, `src/GateController.cpp` (95 dòng): Điều khiển barie và chống kẹp HC-SR04.
  * `include/ParkingSystem.h`, `src/ParkingSystem.cpp` (265 dòng): Danh sách tới 16 thẻ, vé tháng, bảng giá động, LCD 1602, buzzer LEDC.
  * `include/MqttService.h`, `src/MqttService.cpp` (104 dòng): Wi-Fi, MQTT, LWT, nhận lệnh và config `retained`.
  * `src/main.cpp` (276 dòng): Điều phối vòng lặp chính và Serial console.

### Phụ lục B. Tệp Flow Node-RED (JSON)
* Tệp đầy đủ lưu tại `nodered_flow.json` và `docker/nodered/flows.json` (đã kiểm tra không chứa token, mật khẩu hay thông tin nhạy cảm); tệp cấu hình xác thực lưu tại `docker/nodered/settings.js` chỉ lưu chuỗi băm `bcrypt`.
* Để duy trì khả năng lặp lại chính xác cấu hình 69 phần tử (50 node xử lý/UI, 13 config node, 1 tab và 5 khung nhóm), tệp JSON này được import trực tiếp vào Node-RED Editor (`Ctrl + I`) hoặc gắn qua Docker Compose.

### Phụ lục C. Bảng chân GPIO đầy đủ và danh sách thẻ mẫu

* Bảng chân GPIO đầy đủ đã liệt kê ở **Bảng 3.2 (Mục 3.3)**.
* Danh sách thẻ mẫu mặc định nạp sẵn trên ESP32 và Node-RED (Bảng C.1):

| Phím Serial Wokwi | Thẻ mẫu Wokwi MFRC522 | Mã UID | Biển số mặc định | Chủ xe | Trạng thái mặc định |
| :---: | :--- | :--- | :--- | :--- | :--- |
| `1` | Blue Card | `01 02 03 04` | `29A-123.45` | Nguyễn Văn A | Đã đăng ký (Vé lượt) |
| `2` | Green Card | `11 22 33 44` | `51F-999.88` | Trần Thị B | Đã đăng ký (Vé lượt) |
| `3` | Yellow Card | `55 66 77 88` | `43C-678.90` | Lê Văn C | Đã đăng ký (Vé lượt) |
| `4` | Red Card | `AA BB CC DD` | *(Chưa gán)* | *(Chưa gán)* | Chưa đăng ký (dùng thử Rule 3 hoặc thêm ở Tab 2) |

*Bảng C.1: Danh sách thẻ RFID mẫu sử dụng trong mô phỏng Wokwi.*

### Phụ lục D. Nhật ký mẫu và bộ ảnh minh chứng bổ sung
* **Trích đoạn log hệ thống thực tế (`data/parking_log.txt`) thu từ phiên kiểm thử:**
  ```text
  23/11/2026 18:11:40 | Thiết bị trực tuyến          | -            | ESP32 đã kết nối và đồng bộ trạng thái
  23/11/2026 18:11:41 | Xe vào                       | 29A-123.45   | Ô 1 · Nguyễn Văn A
  23/11/2026 18:11:42 | Chống kẹp xe                 | -            | Vật cản 10.2 cm dưới barie, tạm hoãn đóng
  23/11/2026 18:11:44 | Thẻ lạ bị từ chối            | AA BB CC DD  | Lần 1/3 trong 60 giây
  23/11/2026 18:11:44 | Thẻ lạ bị từ chối            | AA BB CC DD  | Lần 2/3 trong 60 giây
  23/11/2026 18:11:45 | Rule 3 · Nghi vấn dò thẻ     | AA BB CC DD  | 3 lần quẹt thẻ lạ trong 60 giây
  23/11/2026 18:11:46 | Xe vào                       | 51F-999.88   | Ô 2 · Trần Thị B
  23/11/2026 18:11:46 | Rule 2 · Bãi đã đầy          | -            | Đạt 2/2 xe, cổng sẽ từ chối xe tiếp theo
  23/11/2026 18:11:47 | Rule 2 · Từ chối do bãi đầy  | 43C-678.90   | Cổng không mở, bãi đang 2/2 xe
  23/11/2026 18:11:58 | Rule 4 · Barie mở quá lâu    | -            | Mở hơn 10 giây, Node-RED đã gửi lệnh đóng
  23/11/2026 18:12:00 | Barie đóng                   | -            | Nguồn: Rule 4 · góc 0°
  23/11/2026 18:12:01 | Xe ra                        | 29A-123.45   | 15 giây · 5.000 đ
  23/11/2026 18:12:17 | Rule 1 · Xe gửi quá giờ      | 51F-999.88   | Ô 2 đã gửi 31 giây (ngưỡng 30 giây)
  ```
* **Phương pháp kiểm tra tự động luồng và giao diện (Chrome Headless CDP):** Kết nối trình duyệt tới `http://127.0.0.1:1880/` (đã bật `adminAuth`) kiểm tra `RED.nodes.eachNode(n => !n.valid)` ghi nhận mảng rỗng (`0` node lỗi trên 69 phần tử); truy cập 3 tab tại `http://127.0.0.1:1880/ui/` (qua `httpNodeAuth` Basic Auth, độ phân giải `1440x1080`) lắng nghe `Runtime.exceptionThrown` (`0` ngoại lệ JS) và kiểm tra `scrollWidth <= window.innerWidth` (`[false, false, false]`).
* **Bộ ảnh minh chứng đi kèm (`docs/`):** `minh_chung_anti_pinch_wokwi.png`, `nodered_flow.png`, `dashboard_demo.png`, `nodered_admin_login.png`, `dashboard_cards_pricing.png`, `dashboard_history.png` (Chương 4) và `test_ch5_lwt_offline.png`, `test_ch5_rules_alerts.png`, `test_ch5_restart_recovery.png` (Chương 5); 5 sơ đồ thiết kế (`Hình 3.1`–`3.5`) hiển thị trực tiếp bằng Mermaid trong tệp Markdown (bản ảnh PNG xuất sẵn lưu cục bộ tại `docs/figures/`).

### Phụ lục E. Liên kết video demo
* **Video demo chính thức (đủ 9 phân cảnh Wokwi thật + Dashboard):** `[Chưa quay — gắn link Google Drive / YouTube sau khi chạy quay 9 bước trực tiếp với Wokwi thật]`
* **Video dự phòng:** `[Gắn link dự phòng nếu có]`

### Phụ lục F. Hướng dẫn chạy lại hệ thống từ đầu
1. Tải mã nguồn về máy:
   ```bash
   git clone https://github.com/Tthoong129/IOT_Nhom4.git
   cd IOT_Nhom4
   ```
2. Khởi chạy Node-RED & Mosquitto bằng Docker Compose:
   ```bash
   docker compose up -d --build
   ```
   Kiểm tra giao diện mở tại `http://localhost:1880/ui` và Flow Editor tại `http://localhost:1880`.
3. Biên dịch firmware ESP32 bằng PlatformIO:
   ```bash
   pio run
   ```
4. Mở dự án trong VS Code có cài tiện ích **Wokwi Simulator**, mở tệp `diagram.json` và nhấn nút **Play**.
5. Khi thấy thẻ `THIẾT BỊ ESP32` trên Dashboard chuyển màu xanh `TRỰC TUYẾN`, nhập các phím `1`, `2`, `3`, `4` trên Serial Monitor của Wokwi hoặc thao tác trực tiếp trên 3 tab Web Dashboard để kiểm chứng toàn bộ quy trình.
