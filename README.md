# ESP8266 - Temperature , Humidity and PM2.5 notify every hour with LINE

- บอร์ดที่ผมใช้คือ WeMos D1 R1 ESP8266 
- เซนเซอร์ DHT22 สำหรับวัดอุณหภูมิและความชื้น
- เซนเซอร์ Sharp GP2Y1010AU0F สำหรับวัดคุณภาพอากาศ ตรวจจับควันและฝุ่นละออง

- ใช้บอร์ดทดลอง Breadboard ขนาด 170 จุด ในการประกอบ
- ต้องมีสายไฟ Jumper , Male to Male , Male to Female เพื่อเชื่อมเซนเซอร์เข้ากับบอร์ด

- ต้องมี Line Notify Access Token ด้วยนะ

- ใช้ Library , NTPClient , DHT sensor library for ESPx , TridentTD_Linenotify

- อุปกรณ์จะทำการ Sync เวลาจาก ntp Server ไม่จำเป็นต้องตั้งเวลาเอง (แต่ WiFI ที่เชื่อมต่อต้องออก Internet ได้)
- การทำงานจะส่งแจ้งเตือน อุณหภูมิ , ความชื้น และ PM 2.5 เข้ากลุ่ม Line ทุก 1 ชั่วโมง
- ส่ง Raw Data และ แจ้งเตือน อุณหภูมิ , ความชื้น และ PM 2.5 ให้เจ้าของอุปกรณ์เพื่อตรวจสอบค่าทุก 30 นาที
- มีแจ้งว่าอุปกรณ์ต่อ WiFi สำเร็จ และหมายเลข IP ให้เจ้าของทราบ 
- ส่งค่าต่าง ๆ เข้า Serial Monitor ทุก 5 วินาที

- ใช้พลังงานราว ๆ 80-90 mAh / ชม.
<br>
ดูรายละเอียดเพิ่มเติมได้ที่กลุ่ม Facebook - https://www.facebook.com/groups/arduino.thai/permalink/3197624113613677/
