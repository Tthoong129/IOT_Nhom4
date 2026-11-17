# HỆ THỐNG BÃI GIỮ XE MÁY TỰ QUẢN SỬ DỤNG RFID (ESP32 SMART PARKING)

Dự án bãi giữ xe máy tự quản ứng dụng kiến trúc IoT 4 tầng: Nhận diện và kiểm soát xe ra vào bằng thẻ RFID, tự động đóng/mở barie với thuật toán an toàn chống kẹp xe bằng cảm biến siêu âm, quản lý trạng thái đỗ xe theo thời gian thực và điều khiển từ xa qua Web Dashboard.

---

## 1. Kiến Trúc 4 Tầng IoT

```mermaid
flowchart TD
    subgraph L4["TẦNG 4: APPLICATION"]
        DASH["Node-RED Web Dashboard (http://localhost:1880/ui)<br/>Sơ đồ ô đỗ trực quan | Bảng điều khiển từ xa Mở/Đóng Barie"]
        EXT["Module Mở Rộng: Hóa đơn VietQR | Cảnh báo Telegram"]
    end

    subgraph L3["TẦNG 3: MIDDLEWARE & AUTOMATION"]
        FLOW["Node-RED Engine (47 Nodes)"]
        R1["Rule 1: Cảnh báo xe đỗ quá giờ (Overstay >30s)"]
        R2["Rule 2: Khóa cổng khi bãi đầy (Lot Full 2/2)"]
        R3["Rule 3: Báo động dò mã thẻ lạ liên tiếp (>=3 lần)"]
        R4["Rule 4: Tự động ép đóng barie khi mở quá lâu (>10s)"]
    end

    subgraph L2["TẦNG 2: NETWORK & CONNECTIVITY"]
        BROKER["MQTT Broker: HiveMQ Cloud / Local Mosquitto (1883)"]
        WIFI["Wi-Fi 802.11 b/g/n (Wokwi-GUEST)"]
        MQTT_CLIENT["PubSubClient (Tự kết nối lại sau 5s)"]
    end

    subgraph L1["TẦNG 1: SENSING & ACTUATION"]
        ESP["ESP32 DevKit V1"]
        RFID["RFID-RC522 (Quét mã thẻ 13.56 MHz)"]
        SONAR["HC-SR04 (Siêu âm - Chống kẹp xe Anti-Pinch)"]
        SERVO["Servo SG90 (Cánh tay Barie 0° - 90°)"]
        LEDS["Cụm LED Giao thông (Đỏ - STOP / Xanh - GO)"]
        BUZZER["Active Buzzer (Còi phản hồi)"]
        LCD["LCD 1602 I2C (Hiển thị biển số & cước phí)"]
    end

    %% Luồng truyền thông
    RFID & SONAR -->|Dữ liệu cảm biến| ESP
    ESP -->|Điều khiển chấp hành| SERVO & BUZZER & LCD & LEDS
    ESP -->|Uplink MQTT| WIFI
    WIFI -->|TCP 1883| BROKER
    BROKER -->|Subscribes| FLOW
    FLOW --> R1 & R2 & R3 & R4
    FLOW -->|Cập nhật giao diện| DASH
    DASH -->|Downlink command| BROKER
    R4 -.->|Downlink Auto-close| BROKER
    BROKER -->|parking_n4/barie/cmd| MQTT_CLIENT
    MQTT_CLIENT --> ESP
    ESP --> SERVO
```

---

## 2. Sơ Đồ Đấu Nối Chân GPIO (ESP32)

| Thiết bị | Chân linh kiện | Chân ESP32 | Điện áp | Chức năng |
| :--- | :--- | :--- | :---: | :--- |
| **RFID-RC522** | SDA / SCK / MOSI / MISO / RST | GPIO 5 / 18 / 23 / 19 / 4 | 3.3V | Đọc mã thẻ xe (SPI) |
| **HC-SR04** | TRIG / ECHO | GPIO 27 / GPIO 32 | 5.0V | Cảm biến khoảng cách chống kẹp xe |
| **Servo SG90** | PWM | GPIO 13 | 5.0V | Điều khiển cánh tay Barie |
| **LED ĐỎ** | Anode (+) | GPIO 25 | 3.3V | Đèn tín hiệu Dừng (Cổng đóng / Bãi đầy) |
| **LED XANH** | Anode (+) | GPIO 26 | 3.3V | Đèn tín hiệu Đi (Cổng mở) |
| **Buzzer** | Signal | GPIO 14 | 3.3V | Còi chíp phản hồi |
| **LCD 1602** | SDA / SCL | GPIO 21 / GPIO 22 | 5.0V | Màn hình hiển thị I2C (0x27) |

