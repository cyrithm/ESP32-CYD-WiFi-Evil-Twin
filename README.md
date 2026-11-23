# CyRithm — Wi-Fi Evil Twin 

> **DISCLAIMER: โปรเจกต์นี้จัดทำขึ้นเพื่อการศึกษา การสาธิต และการทดสอบความปลอดภัยทางไซเบอร์เท่านั้น**

CyRithm เป็นโปรเจกต์สาธิตเทคนิค **Wi-Fi Evil Twin Attack** โดยใช้ ESP32 เพื่อจำลอง Wireless Access Point และ Captive Portal ที่มีลักษณะคล้ายกับระบบ Wi-Fi Login ที่พบได้ทั่วไป

โปรเจกต์นี้มีวัตถุประสงค์เพื่อแสดงให้เห็นถึงความเสี่ยงจากการเชื่อมต่อ Wi-Fi ที่ไม่น่าเชื่อถือ และอธิบายว่าผู้ไม่หวังดีสามารถใช้เครือข่ายไร้สายปลอมร่วมกับหน้า Captive Portal เพื่อหลอกให้ผู้ใช้งานเปิดเผยข้อมูลได้อย่างไร

## ⚠️ Disclaimer & Legal Notice

**โปรเจกต์นี้มีวัตถุประสงค์เพื่อการศึกษาและการทดสอบความปลอดภัยในสภาพแวดล้อมที่ได้รับอนุญาตเท่านั้น**

ผู้พัฒนาขอแจ้งให้ทราบว่า:

- ห้ามนำโปรเจกต์นี้ไปใช้เพื่อเข้าถึง ดักจับ หรือเก็บรวบรวมข้อมูลของบุคคลอื่นโดยไม่ได้รับความยินยอม
- ห้ามนำไปใช้สร้างเครือข่าย Wi-Fi ปลอมเพื่อหลอกลวงผู้ใช้งานจริง
- ห้ามนำไปใช้เพื่อขโมย Username, Password หรือข้อมูลส่วนบุคคล
- การทดสอบกับบุคคล องค์กร หรือเครือข่ายใด ๆ ต้องได้รับอนุญาตจากเจ้าของก่อนเสมอ
- ผู้ใช้งานต้องรับผิดชอบต่อการนำซอฟต์แวร์นี้ไปใช้งาน และต้องปฏิบัติตามกฎหมายที่เกี่ยวข้อง

**ผู้พัฒนาไม่สนับสนุนการนำเทคนิคดังกล่าวไปใช้เพื่อ Phishing, Credential Theft หรือกิจกรรมที่ผิดกฎหมายทุกรูปแบบ**

การนำไปใช้โดยไม่ได้รับอนุญาตถือเป็นความรับผิดชอบของผู้ใช้งานแต่เพียงผู้เดียว

## Project Overview

โปรเจกต์นี้จำลองการทำงานของ Evil Twin ผ่าน ESP32 โดยประกอบด้วยองค์ประกอบหลักดังนี้:

1. **Wireless Access Point (AP)**

   ESP32 สร้าง Wireless Access Point ขึ้นมาเพื่อจำลองเครือข่าย Wi-Fi

2. **DNS Server**

   ใช้ DNS Wildcard เพื่อจำลองพฤติกรรมของ Captive Portal โดยนำ DNS Requests ไปยัง IP Address ของ Access Point

3. **Captive Portal**

   ใช้ ESPAsyncWebServer ให้บริการหน้าเว็บผ่าน HTTP สำหรับสาธิตกระบวนการ Authentication

4. **Credential Submission Demonstration**

   ระบบรับข้อมูล Username และ Password ที่ถูกส่งผ่าน HTTP POST และส่งข้อมูลดังกล่าวไปยัง Serial Monitor และ TFT Display เพื่อแสดงให้เห็นถึงความเสี่ยงของการกรอกข้อมูลบนหน้า Login ที่ไม่น่าเชื่อถือ

5. **TFT Display**

   ใช้แสดงสถานะและข้อมูลที่ได้รับจาก Captive Portal บนหน้าจอ

## Hardware

- ESP32 Development Board
- TFT Display ที่รองรับ TFT_eSPI
- USB Cable สำหรับจ่ายไฟ

## Software & Libraries

โปรเจกต์ใช้ Arduino Framework และไลบรารีต่อไปนี้:

- Arduino Core for ESP32
- WiFi.h
- DNSServer
- LittleFS
- AsyncTCP
- ESPAsyncWebServer
- TFT_eSPI

## Project Structure

```text
.
├── src/
│   ├── main.cpp
│   ├── captive_portal.cpp
│   └── captive_portal.h
└── data/
    └── index.html
```

| File | Description |
|---|---|
| `main.cpp` | Main program และการจัดการ TFT Display |
| `captive_portal.cpp` | DNS Server, Access Point และ Captive Portal |
| `captive_portal.h` | Header สำหรับ Captive Portal |
| `data/index.html` | HTML Interface |

## Security Considerations

โปรเจกต์นี้ใช้ HTTP ซึ่งไม่มีการเข้ารหัสข้อมูลระหว่าง Client และ Server

นอกจากนี้ การสร้าง Access Point และ Captive Portal ไม่ได้หมายความว่าเครือข่ายดังกล่าวมีความปลอดภัยหรือเป็นเครือข่ายที่เชื่อถือได้

ข้อควรระวัง:

- อย่าใช้ Password จริงในการทดสอบ
- ใช้ข้อมูลจำลอง (Dummy Credentials) เท่านั้น
- หลีกเลี่ยงการทดสอบบนเครือข่ายสาธารณะ
- จำกัดพื้นที่ทดสอบให้อยู่ใน Lab Environment
- ไม่ควรนำระบบไปใช้งานจริงในลักษณะ Authentication Service

## Educational Objectives

โปรเจกต์นี้มีจุดประสงค์เพื่อศึกษา:

- หลักการทำงานของ Wi-Fi Access Point
- ความสัมพันธ์ระหว่าง DNS และ Captive Portal
- การทำงานของ HTTP GET และ POST
- ความเสี่ยงจากการเชื่อมต่อ Wi-Fi ที่ไม่น่าเชื่อถือ
- Social Engineering และ Phishing Awareness
- ความสำคัญของ HTTPS และการตรวจสอบความถูกต้องของเครือข่าย

---

**Educational Purpose Only. Use Responsibly.**

โปรดใช้ความรู้ด้าน Cybersecurity เพื่อสร้างระบบที่ปลอดภัยขึ้น ไม่ใช่เพื่อสร้างความเสียหายให้แก่ผู้อื่น.

**Follow us:**
[Instagram](https://www.instagram.com/cyrithm),
[Tiktok](https://www.tiktok.com/@cyrithm),
[YouTube](https://www.youtube.com/@CyRithm)