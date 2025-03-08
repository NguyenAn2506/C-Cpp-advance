# I. POINTER 
***
## 1. khái niệm:
con trỏ (pointer) là một biến chứa địa chỉ bộ nhớ của một đối tượng khác (biến, mảng, hàm). Việc sử dụng con trỏ giúp chúng ta thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.

## 2. khai báo con trỏ, giá trị và địa chỉ của con trỏ:

- Khai báo con trỏ ptr_x chứa địa chỉ của test:
```c
int test = 8;		Address: 0x01
			Value:	0	
int *ptr_x = &test;	Address: 0xf1
			Value:	0x01
```
- Lấy giá trị của địa chỉ ptr_x gán cho y => dùng dải tham chiếu
```c
int y = *ptr_x;   // y sẽ bằng giá trị của x (dereference)	
			Address: 0xa1
			Value: 8
```
=> ptr_x là biến con trỏ
=> *ptr_x là giá trị mà con trỏ ptr_x đang trỏ đến
=> &ptr_x là địa chỉ con trỏ ptr_x

ví dụ:
```c
#include <stdio.h>

int test = 0;
int *ptr = &test;

int main(int argc, char const *argv[]) {
    printf("Gia tri cua con tro: %d\n", *ptr); // Giá trị của test
    printf("Dia chi ma con tro tro toi: %p\n", ptr); // Địa chỉ của test
    printf("Dia chi cua chinh con tro: %p\n", &ptr); // Địa chỉ của ptr
    return 0;
}

```

## 3. kích thước con trỏ

- kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch hoặc kiến trúc vi xử lý. 
- Kiến trúc máy tính là hệ điều hành 64 bit => 8 bytes, 32 bit => 4 bytes 
- Kích thước con trỏ mặc định là số bytes mà hệ điều hành có
- Nếu làm trên vxl: 
Arduino 8 bit => 1 bytes
STM32 32 bit => 4 bytes 
ESP32 32 bit  => 4 bytes

=> lưu ý: khi gán địa chỉ cho con trỏ phải chú ý đến kiểu dữ liệu, phải đồng bộ kiểu dữ liệu của con trỏ và biến con trỏ

```c
double a = 3.14;
double *ptr = &a;
```
- khi con trỏ là 1 mảng
Bản chất của mảng là các ô địa chỉ liền kề nhau
Thì con trỏ chỉ lấy địa chỉ đầu tiên trong mảng, để tăng địa chỉ tiếp theo thì +1 => Bản chất của của số 1 là 1* sizeof(<data type>)

```c
#include <stdio.h>

int main(int argc, char const *argv[])
{
 
    double arr[] = {1,2,3};         
    double *ptr2 = arr;

    printf("gia tri cua ptr2 [0] = %f \n", *(ptr2));
    printf("gia tri cua ptr2 [1] = %f \n", *(ptr2 + 1));
    printf("gia tri cua ptr2 [2] = %f \n", *(ptr2 + 2));
    printf("gia tri cua ptr2 [3] = %f \n", *(ptr2 + 3));

    return 0;
}
```

# II. Void pointer
***
- Void pointer thường dùng để trỏ đến tới bất kỳ địa chỉ nào mà không cần biết tới kiểu dữ liệu của giá trị tại địa chỉ đó.
Cú pháp:
```c
void *ptr_void;
```

**ví dụ 1:**
```c
int a = 43;
void* p = &a;
printf("%d",*((int*)p));
```
**ví dụ 2: khai báo con trỏ void là 1 mảng**
```c
#include <stdio.h>

int main(int argc, char const *argv[])
{
    void *ptr;
    char arr[] = “hello”;
    Ptr = arr;

    for( size_t i = 0; i < (sizeof(arr)/sizeof(arr[0]); i++)
    {
        Printf(“addr: %p – value: %c\n”, ptr, *(char *) (ptr+i));
    }
}

```
**ví dụ 3: con trỏ void trỏ đến mảng lưu trữ đa dữ liệu**
```c
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a = 10;
    double b = 5.6;
    char c = 'A';
    char arr[] = "hello";

    // khai bao con tro void như mang
    void *ptr1[] = {&a, &b, &c, arr};      

    printf("addr: %p - value: %d\n", ptr1, *(int *) ptr1[0]);
    printf("addr: %p - value: %f\n", ptr1, *(double *) ptr1[1]);
    printf("addr: %p - value: %c\n", ptr1, *(char *) ptr1[2]);

    for(size_t i = 0; i < 6; i++)
    {
        printf("addr: %p - value: %c\n", ptr1, *(char *) (ptr1[3]+i));
    }
    
    return 0;
}

```

### ưu nhược điểm của con trỏ void

**Ưu điểm:**
● Không cần phải khai báo biến con trỏ cho từng biến => làm tốn bộ nhớ RAM
● Chỉ cần khai báo 1 con trỏ void, nó có trỏ đến bất kì biến nào cx được, chỉ tốn 1 lần cấp phát cho con trỏ void thôi (1 vùng nhớ)