---

## 3. Hướng Dẫn Vận Hành Hệ Thống

### 3.1. Khởi chạy Backend (Docker Stack)
```bash
docker compose up -d
# Hoặc nhấp đúp file: start_docker.bat
```
* **Node-RED Web Dashboard**: `http://localhost:1880/ui`
* **Node-RED Flow Editor**: `http://localhost:1880`
* **Mosquitto MQTT Broker**: `localhost:1883`

### 3.2. Chạy mô phỏng trên Wokwi
1. Mở file [diagram.json](diagram.json) trong VS Code hoặc trên [Wokwi Web](https://wokwi.com).
2. Nhấn nút **Play** để bắt đầu mô phỏng.
3. Nhập các phím tắt trên Serial Monitor:
   * Phím `1`, `2`, `3`, `4`: Quẹt thẻ xe 1 đến 4 (Vào bãi / Ra bãi).
   * Lệnh `scan <UID>`: Giả lập thẻ bất kỳ (Ví dụ: `scan 99 99 99 99`).
   * Lệnh `open` / `close`: Mở hoặc đóng barie thủ công.
   * Lệnh `sonar`: Xem khoảng cách vật cản dưới barie.

---

## 4. Danh Mục Topic MQTT

Broker: `broker.hivemq.com` / `localhost` | Cổng: `1883` | Tiền tố: `parking_n4/`

| Topic | Hướng | Vai trò | Mẫu Payload |
| :--- | :---: | :--- | :--- |
| `parking_n4/rfid/scan` | **Uplink** | Dữ liệu quẹt thẻ (Check-in/Check-out/Cước) | `{"uid":"04 3B 2A 1C","action":"check_in","licensePlate":"29A-123.45",...}` |
| `parking_n4/barie/status` | **Uplink** | Trạng thái cánh barie thực tế | `{"state":"open"}` hoặc `{"state":"closed"}` |
| `parking_n4/alert` | **Uplink** | Cảnh báo thẻ không hợp lệ | `{"type":"INVALID_CARD","uid":"99 99 99 99"}` |
| `parking_n4/barie/cmd` | **Downlink** | Lệnh điều khiển từ xa từ Dashboard | `{"cmd":"open"}` / `{"cmd":"close"}` |

---

## 5. Cấu Trúc Thư Mục Nguồn

```text
├── docker/
│   ├── mosquitto/config/mosquitto.conf # Cấu hình Mosquitto MQTT Broker
│   └── nodered/                        # Cấu hình container Node-RED & Dashboard
├── include/
│   ├── Config.h                        # Định nghĩa chân GPIO & tham số hệ thống
│   ├── GateController.h                # Module điều khiển Barie & chống kẹp xe
│   ├── MqttService.h                   # Module kết nối Wi-Fi & truyền thông MQTT
│   └── ParkingSystem.h                 # Module quản lý thẻ xe, cước phí & LCD
├── src/
│   ├── GateController.cpp
│   ├── MqttService.cpp
│   ├── ParkingSystem.cpp
│   └── main.cpp                        # Điểm khởi chạy điều phối trung tâm
├── diagram.json                        # Sơ đồ mạch mô phỏng phần cứng Wokwi
├── docker-compose.yml                  # Cấu hình Microservices Docker
├── nodered_flow.json                   # Luồng nghiệp vụ Node-RED (47 nodes)
├── platformio.ini                      # Cấu hình biên dịch PlatformIO ESP32
├── start_docker.bat                    # Script khởi chạy Docker
├── stop_docker.bat                     # Script dừng Docker
└── wokwi.toml                          # Cấu hình nạp firmware Wokwi
```
