# KỊCH BẢN VÀ NỘI DUNG SLIDE THUYẾT TRÌNH (13 SLIDES)
**Đề tài: Hệ thống bãi giữ xe máy tự quản sử dụng RFID (Mô hình kiến trúc IoT 4 tầng)**  
*Thời lượng trình bày: khoảng 14 đến 15 phút*

---

## SLIDE 1: TRANG TIÊU ĐỀ
* **Tiêu đề lớn**: HỆ THỐNG BÃI GIỮ XE MÁY TỰ QUẢN SỬ DỤNG RFID
* **Phụ đề**: Kiến trúc IoT 4 tầng, mô phỏng trên Wokwi Simulator
* **Trường / Khoa**: Trường Đại học Công Thương TP. Hồ Chí Minh (HUIT) — Khoa Công nghệ Thông tin
* **Học phần**: Internet of Things (IoT)
* **Nhóm thực hiện**: Nhóm 4 — `2001230069` Nguyễn Lê Duy Cương · `2001230894` Đinh Tấn Thành · `2001230938` Bùi Tấn Thông
* **Giảng viên hướng dẫn**: Võ Hoàng Hải

> **LỜI THOẠI:**  
> Em chào thầy Võ Hoàng Hải và các bạn. Nhóm 4 xin trình bày đề tài hệ thống bãi giữ xe máy tự quản sử dụng RFID theo kiến trúc IoT 4 tầng. Hệ thống nhận diện thẻ và chống kẹp xe ngay tại cổng trên Wokwi, truyền dữ liệu hai chiều qua MQTT, xử lý bốn quy tắc tự động bằng Node-RED và quản trị qua Web Dashboard có xác thực đăng nhập.

> **CÂU NỐI:**  
> Trước hết, nhóm xin tóm tắt bài toán thực tế và các mục tiêu của đề tài.

---

## SLIDE 2: ĐẶT VẤN ĐỀ VÀ MỤC TIÊU
* **Hạn chế của bãi giữ xe thủ công**:
  * Soát vé giấy chậm, dễ nhầm lẫn và gây ùn tắc giờ cao điểm.
  * Barie đóng theo thời gian cố định tiềm ẩn nguy cơ hạ trúng xe đang di chuyển.
  * Người quản lý khó theo dõi số chỗ trống từ xa và thiếu nhật ký đối soát sự cố.
* **Mục tiêu của đề tài**:
  * Tự động nhận diện xe vào/ra bằng thẻ RFID 13,56 MHz và điều khiển barie (`3 giây`).
  * Cảm biến siêu âm HC-SR04 chống kẹp xe dưới `15 cm` (kiểm tra lại mỗi `0,3 giây`).
  * Truyền thông MQTT 6 topic hai chiều, tự kết nối lại và đồng bộ qua Node-RED (`4` rule tự động).
  * Web Dashboard (`/ui`) bảo vệ đăng nhập `httpNodeAuth`, kèm tính năng mở rộng quản lý thẻ, bảng giá động và xuất CSV.

> **LỜI THOẠI:**  
> Bãi xe truyền thống thường ùn tắc giờ cao điểm, dễ va chạm barie và thiếu công cụ giám sát từ xa. Nhóm giải quyết bằng mạch ESP32 tích hợp RFID và HC-SR04 chống kẹp xe, truyền thông MQTT 6 topic hai chiều lên Node-RED chạy 4 quy tắc tự động và giao diện Dashboard có xác thực truy cập.

> **CÂU NỐI:**  
> Để hoàn thành các mục tiêu này, nhóm bám sát lộ trình 10 tuần của học phần.

---

## SLIDE 3: LỘ TRÌNH THỰC HIỆN 10 TUẦN

