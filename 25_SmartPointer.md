# Smart Pointer
***
## 25.1.	Giới thiệu về RAII
***
RAII (Resource Acquisition Is Initialization) là một kỹ thuật quản lý tài nguyên trong lập trình C++, trong đó tài nguyên (bộ nhớ, file, mutex, socket,...) được cấp phát khi một đối tượng được khởi tạo và được giải phóng khi đối tượng đó bị hủy.

Điều này giúp tránh rò rỉ tài nguyên và đảm bảo việc giải phóng tài nguyên diễn ra một cách tự động, ngay cả khi có ngoại lệ xảy ra.

**Nguyên tắc hoạt động:**
- Cấp phát tài nguyên trong Constructor: Khi một đối tượng được tạo, nó sẽ lấy tài nguyên cần thiết (ví dụ: cấp phát bộ nhớ động, mở file, lock mutex,...).
- Giải phóng tài nguyên trong Destructor: Khi đối tượng đi ra khỏi phạm vi (scope), destructor của nó được gọi và tài nguyên sẽ được giải phóng một cách an toàn.

***
## 25.2.	Khái niệm Smart Pointer
***
Smart Pointers là một cơ chế quản lý bộ nhớ tự động giúp giảm thiểu rủi ro của lỗi liên quan đến quản lý bộ nhớ và giúp người lập trình tránh được việc quên giải phóng bộ nhớ đã được cấp phát.

Cụ thể hơn, Smart Pointer là một class đóng vai trò quản lý bộ nhớ động (head memory) thay cho con trỏ thô (raw pointer), giúp tự động giải phóng vùng nhớ khi không còn sử dụng, từ đó tránh được các lỗi phổ biến như:
- Rò rỉ bộ nhớ (Memory Leak).
- Truy cập vào vùng nhớ đã giải phóng (Dangling Pointer).

Smart Pointer là một class, quản lý một/nhiều con trỏ thô kèm theo các cơ chế quản lý bộ nhớ tự động (RAII) và di chuyển dữ liệu. 

**Smart Pointer được chia làm 3 loại:**
- std::unique_ptr
- std::shared_ptr
- std::weak_ptr

***
## 25.3.	Unique Pointer
***
std::unique_ptr là một loại smart pointer trong C++, giúp quản lý bộ nhớ động và tự động giải phóng bộ nhớ khi không còn cần thiết. 

Đặc điểm chính của unique_ptr là một đối tượng unique_ptr chỉ có thể sở hữu một đối tượng và khi đối tượng unique_ptr đó bị hủy, bộ nhớ của đối tượng mà nó quản lý sẽ được tự động giải phóng.

