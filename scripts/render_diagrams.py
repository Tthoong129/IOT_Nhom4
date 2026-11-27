# -*- coding: utf-8 -*-
"""
render_diagrams.py - Tự động vẽ bộ sơ đồ đồ họa phẳng hiện đại cho Đồ án Bãi giữ xe RFID
Thay thế toàn bộ Mermaid thô sơ bằng ảnh PNG chất lượng cao, sắc nét, chuẩn học thuật.
"""

import os
import matplotlib.pyplot as plt
import matplotlib.patches as patches

# Cấu hình font chữ tiếng Việt sắc nét trên Windows
plt.rcParams['font.sans-serif'] = ['Segoe UI', 'Arial', 'Tahoma', 'DejaVu Sans']
plt.rcParams['axes.unicode_minus'] = False

OUTPUT_DIR = os.path.join(os.path.dirname(__file__), '..', 'docs', 'figures')
os.makedirs(OUTPUT_DIR, exist_ok=True)

# Bảng màu hiện đại (Modern Tailwind Palette)
C_WHITE = "#FFFFFF"
C_BG_PAGE = "#F8FAFC"
C_BORDER_LIGHT = "#E2E8F0"
C_TEXT_MAIN = "#0F172A"
C_TEXT_MUTED = "#64748B"

# Tầng 4 - Emerald
C_L4_BG = "#ECFDF5"
C_L4_BORDER = "#10B981"
C_L4_TITLE = "#065F46"

# Tầng 3 - Indigo / Violet
C_L3_BG = "#EEF2FF"
C_L3_BORDER = "#6366F1"
C_L3_TITLE = "#3730A3"

# Tầng 2 - Amber
C_L2_BG = "#FFFBEB"
C_L2_BORDER = "#F59E0B"
C_L2_TITLE = "#92400E"

# Tầng 1 - Rose / Crimson
C_L1_BG = "#FFF1F2"
C_L1_BORDER = "#F43F5E"
C_L1_TITLE = "#9F1239"

# Trạng thái nghiệp vụ
C_SUCCESS_BG = "#DCFCE7"
C_SUCCESS_BORDER = "#22C55E"
C_SUCCESS_TEXT = "#166534"

C_REJECT_BG = "#FEE2E2"
C_REJECT_BORDER = "#EF4444"
C_REJECT_TEXT = "#991B1B"

C_WARN_BG = "#FEF3C7"
C_WARN_BORDER = "#F59E0B"
C_WARN_TEXT = "#92400E"

C_PROC_BG = "#E0F2FE"
C_PROC_BORDER = "#0284C7"
C_PROC_TEXT = "#0369A1"


def draw_card(ax, x, y, w, h, title, subtitle=None, bg=C_WHITE, border=C_BORDER_LIGHT, title_color=C_TEXT_MAIN, subtitle_color=C_TEXT_MUTED, title_fontsize=11, sub_fontsize=9, radius=0.08, align='center', lw=1.5):
    """Vẽ một khối thẻ (Card) bo góc mềm mại, đổ bóng nhẹ"""
    # Đổ bóng nhẹ phía sau
    shadow = patches.FancyBboxPatch((x + 0.04, y - 0.04), w, h, boxstyle=f"round,pad=0,rounding_size={radius}",
                                    facecolor="#CBD5E1", edgecolor="none", alpha=0.35, zorder=2)
    ax.add_patch(shadow)

    # Thẻ chính
    box = patches.FancyBboxPatch((x, y), w, h, boxstyle=f"round,pad=0,rounding_size={radius}",
                                facecolor=bg, edgecolor=border, linewidth=lw, zorder=3)
    ax.add_patch(box)

    # Chữ bên trong thẻ
    if align == 'center':
        tx = x + w / 2.0
        ha = 'center'
    else:
        tx = x + 0.2
        ha = 'left'

    if subtitle:
        ty_title = y + h * 0.65
        ty_sub = y + h * 0.32
        ax.text(tx, ty_title, title, ha=ha, va='center', fontsize=title_fontsize, fontweight='bold', color=title_color, zorder=4)
        ax.text(tx, ty_sub, subtitle, ha=ha, va='center', fontsize=sub_fontsize, color=subtitle_color, zorder=4)
    else:
        ty_title = y + h * 0.5
        ax.text(tx, ty_title, title, ha=ha, va='center', fontsize=title_fontsize, fontweight='bold', color=title_color, zorder=4)