| Tuần | Nội dung thực hiện (đối chiếu báo cáo tuần) | Mốc Rubric |
| :---: | :--- | :---: |
| **1** | Phân tích yêu cầu, use case, kiến trúc 4 tầng, phân công nhóm | |
| **2** | Mô phỏng Tầng 1 bản đầu trên Wokwi (ESP32, RFID-RC522, Servo SG90, Buzzer) | |
| **3** | Ổn định firmware: State machine (`IDLE` → `CLOSING`), phân biệt vào/ra, debounce | **M1** |
| **4** | Kết nối Wi-Fi và MQTT hai chiều (`publish`, `subscribe`, tự kết nối lại 5s) | **M2** |
| **5** | Dựng luồng Node-RED trung gian (`Check Card`, ghi log và gửi lệnh barie) | |
| **6** | Web Dashboard (`/ui`) và bảo vệ đăng nhập bằng `httpNodeAuth` (`settings.js`) | **M3** |
| **7** | Hoàn thiện 4 quy tắc tự động hóa và xử lý các kịch bản bất thường trên Node-RED | |
| **8** | Tích hợp End-to-End; bổ sung HC-SR04 chống kẹp, LCD I2C, LED Đỏ/Xanh, LWT & `retained` | **M4** |
| **9** | Đóng gói Docker Compose, tính năng mở rộng (16 thẻ, giá động, CSV), test tự động & báo cáo | |
| **10** | Chạy kiểm thử 9 bước trên Wokwi thật, quay video minh chứng và nghiệm thu | |

> **LỜI THOẠI:**  
> Lộ trình 10 tuần phản ánh đúng tiến độ từ Tuần 1 đến Tuần 6 đã báo cáo với thầy: Tuần 2–3 tập trung mạch RFID–Servo–Buzzer và state machine đạt M1; Tuần 4 kết nối MQTT đạt M2; Tuần 5–6 dựng Node-RED, Dashboard và đăng nhập `httpNodeAuth` đạt M3; từ Tuần 7–9 nhóm hoàn thiện 4 rule, bổ sung HC-SR04 chống kẹp, LCD, LED, LWT đạt M4 và đóng gói Docker cùng các tính năng mở rộng.

> **CÂU NỐI:**  
> Toàn bộ các thành phần được kết nối trên kiến trúc IoT 4 tầng sau.

---

## SLIDE 4: KIẾN TRÚC 4 TẦNG VÀ LUỒNG DỮ LIỆU HAI CHIỀU
* **Tầng 1 (Sensing & Actuation)**: ESP32 DevKit V1, RFID-RC522 (SPI), HC-SR04 siêu âm, Servo SG90, LED Đỏ/Xanh, LCD 1602 I2C, Active Buzzer (LEDC kênh 15).
* **Tầng 2 (Network)**: Wi-Fi `Wokwi-GUEST`, MQTT `broker.hivemq.com:1883` với tiền tố `parking_n4/`, `reconnect` mỗi 5 giây và LWT.
* **Tầng 3 (Middleware)**: Node-RED (`nodered_flow.json`: `69` phần tử JSON, gồm `50` node xử lý/UI) điều phối 4 rule và lưu `parking_log.txt`, `parking_database.json`.
* **Tầng 4 (Application)**: Web Dashboard 3 tab (`/ui`) có xác thực HTTP Basic Auth (`httpNodeAuth`), điều khiển từ xa và quản trị mở rộng.
* **Luồng Uplink / Downlink**: Quẹt thẻ → ESP32 → MQTT → Node-RED → Dashboard; nút barie / Rule 4 / cấu hình thẻ & giá → MQTT → ESP32.

> **LỜI THOẠI:**  
> Hệ thống tách thành 4 tầng độc lập. Dữ liệu từ cổng đi theo luồng Uplink lên Node-RED và Dashboard. Ngược lại, lệnh điều khiển barie cùng cấu hình thẻ và bảng giá đi theo luồng Downlink về ESP32.

> **CÂU NỐI:**  
> Bắt đầu ở Tầng 1 tại cổng, nhóm đấu nối các ngoại vi như sau.

---

## SLIDE 5: TẦNG 1 — PHẦN CỨNG MÔ PHỎNG TRÊN WOKWI
* **Nhận dạng**: RFID-RC522 (SPI: `SDA=5`, `SCK=18`, `MOSI=23`, `MISO=19`, `RST=4`), hỗ trợ mảng tối đa `16` thẻ động.
* **An toàn**: Cảm biến siêu âm HC-SR04 (`TRIG=27`, `ECHO=32`) đo khoảng cách vật cản dưới cần barie.
* **Chấp hành & Hiển thị**: Servo SG90 (`GPIO 13`, góc `0°–90°`), LED Đỏ/Xanh (`GPIO 25/26`), LCD 1602 I2C (`0x27`, `SDA=21`, `SCL=22`), Buzzer (`GPIO 14`, LEDC kênh 15).
* **Kiểm thử trên Wokwi**: Phím Serial `1`–`3` (Blue, Green, Yellow) tương ứng 3 thẻ mặc định; phím `4` (Red) mặc định chưa đăng ký; thanh trượt HC-SR04 giả lập vật cản.

