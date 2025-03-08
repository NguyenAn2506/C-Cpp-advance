# struct - union
***
## 7.1. struct
***
- struct là một cấu trúc dữ liệu cho phép người dùng tự định nghĩa một kiểu dữ liệu mới bằng cách nhóm các biến có các kiểu dữ liệu khác nhau lại với nhau. 
- struct cho phép tạo ra một thực thể dữ liệu lớn hơn và có tổ chức hơn từ các thành viên (members) của nó.
- Có 2 dạng khai báo:

**cách 1**
```c
struct name_struct 
{
    <data type 1> <member 1>;
    <data type 2> <member 2>;
    // ...
};
```
**cách 2**
```c
typedef struct name_struct
{
    <data type 1> <member 1>;
    <data type 2> <member 2>;
    // ...
} name_struct;
```
**ví dụ**
```c
#include <stdio.h>

typedef struct 
{
    // char name;
    char* name;
    int age;
    double gpa;
}SinhVien;

int main(int argc, char const *argv[])
{
    // sinh viên 1
    SinhVien sv1; 
    sv1.name = "Hoàng";
    sv1.age = 8;
    sv1.gpa = 4.0;

    // sinh viên 2
    SinhVien *sv2;
    sv2 -> name = "An";
    sv2 -> age = 22;
    sv2 -> gpa = 8.0;

    return 0;
}
```
- Khi sử dụng struct thì khi mà sử dụng với biến bình thường thì sử dụng **.**
- Còn khi sử dụng con trỏ thì sử dụng **->**

### 7.1.1. kích thước của struct
#### a) data alignment
Data alignment (căn chỉnh dữ lệu): sắp xếp các biến thành viên của 1 struct sao cho mỗi biến thành viên sẽ nằm ở địa chỉ phù hợp với căn chỉnh của CPU
Đối với các kiểu dữ lệu như sau thì trong struct sẽ có được chia vào các ô nhớ tương ứng 

```c
// data alignment (căn chỉnh dữ liệu)
/*
    - double (8 bytes): 0xa0, 0xa8, 0xa16 v.v  : các địa chỉ chia hết cho 8
    - int, int32_t, uint32_t (4 bytes): 0xb0, 0xb4, 0xb8, v.v   : các địa chỉ chia hết cho 4 
    - float, int16_t, uint16_t, short (2 bytes): 0xc0, 0xc2, 0xc4 : các địa chỉ chia hết cho 2
    - char, int8_t, uint8_t (1 byte): bất kì ô địa chỉ nào
*/
```
#### b) data padding
Data padding (căn chỉnh dữ lệu):những địa chỉ được cấp phát ra mà tại đó nó không có dữ liệu
Đối với data alignment thì sau khi mà được phân chia các ô nhớ phù hợp thì sẽ có những ô nhớ bị thừa ra sẽ gọi là padding

```c
// data padding
/*
    0xa0 0xa1 0xa2 0xa3 0xa4
    int name;    => 4 bytes và lưu vào 0xa0 
    => vậy thì biến name sẽ lưu vào 4 byte là 0xa0 đến 0xa3 và 0xa4 sẽ bị dư ra: padding
*/
```
#### c) Cách tính kích thước 
●	Dựa vào kiểu dữ liệu có kích thước lớn nhất
●	Bắt đầu cấp phát từ trên xuống dưới
●	Địa chỉ của từng biến thành viên phải liền kề với nhau

##### Đối với các kiểu dữ liệu thông thường
**ví dụ:**
```c
typedef struct 
{                          // ban đầu cấp phát 0xa0 0xa1 0xa2 0xa3
    short a; // 2bytes     // 0xa0 0xa1  : sử dụng 2 bytes trong 4 bytes, padding 2 bytes
    short b; // 2 bytes    // 0xa2 0xa3  : sd 2 bytes, padding = 0

                           // cấp phát tiếp 4 bytes 
                           // 0xa0 0xa1 0xa2 0xa3 0xa4 0xa5 0xa6 0xa7
    int c;   // 4 bytes    // 0xa4 0xa5 0xa6 0xa7 : sử dụng 4 bytes => padding = 0

                           // cấp phát tiếp  
                           // 0xa0 0xa1 0xa2 0xa3 0xa4 0xa5 0xa6 0xa7 0xa8 0xa9 0xaa 0xab
    int d;   // 4 bytes    // 0xa8 0xa9 0xaa 0xab : sd 4 bytes => padding = 0
                           // cấp phát tiếp  
                           // 0xa0 0xa1 0xa2 0xa3 0xa4 0xa5 0xa6 0xa7 0xa8 0xa9 0xaa 0xab 0xac 0xad 0xae 0xaf
    char m;           // 0xac => padding 3

                           
}SinhVien;

```