def draw_arrow(ax, x1, y1, x2, y2, color="#475569", lw=2, label=None, label_pos=0.5, label_color="#334155", label_fontsize=9, curved=0.0):
    """Vẽ mũi tên kết nối vector đẹp mắt"""
    if curved != 0.0:
        connectionstyle = f"arc3,rad={curved}"
    else:
        connectionstyle = "arc3,rad=0"

    arrow = patches.FancyArrowPatch((x1, y1), (x2, y2),
                                    arrowstyle="-|>,head_length=6,head_width=4",
                                    connectionstyle=connectionstyle,
                                    color=color, linewidth=lw, zorder=5)
    ax.add_patch(arrow)

    if label:
        lx = x1 + (x2 - x1) * label_pos
        ly = y1 + (y2 - y1) * label_pos
        ax.text(lx, ly, label, ha='center', va='center', fontsize=label_fontsize,
                fontweight='bold', color=label_color,
                bbox=dict(boxstyle="round,pad=0.25", facecolor=C_WHITE, edgecolor=color, alpha=0.95, lw=1),
                zorder=6)


# ==============================================================================
# 1. HÌNH 3.1: SƠ ĐỒ KIẾN TRÚC TỔNG THỂ 4 TẦNG & LUỒNG 2 CHIỀU
# ==============================================================================
def render_fig_3_1():
    print("-> Rendering Hình 3.1: Kiến trúc 4 tầng IoT...")
    fig, ax = plt.subplots(figsize=(16, 10), dpi=300)
    ax.set_xlim(0, 16)
    ax.set_ylim(0, 10)
    ax.axis('off')
    fig.patch.set_facecolor(C_BG_PAGE)

    # Tiêu đề biểu đồ
    ax.text(8, 9.6, "SƠ ĐỒ KIẾN TRÚC 4 TẦNG IoT & LUỒNG TRUYỀN THÔNG HAI CHIỀU",
            ha='center', va='center', fontsize=16, fontweight='bold', color=C_TEXT_MAIN)
    ax.text(8, 9.25, "Hệ thống Quản lý Bãi giữ xe Máy Tự quản Thông minh sử dụng RFID & Cảm biến Siêu âm",
            ha='center', va='center', fontsize=11, color=C_TEXT_MUTED)

    # --- KHUNG TẦNG 4: ỨNG DỤNG ---
    draw_card(ax, 1.5, 6.9, 13.0, 2.0, "", bg=C_L4_BG, border=C_L4_BORDER, radius=0.15, lw=2)
    ax.text(1.8, 8.6, "TẦNG 4: ỨNG DỤNG (WEB DASHBOARD 3 TAB & XÁC THỰC BẢO MẬT)",
            fontsize=12, fontweight='bold', color=C_L4_TITLE)
    draw_card(ax, 1.8, 7.1, 3.8, 1.3, "Tab 1: Giám sát Trực tiếp", "4 Thẻ KPI · 2 Ô đỗ · Nút đóng/mở · Nhật ký",
              bg=C_WHITE, border=C_L4_BORDER, title_color=C_L4_TITLE)
    draw_card(ax, 6.1, 7.1, 3.8, 1.3, "Tab 2: Quản lý Thẻ & Giá", "CRUD 16 Thẻ · Vé tháng 0đ · 3 Khung giá",
              bg=C_WHITE, border=C_L4_BORDER, title_color=C_L4_TITLE)
    draw_card(ax, 10.4, 7.1, 3.8, 1.3, "Tab 3: Lịch sử Giao dịch", "Ghép cặp Vào-Ra · Tìm kiếm · Xuất CSV",
              bg=C_WHITE, border=C_L4_BORDER, title_color=C_L4_TITLE)

    # --- KHUNG TẦNG 3: XỬ LÝ TRUNG GIAN ---
    draw_card(ax, 1.5, 4.6, 13.0, 2.0, "", bg=C_L3_BG, border=C_L3_BORDER, radius=0.15, lw=2)
    ax.text(1.8, 6.3, "TẦNG 3: XỬ LÝ TRUNG GIAN & TỰ ĐỘNG HÓA (NODE-RED RUNTIME IN DOCKER)",
            fontsize=12, fontweight='bold', color=C_L3_TITLE)
    draw_card(ax, 1.8, 4.8, 3.8, 1.3, "Đồng bộ Trạng thái Tập trung", "flow.get('park') hợp nhất toàn bãi",
              bg=C_WHITE, border=C_L3_BORDER, title_color=C_L3_TITLE)
    draw_card(ax, 6.1, 4.8, 3.8, 1.3, "Bộ 4 Quy tắc Tự động (Rule)", "R1: Quá giờ · R2: Đầy bãi · R3: Thẻ lạ · R4: Kẹt",
              bg=C_WHITE, border=C_L3_BORDER, title_color=C_L3_TITLE)
    draw_card(ax, 10.4, 4.8, 3.8, 1.3, "Lưu trữ Tệp Bền vững", "parking_log.txt & parking_database.json",
              bg=C_WHITE, border=C_L3_BORDER, title_color=C_L3_TITLE)

    # --- KHUNG TẦNG 2: MẠNG & TRUYỀN THÔNG ---
    draw_card(ax, 1.5, 2.4, 13.0, 1.9, "", bg=C_L2_BG, border=C_L2_BORDER, radius=0.15, lw=2)
    ax.text(1.8, 4.0, "TẦNG 2: MẠNG & TRUYỀN THÔNG (HIVEMQ PUBLIC MQTT BROKER :1883)",
            fontsize=12, fontweight='bold', color=C_L2_TITLE)
    draw_card(ax, 1.8, 2.6, 5.8, 1.2, "Luồng Uplink (4 Topic)", "rfid/scan · barie/status · alert · status (LWT)",
              bg=C_WHITE, border=C_L2_BORDER, title_color=C_L2_TITLE)
    draw_card(ax, 8.4, 2.6, 5.8, 1.2, "Luồng Downlink (2 Topic)", "barie/cmd (lệnh mở/đóng) · config (retained)",
              bg=C_WHITE, border=C_L2_BORDER, title_color=C_L2_TITLE)

    # --- KHUNG TẦNG 1: THIẾT BỊ CẢM BIẾN & CHẤP HÀNH ---
    draw_card(ax, 1.5, 0.3, 13.0, 1.8, "", bg=C_L1_BG, border=C_L1_BORDER, radius=0.15, lw=2)
    ax.text(1.8, 1.8, "TẦNG 1: CẢM BIẾN & CHẤP HÀNH TẠI CỔNG (ESP32 EDGE COMPUTING)",
            fontsize=12, fontweight='bold', color=C_L1_TITLE)
    draw_card(ax, 1.8, 0.5, 3.8, 1.1, "Khối Cảm biến", "RFID-RC522 (SPI) · Siêu âm HC-SR04",
              bg=C_WHITE, border=C_L1_BORDER, title_color=C_L1_TITLE)
    draw_card(ax, 6.1, 0.5, 3.8, 1.1, "Xử lý Biên Độc lập", "Cấp ô · Tính cước · Chống kẹp · Chống lặp",
              bg=C_WHITE, border=C_L1_BORDER, title_color=C_L1_TITLE)
    draw_card(ax, 10.4, 0.5, 3.8, 1.1, "Khối Chấp hành", "Servo SG90 (0°-90°) · LCD 1602 · LED · Còi",
              bg=C_WHITE, border=C_L1_BORDER, title_color=C_L1_TITLE)

    # --- MŨI TÊN UPLINK & DOWNLINK ---
    # Uplink (Xanh lá - đi lên bên trái)
    draw_arrow(ax, 0.9, 1.2, 0.9, 8.1, color="#10B981", lw=3.5, label="UPLINK: Sự kiện thẻ · Barie · Cảnh báo · Snapshot", label_pos=0.5, label_color="#065F46", curved=0.0)

    # Downlink (Cam - đi xuống bên phải)
    draw_arrow(ax, 15.1, 8.1, 15.1, 1.2, color="#F59E0B", lw=3.5, label="DOWNLINK: Lệnh mở/đóng barie · Cấu hình 16 thẻ & Giá", label_pos=0.5, label_color="#92400E", curved=0.0)

    out_path = os.path.join(OUTPUT_DIR, "fig_3_1_arch_4layer.png")
    plt.tight_layout()
    plt.savefig(out_path, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"-> Saved: {out_path}")