**Nhược điểm:**
● Muốn đọc được dữ liệu phải ép kiểu về để đồng bộ dữ liệu


# III. Pointer to function
***
- Pointer to function (con trỏ hàm) là một biến mà giữ địa chỉ của một hàm. Nó trỏ đến vùng nhớ trong bộ nhớ chứa mã máy của hàm được định nghĩa trong chương trình
- Con trỏ hàm cho phép bạn truyền một hàm như là một đối số cho một hàm khác, lưu trữ địa chỉ của hàm trong một cấu trúc dữ liệu, hoặc thậm chí truyền hàm như một giá trị trả về từ một hàm khác.
Cú pháp:
```c
<return_type> (* func_pointer)(<data_type_1>, <data_type_2>);
```
## các loại con trỏ hàm
### a) Biến con trỏ hàm
ví dụ:
```c
Void func1()
{printf(“This is function 1”);}
Void func2(int a, double b, char c)
{printf(“This is function 2”);}
Void func(int a, int b)
{printf(“This is function 3”);}

Main()
{
    void(*ptr)();                       => con trỏ này chỉ lưu trữ địa chỉ của hàm func1
    ptr = func1;                        => gán địa chi của hàm
    ptr();                                   => thực thi con trỏ hàm
    int (*ptr1)(int, double, char);    => con trỏ này chỉ lưu trũ địa chỉ hàm func2
    ptr1 = func2;                        => gán địa chi của hàm
    ptr1(4, 4.8, ‘a’);                   => thực thi con trỏ hàm
    void (*ptr2)(int, int);             => còn con trỏ này thì lưu trữ địa chỉ hàm func3
    ptr2 = func3;                        => gán địa chi của hàm
    ptr2(3,4);                              => thực thi con trỏ hàm
    
    return 0;
}

```
### b) Con trỏ hàm hoạt động như 1 tham số truyền vào của hàm
ví dụ:
```c
void tong(int a, int b)
{printf(“%d + %d = \n”, a,b, a+b);}

Void compute(void (*ptr)(int, int), int a, int b)
{
    Ptr(a,b);
}

main()
{
    Int a= 20, b= 30;
    Compute(tong, a,b);
}

```
### c) Mảng con trỏ hàm
ví dụ:
```c
void tong(int a, int b)
{printf(“%d + %d = \n”, a,b, a+b);}

main()
{
    Int a= 20, b= 30;
    void((*tinhtoan[])(int, int) = {&tong});
    tinhtoan[0](a,b);
    return 0;
}

```
## Ưu nhược điểm của con trỏ hàm
**Ưu điểm:** Linh hoạt hơn các hàm thông thường do là con trỏ hàm xảy ra ở quá trình runtime, còn các hàm thông thường thì xảy ở qua trình biên dịch

# IV. pointer to const
***
Là cách định nghĩa một con trỏ không thể thay đổi giá trị tại địa chỉ mà nó trỏ đến thông qua dereference nhưng giá trị tại địa chỉ đó có thể thay đổi.
**READ ONLY**
Cú pháp: 
```c
int const *ptr_const; 
const int *ptr_const;
```

# V. const to pointer
***
- Định nghĩa một con trỏ mà giá trị nó trỏ đến (địa chỉ ) không thể thay đổi. Tức là khi con trỏ này được khởi tạo thì nó sẽ không thể trỏ tới địa chỉ khác.
- Chỉ trỏ đến 1 địa chỉ duy nhất xuyên suốt chương trình. 

Cú pháp
```c
int *const const_ptr = &value;
```

# VI. con trỏ NULL
***
Null Pointer là một con trỏ không trỏ đến bất kỳ đối tượng hoặc vùng nhớ cụ thể nào. một con trỏ có thể được gán giá trị NULL để biểu diễn trạng thái null, C++ (NULL, nullptr).

Được sử dụng để kiểm tra xem một con trỏ đã được khởi tạo và có trỏ đến một vùng nhớ hợp lệ chưa. Tránh dereferencing (sử dụng giá trị mà con trỏ trỏ đến) một null pointer là quan trọng để tránh lỗi chương trình.

# VII. pointer to pointer
***
Con trỏ đến con trỏ (Pointer to Pointer) là một kiểu dữ liệu  cho phép bạn lưu trữ địa chỉ của một con trỏ. **Con trỏ đến con trỏ** cung cấp một cấp bậc trỏ mới, cho phép thay đổi giá trị của con trỏ gốc.

- đây là con trỏ cấp 1: lưu trữ địa chỉ của 1 biến
```c
int *ptr = NULL;		
```
- con trỏ cấp 2: lưu địa chỉ của con trỏ cấp 1
```c
int **ptr2 = &ptr;		
```
-con trỏ cấp 3 lưu địa chỉ của con trỏ cấp 2
```c
int ***ptr3 = &ptr2		
```