**lưu ý**
Đối với data alignment thì khi mà đi qua biến nào rồi thì nó sẽ không lấy lại nữa và tiếp tục đi tiếp 

##### Đối với mảng
Mỗi phần tử trong mảng sẽ chiếm 1 bytes. Những phần tử cũng sẽ liền kề với nhau, nên địa chỉ cũng sẽ liền kề với nhau

**ví dụ**
```c
struct Example1 
{
    uint8_t  arr1[5];    
    uint16_t arr2[4];    
    uint32_t arr3[2];  
};
```
tương đương với
```c
struct Example1 
{
    uint8_t  arr1[0];
uint8_t  arr1[1];
uint8_t  arr1[2];
uint8_t  arr1[3];
uint8_t  arr1[4];
uint16_t arr2[0];  
uint16_t arr2[1]; 
uint16_t arr2[2]; 
uint16_t arr2[3];   
uint32_t arr3[2];
uint32_t arr3[0];
uint32_t arr3[1];
};
```

### 7.1.2. bit field
“bit field” (trường bit) là một thành phần đặc biệt của cấu trúc (struct) cho phép bạn chỉ định số lượng bit cụ thể dùng để lưu trữ một biến số nguyên. Thay vì sử dụng toàn bộ kích thước của một kiểu dữ liệu, bạn có thể “cắt nhỏ” bộ nhớ theo số bit cần thiết, giúp tiết kiệm không gian bộ nhớ và mô tả chính xác hơn ý nghĩa của dữ liệu (ví dụ: lưu trạng thái bật/tắt chỉ với 1 bit)

**Cú pháp**
```c
struct name_struct 
{
    <data type 1> <member 1> : <number of bits>;
    <data type 2> <member 2> : <number of bits>;
    // ...
};
```

**ví dụ**
```c
struct Example 
{
    int32_t flag  : 1;	// chỉ sử dụng 1 trong 32 bit
    int64_t count : 4;	// chỉ sử dụng 4 trong 64 bit
};
```

-	Số bit chỉ định trực tiếp giới hạn phạm vi giá trị có thể lưu. Ví dụ: một bit field khai báo với : 3 có thể lưu các giá trị từ 0 đến 7 (2 ^3 -1) (đối với unsigned). 
-	Không thể sử dụng toán tử lấy địa chỉ (&) trên  các thành viên bit field, khác với biến struct (biến, mảng) thông thường. (không thể in ra địa chỉ của bit field)
***
## 7.2. Union
union là một cấu trúc dữ liệu giúp lập trình viên kết hợp nhiều kiểu dữ liệu khác nhau vào cùng một vùng nhớ. Mục đích chính của union là tiết kiệm bộ nhớ bằng cách chia sẻ cùng một vùng nhớ cho các thành viên của nó. Điều này có nghĩa là, trong một thời điểm, chỉ một thành viên của union có thể được sử dụng. Điều này được ứng dụng nhằm tiết kiệm bộ nhớ
**Cú pháp**
```c
union name_union 
{
    kieuDuLieu1 thanhVien1;
    kieuDuLieu2 thanhVien2;
    // ...
};
```
**Đặc điểm:**
-	chia sẻ cùng 1 bộ nhớ
-	ảnh hưởng giá trị của các thành phần khác: vì chia sẻ cùng bộ nhớ nên giá trị của thành viên phía sau khi được gán lên thì sẽ ghi đề lên giá trị của thành viên trươc đó
-	giá trị của các thành phần: mỗi thành viên sẽ có các kiểu dữ liệu khác nhau và giới hạn của mỗi kiểu dữ liệu cũng vậy nên khi giá trị vượt quá giới hạn thì sẽ là giá trị rác

**ví dụ: ứng dụng lồng struct vào union**
**Đặc điểm:** dùng chung 1 bộ nhớ

```c
typedef union
{
    struct                 // dùng struct để gộp 3 thông tin bên trong lại 
    {
        uint8_t id[2];
        uint8_t data[4];
        uint8_t check_sum[2];
    } data;
   
    uint8_t frame[8];       // khi 1 trong 3 tt trong stuct thay đổi thì dữ liệu trong frame cx thay đổi 
} Data_Frame; 
```
Ngoài ra có thể làm ngược lại 
Lồng struct - union - struct ,....