# ==============================================================================
# 2. HÌNH 3.2: LƯU ĐỒ XỬ LÝ THẺ RFID & CHỐNG KẸP BARIE
# ==============================================================================
def render_fig_3_2():
    print("-> Rendering Hình 3.2: Lưu đồ xử lý thẻ RFID...")
    fig, ax = plt.subplots(figsize=(18, 9.5), dpi=300)
    ax.set_xlim(0, 18)
    ax.set_ylim(0, 9.5)
    ax.axis('off')
    fig.patch.set_facecolor(C_BG_PAGE)

    # Tiêu đề
    ax.text(9, 9.1, "LƯU ĐỒ THUẬT TOÁN XỬ LÝ QUẸT THẺ RFID VÀ CHỐNG KẸP XE TẠI CỔNG",
            ha='center', va='center', fontsize=16, fontweight='bold', color=C_TEXT_MAIN)
    ax.text(9, 8.75, "Xử lý tại biên (Edge Computing) trên ESP32: Tự động phân luồng Vào/Ra, tính cước và an toàn siêu âm",
            ha='center', va='center', fontsize=11, color=C_TEXT_MUTED)

    # --- KHỐI 1: TIẾP NHẬN & XÁC THỰC THẺ (Cột trái X: 0.5 - 5.5) ---
    draw_card(ax, 0.5, 0.5, 5.2, 8.0, "", bg="#F0F9FF", border="#0284C7", radius=0.15, lw=2)
    ax.text(3.1, 8.2, "1. TIẾP NHẬN & XÁC THỰC THẺ", ha='center', fontsize=12, fontweight='bold', color="#0369A1")

    draw_card(ax, 1.1, 7.2, 4.0, 0.7, "Quẹt thẻ RFID", "Tần số 13,56 MHz", bg=C_WHITE, border="#0284C7")
    draw_card(ax, 1.1, 6.1, 4.0, 0.7, "Đọc & Chuẩn hóa UID", "Chuyển thành Hex viết hoa (vd: 01 02 03 04)", bg=C_WHITE, border="#0284C7")
    draw_card(ax, 1.1, 4.8, 4.0, 0.9, "Chống đọc lặp (Debounce)?", "Cùng thẻ > 1,5s & Barie đang đóng?", bg=C_WARN_BG, border=C_WARN_BORDER, title_color=C_WARN_TEXT)
    draw_card(ax, 1.1, 3.4, 4.0, 0.9, "Thẻ đã đăng ký?", "UID có trong danh sách 16 thẻ?", bg=C_WARN_BG, border=C_WARN_BORDER, title_color=C_WARN_TEXT)
    draw_card(ax, 1.1, 2.0, 4.0, 0.9, "Thẻ có bị khóa?", "Trạng thái thẻ active == true?", bg=C_WARN_BG, border=C_WARN_BORDER, title_color=C_WARN_TEXT)

    # Nút từ chối cột 1
    draw_card(ax, 1.1, 0.8, 4.0, 0.8, "TỪ CHỐI · GIỮ ĐÓNG CỔNG", "Còi bíp 3 tiếng · LCD báo lỗi · Alert", bg=C_REJECT_BG, border=C_REJECT_BORDER, title_color=C_REJECT_TEXT)

    # Mũi tên cột 1
    draw_arrow(ax, 3.1, 7.2, 3.1, 6.8, lw=2)
    draw_arrow(ax, 3.1, 6.1, 3.1, 5.7, lw=2)
    draw_arrow(ax, 3.1, 4.8, 3.1, 4.3, label="Hợp lệ", lw=2, label_color="#15803D")
    draw_arrow(ax, 3.1, 3.4, 3.1, 2.9, label="Đã đăng ký", lw=2, label_color="#15803D")

    # Mũi tên từ chối
    draw_arrow(ax, 1.1, 5.25, 0.8, 1.2, color=C_REJECT_BORDER, lw=1.5, curved=-0.3)
    draw_arrow(ax, 5.1, 3.85, 4.8, 1.6, color=C_REJECT_BORDER, lw=1.5, label="Chưa", label_color=C_REJECT_TEXT)
    draw_arrow(ax, 5.1, 2.45, 4.8, 1.6, color=C_REJECT_BORDER, lw=1.5, label="Bị khóa", label_color=C_REJECT_TEXT)

    # --- KHỐI 2: PHÂN LUỒNG VÀO / RA (Cột giữa X: 6.2 - 11.8) ---
    draw_card(ax, 6.2, 0.5, 5.6, 8.0, "", bg="#F0FDF4", border="#16A34A", radius=0.15, lw=2)
    ax.text(9.0, 8.2, "2. PHÂN LUỒNG NGHIỆP VỤ TẠI CỔNG", ha='center', fontsize=12, fontweight='bold', color="#14532D")

    draw_card(ax, 7.0, 6.8, 4.0, 0.9, "Xe đang ở trong bãi?", "Kiểm tra ô đỗ hiện tại của thẻ", bg=C_WARN_BG, border=C_WARN_BORDER, title_color=C_WARN_TEXT)

    # Nhánh VÀO (Bên trái cột 2)
    ax.text(7.6, 6.3, "Chưa gửi (LƯỢT VÀO)", fontsize=9.5, fontweight='bold', color="#0369A1")
    draw_card(ax, 6.5, 4.8, 2.4, 1.0, "Còn ô trống?", "Sức chứa 2 xe", bg=C_WARN_BG, border=C_WARN_BORDER, title_color=C_WARN_TEXT)
    draw_card(ax, 6.5, 3.2, 2.4, 1.1, "BÃI ĐÃ ĐẦY", "Từ chối · Còi 3 bíp\nLCD: BAI DA DAY", bg=C_REJECT_BG, border=C_REJECT_BORDER, title_color=C_REJECT_TEXT)
    draw_card(ax, 6.5, 1.3, 2.4, 1.4, "CẤP Ô ĐỖ VÀO", "Gán Slot 1 hoặc 2\nLưu giờ vào (millis)\nBật LED Xanh", bg=C_SUCCESS_BG, border=C_SUCCESS_BORDER, title_color=C_SUCCESS_TEXT)

    # Nhánh RA (Bên phải cột 2)
    ax.text(10.4, 6.3, "Đang gửi (LƯỢT RA)", fontsize=9.5, fontweight='bold', color="#166534")
    draw_card(ax, 9.2, 4.3, 2.3, 1.5, "TÍNH CƯỚC PHÍ", "Vé tháng: 0 đồng\nVé lượt: 3k / 5k / 9k\ntheo block thời gian", bg=C_PROC_BG, border=C_PROC_BORDER, title_color=C_PROC_TEXT)
    draw_card(ax, 9.2, 1.8, 2.3, 1.4, "GIẢI PHÓNG Ô", "Trả ô đỗ trống\nLCD hiện cước phí\nCòi bíp 2 tiếng", bg=C_SUCCESS_BG, border=C_SUCCESS_BORDER, title_color=C_SUCCESS_TEXT)

    # Mũi tên từ Khối 1 sang Khối 2
    draw_arrow(ax, 5.1, 2.45, 7.0, 7.25, color="#16A34A", lw=2.5, label="Hợp lệ", label_color="#166534")

    # Mũi tên phân nhánh Vào/Ra
    draw_arrow(ax, 7.5, 6.8, 7.5, 5.8, lw=2)
    draw_arrow(ax, 10.5, 6.8, 10.5, 5.8, lw=2)
    draw_arrow(ax, 7.7, 4.8, 7.7, 4.3, label="Hết ô (2/2)", lw=1.5, label_color=C_REJECT_TEXT, color=C_REJECT_BORDER)
    draw_arrow(ax, 7.7, 4.8, 7.7, 2.7, label="Còn ô", lw=2, label_color=C_SUCCESS_TEXT, color=C_SUCCESS_BORDER, curved=0.3)
    draw_arrow(ax, 10.35, 4.3, 10.35, 3.2, lw=2)

    # --- KHỐI 3: CHẤP HÀNH & AN TOÀN CHỐNG KẸP (Cột phải X: 12.3 - 17.5) ---
    draw_card(ax, 12.3, 0.5, 5.2, 8.0, "", bg="#FFF7ED", border="#EA580C", radius=0.15, lw=2)
    ax.text(14.9, 8.2, "3. CHẤP HÀNH & CHỐNG KẸP (HC-SR04)", ha='center', fontsize=12, fontweight='bold', color="#9A3412")

    draw_card(ax, 12.8, 6.8, 4.2, 1.0, "SERVO XOAY 90° MỞ BARIE", "Bật LED Xanh · Phát MQTT Uplink (scan)", bg=C_SUCCESS_BG, border=C_SUCCESS_BORDER, title_color=C_SUCCESS_TEXT)
    draw_card(ax, 12.8, 5.3, 4.2, 0.9, "Đếm Giữ Mở 3 Giây", "Cho phép xe di chuyển qua cổng", bg=C_WHITE, border="#EA580C")
    draw_card(ax, 12.8, 3.7, 4.2, 1.0, "Cảm biến Siêu âm d < 15 cm?", "Phát hiện xe/người đang đứng dưới cần", bg=C_WARN_BG, border=C_WARN_BORDER, title_color=C_WARN_TEXT)
    draw_card(ax, 12.8, 2.0, 4.2, 1.1, "TẠM HOÃN ĐÓNG, GIỮ 90°", "LCD cảnh báo · Đo lại sau mỗi 300 ms", bg=C_WARN_BG, border=C_WARN_BORDER, title_color=C_WARN_TEXT)
    draw_card(ax, 12.8, 0.7, 4.2, 0.9, "HẠ BARIE VỀ 0° AN TOÀN", "Bật LED Đỏ · Báo barie/status (closed)", bg=C_SUCCESS_BG, border=C_SUCCESS_BORDER, title_color=C_SUCCESS_TEXT)

    # Mũi tên từ Khối 2 sang Khối 3
    draw_arrow(ax, 8.9, 2.0, 12.8, 7.3, color="#16A34A", lw=2.5, label="Mở barie", label_color="#166534")
    draw_arrow(ax, 11.5, 2.5, 12.8, 7.3, color="#16A34A", lw=2.5)

    # Mũi tên trong Khối 3
    draw_arrow(ax, 14.9, 6.8, 14.9, 6.2, lw=2)
    draw_arrow(ax, 14.9, 5.3, 14.9, 4.7, lw=2)
    draw_arrow(ax, 14.9, 3.7, 14.9, 3.1, label="Có vật cản (< 15cm)", lw=2, label_color=C_WARN_TEXT, color=C_WARN_BORDER)
    draw_arrow(ax, 17.0, 2.55, 17.0, 4.2, label="Đo lại 300ms", lw=1.5, label_color=C_WARN_TEXT, color=C_WARN_BORDER, curved=0.5)
    draw_arrow(ax, 14.0, 3.7, 14.0, 1.6, label="An toàn (d >= 15cm)", lw=2, label_color=C_SUCCESS_TEXT, color=C_SUCCESS_BORDER, curved=-0.3)

    out_path = os.path.join(OUTPUT_DIR, "fig_3_2_flow_rfid.png")
    plt.tight_layout()
    plt.savefig(out_path, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"-> Saved: {out_path}")


