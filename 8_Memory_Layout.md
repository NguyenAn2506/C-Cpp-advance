# Memory Layout
***
## 8.1. Khái niệm
- Khi khai báo địa chỉ hay hàm thì nó sẽ cấp phát 1 địa chỉ cụ thể, nằm ở các vùng nhớ khác nhau tùy từng loại.
- Có tổng cộng 5 vùng nhớ trên RAM
![Image](https://github.com/user-attachments/assets/56f7ca59-27d2-42e8-96b5-7351ddff6313)
***
## 8.2. phân vùng Text segment (Code segment)
-	Phân vùng này chứa những mã máy (những mã lệnh thực thi), nghĩa là khi viết các câu lệnh trong chương trình thì nó sẽ thực hiện các câu lẹnh trong hàm main và các câu lệnh sẽ có những địa chỉ và sẽ được thanh ghi Program Counter trỏ tới từng địa chỉ, từng câu lệnh để thực thi. Thực thi qua từng câu lệnh
-	**Quyền truy cập**: Text Segment thường có quyền đọc và thực thi, nhưng không có quyền ghi. (thanh ghi Program Counter đã làm luôn rồi) (như là const, choỗi,…)
-	Lưu hằng số toàn cục (const), chuỗi hằng - string literal (Clang – macOS, windows - minGW)
***
## 8.3. Data segment
Trong phân vừng data sẽ được chia nhỏ ra thành 2 phân vùng nữa, là Initialized Data (Data) và Uninitialized Data (BSS)
Nếu gán là NULL thì sẽ nằm ở trong phân vùng static

### 8.3.1. Data segment (Initialized Data)
-	Initialized Data Segment (Dữ liệu Đã Khởi Tạo):
    ●	Chứa các biến toàn cục (với con trỏ cũng vậy) được khởi tạo với giá trị khác 0.
    ●	Chứa các biến static (global + local) được khởi tạo với giá trị khác 0.
    ●	Quyền truy cập là đọc và ghi, tức là có thể đọc và thay đổi giá trị của biến .
    ●	Tất cả các biến sẽ được thu hồi sau khi chương trình kết thúc.
### 8.3.2. BSS segment
-	Uninitialized Data Segment (Dữ liệu Chưa Khởi Tạo):
    ●	Chứa các biến toàn cục khởi tạo với giá trị bằng 0 hoặc không gán giá trị. (giá trị bất định) hoặc gán bằng giá trị NULL
    ●	Chứa các biến static với giá trị khởi tạo bằng 0 hoặc không gán giá trị.
    ●	Quyền truy cập là đọc và ghi, tức là có thể đọc và thay đổi giá trị của biến .
    ●	Tất cả các biến sẽ được thu hồi sau khi chương trình kết thúc.
## 8.4. các trường hợp đạc biệt
Các trường hợp này đều là dành cho khai báo biến toàn cục
### 8.4.1. struct
●	Đối với struct thì khi khai báo struct thì các biên thành viên sẽ chưa được cấp phát địa chỉ 
○	Đến khi mà khai báo những biến p1, p2, p3 thuộc kiểu của phân vùng nào thì các biến thành viên sẽ nằm trong phân vùng đó 
Phụ thuộc cách khởi tạo của những biến kiểu struct

```c
typedef struct 
{
    int x;
    int y;
}Point_Data;   

Point_Data p1 = {5,0};      // p1,x,y : data 
Point_Data p2;              // p2,x,y : bss 
Point_Data p3 = {0,0};      // p3,x,y : bss
```
### 8.4.2. const
●	Đối với các biến kiểu const thì nó sẽ được phân vùng dựa theo trình biên dịch hiện tại
●	Ví dụ: nếu là trên gcc (window) thí sẽ được phân vào phân vùng data, còn nếu là Clang (Mac ÓS) thì sẽ được phân vào phân vùng text
```c
const int b2 = 0;   // gcc (Window) : data - read only (rdata)
                    // Clang (MacOS) : text
```
### 8.4.3. string
●	Đối với chuỗi cũng vậy, nhưng có 1 điều đặc biệt
●	Như đã nói thì str và “Hello world” sẽ phụ thuộc vào trình biên dịch của hệ điều hành
●	chuỗi “Hello World” là phân vùng data (data có thể có đọc và ghi) thì khi mà thay đổi giá trị của choỗi thì nó sẽ gây ra việc kết thúc luôn chương trình (là lỗi đó)
●	Nên sử dụng const char khi dùng con trỏ thao tác với chuỗi
```c
char *str = "Hello World";      // chuỗi hằng (string literal)
// str : data
// "Hello World" : gcc (Window) : data - read only (rdata)
                // Clang (MacOS) : text 
```
## 8.5. Stack
-	Chứa các biến cục bộ (trừ static cục bộ), tham số truyền vào của các hàm.
-	Hằng số cục bộ, có thể thay đổi thông qua con trỏ.
-	Quyền truy cập: đọc và ghi, nghĩa là có thể đọc và thay đổi giá trị của biến trong suốt thời gian chương trình chạy, đối vời các hàm thì chỉ thay đổi dược trong nội bộ hàm đó thôi.
-	Sau khi ra khỏi hàm, tự động thu hồi vùng nhớ.

**Lưu ý:**
●	Thì đối với 1 biến được khai báo bằng const
●	Nếu nó là biến toàn cục thì nó nằm trong phân vùng data (đã nói ở TH đặc biệt)
●	Còn là biến cục bộ thì nằm trong stack

## 8.6. Heap segment
●	Heap được sử dụng để cấp phát bộ nhớ động trong quá trình thực thi của chương trình.
●	Điều này cho phép chương trình tạo ra và giải phóng bộ nhớ theo nhu cầu, thích ứng với sự biến đổi của dữ liệu trong quá trình chạy.
●	Các hàm như malloc(), calloc(), realloc(), và free() được sử dụng để cấp phát và giải phóng bộ nhớ trên heap.
### 8.6.1. hàm malloc()
Hàm malloc() viết tắt của từ memory allocation tức là cấp phát động vùng nhớ, hàm này được sử dụng để xin cấp phát khối bộ nhớ theo kích thước byte mong muốn. 
Giá trị trả về của hàm là một con trỏ kiểu void, bạn nên ép kiểu sang kiểu dữ liệu mà bạn cần dùng. 
Các giá trị trong các ô nhớ được cấp phát là giá trị rác
**Cú pháp :**
```c
ptr = (cast_type*)malloc(byte_size)
```
**Trong đó :** 
•	ptr là con trỏ lưu trữ ô nhớ đầu tiên của vùng nhớ được cấp phát
•	cast_type* là kiểu con trỏ mà bạn muốn ép kiểu sang
•	byte_size là kích thước theo byte bạn muốn cấp phát

### 8.6.2. hàm calloc()
Hàm calloc() viết tắt của contiguous allocation tương tự như malloc() sử dụng để cấp phát vùng nhớ động nhưng các giá trị của các vùng nhớ được cấp phát sẽ có giá trị mặc định là 0 thay vì giá trị rác như hàm malloc()
**Cú pháp:** 
```c
ptr = (cast_type*) calloc(n, element_size)
```
**Trong đó:**
•	ptr là con trỏ lưu trữ ô nhớ đầu tiên của vùng nhớ được cấp phát
•	cast_type* là kiểu con trỏ mà bạn muốn ép kiểu sang
•	n là số lượng phần tử bạn muốn cấp phát
•	element_size là kích thước theo byte của 1 phần tử

### 8.6.3. hàm free()
Hàm malloc() và calloc() xin cấp phát vùng nhớ nhưng lại không tự giải phóng vùng nhớ mà nó xin cấp phát, hàm free() có chắc năng giải phóng vùng nhớ mà malloc() hoặc calloc() đã xin cấp phát.
Việc sử dụng free() sau khi sử dụng malloc() và calloc() là cần thiết để tránh lãng phí bộ nhớ
**Cú pháp :**
```c
free(ptr)
```
### 8.6.4. hàm realloc()
Hàm realloc() viết tắt của re-allocation tức là cấp phát lại, trong trường hợp sử dụng malloc() và calloc() nhưng cần bổ sung thêm bạn sử dụng realloc(). 
realloc() giúp bạn giữ lại các giá trị trên vùng nhớ cũ và bổ sung thêm vùng nhớ mới với các giá trị rác.
Ví dụ khi bạn đang xin cấp phát 5 phần tử nhưng lại muốn cấp phát lại thành 10 phần tử và giữ nguyên giá trị của 5 phần tử trước đó. Nếu bạn sử dụng malloc() hay calloc() thì 5 phần tử cũ sẽ không còn vì bạn được cấp phát 1 vùng nhớ mới, calloc() thì chỉ bổ sung thêm vùng nhớ cho 5 phần tử mới còn 5 phần tử cũ thì vấn giữ nguyên.
**Cú pháp:** 
```c
ptr = (cast_type*)realloc(ptr, new_size)
```
