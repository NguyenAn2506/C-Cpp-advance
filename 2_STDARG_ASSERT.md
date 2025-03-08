# Bài 2: STDARG - ASSERT LIBRARY
***
## 1. STDARG Library
- Cung cấp các phương thức để làm việc với các hàm có số lượng input parameter không cố định.

Các câu lệnh trong thư viện:

**1. va_list:** 
- là một kiểu dữ liệu để đại diện cho danh sách các đối số biến đổi.
- Cú pháp
```c
typedef char* va_list
```
**2. va_start:** 
- Bắt đầu một danh sách đối số biến đổi. Nó cần được gọi trước khi truy cập các đối số biến đổi đầu tiên.
- Cú pháp:
```c
va_start(va_list args, label)
```
**3.va_arg:**
- Truy cập một đối số trong danh sách. Hàm này nhận một đối số của kiểu được xác định bởi tham số thứ hai
- Cú pháp
```c
va_arg(va_list args, <data_type>)
```
**4.va_end:** 
- Kết thúc việc sử dụng danh sách đối số biến đổi. Nó cần được gọi trước khi kết thúc hàm.
- Cú pháp
```c
va_end(va_list args)
```
**5. va_copy: (C99 trở lên mới có):** 
- sao chép nội dung từ 1 biến va_list sang 1 biến khác
- Cú pháp
```c
va_copy(va_list args1, va_list args2)
```

__VA_ARGS__ : là một phần trong cú pháp của variadic macros, cho phép truyền một số lượng tham số không cố định vào trong một macro.

ví dụ:
- **a) có quy định số lượng tham số**
```c
void test (int count,…)
{
   va_list args; 
   va_start(args, count);
   printf(“value1: %d\n”, va_arg(args, int));
   va_end(args);
}
int main(void)
{
    test(1,2);
}
```
- tham số là tên count (số lượng phần tử)
- “…” tượng trưng cho các tham số không xác định
kết quả :
```c
value1: 2
```

- **b) không cần quy định số lượng tham số**
```c

#define tong(…)          sum(__VA_ARGS__, 0)
int sum(int count,…)
{
   va_list args; 
   va_start(args, count);
   int result = count;
   int value;
   while((value = va_arg(args, int)) != 0)
   { result += value;}
   va_end(args);
}
int main(void)
{
    printf(“value1: %d\n”, tong(4,1,2,3,0,1);
}
```
kết quả :

- Kết quả sẽ là 4+1+2+3, vì có số 0 chặn nên sẽ không tính các số ở sau số 0
```c
value1: 10 
```
## 2. Assert Library
- Cung cấp macro assert. 
- Macro này được sử dụng để kiểm tra một điều kiện. 
- Nếu điều kiện đúng (true), không có gì xảy ra và chương trình tiếp tục thực thi.
- Nếu điều kiện sai (false), chương trình dừng lại và thông báo một thông điệp lỗi.
- Dùng trong debug, dùng #define NDEBUG để tắt debug
Cú pháp: 
```c
assert(condition && condition2)
```
Ứng dụng:
- **Dùng assert để thay thế cho if-else**
ví dụ:
```c
#include <stdio.h>
#include <assert.h>

int main() {
    int x = 5;
    assert(x == 5);
    // Chương trình sẽ tiếp tục thực thi nếu điều kiện là đúng.
    printf("X is: %d", x);
    return 0;
}

```

- **dùng macro trong assert thay thế cho assert**
```c
// Macro dùng để debug
#define LOG(condition, cmd) assert(condition && #cmd)
```

ví dụ:
```c
#include<assert.h>
#include<stdio.h>

#define LOG(condition,cmd) assert(condition && #cmd) // ký tự # cho phép chuẩn hóa lên chuỗi

double divide(int mau,int tu){
    LOG(mau=0,mau phai khac 0);
    return (double)mau/tu;
}
int main(){
    double result = divide(0,21); 
    printf("%.2f",result);
}
```