# ==============================================================================
# 3. HÌNH 3.3: LUỒNG DỮ LIỆU & 4 QUY TẮC TỰ ĐỘNG TRONG NODE-RED
# ==============================================================================
def render_fig_3_3():
    print("-> Rendering Hình 3.3: Luồng Node-RED & 4 Quy tắc...")
    fig, ax = plt.subplots(figsize=(16, 9), dpi=300)
    ax.set_xlim(0, 16)
    ax.set_ylim(0, 9)
    ax.axis('off')
    fig.patch.set_facecolor(C_BG_PAGE)

    # Tiêu đề
    ax.text(8, 8.6, "LUỒNG XỬ LÝ DỮ LIỆU VÀ 4 QUY TẮC TỰ ĐỘNG HÓA TRONG NODE-RED",
            ha='center', va='center', fontsize=16, fontweight='bold', color=C_TEXT_MAIN)
    ax.text(8, 8.25, "Kiến trúc Middleware tập trung: Nhận sự kiện MQTT -> Quản lý trạng thái flow.get('park') -> Đồng bộ Dashboard & File",
            ha='center', va='center', fontsize=11, color=C_TEXT_MUTED)

    # --- KHỐI ĐẦU VÀO (Cột trái X: 0.5 - 4.8) ---
    draw_card(ax, 0.5, 0.5, 4.3, 7.4, "", bg="#F0F9FF", border="#0284C7", radius=0.15, lw=2)
    ax.text(2.65, 7.6, "CÁC LUỒNG ĐẦU VÀO (INPUT)", ha='center', fontsize=12, fontweight='bold', color="#0369A1")

    inputs = [
        ("Topic: parking_n4/status", "Snapshot hiện trạng 2 ô & LWT kết nối"),
        ("Topic: parking_n4/rfid/scan", "Sự kiện xe vào/ra hợp lệ & cước phí"),
        ("Topic: parking_n4/barie/status", "Góc mở Servo (0°-90°) & trạng thái cổng"),
        ("Topic: parking_n4/alert", "Cảnh báo thẻ lạ, thẻ khóa, bãi đầy, kẹp"),
        ("Bộ đếm nhịp 1 giây", "Inject node kích hoạt kiểm tra Rule định kỳ"),
        ("Thao tác Web Dashboard", "Lệnh đóng/mở barie, CRUD thẻ, đổi bảng giá")
    ]
    for i, (title, sub) in enumerate(inputs):
        draw_card(ax, 0.8, 6.4 - i * 1.15, 3.7, 0.95, title, sub, bg=C_WHITE, border="#0284C7", title_color="#0369A1", title_fontsize=9.5, sub_fontsize=8)

    # --- KHỐI BỘ NÃO TRUNG TÂM (Cột giữa X: 5.3 - 10.7) ---
    draw_card(ax, 5.3, 0.5, 5.4, 7.4, "", bg="#FAF5FF", border="#A855F7", radius=0.15, lw=2)
    ax.text(8.0, 7.6, "BỘ ĐIỀU PHỐI TRUNG TÂM & 4 RULE", ha='center', fontsize=12, fontweight='bold', color="#6B21A8")

    draw_card(ax, 5.6, 6.2, 4.8, 1.1, "ĐỒNG BỘ TRẠNG THÁI TẬP TRUNG", "Duy trì đối tượng duy nhất: flow.get('park')\nTránh lệch số liệu giữa các tab hiển thị",
              bg=C_WHITE, border="#A855F7", title_color="#6B21A8", title_fontsize=10.5, sub_fontsize=8.5)

    rules = [
        ("Rule 1: Xe gửi quá giờ (> 30s demo / 4-12h thật)", "Đổi viền ô đỗ sang vàng · Hiện banner & toast cảnh báo", C_WARN_BG, C_WARN_BORDER, C_WARN_TEXT),
        ("Rule 2: Bãi đầy xe (2/2 ô đã có xe)", "Đổi thẻ KPI Tổng quan sang đỏ · ESP32 tự chặn ở cổng", C_REJECT_BG, C_REJECT_BORDER, C_REJECT_TEXT),
        ("Rule 3: Dò thẻ lạ liên tiếp (>= 3 lần / 60s)", "Nâng cấp mức an ninh · Cảnh báo dấu hiệu kẻ gian thử thẻ", C_REJECT_BG, C_REJECT_BORDER, C_REJECT_TEXT),
        ("Rule 4: Barie kẹt mở quá lâu (> 10s)", "Node-RED tự phát lệnh đóng barie/cmd (vẫn đo siêu âm)", C_WARN_BG, C_WARN_BORDER, C_WARN_TEXT)
    ]
    for i, (title, sub, bg, b_col, t_col) in enumerate(rules):
        draw_card(ax, 5.6, 4.8 - i * 1.35, 4.8, 1.15, title, sub, bg=bg, border=b_col, title_color=t_col, title_fontsize=9.5, sub_fontsize=8)

    # --- KHỐI ĐẦU RA (Cột phải X: 11.2 - 15.5) ---
    draw_card(ax, 11.2, 0.5, 4.3, 7.4, "", bg="#F0FDF4", border="#16A34A", radius=0.15, lw=2)
    ax.text(13.35, 7.6, "CÁC ĐẦU RA (OUTPUT)", ha='center', fontsize=12, fontweight='bold', color="#14532D")

    outputs = [
        ("Giao diện Dashboard 3 Tab", "KPI, 2 ô đỗ, biểu đồ, nút bấm, lịch sử"),
        ("Thông báo Toast Nổi", "Hiển thị tức thời trên góc màn hình quản trị"),
        ("Tệp Nhật ký parking_log.txt", "Ghi nối tiếp mọi sự kiện theo thời gian thực"),
        ("CSDL JSON parking_database.json", "Lưu 16 thẻ, bảng giá, 100 giao dịch ghép cặp"),
        ("Topic: parking_n4/barie/cmd", "Downlink: Lệnh đóng barie an toàn từ Rule 4"),
        ("Topic: parking_n4/config", "Downlink retained: Danh sách 16 thẻ & bảng giá")
    ]
    for i, (title, sub) in enumerate(outputs):
        draw_card(ax, 11.5, 6.4 - i * 1.15, 3.7, 0.95, title, sub, bg=C_WHITE, border="#16A34A", title_color="#14532D", title_fontsize=9.5, sub_fontsize=8)

    # Mũi tên Input -> Trung tâm
    draw_arrow(ax, 4.5, 6.8, 5.6, 6.7, lw=2, color="#0284C7")
    draw_arrow(ax, 4.5, 5.6, 5.6, 6.7, lw=2, color="#0284C7")
    draw_arrow(ax, 4.5, 4.5, 5.6, 6.7, lw=2, color="#0284C7")
    draw_arrow(ax, 4.5, 3.3, 5.6, 6.7, lw=2, color="#0284C7")
    draw_arrow(ax, 4.5, 2.2, 5.6, 3.5, lw=2, color="#A855F7", label="Kích hoạt Rule", label_color="#6B21A8")
    draw_arrow(ax, 4.5, 1.0, 5.6, 6.7, lw=2, color="#0284C7")

    # Mũi tên Trung tâm -> Output
    draw_arrow(ax, 10.4, 6.7, 11.5, 6.8, lw=2, color="#16A34A")
    draw_arrow(ax, 10.4, 6.7, 11.5, 5.6, lw=2, color="#16A34A")
    draw_arrow(ax, 10.4, 6.7, 11.5, 4.5, lw=2, color="#16A34A")
    draw_arrow(ax, 10.4, 6.7, 11.5, 3.3, lw=2, color="#16A34A")
    draw_arrow(ax, 10.4, 1.2, 11.5, 2.0, lw=2, color=C_WARN_BORDER, label="Lệnh Rule 4", label_color=C_WARN_TEXT)
    draw_arrow(ax, 10.4, 6.2, 11.5, 1.0, lw=2, color="#16A34A")

    out_path = os.path.join(OUTPUT_DIR, "fig_3_3_flow_nodered.png")
    plt.tight_layout()
    plt.savefig(out_path, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"-> Saved: {out_path}")