> **LỜI THOẠI:**  
> Trên Wokwi, đầu đọc RFID kết nối qua SPI, LCD 1602 nối qua I2C, cảm biến siêu âm HC-SR04 giám sát khu vực dưới thanh chắn và còi buzzer được tách sang kênh LEDC riêng để tránh xung đột bộ định thời PWM với servo.

> **CÂU NỐI:**  
> Khi người dùng quẹt thẻ tại cổng, firmware ESP32 xử lý theo lưu đồ nào?

---

## SLIDE 6: LUỒNG XỬ LÝ TẠI CỔNG VÀ CHỐNG KẸP XE
* **Xử lý tức thời tại ESP32 (chạy độc lập khi mất mạng)**:
  * **Thẻ hợp lệ còn chỗ**: Mở barie `90°`, bật LED xanh, LCD báo biển số & ô (`1` hoặc `2`, hoặc `VE THANG - 0d`), còi 1 tiếng; giữ mở `3 giây`.
  * **Thẻ bị khóa**: Từ chối tại chỗ, LCD báo `THE DA BI KHOA!`, gửi cảnh báo `LOCKED_CARD`.
  * **Bãi đầy (`2/2`) hoặc thẻ lạ**: Từ chối, LED đỏ sáng, còi báo và hiển thị `BAI XE DA DAY!` hoặc `THE CHUA DANG KY` kèm UID.
* **Chống kẹp xe an toàn (`GateController`)**: Khi hết giờ giữ mở `3 giây` hoặc nhận lệnh đóng từ xa, nếu HC-SR04 đo `< 15 cm` thì giữ mở (`TAM HOAN DONG`) và kiểm tra lại mỗi `0,3 giây` đến khi thông thoáng.

> **LỜI THOẠI:**  
> Mọi quyết định cho xe qua hay từ chối thực hiện trực tiếp trên ESP32 trong vòng lặp không chặn. Sau 3 giây giữ mở hoặc khi nhận lệnh đóng từ xa, hàm kiểm tra khoảng cách chạy mỗi 0,3 giây: nếu còn vật cản dưới 15 cm thì thanh chắn được giữ mở an toàn.

> **CÂU NỐI:**  
> Sau mỗi sự kiện tại cổng, dữ liệu được đóng gói JSON và truyền qua tầng mạng MQTT.

---

## SLIDE 7: TẦNG 2 — TRUYỀN THÔNG MQTT HAI CHIỀU
* **Broker & Tham số thực tế**: `broker.hivemq.com:1883` | Tiền tố `parking_n4/` | `keepAlive = 15s`, `reconnect` mỗi `5s` | Uplink ESP32 dùng `QoS 0` (`PubSubClient 2.8.0`), LWT khai báo `willQos = 1`, Node-RED xuất/nhận cấu hình `QoS 1`.

| Topic MQTT (6 topic) | Chiều | Cơ chế | Ý nghĩa dữ liệu JSON |
| :--- | :---: | :---: | :--- |
| `parking_n4/rfid/scan` | Uplink | Thường | Lượt `check_in`/`check_out`, biển số, loại vé, ô đỗ và cước phí |
| `parking_n4/barie/status` | Uplink | Retained | Trạng thái barie (`open`, `closed`), góc mở và nguồn lệnh |
| `parking_n4/alert` | Uplink | Thường | Cảnh báo `INVALID_CARD`, `LOCKED_CARD`, `LOT_FULL`, `ANTI_PINCH` |
| `parking_n4/status` | Uplink | Retained + LWT | Snapshot 2 ô đỗ; Broker phát `{"online":false}` khi đứt kết nối |
| `parking_n4/barie/cmd` | Downlink | Thường | Lệnh `open`, `close`, `sync` từ Dashboard hoặc Rule 4 |
| `parking_n4/config` *(Mở rộng)* | Downlink | Retained | Đồng bộ danh sách tới 16 thẻ và bảng giá động xuống ESP32 |

> **LỜI THOẠI:**  
> Hệ thống sử dụng 6 topic với tiền tố riêng `parking_n4/`. Về QoS thực tế, thư viện `PubSubClient 2.8.0` phát Uplink ở QoS 0 nhưng hỗ trợ LWT với `willQos = 1`, còn Node-RED dùng `QoS 1` cho lệnh và bản tin cấu hình `retained` giúp ESP32 tự đồng bộ ngay khi vừa kết nối lại.

