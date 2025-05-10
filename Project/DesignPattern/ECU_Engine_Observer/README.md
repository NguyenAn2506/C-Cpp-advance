# Observer:
***
Trong hệ thống ô tô, nhiều thành phần có thể cần được thông báo khi một sự kiện hoặc trạng thái quan trọng thay đổi. Ví dụ, khi nhiệt độ động cơ vượt quá một mức nhất định, các hệ thống khác như hệ thống làm mát, cảnh báo trên bảng điều khiển, và ECU (Engine Control Unit) cần được thông báo để thực hiện các hành động thích hợp. Mẫu thiết kế Observer cho phép một đối tượng (Subject) thông báo cho nhiều đối tượng khác (Observer) khi trạng thái của nó thay đổi.
***
## **Yêu cầu:**
***
### 1.	Thiết kế một lớp Subject đại diện cho động cơ (Engine)

nơi có thể theo dõi và thông báo cho các đối tượng quan sát (Observers) khi có thay đổi về trạng thái, chẳng hạn như nhiệt độ hoặc tốc độ động cơ.
***
### 2.	Thiết kế các lớp Observer 

Đại diện cho các hệ thống liên quan, bao gồm:
○	Hệ thống làm mát (CoolingSystem): Hệ thống này cần được thông báo khi nhiệt độ động cơ vượt quá mức an toàn để kích hoạt quạt làm mát.
○	Hệ thống cảnh báo (WarningSystem): Cảnh báo trên bảng điều khiển sẽ được kích hoạt khi có bất kỳ sự cố nào liên quan đến nhiệt độ hoặc tốc độ động cơ.
○	ECU (EngineControlUnit): Theo dõi và điều chỉnh các tham số khác như nhiên liệu và hiệu suất dựa trên nhiệt độ và tốc độ động cơ.
***
### 3.	Chương trình chính (main):

a.	Khởi tạo đối tượng Engine và các đối tượng quan sát (Observers) như CoolingSystem, WarningSystem, và EngineControlUnit.
b.	Đăng ký các đối tượng quan sát vào đối tượng Engine.
c.	Khi có thay đổi về nhiệt độ hoặc tốc độ, đối tượng Engine sẽ thông báo cho tất cả các hệ thống đã đăng ký để chúng có thể xử lý sự kiện tương ứng.
***
### 4. Mô tả chi tiết:
***
#### 4.1. Thiết kế lớp Subject (Engine): (Object (subject) class)

●	Nhiệm vụ: Lớp này sẽ đóng vai trò là chủ thể theo dõi và thông báo cho các hệ thống khác về thay đổi trạng thái (ví dụ: nhiệt độ hoặc tốc độ động cơ).
●	Chức năng:
○	addObserver(Observer*): Thêm một đối tượng quan sát (Observer) vào danh sách theo dõi.
○	removeObserver(Observer*): Gỡ bỏ một đối tượng quan sát khỏi danh sách theo dõi.
○	notifyObservers(): Thông báo cho tất cả các đối tượng quan sát về thay đổi trạng thái.
○	setEngineState(int speed, float temperature): Thay đổi trạng thái của động cơ (tốc độ, nhiệt độ) và kích hoạt thông báo đến các hệ thống quan sát.
○	getState(): Trả về trạng thái hiện tại của động cơ (tốc độ và nhiệt độ).
***
#### 4.2. Thiết kế các lớp Observer: (Observer class)

●	Nhiệm vụ: Các hệ thống như CoolingSystem, WarningSystem, và EngineControlUnit sẽ đăng ký để nhận thông báo khi trạng thái của động cơ thay đổi. Mỗi hệ thống sẽ xử lý thông tin theo cách riêng của mình.
●	Chức năng chung:
○	update(int speed, float temperature): Phương thức được gọi bởi Engine khi có sự thay đổi về tốc độ hoặc nhiệt độ.
●	Cụ thể:
○	CoolingSystem: Theo dõi nhiệt độ động cơ. Khi nhiệt độ vượt ngưỡng an toàn (ví dụ: 90 độ C), hệ thống sẽ bật quạt làm mát.
○	WarningSystem: Kích hoạt cảnh báo trên bảng điều khiển khi nhiệt độ vượt quá 100 độ C hoặc tốc độ vượt quá 6000 RPM.
○	EngineControlUnit: Điều chỉnh các tham số hiệu suất và nhiên liệu khi tốc độ hoặc nhiệt độ động cơ thay đổi.
***
#### 4.3. Chương trình chính (main):

●	Bước 1: Tạo đối tượng Engine (Subject) và các đối tượng quan sát (Observers) như CoolingSystem, WarningSystem, và EngineControlUnit.
●	Bước 2: Đăng ký các hệ thống quan sát vào động cơ.
●	Bước 3: Khi nhiệt độ hoặc tốc độ động cơ thay đổi, hệ thống sẽ kích hoạt thông báo đến các đối tượng quan sát. Mỗi đối tượng sẽ thực hiện hành động tương ứng dựa trên thông tin nhận được.
***
## Yêu cầu nâng cao:
***
### 1.	Kiểm tra và kích hoạt sự kiện quá nhiệt:

○	Nếu nhiệt độ động cơ vượt quá 100 độ C, hệ thống cảnh báo sẽ thông báo ngay lập tức cho người lái xe. Nếu nhiệt độ giảm xuống dưới mức này, cảnh báo sẽ được tắt.
***
### 2.	Mở rộng thêm các hệ thống quan sát khác:

○	FuelInjectionSystem: Điều chỉnh lượng nhiên liệu được bơm vào động cơ dựa trên tốc độ hiện tại và nhiệt độ của động cơ.
○	TransmissionControlUnit: Điều chỉnh hộp số tự động dựa trên tốc độ của động cơ.
***
### 3.	Hủy đăng ký (Unsubscribe):

○	Khi một hệ thống không còn cần theo dõi động cơ, nó có thể hủy đăng ký khỏi danh sách quan sát để giảm tải cho hệ thống điều khiển trung tâm.
***
### 4.	Tối ưu hóa thông báo:

○	Khi có sự thay đổi nhỏ không ảnh hưởng đến trạng thái tổng thể của động cơ (ví dụ: thay đổi nhỏ trong khoảng nhiệt độ an toàn), hệ thống không cần thông báo cho các đối tượng quan sát để tránh quá tải và xử lý không cần thiết.

***
# Demo
***
Video demo: [Engine - Observer](https://www.google.com)