# ==============================================================================
# 4. SƠ ĐỒ TUẦN TỰ CHO SLIDE THUYẾT TRÌNH (fig_slide_sequence.png)
# ==============================================================================
def render_slide_sequence():
    print("-> Rendering Sơ đồ Tuần tự cho Slide...")
    fig, ax = plt.subplots(figsize=(15, 8.5), dpi=300)
    ax.set_xlim(0, 15)
    ax.set_ylim(0, 8.5)
    ax.axis('off')
    fig.patch.set_facecolor(C_BG_PAGE)

    # Tiêu đề
    ax.text(7.5, 8.1, "SƠ ĐỒ TUẦN TỰ LUỒNG NGHIỆP VỤ VÀ ĐIỀU KHIỂN TỪ XA",
            ha='center', va='center', fontsize=15, fontweight='bold', color=C_TEXT_MAIN)

    # 4 Trục thực thể (Lifelines)
    lifelines = [
        ("Người gửi / Bảo vệ", 1.8),
        ("ESP32 & Cảm biến (Tầng 1)", 5.6),
        ("MQTT Broker (Tầng 2)", 9.4),
        ("Node-RED & Web (Tầng 3-4)", 13.2)
    ]
    for name, x in lifelines:
        draw_card(ax, x - 1.5, 7.1, 3.0, 0.7, name, bg=C_WHITE, border="#475569", title_fontsize=10)
        ax.plot([x, x], [0.8, 7.1], color="#94A3B8", linestyle="--", linewidth=1.5, zorder=2)

    # Khung Luồng 1: Xe Vào/Ra tại chỗ
    draw_card(ax, 0.5, 4.4, 14.0, 2.5, "", bg="#F0FDF4", border="#16A34A", radius=0.1, lw=1.5)
    ax.text(0.8, 6.6, "LUỒNG 1: QUẸT THẺ TẠI CỔNG & TỰ ĐỘNG BẢO VỆ CHỐNG KẸP (EDGE COMPUTING)",
            fontsize=10.5, fontweight='bold', color="#166534")

    draw_arrow(ax, 1.8, 6.1, 5.6, 6.1, color="#0369A1", lw=2, label="1. Quẹt thẻ RFID", label_color="#0369A1")
    draw_card(ax, 4.3, 5.2, 2.6, 0.6, "ESP32 tự cấp ô/tính phí", "Mở barie 90° tức thì", bg=C_SUCCESS_BG, border=C_SUCCESS_BORDER, title_fontsize=9, sub_fontsize=7.5)
    draw_arrow(ax, 5.6, 4.8, 9.4, 4.8, color="#16A34A", lw=2, label="2. Uplink rfid/scan & status", label_color="#166534")
    draw_arrow(ax, 9.4, 4.8, 13.2, 4.8, color="#16A34A", lw=2)

    # Khung Luồng 2: Điều khiển barie & Chống kẹp
    draw_card(ax, 0.5, 2.2, 14.0, 2.0, "", bg="#FFFBEB", border="#F59E0B", radius=0.1, lw=1.5)
    ax.text(0.8, 3.9, "LUỒNG 2: ĐIỀU KHIỂN TỪ XA & CẢM BIẾN SIÊU ÂM HC-SR04 CHỐNG KẸP",
            fontsize=10.5, fontweight='bold', color="#92400E")

    draw_arrow(ax, 13.2, 3.3, 9.4, 3.3, color="#D97706", lw=2, label="Bấm 'Đóng Barie' / Rule 4", label_color="#92400E")
    draw_arrow(ax, 9.4, 3.3, 5.6, 3.3, color="#D97706", lw=2, label="Lệnh barie/cmd (close)", label_color="#92400E")
    draw_card(ax, 4.0, 2.4, 3.2, 0.7, "HC-SR04 đo d < 15cm", "Tạm hoãn đóng · Giữ mở 90°", bg=C_WARN_BG, border=C_WARN_BORDER, title_fontsize=9, sub_fontsize=7.5)

    # Khung Luồng 3: Cấu hình retained
    draw_card(ax, 0.5, 0.6, 14.0, 1.4, "", bg="#EEF2FF", border="#6366F1", radius=0.1, lw=1.5)
    ax.text(0.8, 1.7, "LUỒNG 3: CẬP NHẬT 16 THẺ & BẢNG GIÁ ĐỘNG (DOWNLINK RETAINED)",
            fontsize=10.5, fontweight='bold', color="#3730A3")

    draw_arrow(ax, 13.2, 1.0, 9.4, 1.0, color="#6366F1", lw=2, label="Cấu hình mới từ Tab 2", label_color="#3730A3")
    draw_arrow(ax, 9.4, 1.0, 5.6, 1.0, color="#6366F1", lw=2, label="config retained -> ESP32 nạp ngay", label_color="#3730A3")

    out_path = os.path.join(OUTPUT_DIR, "fig_slide_sequence.png")
    plt.tight_layout()
    plt.savefig(out_path, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"-> Saved: {out_path}")


if __name__ == "__main__":
    print("=== BẮT ĐẦU TẠO BỘ ẢNH ĐỒ HỌA SƠ ĐỒ CHUYÊN NGHIỆP ===")
    render_fig_3_1()
    render_fig_3_2()
    render_fig_3_3()
    render_slide_sequence()
    print("=== HOÀN TẤT 4 SƠ ĐỒ SẮC NÉT TẠI docs/figures/ ===")
