# BÀI 1: COMPILER-MACRO
***
**quá trình compiler sẽ trải qua 4 bước như sau:**

![Image](https://github.com/user-attachments/assets/086c1815-10f9-45d8-9a16-6a44ce646de3)

***
## 1. Bước 1: tiền xử lý Preprocessor
- Đây là bước biến đổi file main.c thành file main.i
- cú pháp câu lệnh:
```c
gcc -E main.c -o main.i
```
- copy toàn bộ nội dung trong main.c
- copy toàn bộ nội dung thư viện đã được #include, thay thế các hàm được gọi bằng nội dung đã định nghĩa 
- thay thế các macro định nghĩa thông qua #define bằng nội dung mà nó định nghĩa
- các comment sẽ bị loại bỏ trong main.i

### 1.1. các chỉ thị tiền xử lý
#### a) Chỉ thị tiền xử lý #include
Chỉ thị #include dùng để chèn nội dung của một file vào mã nguồn chương trình.

Chỉ thị #include hay còn gọi là chỉ thị bao hàm tệp được phân chia thành 2 loại
```c
- <> : khi nhấn run thì compiler sẽ tìm file này trong thư mục cài đặt gốc
- "" : khi nhấn run thì compiler thì sẽ tìm trong project hiện tại.
```
ứng dụng: 
-	tái sử dụng mã nguồn
-	phân chia chương trình thành các phần nhỏ, giúp quản lý mã nguồn hiệu quả

#### b)	Chỉ thị tiền xử lý #define 
Chỉ thị #define là 1 macro dùng để định nghĩa các hằng số, macro, hoặc các đoạn mã thay thế trước khi chương trình biên dịch
Chỉ thị #define có 2 loại: 
-	Loại 1: khai báo 1 dòng
-	Loại 2: khai báo nhiều dòng

**Cú pháp của khai báo 1 dòng:**
```c
#define name value
```
Trong đó: 
-	Name: tên đại diện cho giá trị hoặc mã thay thế
-	Value: giá trị hoặc đoạn mã thay thế cho name
Ví dụ: 
```c 
#define SIZE 20 
```

**Cú pháp của khai báo nhiều dòng:**
```c
#define CREATE_FUNC (name, cmd)     \
Void name()                         \
{                                   \
   printf(cmd);                     \
}
CREATE_FUNC(test1, “This is function 1\n”);
```
#### c)	Chỉ thị tiền xử lý #undef
Chỉ thị #undef dùng để hủy định nghĩa của 1 macro đã được định nghĩa trước đó bằng #define 

khi đã define 1 biến bằng 1 giá trị thì sẽ không thay đổi được, cần phải undef sau đo define lại 

#### d)	Chỉ thị biên dịch có điều kiện
**Chỉ thị tiền xử lý #if, #elif, #else**
- #if sử dụng để bắt đầu một điều kiện tiền xử lý.
     + Nếu điều kiện trong #if là đúng, các dòng mã nguồn sau #if sẽ được biên dịch
     + Nếu sai, các dòng mã nguồn sẽ bị bỏ qua đến khi gặp #endif
- #elif dùng để thêm một điều kiện mới khi điều kiện trước đó trong #if hoặc #elif là sai
- #else dùng khi không có điều kiện nào ở trên đúng.
Ví dụ: 
```c
#define A 0 
#define B 1
#define C 2

#define SU A
#if SU == A
     Void inNhomA() {printf(“Nhom A\n”);}
#elif SU == B
     Void inNhomB() {printf(“NhomB\n”);}
#endif
```

## Bước 2: compiler 
Sau khi chương trình đi qua quá trình tiền xử lý dữ liệu thì sẽ thực hiện quá trình compiler. Chuyển các file .i thành các file.s (file hợp ngữ assembly) 
Sử dụng câu lệnh sau để chuyển đổi
```c
gcc -S main.c -o main.s
```
## Bước 3: Assembler
- Từ file assembly (file.s) sẽ chuyển thành file .o (obj) chứa những mã nhị phân mà máy tính có thể hiểu được
- Sử dụng câu lệnh để chuyển đổi
```c
gcc –c main.c –o main.c
```

## Bước 4: linker
- Linker là quá trình liên kết tất cả file .o lại để thành file .exe để máy có thể run được 
- Thực hiện cú pháp sau trên terminal 
```c
gcc main.o -o name
```
- sau đó chạy chương trình bằng câu lệnh sau
```
./name
```
***
# Tổng kết
***
![Image](https://github.com/user-attachments/assets/768b599e-ef43-43c0-8d0e-a728950ae0a2)
Khi run file chương trình file.c hoặc file.h thì compiler nó sẽ tạo ra file .exe. file.exe này tượng trưng cho việc chương trình sẽ chạy qua 4 quá trình: Tiền xử lý preprocessor -> Compiler ->  Assembler  -> Linker 


