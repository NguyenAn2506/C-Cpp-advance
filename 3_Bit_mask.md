# Bài 3: BIT MASK 
***
## 1. khái niệm

- Đây là 1 kỹ thuật để ta thao tác với giá trị các bit của 1 số ở dạng nhị phân, mục đích là để lưu trữ nhiều tính năng bằng trạng thái của các bit. 
- Bitmask thường được sử dụng để tối ưu hóa bộ nhớ, thực hiện các phép toán logic trên một cụm bit, và quản lý các trạng thái, quyền truy cập, hoặc các thuộc tính khác của một đối tượng.
### 1.1. Lí do nên dùng bit mask 
Khi khai báo các biến với các kiểu dữ liệu int, uint, char,….thì sẽ chiếm bộ nhớ lớn 
```c
	// int, int32_t, uint32_t   : 4 byte = 32 bit
	// int8_t, uint8_t          : 1 byte = 8 bit
	// int16_t, uint16_t        : 2 byte = 16 bit
```
Nhưng nếu sử dụng bit mask thì ta có thể lưu trữ trạng thái của từng biến (0, 1) trong các bit => điều này sẽ giúp giảm thiểu được số lượng bộ nhớ hơn 

## 2. các loại toán tử bitwise

a) NOT bitwise:
```c
int result = ~num ;
``` 
b) AND bitwise
```c
int result = num1 & num2;
```    
c) OR bitwise
```c
int result = num1 | num2;
```
d) XOR bitwise
```c
int result = num1 ^ num2;
```
![Image](https://github.com/user-attachments/assets/d4c6993a-bdc1-4b07-80ac-459575e65e22)
e) Shift left và Shift right bitwise
- Dùng để di chuyển bit sang trái hoặc sang phải.
- Trong trường hợp <<, các bit ở bên phải sẽ được dịch sang trái, và các bit trái cùng sẽ được đặt giá trị 0.
- Trong trường hợp >>, các bit ở bên trái sẽ được dịch sang phải, và các bit phải cùng sẽ được đặt giá trị 0 hoặc 1 tùy thuộc vào giá trị của bit cao nhất (bit dấu).
```c
int resultLeftShift = num << shiftAmount;
int resultRightShift = num >> shiftAmount;
```
Ví dụ: 
10010010 << 2 => 01001000
10010010 >> 5 => 00000100



