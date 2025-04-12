# Namespace
***
Tình huống thường xảy ra trong lập trình C/C++. Ví dụ: Code bạn đang viết có hàm tên là test() và có thư viện khác có sẵn mà cũng có hàm test(). Bây giờ, trình biên dịch không biết phiên bản nào của hàm xyz() mà bạn muốn sử dụng trong code của mình.

Làm sao để giải quyết vấn đề trên?

=> Mục đích là rút ngắn câu lệnh sử dụng
=> Trong C không được phép khai báo biến hoặc hàm trùng tên vs nhau. C++ thì được. Tuy nhiên không phải lúc nào cx sử dụng tới template, class mà chỉ cần sử dụng struct,…

***
## 1. Khái niệm
***
- Namespace là cách nhóm các đối tượng như biến, hàm, class, struct,... vào một không gian tách biệt.
- Namespace được sử dụng với mục đích là để tránh xung đột tên khi có các định danh giống nhau được khai báo trong các phần của chương trình hoặc các thư viện khác nhau.
***
## 2. Ví dụ:
***
```cpp
#include <iostream>
using namespace std;
namespace A{
    char *name = (char*)"Anh 20";

    void display(){
        cout << "Name: " << name << endl;
    }
}
namespace B{
    char *name = (char*)"Anh 21";

    void display(){
        cout << "Name: " << name << endl;
    }
}

int main(int argc, char const *argv[]){
    cout << "Name: " << A::name << endl;
    cout << "Name: " << B::name << endl;
    A::display();
    B::display();
    return 0;
}
```
Kết quả
```cpp
Name: Anh 20
Name: Anh 21
Name: Anh 20
Name: Anh 21
```
***
## 3. Name Mangling
***
Biến đổi tên (Name Mangling) là một cơ chế của trình biên dịch g++ nhằm mã hóa tên hàm, biến, class, namespace,... thành tên duy nhất, để tránh xung đột trong quá trình biên dịch (các file mã hóa sẽ được viết trong file object (.o)). Việc mã hóa này xảy ra trong quá trình tiền xử lý của compiler

Ví dụ:
```cpp
Vf(i) => 100
Vf(a) => 101
```
### 3.1. Ví dụ
***
#### Ví dụ 1
```cpp
namespace A {
    void foo() {
        cout << "A::foo()" << endl;
    }
}

namespace B {
    void foo() {
        cout << "B::foo()" << endl;
    }
}
```
Các dữ liệu khi được mã hóa
```cpp
A::foo() -> _ZN1A3fooEv
B::foo() -> _ZN1B3fooEv
```
### 3.2. Cách mã hóa và giải mã
***
#### Cách mã hóa
||Ý nghĩa|
|----|-----|
|_z	| Bắt đầu name mangling |
| N…E | Tên nằm trong namespace hoặc class |
| 1A | Namespace "A" (1 ký tự) |
| 3foo | Tên hàm "foo" (3 ký tự) |
| v | Không có tham số |

Cú pháp:
```cpp
nm <name_file>.o | grep <function>
```
#### Giải mã: 
Cú pháp
```cpp
c++filt _ZN1A3fooEv
```
Để có thể mã hóa thì phải đưa về dạng của file object 

Sau đó mới lấy file object để giải mã

```cpp
g++ -E EX1.cpp -o EX1.i
g++ -S EX1.i -o EX1.s
g++ -c EX1.s -o EX1.o

hoặc làm trực tiếp qua
g++ -c EX1.c -o EX1.o

nm EX1.o | grep display
```
![Image](https://github.com/user-attachments/assets/f5c66422-821d-4e9c-b7d5-2409998686ae)

***
### 3.3. Từ khóa Using trong namespace
Từ khóa using cho phép bạn sử dụng các phần tử trong namespace mà không cần phải sử dụng toán tử '::' mỗi khi truy cập.

Chỉ sử dụng using namespace khi member muốn truy cập đến là duy nhất.

Ví dụ:

```cpp
namespace A{
    char *name = (char*)"Anh 20";

    void display(){
        cout << "Name: " << name << endl;
    }
}
namespace B{
    char *name = (char*)"Anh 21";

    void display(){
        cout << "Name: " << name << endl;
    }
}

using namespace A;
// using namespace B;

int main(int argc, char const *argv[]){
    cout << "Name: " << name << endl;
    cout << "Name: " << B::name << endl;
    A::display();
    B::display();
    return 0;
}
```
***
## 4. Namespace lồng nhau
***
C++ cho phép tạo các namespace lồng nhau, nghĩa là một namespace có thể chứa một namespace khác bên trong nó.

Ví dụ:
```cpp
namespace A{
    char *name = (char*)"Anh 20";

    void display(){
        cout << "Name: " << name << endl;
    }
    
    namespace C
    {
        void test()
        {
            cout << "This is test function()\n";
        }

        void display()
        {
            cout<< "this is display function()\n"<< endl;
        }
    }
}
namespace B{
    char *name = (char*)"Anh 21";

    void display(){
        cout << "Name: " << name << endl;
    }
}

using namespace A;
// using namespace B;

int main(int argc, char const *argv[]){
    cout << "Name: " << A::name << endl;
    cout << "Name: " << B::name << endl;
    display();
    B::display();

    C::test();
    C::display();
    return 0; 
}
```
***
## 5. Namespace mở rộng
***
Namespace có thể được mở rộng bằng cách khai báo nhiều lần cùng một tên namespace trong các phần khác nhau của chương trình. Các khai báo này sẽ được trình biên dịch ghép lại thành một namespace duy nhất.

=> Khai báo namespace trùng tên với nhau, thì trình biên dịch sẽ tự động gộp 2 cái lại chung vs nhau để mở rộng thêm ra

### 5.1. Ví dụ 
```cpp
// namespace mở rộng

#include <iostream>
using namespace std;
namespace A{
    char *name = (char*)"Anh 20";

    void display(){
        cout << "Name: " << name << endl;
    }
    
    namespace C
    {
        void test()
        {
            cout << "This is test function()\n";
        }

        void display()
        {
            cout<< "this is display function()\n"<< endl;
        }
    }
}

namespace A
{
    int x;
    int y;
    int z;
}

using namespace A::C;
// using namespace B;

int main(int argc, char const *argv[]){
    cout << "Name: " << A::name << endl;
    display();

    test();
    display();
    return 0;
}
```
***
## 6. Namespace tiêu chuẩn (std)
***
Một trong những namespace quan trọng và phổ biến nhất trong C++ là std. Tất cả các thành phần của thư viện chuẩn C++ (như cout, cin, vector, string) đều được định nghĩa bên trong namespace std.

Std thông thường sẽ chưa nhũng câu lệnh để tương tác vs màn hình terminal như cout cin,…

Nó có thể có tất cả những đặc điêm ở trên 

Ví dụ
```cpp
// namespace std

#include <iostream>

using namespace std;

namespace std{
    struct{
        int x;
        int y;
    } point;

    void display(){
        cout << "x = " << point.x << endl;
        cout << "y = " << point.y << endl;
    }
}

int main(int argc, char const *argv[])
{
    std::cout << "Hello world!" << std::endl;

    cout << "Hello world!" << endl;
   
    std::point.x = 10;
    std::point.y = 20;
    std::display();

    return 0;
}
```