> **CÂU NỐI:**  
> Dữ liệu đến broker được chuyển vào tầng xử lý trung gian Node-RED.

---

## SLIDE 8: TẦNG 3 — NODE-RED VÀ 4 QUY TẮC TỰ ĐỘNG HÓA
* **Kiến trúc luồng (`nodered_flow.json`)**: Gồm `69` phần tử JSON (`50` node xử lý/UI, `13` config node, `1` tab, `5` khung nhóm), giữ đồng bộ tập trung qua `flow.get('park')` và chỉ cập nhật widget nào thay đổi nội dung.
* **4 quy tắc tự động hóa (quét chu kỳ `1 giây`)**:
  * **Rule 1 — Xe gửi quá giờ**: Vượt ngưỡng cấu hình (demo `30 giây`, thực tế `4–12 giờ`) → Gắn nhãn `QUÁ GIỜ` màu vàng trên ô đỗ và cảnh báo.
  * **Rule 2 — Bãi đầy**: Đủ `2/2` xe hoặc nhận alert `LOT_FULL` → Thẻ Tổng quan chuyển đỏ (từ chối xe do ESP32 chặn ngay tại cổng).
  * **Rule 3 — Dò thẻ lạ liên tiếp**: Nhận `>= 3` lần `INVALID_CARD` trong `60 giây` → Bật cảnh báo đỏ `Nghi vấn dò thẻ` và lưu UID gợi ý.
  * **Rule 4 — Barie mở quá lâu**: Mở `> 10 giây` (thực tế `30–60 giây`) → Tự gửi lệnh Downlink `{"cmd":"close","src":"rule4"}` xuống ESP32 (vẫn qua chống kẹp HC-SR04).

> **LỜI THOẠI:**  
> Luồng Node-RED gồm 69 phần tử với 50 node xử lý và hiển thị UI hoạt động chính, dùng chung một đối tượng trạng thái `park` để tránh lệch số giữa các bảng. Bốn quy tắc tự động hóa quét theo xung 1 giây; riêng Rule 4 phát lệnh đóng tự động nhưng vẫn chịu sự kiểm soát của cảm biến siêu âm tại cổng.

> **CÂU NỐI:**  
> Toàn bộ trạng thái, xác thực đăng nhập và điều khiển nằm ở Tầng 4 Web Dashboard.

---

## SLIDE 9: TẦNG 4 — DASHBOARD, XÁC THỰC TRUY CẬP & MỞ RỘNG
* **Xác thực truy cập (`settings.js`)**: Bảo vệ Web Dashboard (`/ui`) bằng HTTP Basic Auth (`httpNodeAuth`) và bảo vệ Flow Editor (`/`) bằng `adminAuth` dùng mật khẩu băm bcrypt (`401 Unauthorized` khi chưa đăng nhập hoặc sai mật khẩu).
* **Tab 1 — Giám sát bãi xe (Cốt lõi)**: 4 thẻ KPI, sơ đồ 2 ô đỗ (`VÉ THÁNG`, `QUÁ GIỜ`), mô phỏng barie + nút `MỞ BARIE` / `ĐÓNG BARIE`, nhật ký 12 sự kiện và 2 biểu đồ thời gian thực.
* **Tab 2 & Tab 3 (Mở rộng)**: Quản lý tới `16` thẻ động (hỗ trợ nút **Lấy UID này** khi vừa quẹt thẻ lạ, khóa thẻ, vé tháng), bảng giá động 3 mức, đối soát giao dịch vào/ra và xuất tệp CSV (Excel); kèm cấu hình đóng gói chạy một lệnh qua Docker Compose.

> **LỜI THOẠI:**  
> Khớp với báo cáo Tuần 6, Dashboard được bảo vệ bằng `httpNodeAuth` cấu hình mật khẩu băm trong `settings.js`, kiểm tra trả mã 401 khi sai thông tin và cho phép truy cập `/ui` sau khi đăng nhập. Trên giao diện chính, người trực xem trọn vẹn 2 ô đỗ, biểu đồ và điều khiển barie; hai tab mở rộng phục vụ quản lý 16 thẻ, chỉnh giá động và xuất CSV.

> **CÂU NỐI:**  
> Dữ liệu vận hành của hệ thống được lưu trữ cục bộ để khôi phục khi khởi động lại.

---

