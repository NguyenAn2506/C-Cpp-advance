# Các tính chất hướng đối tượng trong Class
***
Trong C++ có những tính chất hướng đối tượng như sau:

-	Tính đóng gói (Encapsulation)
-	Tính trừu tượng (abstract)
-	Tính kế thừa (inheritance)
-	Tính đa hình (Polymorphism)

***
## 1. tính đóng gói (Encapsulation)
***
Tính đóng gói (Encapsulation) là ẩn đi các property “mật” khỏi người dùng. Và để làm được điều này, ta sẽ khai báo các property ở quyền truy cập private/protected (tức là không thể truy cập trực tiếp tới các property này thông qua object bên ngoài). 

Lí do cần ẩn đi là để có thể kiểm tra tính đúng đắn của dữ liệu mà các thuộc tính đang lưu trữ hoặc không muốn người dùng biết thuật toán đang thực thi

Trong trường hợp ta muốn đọc hoặc ghi các property này, thì ta sẽ truy cập gián tiếp thông qua các method ở quyền truy cập public. (thông qua các setter và getter)

Cú pháp:
```cpp
Class <tên class>
{
    Private:
      Các đối tượng 
    Public:
      Các hàm kiểm tra độ chính xác dữ liệu
}
```

Ví dụ:
```cpp
using namespace std;

class SinhVien 
{
    private:
        // char * name;
        string name;
        int age;        // thuộc tính (property)
        string major;
        // int *ptr;
        int id;
        double gpa;
    public:
        void setName(string newName){
            if(checkName(newName) == true)
            {
                name = newName;           
            }
        }
        void setAge(int newAge){
            if(newAge > 0 && newAge <= 100)
            {
                age = newAge;
            }
        }
}
main()
{
    SinhVien sv2;
    sv2.setName("Nta1");      // bị sai tên 
    sv2.setAge(23);
}
```

=> tính đóng gói liên quan đến các **biến trong class**

*** 

## 2. tính trừu tượng (abstract)
***
### 2.1. khái niệm:

Tính trừu tượng đề cập đến việc ẩn đi các chi tiết cụ thể của một đối tượng và chỉ hiển thị những gì cần thiết để sử dụng đối tượng đó.

Ví dụ:
```cpp
class SinhVien 
{
    private:
        // char * name;
        string name;
        int age;        // thuộc tính (property)
        string major;
        // int *ptr;
        int id;
        double gpa;

        bool checkName(string str)
        {
            // không có số và ko có ký tự đặc biệt
            // chữ hoa  'A' --> 'Z'
            // chứ thường   'a' --> 'z'
            for(int i = 0; i<str.length(); i++)
            {
                char c = str[i];
                if(! ( (c>='A' && c<= 'Z') || (c>='a'  && c<= 'z') || (c== ' '))) return false;
            }
            return true;
        }

        bool checkAge(int newAge)
        {
            if(newAge < 0) return false;
            else return true;
        }

    public:
        static int x;   //  static property

        // initialization list
        SinhVien(string newName = "", int newAge = 8, string newMajor = "")  
            : name(newName), age(newAge), major(newMajor)
        {
            static int __ID = 1;
            id = __ID;
            __ID++;
            display();
        }
        // setter method
        void setName(string newName){
        void display()      // phương thức (method)
        }
}
```
Ví dụ trên là lấy nguyên cái hàm kiểm tra đó bỏ vào trong private hoặc là protected luôn => làm cho ng dùng chả có thể sử dụng để làm nữa

Kết quả hệ thống đâu có cho gợi ý đâu (không gợi ý là ko sử dụng đưuọc đó)

