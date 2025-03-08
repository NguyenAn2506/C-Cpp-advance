# STORAGE CLASSES
***
## I. extern
***
### 1. Khái niệm 
- Extern được sử dụng để thông báo rằng một biến hoặc hàm đã được khai báo ở một nơi khác trong chương trình hoặc trong một file nguồn khác.
- Giúp chương trình hiểu rằng biến hoặc hàm đã được định nghĩa và sẽ được sử dụng từ một vị trí khác, giúp quản lý sự liên kết giữa các phần khác nhau của chương trình hoặc giữa các file nguồn

Để có thể sử dụng extern các file cần phải được liên kết lại với nhau thông qua câu lệnh
      
      gcc <tên file1.c> <tên file2.c>…. –o “file names” 

**Cú pháp khai báo extern**:
```C
extern int a;
extern int b;
```

đối với các hàm do người dùng tự định nghĩa thì không cần phải khai báo extern

**ứng dung**:
- Viết thư viện
- Chỉ sử dụng cho biến toàn cục

***
## II. static
***
Static có thể được sử dụng cho biến cục bộ và cả biến toàn cục

### 1. static cục bộ
#### 1.1. khái niệm:

Khi static được sử dụng với local variables (biến cục bộ - khai báo biến trong một hàm), nó giữ giá trị của biến qua các lần gọi hàm và giữ phạm vi của biến chỉ trong hàm đó.

#### 1.2. ứng dụng static cục bộ:
muốn biến nào giữ nguyên giá trị sau mỗi lần gọi hàm thì dùng static cục bộ

### 2. static toàn cục
#### 2.1. khái niệm:

Khi static được sử dụng với global variables ( biến toàn cục - khai báo biến bên ngoài hàm), nó hạn chế phạm vi của biến đó chỉ trong file nguồn hiện tại.

**Ứng dụng**: dùng để thiết kế các file thư viện.

**Đặc điểm**:
- bị giới hạn trong file hiện tại

***
## III. register
***
### 1. khái niệm
register được sử dụng để chỉ ra ý muốn của lập trình viên rằng 1 biến được sử dụng thường xuyên và có thể được lưu vào trong thanh ghi máy tính chứ không phải trong RAM. 

Việc này nhằm tăng tốc độ truy cập. 

### 2. quá trình thực hiện
![Image](https://github.com/user-attachments/assets/3d35f663-138f-40f8-a900-d21a7c28edef)
ALU là bộ xử lý các phép toán số học
Quá trình 
-	(1) Khi khai báo int i = 5 (khai báo static, extern cx vậy) thì nó sẽ lưu giá trị của biến này tại địa chỉ nào đó trong bộ nhớ RAM
-	(2) Từ bộ nhớ RAM nó sẽ dẩy sang các thanh ghi, lưu giá trị của biến i vào trong 1 trong các thanh ghi, thanh ghi nào trống thì nó sẽ lưu vào
-	Từ thanh ghi này thì nó sẽ tác động vào bộ ALU này, trong bộ ALU thì có bộ xử lý tính toán số học và đặc điểm của bộ ALU là nó sẽ nhận dữ liệu từ  thanh ghi thôi, không nhận dữ liệu từ bộ nhớ RAM. 
=> Nên muốn lấy dữ liệu để tính toán thì mình phải lưu qua các trung gian là những thanh ghi 
-	Phép ++i cx vậy, thông tin ++ này sẽ được lưu vào trong các thanh ghi nào đó, sau đó gửi thông tin này đến ALU
-	(3) Sau đó, ALU tính toán xong thì nó sẽ trả ngược về thanh ghi
-	(4) thanh ghi sẽ gửi giá trị này về lại địa chỉ của biến 
-	=> 4 giai đoạn

### 3. tổng kết: 
- Thường sử dụng khi mà ưu tiên cho biến đó thực hiện những phép toán số học 
- Khi mà trình biên dịch thấy sử dụng register nghĩa là nó sẽ không lưu trữ trên RAM mà nó sẽ lưu trữ trực tiếp trên thanh ghi
- Register sẽ không thể lấy địa chỉ được, không sử dụng con trỏ để trỏ đến các biến register. Vì thanh ghi không có địa chỉ. 
- Register chỉ sử dụng cho những biến cục bộ. 
( vì thanh ghi có giới hạn nên không thể sử dụng biến toàn cục. Việc chiếm dụng thanh ghi sẽ làm chậm hiệu suất của chương trình)
- Ngày nay, do đã phát minh ra các vi điều khiển chạy rất nhanh rồi nên bây h người ta ít xài từ khóa register. Do bộ xử lý về sau này rất nhanh và mạnh, nhưng mà nếu sử dụng các dòng vi xử lý xưa cổ thì bộ xử lý của nó sẽ rất chậm, nếu muốn tăng tốc thì sử dụng register vào  

***
## IV. volatile 
***
Được sử dụng để báo hiệu cho trình biên dịch rằng một biến có thể thay đổi ngẫu nhiên, ngoài sự kiểm soát của chương trình. 

Việc này ngăn chặn trình biên dịch tối ưu hóa hoặc xóa bỏ các thao tác trên biến đó, giữ cho các thao tác trên biến được thực hiện như đã được định nghĩa.
 
- Volatile là dùng để ngăn trình biên dịch tối ưu hóa 1 biến nào đó
- Thực tế, khi mà lập trình vi điều khiển thì sẽ có những lúc làm cho các biến thay đổi đột ngột như là Ngắt, … giá trị bị thay đổi đột ngột 
- Khi mà ngắt thì dữ liệu vẫn giữ chứ không mất đi
- Thường ứng dụng cho những việc đọc dữ liệu cảm biến,…

***


 