## SLIDE 10: LƯU TRỮ BỀN VỮNG VÀ CƠ CHẾ KHÔI PHỤC
* **Hai tệp lưu trữ (`data/` gắn `/data/storage` trong Docker)**:
  * `data/parking_log.txt`: Ghi nối tiếp từng sự kiện theo mốc thời gian `HH:MM:SS` phục vụ truy vết.
  * `data/parking_database.json`: Lưu danh sách thẻ, bảng giá, doanh thu, tối đa `100` giao dịch ghép cặp và `12` sự kiện gần nhất.
* **Lý do dùng JSON thay CSDL rời**: Gọn nhẹ trên container Node-RED, không cần cài dịch vụ MongoDB/MySQL hoặc biên dịch thư viện native trên Alpine Linux, vẫn đáp ứng đủ CRUD thẻ, bảng giá và khôi phục số liệu tức thì.
* **Kiểm chứng thực tế**: Khi khởi động lại Node-RED, toàn bộ doanh thu, thẻ đã thêm, bảng giá và lịch sử giao dịch được nạp lại từ `parking_database.json`, đồng thời ESP32 đồng bộ ô đỗ qua bản tin `retained`.

> **LỜI THOẠI:**  
> Nhóm chọn lưu trữ bằng tệp JSON cấu trúc kết hợp tệp log văn bản để giữ container Docker gọn nhẹ nhưng vẫn đầy đủ CRUD và đối soát. Khi thử khởi động lại Node-RED, toàn bộ doanh thu, danh sách thẻ, bảng giá và lịch sử giao dịch đều được khôi phục nguyên vẹn.

> **CÂU NỐI:**  
> Sau khi hoàn thiện 4 tầng, nhóm đối chiếu các tiêu chí với rubric môn học.

---

## SLIDE 11: ĐỐI CHIẾU YÊU CẦU MÔN HỌC (RUBRIC)

| Yêu cầu Rubric | Minh chứng thực hiện của Nhóm 4 | Trạng thái |
| :--- | :--- | :---: |
| **Simulation & 4 tầng IoT** | Mạch Wokwi (ESP32, RC522, HC-SR04, Servo, LED, LCD, Buzzer) + MQTT + Node-RED + Dashboard | Đạt |
| **Uplink & Downlink** | Uplink sự kiện, snapshot, cảnh báo; Downlink lệnh Mở/Đóng, Rule 4 & `config` | Đạt |
| **M1 Device Prototype (T3)** | State machine, phân biệt vào/ra, debounce 1,5s (mở rộng thêm chống kẹp `< 15 cm` ở T8) | Đạt |
| **M2 Connected Device (T4)** | Kết nối HiveMQ MQTT 6 topic, tự kết nối lại 5s, bổ sung LWT & `retained` | Đạt |
| **M3 Full 4-Layer IoT (T6)** | Dashboard `/ui`, điều khiển từ xa, bảo vệ đăng nhập `httpNodeAuth` (`401` / `200`) | Đạt |
| **Automation ($\ge 2$ rule, 1 bất thường)** | Đủ 4 rule (quá giờ, bãi đầy, dò thẻ lạ $\ge 3$ lần/60s, barie mở > 10s tự đóng) | Đạt |
| **M4 End-to-End 9 bước & Video** | Đã kiểm chứng logic qua script MQTT + Chrome CDP; **chờ chạy 9 bước trên Wokwi thật & quay video** | Đang hoàn thiện video |

> **LỜI THOẠI:**  
> Nhóm đã hoàn thiện và kiểm chứng phần lớn tiêu chí từ M1 đến M3, cùng xác thực `httpNodeAuth`, 4 rule tự động và kiểm thử tự động luồng Node-RED–Dashboard. Riêng phần quay video liên hoàn 9 bước giữa Wokwi thật và Dashboard đang được nhóm hoàn tất để đính kèm trước buổi nghiệm thu.

> **CÂU NỐI:**  
> Dưới đây là kịch bản 9 phân cảnh kiểm thử đầu-cuối của hệ thống.

---

## SLIDE 12: KỊCH BẢN DEMO ĐẦU-CUỐI (9 PHÂN CẢNH)

