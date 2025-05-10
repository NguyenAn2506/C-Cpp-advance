# Singleton:
***
Trong hệ thống ô tô, ECU chịu trách nhiệm điều khiển động cơ, bao gồm việc kiểm soát tốc độ động cơ, nhiệt độ và các thông số quan trọng khác. Vì chỉ có duy nhất một ECU trong xe, nó cần được triển khai như một Singleton để đảm bảo có thể truy cập nó từ bất kỳ phần nào của hệ thống mà không cần khởi tạo nhiều lần.
***
## Yêu cầu:
### 1. Thiết kế lớp EngineControlUnit theo mẫu Singleton:
**Mục đích:** Lớp EngineControlUnit mô phỏng hệ thống điều khiển động cơ của xe (ECU). Mẫu thiết kế Singleton đảm bảo rằng trong toàn bộ chương trình chỉ tồn tại duy nhất một instance của ECU. Điều này là cần thiết trong các hệ thống automotive, nơi chỉ có một ECU điều khiển toàn bộ động cơ, và bất kỳ bộ phận nào cũng có thể truy cập được nó.

**Cấu trúc Singleton:**
- Phương thức khởi tạo (constructor): Được đặt là private để ngăn chặn việc khởi tạo instance mới từ bên ngoài.
- Biến static instance: Dùng để lưu trữ instance duy nhất của lớp. Biến này được khởi tạo là nullptr hoặc giá trị ban đầu trong phần khai báo.
- Phương thức getInstance(): Phương thức static kiểm tra xem instance đã tồn tại chưa, nếu chưa thì tạo mới instance, nếu đã tồn tại thì trả về instance hiện tại.
***
### 2. Các chức năng cần thiết trong lớp EngineControlUnit:
**setEngineSpeed(int speed):**
- Chức năng này dùng để thiết lập tốc độ động cơ (RPM). Giá trị tốc độ phải nằm trong khoảng từ 0 đến 6000 RPM để đảm bảo an toàn và tính thực tế trong mô phỏng.
- Nếu tốc độ không hợp lệ (nằm ngoài khoảng cho phép), hàm sẽ in ra thông báo cảnh báo và không thay đổi giá trị hiện tại.

**getEngineSpeed():**
- Trả về tốc độ động cơ hiện tại. Điều này giúp các bộ phận khác trong hệ thống có thể truy cập và lấy thông tin về tốc độ động cơ bất cứ lúc nào.

**setEngineTemperature(float temperature):**
- Chức năng này dùng để thiết lập nhiệt độ động cơ (Celsius). Giá trị nhiệt độ phải nằm trong khoảng từ -20 đến 120 độ C để mô phỏng phạm vi nhiệt độ thực tế của động cơ.
- Nếu nhiệt độ không hợp lệ, hàm sẽ đưa ra cảnh báo và không cập nhật giá trị.

**getEngineTemperature():**
- Trả về nhiệt độ động cơ hiện tại. Các hệ thống giám sát hoặc bộ phận điều khiển khác có thể cần thông tin này để kiểm tra tình trạng động cơ.

**diagnostics():**
- Chức năng này sẽ chạy các chẩn đoán cơ bản trên động cơ, in ra các thông số hiện tại như tốc độ và nhiệt độ động cơ.
- Kiểm tra quá nhiệt: Nếu nhiệt độ động cơ vượt quá 100 độ C, chương trình sẽ cảnh báo rằng động cơ đang quá nhiệt. Đây là một kiểm tra quan trọng trong automotive để đảm bảo rằng động cơ không bị hư hại do nhiệt độ quá cao.
***
### 3. Chương trình chính (main) mô phỏng việc điều khiển ECU:
Trong chương trình chính:
- **Khởi tạo và sử dụng Singleton**: Sử dụng phương thức getInstance() để lấy instance của lớp EngineControlUnit. Điều này đảm bảo rằng tất cả các lần truy cập đến ECU đều dùng chung một đối tượng duy nhất.

- **Thiết lập và lấy giá trị tốc độ, nhiệt độ**: Gọi các phương thức setEngineSpeed() và setEngineTemperature() để mô phỏng việc thay đổi giá trị tốc độ và nhiệt độ của động cơ. Các giá trị này sẽ được giới hạn để đảm bảo rằng không có tốc độ hoặc nhiệt độ không hợp lệ.
- **Chạy chẩn đoán**: Gọi hàm diagnostics() để thực hiện kiểm tra và in ra các thông số hiện tại của động cơ, bao gồm cả việc kiểm tra động cơ có đang quá nhiệt hay không.
***
### 4. Nâng cao bài tập:
**Kiểm tra và cảnh báo quá nhiệt:**
- Chức năng isOverheating() được thêm vào để kiểm tra nhiệt độ động cơ có vượt ngưỡng 100 độ C không. Nếu vượt ngưỡng, chương trình sẽ in ra cảnh báo về tình trạng quá nhiệt của động cơ, mô phỏng một cơ chế cảnh báo quan trọng trong các hệ thống điều khiển xe.

**Lưu trữ lịch sử dữ liệu:**
- Thêm khả năng lưu trữ lịch sử của tốc độ và nhiệt độ động cơ. Mỗi khi giá trị mới được thiết lập, nó sẽ được ghi lại vào lịch sử. Khi chạy chẩn đoán, chương trình sẽ in ra danh sách các giá trị lịch sử để người dùng hoặc kỹ sư có thể theo dõi sự thay đổi của động cơ theo thời gian.

**Giao diện với các hệ thống khác:**
- Trong thực tế, ECU thường giao tiếp với các hệ thống khác trong xe, như hệ thống phanh hoặc hệ thống kiểm soát nhiên liệu. Có thể thêm các phương thức để mô phỏng sự tương tác này, chẳng hạn như:
  - setFuelInjectionRate(): Điều chỉnh mức nhiên liệu được bơm vào động cơ dựa trên tốc độ và tình trạng của động cơ.
  - brakeControlInteraction(): Giả lập giao tiếp với hệ thống phanh, giảm tốc độ động cơ khi hệ thống phanh kích hoạt.

***

# Demo: 

Video demo: [Engine - Singleton](https://www.google.com)