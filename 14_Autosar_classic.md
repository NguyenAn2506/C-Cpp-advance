# AUTOSAR_CLASSIC
***
Trong thực tế hay trong các hệ điều hành trên máy tính, vì sao phải dùng hệ điều hành mà sao ko dùng pthread trực tiếp?

=> Vì khi chạy song song tại 1 thời điểm thì các tác vụ có thể cùng truy cập vào các khối phần cừng liên tục nếu không có hệ điều hành quản lý thì có thể các khối phần cứng ví dụ GPIO sẽ không biết nên ưu tiên cho task nào 
=> Thông qua hệ điều hành quản lý thì có thể chạy đa luồng tại các thời điểm khác nhau, autosar là 1 ví dụ về hệ điều hành này
![Image](https://github.com/user-attachments/assets/0e8a7431-1da2-4c49-81eb-96904f7fe81a)
***
## 14.1.  Khái niệm:
**AUTOSAR** (**AUT**omotive **O**pen **S**ystem **AR**chitecture) là một tiêu chuẩn toàn cầu cho phát triển phần mềm ô tô với mục tiêu là chuẩn hóa kiến trúc phần mềm cho các hệ thống điều khiển điện tử (ECU) trong ô tô, nhằm tăng tính khả chuyển, khả mở rộng và giảm chi phí phát triển.
***
## 14.2. So sánh việc sử dụng Autosar và không sử dụng Autosar
|Không sử dụng Autosar|Sử dụng Autosar|
|:-----|:-----|
|❖ Thiếu sự đồng nhất giữa các task của ECU, chạy tuần tự|❖ Có sẵn các tiêu chuẩn để dựa vào.|
|❖	Khả năng tái sử dụng thấp.| ❖	Khả năng tái sử dụng phần mềm cao với các dự án khác nhau.|
|❖	Quản lý lỗi và bảo trì phức tạp.|❖	Dễ dàng thay đổi để tương thích với các dòng MCU khác nhau.|
|❖	Hệ thống thiếu linh hoạt, mở rộng và phát triển hệ thống khó khăn, => chỉ viết cho 1 ô tô, phải viết lại cho ô tô khác.| ❖	Phần mềm và phần mềm được tách biệt với nhau.|
|❖	Làm việc nhóm khó khăn.|❖	Dễ quản lý và bảo trì phần mềm.|
***
## 14.3. Autosar classic
![Image-1](https://github.com/user-attachments/assets/8f78fa45-dfcd-4977-b365-fdbf00dfc83b)
***
### 14.3.1. Kiến trúc phân lớp của AUTOSAR:
-	**Application Layer**: Bao gồm các thành phần phần mềm ứng dụng, thực hiện các chức năng cụ thể của xe (như kiểm soát động cơ, phanh, v.v).
-	**Runtime Environment (RTE)**: Là lớp trung gian giữa phần mềm ứng dụng và phần mềm cơ bản, giúp phần mềm ứng dụng có thể giao tiếp với nhau một cách chuẩn hóa (liên kết SWC và BSW).
-	**Basic Software (BSW)**: Là phần mềm cơ bản, bao gồm các thành phần phần mềm tiêu chuẩn để quản lý các chức năng hệ thống, giao tiếp và điều khiển phần cứng.
-	**Micorcontroller**: sau khi làm 3 tầng trên mới làm tầng này
***
### 14.3.2. Application Layer
**Application layer (lớp ứng dụng):**
-	Bao gồm nhiều khối phần mềm ứng dụng (Software Component - SWC). Mỗi SWC thực hiện 1 chức năng cụ thể trong hệ thống ECU. 
-	SWC chỉ quan tâm đến logic (tính toán số học, khởi động thế nào), không cần quan tâm đến phần cứng. Tuy nhiên, SWC vẫn có thể giao tiếp với nhau và giao tiếp với phần cứng thông qua RTE.

=>	Viết các thuật toán, logic ở lớp này

![Image-2](https://github.com/user-attachments/assets/127410fd-3158-4c18-ab5e-6000f0e4d907)
***
### 14.3.3. Runtime Environment (RTE)
**RTE** đóng vai trò quan trọng trong việc kết nối Software Components (SWC) và Basic Software (BSW) thông qua một kiến trúc trừu tượng.
Một số chức năng của RTE:
-	**Truyền thông tin giữa các SWCs**: RTE cung cấp cơ chế truyền thông để các thành phần phần mềm (SWCs) có thể trao đổi dữ liệu hoặc gọi dịch vụ với nhau mà không cần biết chi tiết về các phần còn lại của hệ thống. 
-	**Kết nối với BSW**: RTE cung cấp giao diện để các SWCs có thể tương tác với BSW. Điều này giúp các SWCs có thể sử dụng các dịch vụ hoặc điều khiển phần cứng một cách dễ dàng.
-	Hỗ trợ việc lập lịch và điều phối thực thi của các SWCs theo các sự kiện hoặc chu kỳ định sẵn. 

=>	Điều hướng dữ liệu từ cảm biến để gọi hàm nào cho phù hợp

***
### 14.3.4. Basic Software (BSW)
**Basic Software (BSW)** là một trong ba thành phần chính của kiến trúc AUTOSAR, đóng vai trò nền tảng để hỗ trợ phần mềm ứng dụng (SWC) hoạt động trên phần cứng. BSW cung cấp các dịch vụ cơ bản như quản lý phần cứng, giao tiếp, chẩn đoán, và các dịch vụ hệ thống.

**BSW được chia thành 3 lớp chính:**
-	**Service Layer**.    
-	**ECU Abstraction Layer**.
-	**Microcontroller Abstraction Layer - MCAL**.

Cả 3 lớp này đều có điểm chung là System Service, hay nói đúng hơn là SS này là hệ điều hành OS, cụ thể hơn thì nó là thư viện pthread đã viết ở bài học trước

**a)	Service Layer**
Đây là lớp cao nhất trong BSW, cung cấp các dịch vụ hệ thống và tiện ích cho các phần mềm ứng dụng (SWC) và các lớp khác của BSW. Các dịch vụ này bao gồm quản lý thời gian thực, chẩn đoán, quản lý lỗi, quản lý nguồn, v.v.
-	Ở lớp **Service Layer** thì thông thường sẽ quản lý bộ nhớ như thời gian thực, RAM, ROM; mã hóa; giao tiếp bên ngoài phần cứng, giao tiếp UART, CAN LIN

**b)	ECU Abstraction Layer:**
Lớp này cung cấp một giao diện trừu tượng cho tất cả các thiết bị ngoại vi và phần cứng cụ thể của ECU. Nó ẩn đi sự khác biệt về phần cứng của các thiết bị ngoại vi khác nhau và cung cấp một giao diện tiêu chuẩn cho các lớp bên trên (Service Layer và SWC).
-	Ở lớp thứ **ECU** thì lớp naỳ cũng tương đồng với tầng RTE (tầng thứ 2), tuy nhiên h nó là trung gian của lớp service và lớp MCAL

**c)	MCAL:**
Đây là lớp thấp nhất trong BSW, cung cấp giao diện trừu tượng để tương tác trực tiếp với các thành phần phần cứng của vi điều khiển, chẳng hạn như bộ xử lý trung tâm (CPU), các thiết bị ngoại vi tích hợp (như ADC, PWM, UART), và các bộ định thời (timer).
-	Ở lớp **MCAL** thì lớp liên quan đến phần cứng, cụ thể là phần cấu hình các khối ở trên bao gồm thông số đã nhận từ lớp 2,  or là thông qua tầng 1 và thông qua tầng 2 là RTE để lấy thông số
