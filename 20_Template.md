# Template (Generic Programming)
***
Trong C++ có thể viết tên hàm cùng tên vơi nhau nhưng phải khác về các tham số hàm, cũng có thể khác về các kiểu dữ liệu trả về như ví dụ 

Câu hỏi đặt ra là có thể gộp 2 hàm này lại không
__sum(__a, __b){}

![Image](https://github.com/user-attachments/assets/132d8ed9-d775-4a2e-abb9-50cbc0a78c85)
***
## 1. Khái niệm:
***
Generic Programming (Lập trình tổng quát) là một phương pháp lập trình sử dụng các tham số kiểu dữ liệu (type parameter) để viết mã có thể tái sử dụng và hoạt động với nhiều kiểu dữ liệu khác nhau. Kỹ thuật này giúp loại bỏ sự trùng lặp code và tăng tính linh hoạt trong thiết kế phần mềm.

Lập trình tổng quát thường được áp dụng trong các ngôn ngữ hỗ trợ Generics (như Java, Rust) hoặc Templates (C++).

C++ sử dụng Templates để triển khai Generic Programming. Templates có hai loại:

- Function Templates (Hàm tổng quát)
- lass Templates (Lớp tổng quát)

### 1.1. Ứng dụng
***
- Ứng dụng cho việc viết thư viện
- Trong lập trình nhúng thì chỉ sử dụng C
- Còn hệ thống phức tạp thì đều là C++ như là màn hình trên ô tô (backend)
- Còn frontend thì là Qt/ Java,…

***
## 2 Function Template
***
Trong C++, Templates giúp viết hàm có thể làm việc với nhiều kiểu dữ liệu mà không cần overload nhiều lần.

Template chỉ áp dụng cho một định nghĩa cụ thể của hàm (hàm viết ngay bên dưới nó), không áp dụng cho tất cả các hàm.

**Cú pháp:**
```cpp
template <typename T>
T func(T a, T b){}

template <typename T1, typename T2, typename T3>
T1 func(T1 a, T2 b, T3 c){}
```
Tổng quát cho nhiều kiểu dữ liệu khác nhau thì dùng cụm từ <typename T>  

trong đó T đại diện cho nhiều kiểu dữ liệu khác nhau

### 2.1. Ví dụ
***
#### Ví dụ 1: ví dụ về template 1 kiểu dữ liệu hoặc nhiều kiểu dữ liệu
***
```cpp
#include <iostream>
using namespace std;

template <typename T>
T sum(T a, T b)
{
    return a + b;
}

template <typename T1, typename T2>
// T1 sum(T1 a, T2 b)
auto sum(T1 a, T2 b)
{
    return a+b;
}

int result1 = sum(5, 10);           // Tự động suy luận T là int
double result2 =sum(3.14, 2.71);    // Tự động suy luận T là double

int main(int argc, char const *argv[])
{
    cout << "Sum: "<< result1 << endl;
    cout << "Sum: "<< result2 << endl;
    cout << "Sum: "<< sum(1.5, 2) << endl;
    cout << "Sum: "<< sum(1, 2.7) << endl;
    return 0;
}
```
Nhưng kết quả sinh ra
```cpp
Sum: 15
Sum: 5.85
Sum: 3.5
Sum: 3
```
Như kết quả sinh ra có 1 sự khác lạ

=> Lí do khi sử dụng sum (1, 2.7) không ra được 3.7 là do nó đang lấy kiểu trả về của a mà a đang là int nên nó sẽ trả về là int

=> Còn ở trên là a là 1.5 nên mặc định nó là float nên kết quả sinh ra vô tình đúng

#### vÍ dụ 2: từ khóa auto
Để khắc phục điểm yếu của ví dụ 1 thì ta có thể sử dụng từ khóa auto

●	Từ khóa auto giúp cho trình biên dịch tự động suy luận và quy định kiểu dữ liệu của biến qua giá trị mà nó đang mang

```cpp
#include <iostream>
using namespace std;

template <typename T>
T sum(T a, T b)
{
    return a + b;
}

template <typename T1, typename T2>
// T1 sum(T1 a, T2 b)
auto sum(T1 a, T2 b)
{
    return a+b;
}

int result1 = sum(5, 10);           // Tự động suy luận T là int
double result2 =sum(3.14, 2.71);    // Tự động suy luận T là double

int main(int argc, char const *argv[])
{
    cout << "Sum: "<< result1 << endl;
    cout << "Sum: "<< result2 << endl;
    cout << "Sum: "<< sum(1.5, 2) << endl;
    cout << "Sum: "<< sum(1, 2.7) << endl;
    return 0;
}
```
Kết quả đầu ra chính xác
```cpp
Sum: 15
Sum: 5.85
Sum: 3.5
Sum: 3.7
```
***
## 3. Class Template
***
Class templates trong C++ là một khái niệm tương tự như function templates, nhưng được áp dụng cho class thay vì function. Class templates cho phép tạo các  class có thể làm việc với nhiều kiểu dữ liệu mà không cần viết lại code.

Template chỉ áp dụng cho một định nghĩa cụ thể của class, không áp dụng cho tất cả các class.

Cú pháp:
```cpp
template <typename T>
class <name_of_class>
{
    private:
        T var;
}
```
### Ví dụ 1: sử dụng cho hàm
***
```cpp
#include <iostream>
using namespace std;

template <typename T>
class Sensor{
    private:
        T value;
    public:
        Sensor(T init): value(init){}
        void readSensor(T newValue){ value = newValue; }
        T getValue() const { return value; }
        void display(){ cout << "Gia tri cam bien: " << value << endl; }
};

int main(int argc, char const *argv[]){

    // cách 1: quy định kiểu dữ liệu mặc định
    Sensor<double> tempSensor(36.5);
    tempSensor.display();

    Sensor<int> lightSensor(512);
    lightSensor.display();

    Sensor<string> stateSensor("OFF");
    stateSensor.display();

    // cách 2: không quy định kiểu dữ liệu  

    // Sensor tempSensor(36.5);
    // tempSensor.display();

    // Sensor lightSensor(512);
    // lightSensor.display();

    // Sensor stateSensor("OFF");
    // stateSensor.display();

    return 0;
}
```
Bên trong class là dữ liệu của sensor

Khi sử dụng constructor do bên trên đang dùng kiểu dữ liệu là T thì ở đây cũng phải dùng T

Còn getter và setter thì cũng phải kiểu T 

Kết quả:
```cpp
Gia tri cam bien: 36.5
Gia tri cam bien: 512
Gia tri cam bien: OFF
```
### Ví dụ 2: sử dụng cho class
```cpp
#include <iostream>
using namespace std;

class Sensor
{
    public:
        virtual double getValue() const = 0;
        virtual string getUnit() const = 0;
};

// class đại diện cho cảm biens nhiệt độ (Temperature Sensor)
class TemperatureSensor : public Sensor
{
    private:
        double temp;
    public:
        double getValue() const override
        {
            return 40.5;        // giá trị cảm biến giả định
        }
        string getUnit() const override
        {
            return "Celsius";
        }
};

// class đại diện cho cảm biens áp suất (Tire Pressure Sensor)
class TirePressureSensor : public Sensor
{
    private:
        double temp;
    public:
        double getValue() const override
        {
            return 32;        // giá trị cảm biến giả định
        }
        string getUnit() const override
        {
            return "PSI";
        }
};

// template class quản lý 2 cảm biến khác nhau
template <typename Sensor1, typename Sensor2>
class VehicleSensors
{
    private:
        Sensor1 sensor1;
        Sensor2 sensor2;
    public:
        // constructor nhận vào 2 đối tượng cảm biến
        VehicleSensors (Sensor1 s1, Sensor2 s2) : sensor1(s1), sensor2(s2) {}

        // hàm hiển thị thông tin của cả 2 cảm biến
        void displaySensorInfo() const
        {
            cout << "Sensor 1 Value: "<< sensor1.getValue() << " " << sensor1.getUnit() << endl;
            cout << "Sensor 2 Value: "<< sensor2.getValue() << " " << sensor2.getUnit() << endl;
        }
};

int main(int argc, char const *argv[]){
    // tạo đối tượng cảm biến nhiệt độ
    TemperatureSensor tempSensor;
    // tạo đối tượng cảm biến áp suất lốp
    TirePressureSensor pressureSensor;

    // quản lý cả 2 cmar biến bằng claas VehicleSensors
    VehicleSensors<TemperatureSensor, TirePressureSensor> vehicleSensors(tempSensor, pressureSensor);
    vehicleSensors.displaySensorInfo();
    
    return 0;
}
```
Kết quả
```cpp
Sensor 1 Value: 40.5 Celsius
Sensor 2 Value: 32 PSI
```
***
## 4.Template Specialization
***
Template chuyên biệt hóa (Template Specialization) trong C++ cho phép tùy chỉnh hành vi của template cho một kiểu dữ liệu cụ thể.

Cú pháp:
```cpp
template <>
class name_of_class<data_type>
{
    private:
        T var;
}
```
### 4.1. Ví dụ
***
```cpp
#include <iostream>
using namespace std;

// Template tổng quát
template <typename T>
void display(T value){
    cout << "Generic: " << value << endl;
}

// Chuyên biệt hóa cho kiểu `int`
template <>
void display<int>(int value){
    cout << "Specialized for int: " << value << endl;
}

// Chuyên biệt hóa cho kiểu `char*`
template <>
void display<char*>(char* value){
    cout << "Specialized for string: " << value << endl;
}

int main(){
    display(42);        // Sử dụng chuyên biệt hóa cho int
    display(3.14);      // Sử dụng template tổng quát
    display("Hello");   // Sử dụng chuyên biệt hóa cho char*
    return 0;
}
```
Kết quả
```cpp
Specialized for int: 42
Generic: 3.14
Generic: Hello
```
***
## 5. Variadic Template
***
Trong C thì variadic là 1 macro ứng dụng cho việc khai báo số lượng tham số không xác định

Variadic Template cho phép bạn tạo các hàm template hoặc lớp template có thể nhận một số lượng tham số không xác định. Điều này giúp bạn viết mã linh hoạt hơn khi làm việc với danh sách tham số có kích thước động.

### 5.1. Ví dụ variadic cho hàm 
***
```cpp
#include <iostream>

using namespace std;

// Function Template khi chỉ có một tham số
template<typename T>
T sum(T value)
{
    return value;
}

// Function Template sử dụng Variadic Template, ít nhất 2 tham số
template<typename T, typename... Args>  
auto sum(T first, Args... args)
{        
    return first + sum(args...);        
}

int main(int argc, char const *argv[])
{
    cout << sum(1, 2, 3.6, 5.7, 40) << endl;
    return 0;
}
```
### 5.2. ví dụ variadic cho class
```cpp
#include <iostream>

using namespace std;

// Class tổng quát sử dụng Variadic Template
template <typename... Args>
class MyClass;

// Định nghĩa class khi không có đối số
template <>
class MyClass<>
{
    public:
        void display()
        {
            cout << "No arguments" << endl;
        }
};

// Định nghĩa class khi có ít nhất một đối số
template <typename T, typename... Args>
class MyClass<T, Args...> : public MyClass<Args...>
{
    private:
        T first_;

    public:
 // T first_ = first, Args1 args1_ = args1, Args2 args2_ = args2,...
        MyClass(T first, Args... args): first_(first),  MyClass<Args...>(args...){} 

        void display()
        {
            cout << first_ << " ";
            MyClass<Args...>::display(); // Gọi hàm display của lớp cơ sở
        }  

};

int main()
{
    MyClass<int, double, char> obj(1, 2.5, 'A');
    obj.display();  // Kết quả: 1 2.5 A

    MyClass obj1;
    obj1.display();
    return 0;
}

```