![Image](https://github.com/user-attachments/assets/0db9de58-e045-4fd7-87ac-cd31d2acde51)

Vậy thì khi nào uptr2 có thể lấy được dữ liệu của object1 
**TH1:** ta cần dùng hàm move để di chuyển đối tượng sang cho uptr2 => thì lúc này uptr2 sẽ quản lý object1
**TH2:** là object 1 sẽ chờ cho uptr1 từ bỏ quản lý object 1 thì lúc này uptr2 sẽ có thể quản lý object 1

|Method|Mô tả|
|---|---|
|operator * ()| Truy cập giá trị của đối tượng mà unique_ptr đang quản lý.|
|operator → ()|Truy cập thành viên của đối tượng mà unique_ptr trỏ tới.|
|get()|Trả về con trỏ thô (raw pointer) đến đối tượng mà unique_ptr đang quản lý. Không chuyển quyền sở hữu.|
|release() | Giải phóng quyền sở hữu đối với đối tượng mà unique_ptr đang quản lý và trả về con trỏ thô đến đối tượng đó.|
|reset() | Giải phóng đối tượng mà unique_ptr đang quản lý (nếu có) và có thể quản lý một đối tượng mới (nếu được cung cấp)
| move() | Chuyển nhượng quyền sở hữu tài nguyên (move semantics) |
***
### 25.3.1. toán tử *
***
```cpp
#include <iostream>
#include <memory>   // cần thiết để sử dụng smart pointer

using namespace std;

int main(int argc, char const *argv[])
{
    // cách 1
    // unique_ptr<int> uptr(new int (10));     // rptr -> &obj (10)

    // cách 2: 
    unique_ptr<int> uptr = make_unique<int> (10);

    cout << "Value: " << *uptr << endl;     // *rptr
    return 0;
}
```
Kết quả
```cpp
Value: 10
```
***
### 25.3.2. Toán tử ->
***
```cpp
#include <iostream>
#include <memory>   // cần thiết để sử dụng smart pointer

using namespace std;

class Sensor
{
    public:
        void display() const
        {
            cout << "data = 10\n";
        }

};

int main(int argc, char const *argv[])
{
    // cách 1
    // unique_ptr<int> uptr(new int (10));     // rptr -> &obj (10)

    // cách 2: 
    unique_ptr<Sensor> uptr = make_unique<Sensor> ();

    uptr -> display();
    (*uptr).display();

    return 0;
}
```
Kết quả
```cpp
data = 10
data = 10
```
***
### 25.3.3. Hàm get()
***
![Image](https://github.com/user-attachments/assets/c43a5793-577b-409a-9046-4bd932e2021d)

Biết rằng uptr sẽ ngăn không cho rptr truy cập tới được object 1. Tuy nhiên nếu như có những con trỏ thô khác, không bị quản lý bởi 1 đối tượng nào hoặc là biến con trỏ thì nó sẽ có thể truy cập được object1

#### Ví dụ
```cpp
#include <iostream>
#include <memory>   // cần thiết để sử dụng smart pointer

using namespace std;

int main(int argc, char const *argv[])
{
    // cách 1
    unique_ptr<int> uptr(new int (10));     // rptr -> &obj (10)
    // unique_ptr<int> uptr2 = uptr1;          // copy constructor
    // unique_ptr<int> uptr2; 
    // uptr2 = uptr ;   // copy assignment operator

    cout << "Value: " << *uptr << endl;     // *rptr

    int *rptr1 = uptr.get();
    cout <<  "This is new raw pointer " << *rptr1 << endl;

    if(uptr == NULL)
    {
        cout << "khong con so huu\n";
    }
    else
    {
        cout << "van con so huu\n";
    }
    return 0;
}
```
Kết quả
```cpp
Value: 10
This is new raw pointer 10
van con so huu
```
***
### 25.3.4. Hàm release()
***
Ví dụ 
```cpp
#include <iostream>
#include <memory>   // cần thiết để sử dụng smart pointer

using namespace std;

int main(int argc, char const *argv[])
{
    // cách 1
    unique_ptr<int> uptr(new int (10));     // rptr -> &obj (10)

    cout << "Value: " << *uptr << endl;     // *rptr

    int *rptr1 = uptr.get();
    cout <<  "1. This is new raw pointer " << *rptr1 << endl;

    if(uptr == NULL)
    {
        cout << "khong con so huu\n";
    }
    else
    {
        cout << "van con so huu\n";
    }

    rptr1 = uptr.release();
    cout <<  "2. This is new raw pointer " << *rptr1 << endl;

    if(uptr == NULL)
    {
        cout << "khong con so huu\n";
    }
    else
    {
        cout << "van con so huu\n";
    }
    return 0;
}
```
Kết quả
```cpp
Value: 10
1. This is new raw pointer 10
van con so huu
2. This is new raw pointer 10
khong con so huu
```
***
### 25.3.5. Hàm reset()
***
Ví dụ
```cpp
#include <iostream>
#include <memory>   // cần thiết để sử dụng smart pointer

using namespace std;

int main(int argc, char const *argv[])
{
    unique_ptr<int> uptr(new int (10));     // rptr -> &obj (10)
    cout << "Value: " << *uptr << endl;     // *rptr

    uptr.reset(new int (100));
    cout << "Value: " << *uptr << endl;     // *rptr

    uptr.reset();
    if(uptr == NULL)
    {
        cout << "khong con so huu\n";
    }
    else
    {
        cout << "van con so huu\n";
        cout << "Value: " << *uptr << endl;     // *rptr
    }
    return 0;
}

```
Két quả
```cpp
Value: 10
Value: 100
khong con so huu
```
***
### 25.3.6. Hàm move()
***
```cpp
#include <iostream>
#include <memory>   // cần thiết để sử dụng smart pointer

using namespace std;

int main(int argc, char const *argv[])
{
    unique_ptr<int> uptr(new int (10));     

    unique_ptr<int> uptr3;
    uptr3 = move(uptr);

    if(uptr == NULL)
    {
        cout << "khong con so huu\n";
    }
    else
    {
        cout << "van con so huu\n";
        cout << "Value uptr: " << *uptr << endl;     // *rptr
    }

    if(uptr3 == NULL)
    {
        cout << "khong con so huu\n";
    }
    else
    {
        cout << "van con so huu\n";
        cout << "Value uptr3: " << *uptr3 << endl;     // *rptr
    }
    return 0;
}
```
Kết quả
```cpp
khong con so huu
van con so huu
Value uptr3: 10
```
***

## 25.4. Shared Pointer
***
std::shared_ptr là một smart pointer khác trong C++ và cũng giúp quản lý bộ nhớ động. 

std::shared_ptr là một smart pointer hỗ trợ chia sẻ quyền sở hữu một đối tượng với nhiều đối tượng shared_ptr khác..

std::shared_ptr sử dụng một bộ đếm tham chiếu để theo dõi số lượng đối tượng shared_ptr đang tham chiếu đến một đối tượng, và chỉ giải phóng bộ nhớ khi không còn shared_ptr nào tham chiếu đến nó.

### 25.4.1. Các phương thức
***
|phương thức| Mô tả|
|---|---|
|operator * ()|		tương tự unique_ptr|
|operator → ()|		tương tự unique_ptr|
|get()		|	tương tự unique_ptr|
|reset()	|		tương tự unique_ptr|
|operator = ()	|	Sao chép hoặc di chuyển quyền sở hữu giữa các shared_ptr.|
|use_count()	|	Trả về số lượng shared_ptr đang cùng quản lý đối tượng.|

***
## 25.5. Weak Pointer
***
std::weak_ptr là một cơ chế giữ tham chiếu yếu (weak reference) đến một đối tượng được quản lý bởi shared_ptr. Nó cung cấp một cách an toàn để theo dõi một đối tượng mà không tăng bộ đếm tham chiếu của shared_ptr. 

std::weak_ptr không trực tiếp truy cập đến đối tượng của std::shared_ptr mà nó chỉ theo dõi trạng thái. 

std::weak_ptr có một phương thức là lock(). 
- Nếu shared_ptr mà weak_ptr theo dõi vẫn tồn tại, lock() sẽ trả về một shared_ptr hợp lệ có thể sử dụng để truy cập đối tượng. 
- Nếu shared_ptr đã bị giải phóng, lock() sẽ trả về một shared_ptr rỗng.
***