![Image](https://github.com/user-attachments/assets/3a84f801-1122-4446-8103-6268c113dfed)

Lúc này không thể tác động vào các biến thuộc tính nữa, mà phải thông qua hàm setter và getter hoặc là constructor để ghi giá trị vào 

```cpp
int main(int argc, char const *argv[])
{
    SinhVien sv1("An", 23, "HTN");
    SinhVien sv2;
    sv2.setName("Nta1");
    sv2.setAge(-1);
    sv2.setMajor("emb sys");
    sv2.display();
    SinhVien sv3("Que", 25, "elec");       

    return 0;
}
```
***
## 3. tính kế thừa (Inheritance)
***
Trong trường hợp như thế này, có nhiều task có các thuộc tính giống nhau chỉ khác 1 số thuộc tính riêng

```cpp
class SinhVien
{
    public:
        string ten;
        int id;
        string chuyenNganh;
};

class HocSinh
{
    public:
        string ten;
        int id;
        string lop;
};

class GiaoVien
{
    public:
        string ten;
        int id;
        string chuyenMon;
};
```

=> 3 class trên có 2 thuộc tính lặp đi lặp lại. 
=> vậy liệu có cách nào để rút gọn source code không?
***
### 3.1. Khái niệm:

Tính kế thừa ( Inheritance) là khả năng sử dụng lại các property và method của một class trong một class khác và có thể mở rộng thêm tính năng. Ta chia chúng làm 2 loại là class cha và class con. Để kế thừa từ class khác, ta dùng ký tự ":".

Có 3 kiểu kế thừa là **public, private và protected**. Những property và method được kế thừa từ class cha sẽ nằm ở quyền truy cập của class con tương ứng với kiểu kế thừa.

Cú pháp:
```cpp
Class <tên class con>: <kiểu kế thừa> <tên class cha>
```
Lưu ý:
-	Public ở khai báo kế thừa khác với public trong class nhé 
-	Public trong class là mang tính truy cập, còn public trên là liên quan đến kế thừa

Lúc này thì không cần phải khai báo các thuộc tính của class cha nữa mà chỉ cần khai báo thuộc tính mới của class con thôi
***
### 3.2. kế thừa public

-	Các member public của class cha vẫn sẽ là public trong class con.
-	Các member protected của class cha vẫn sẽ là protected trong class con.
-	Các member private của class cha không thể truy cập trực tiếp từ class con nhưng có thể được truy cập gián tiếp qua các phương thức public hoặc protected của class cha

Cú pháp:

```cpp
Class <tên class con>: public <tên class cha>
```
Các hàm và thuộc tính của public là class cha sẽ có thể dược dùng lại trong class con với phạm vi không đổi (phạm vi public), và không thể kế thừa phạm vi private của class cha được => class con không thể chạm được vào trong private

**Vi dụ: đổi phạm vi private sang protected**

```cpp
class DoiTuong{

    private:
        string ten;
        int id;

    public:
};

class SinhVien : public DoiTuong{
    protected:
        // string ten;
        // int id;
        string chuyenNganh;

    public:
        void setChuyenNganh(string _nganh){
            chuyenNganh = _nganh;
        }

       void display(){ // override
            cout << "ten: " << ten << endl;
            cout << "id: " << id << endl;
            cout << "chuyen nganh: " << chuyenNganh << endl;
        }
};
```

#### Lấy giá trị của các thuộc tính trong kế thừa public
##### Cách 1: chuyển đổi phạm vi từ private sang protected
Nếu muốn sử dụng các thuộc tính (biến) trong private của class cha thì cần phải thay đổi phạm vi của class cha về lại protected (vì nó có thể được truy cập và sửa đổi).

2 đặc điểm của protected là 
●	có thể truy xuất ngay trong class của nó
●	Và có thể truy xuất từ 1 class con kế thừa nó (private là không thể truy xuất)

**Ví dụ: lấy giá trị của các thuộc tính trong protected**

```cpp
class DoiTuong{
    // private:
    //    string ten;
    //    int id;
    protected:
        string ten; 
        int id;

    public:
        DoiTuong(){  
            static int ID = 1;
            id = ID;
            ID++;
        }

        void setName(string _ten){
            // check chuỗi nhập vào
            ten = _ten;
        }

        void display(){
            cout << "ten: " << ten << endl;
            cout << "id: " << id << endl;
        }
};

class SinhVien : public DoiTuong{
    protected:
        // string ten;
        // int id;
        string chuyenNganh;

    public:
        void setChuyenNganh(string _nganh){
            chuyenNganh = _nganh;
        }

        void display() override { // 
            // cout << "ten: " << ten << endl;  không cần khai báo lại nữa vì class cha đã khai báo
            // cout << "id: " << id << endl;
            DoiTuong::display();
            cout << "chuyen nganh: " << chuyenNganh << endl;
        }
};
```

=> Các hàm như display ở trong class cha và con không bị báo lỗi, do class con kế thừa từ class cha và nó có thể dùng lại hoặc là mở rộng thêm tính năng cho hàm đó (chỉ trong phạm vi class con thôi)

##### Cách 2: sử dụng kết hợp private với setter/getter

```cpp
class DoiTuong {
    private:
        string ten;
        int id;
    
    public:
        DoiTuong() {  
            static int ID = 1;
            id = ID;
            ID++;
        }
        void setName(string _ten) {
            ten = _ten;
        }
        void setId(int _id) {
            id = _id;
        }
        void display() {
            cout << "ten: " << ten << endl;
            cout << "id: " << id << endl;
        }
    };
    
class SinhVien : public DoiTuong {
    private:
        string chuyenNganh;
    
    public:
        void setChuyenNganh(string _nganh) {
            chuyenNganh = _nganh;
        }
        void setStudentInfo(string _ten, int _id, string _nganh) {
            setName(_ten);  // Gọi setter từ lớp cha để thiết lập tên
            setId(_id);     // Gọi setter từ lớp cha để thiết lập ID
            chuyenNganh = _nganh;
        }
        void display() override { // override
            DoiTuong::display();
            cout << "chuyen nganh: " << chuyenNganh << endl;
        }
};
    
int main() {
    SinhVien sv1;
    // Sử dụng setter để thay đổi giá trị
    sv1.setStudentInfo("Nguyen Van A", 10, "Embedded System");
    // In ra thông tin
    sv1.display();
    return 0;
}
```
***
### 3.3. Kế thừa protected

Nhắc lại đặc điểm của protected:
●	có thể truy xuất ngay trong class của nó
●	Và có thể truy xuất từ 1 class con kế thừa nó (private là không thể truy xuất)

Các member public, protected của class cha sẽ là protected trong class con, nên không thể truy cập trực tiếp từ bên ngoài (main)

Các member private của class cha không thể truy cập trực tiếp từ class con nhưng có thể được truy cập gián tiếp qua các phương thức public hoặc protected của class cha.

Class con ngầm truy cập vào class cha copy phạm vi public và protected sang class con và chuyển đổi về đúng kiểu phạm vi kế thừa protected
-	public -> protected
-	protected -> protected

ví dụ 
**ở cách lấy giá trị của các thuộc tính trong kế thừa public (3.2. cách 1)**
***
### 3.4. Kế thừa private
Các member public, protected của class cha sẽ trở thành private trong class con, không thể truy cập từ bên ngoài (main)

Các member private của class cha không thể truy cập trực tiếp từ class con nhưng có thể được truy cập gián tiếp qua các phương thức public hoặc protected của class cha.

Class con ngầm truy cập vào class cha copy phạm vi public và protected sang class con và chuyển đổi về đúng kiểu phạm vi kế thừa private

-	public -> private
-	protected -> private

ví dụ
**ở cách lấy giá trị các thuộc tính trong kế thừa public (cách 2) => sử dụng setter + private**
***
### 3.5. Đa kế thừa
-	từ 1 class mà có thể kế thừa từ nhiều class khác nhau
-	Chức năng là kết hợp chức năng từ nhiều class khác nhau

```cpp
#include <iostream>

using namespace std;

class A
{
    public:
        A() { cout<< "Constructor A" << endl; }
        void displayA() { cout << "Display class A" << endl; }
};

class B : public A
{
    public:
        B() { cout<< "Constructor B" << endl; }
        void displayB() { cout << "Display class B" << endl; }
};

class C : public A
{
    public:
        C() { cout<< "Constructor C" << endl; }
        void displayC() { cout << "Display class C" << endl; }
};

class D : public B, public C
{
    public:
        D() { cout<< "Constructor D" << endl; }
        void displayD() { cout << "Display class D" << endl; }
};

int main(int argc, char const *argv[])
{
    D d;
    d.displayB();
    d.displayC();
    d.displayD();
    // d.displayA();

    d.B::displayA();
    d.C::displayA();
    // d.A::displayA();
    return 0;
}
```
***
## 4. Tính đa hình (Polymorphism)
***
### 4.1. khái niệm:
Tính đa hình ( Polymorphism) có nghĩa là "nhiều dạng" và nó xảy ra khi chúng ta có nhiều class có liên quan với nhau thông qua tính kế thừa.

Tính đa hình có thể được chia thành hai loại chính:
-	Đa hình tại thời điểm biên dịch (Compile-time Polymorphism).
-	Đa hình tại thời điểm chạy (Run-time Polymorphism).

### 4.2. đa hình tại runtime

ta có trường hợp như thế này
```cpp
class DoiTuong{........ display("a")}

class SinhVien : public DoiTuong{......... display("b")}

int main(int argc, char const *argv[])
{
    SinhVien sv1;

    DoiTuong *dt;
    dt = &sv1;
    dt->display();
}

```

Kết quả:
```cpp
b
```
=> Nếu theo cách nghĩ thông thường thì khi mà con trỏ này trỏ đến sv1 thì nó phải in thông tin của sv1, tức là class SinhVien 
Nhưng ở đây nó in ra chỉ có 1 thông tin của mỗi class cha (DoiTuong) thôi

Lí do là vì nó đã bị ép kiểu rồi

#### cách 1: sử dụng phương pháp down casting
Để giải quyết việc tự động ép kiểu ta cx sẽ ép kiểu cho từ class DoiTuong (class cha) về lại class SinhVien (class con) 

```cpp
class DoiTuong{
    // private:
    //    string ten;
    //    int id;

    protected:
        string ten;
        int id;

    public:
        DoiTuong(){  
            static int ID = 1;
            id = ID;
            ID++;
        }

        void setName(string _ten){
            // check chuỗi nhập vào
            ten = _ten;
        }

        void display(){
            cout << "ten: " << ten << endl;
            cout << "id: " << id << endl;
        }
};

class SinhVien : public DoiTuong{
    protected:
        // string ten;
        // int id;
        string chuyenNganh;

    public:
        void setChuyenNganh(string _nganh){
            chuyenNganh = _nganh;
        }

        void display(){ // override
            // cout << "ten: " << ten << endl;
            // cout << "id: " << id << endl;
            DoiTuong::display();
            cout << "chuyen nganh: " << chuyenNganh << endl;
        }
};
int main(int argc, char const *argv[])
{
    SinhVien sv1;
    sv1.setName("Trung");
    sv1.setChuyenNganh("TDH");
    // sv1.display();
    cout << endl;

    DoiTuong *dt;
    dt = &sv1;
    // dt->display();
    ((SinhVien *)dt) -> display();    // down-casting

}
```

Quá trình chuyển đổi từ lớp cha về lại lớp con được gọi là down-casting

Với việc có down – casting thì ngược lại sẽ là up-casting

```cpp
    SinhVien *sv = &sv1;
    ((DoiTuong*)sv) ->display();    //  up-casting
```

##### Lưu ý: khi dùng up/down casting

khi thay thế hàm main thành như thế này

```cpp
    DoiTuong *dt;
    dt = &sv1;

    DoiTuong dt1;
    dt = &dt1;
    ((SinhVien *)dt)->display();

```
o	Với việc trình tự như vậy xảy ra nên hệ thống sẽ báo lỗi, như có thể thấy hàm display() của class SinhVien đang được lặp lại đến lần thứ 2

o	Gây cho trình biên dịch không thể biết được là đang muốn sử dụng display() nào

o	Lỗi không đủ dữ liệu để in ra 

![Image](https://github.com/user-attachments/assets/b78910f4-972e-41bc-8128-a4a3d4eb5a84)

=> đây là lỗi hệ thống trong quá trình runtime nên khi biên dịch không phát hiện ra được

#### cách 2: sử dụng từ khóa virtual 
(Bài 17: virtual Function)