| Bước | Thao tác | Luồng qua 4 tầng & Kỳ vọng kiểm chứng |
| :---: | :--- | :--- |
| **1** | Mở Dashboard (đăng nhập `httpNodeAuth`) và chạy Wokwi | ESP32 trực tuyến (`0 / 2` xe), barie đóng, đèn đỏ sáng |
| **2** | Quẹt thẻ xe 1 (`29A-123.45` / phím `1`) | Barie mở `90°`, giữ mở `3 giây`, LCD hiện Ô 1, Dashboard cập nhật `1 / 2` |
| **3** | Kéo thanh trượt HC-SR04 `< 15 cm`, rồi `> 15 cm` | Giữ mở an toàn (`TAM HOAN DONG`), hết vật cản tự đóng sau `0,3 giây` |
| **4** | Để xe quá ngưỡng Rule 1 (`30 giây`) | Ô đỗ gắn nhãn `QUÁ GIỜ`, bật cảnh báo vàng và ghi `parking_log.txt` |
| **5** | Quẹt xe 2 (`2`) rồi quẹt tiếp xe 3 (`3`) | Bãi đầy `2 / 2` (Rule 2); xe 3 bị từ chối ngay tại ESP32 (`BAI XE DA DAY!`) |
| **6** | Quẹt thẻ lạ (`4` / `AA BB CC DD`) 3 lần liên tiếp | Còi 3 tiếng; lần 3 kích hoạt báo động đỏ Rule 3 và gợi ý UID |
| **7** | Tab 2: đăng ký thẻ vừa quẹt (`Vé tháng`), khóa 1 thẻ, đổi giá | Đẩy `config` retained về ESP32; vé tháng `0đ`, thẻ khóa báo `LOCKED_CARD` |
| **8** | Bấm `MỞ BARIE`, chờ `> 10 giây`, rồi thử `ĐÓNG BARIE` | Rule 4 tự bắn lệnh `{"cmd":"close","src":"rule4"}`; servo đóng qua HC-SR04 |
| **9** | Cho xe ra, kiểm tra Tab 3 Lịch sử và `data/parking_log.txt` | Tính cước, ghép cặp giờ vào–ra, xuất CSV mở được trên Excel |

> **LỜI THOẠI:**  
> Kịch bản 9 bước đi từ đăng nhập Dashboard, quẹt xe vào, kiểm tra chống kẹp xe dưới 15 cm, kích hoạt lần lượt 4 rule tự động, thử tính năng đồng bộ thẻ và bảng giá mới xuống Wokwi, điều khiển barie hai chiều và đối soát giao dịch qua tệp log và CSV.

> **CÂU NỐI:**  
> Cuối cùng, nhóm xin tổng kết số đo, hạn chế hiện tại và hướng phát triển.

---

## SLIDE 13: SỐ ĐO, HẠN CHẾ VÀ HƯỚNG PHÁT TRIỂN
* **Số liệu biên dịch & kiểm thử**:
  * Firmware ESP32 (`pio run` / PlatformIO 6.2.0): **Flash 62,7%** (`821.629 / 1.310.720 bytes`), **RAM 14,3%** (`46.764 / 327.680 bytes`).
  * Xác thực Node-RED (`/ui`): `401 Unauthorized` khi chưa đăng nhập, `200 OK` sau Basic Auth; Editor đạt `0` lỗi validation trên `69` phần tử; Chrome CDP ghi nhận `0` lỗi JavaScript trên 3 tab.
  * Độ trễ mạng MQTT đo từ Node.js tới `broker.hivemq.com`: `167–172 ms` (log `parking_log.txt` phân giải 1 giây nên chưa đo độ trễ mili giây đầu-cuối từ Wokwi).
* **Hạn chế hiện có**: Chạy mô phỏng trên Wokwi (sức chứa 2 ô, ngưỡng demo rút gọn), phụ thuộc public broker chưa TLS, và cần hoàn thành quay video 9 bước trên Wokwi thật.
* **Hướng phát triển**: Lắp đặt mạch thật, bổ sung camera nhận diện biển số (ANPR), thanh toán VietQR, cảm biến từng ô đỗ và cảnh báo qua Telegram Bot.

> **LỜI THOẠI:**  
> Hệ thống đạt bộ nhớ Flash 62,7% và RAM 14,3% trên ESP32, toàn bộ 69 phần tử Node-RED không có lỗi cấu hình và Dashboard đã bật xác thực đăng nhập. Hạn chế còn lại là môi trường mô phỏng hai ô đỗ dùng public broker. Nhóm xin cảm ơn thầy Võ Hoàng Hải và các bạn đã lắng nghe.
