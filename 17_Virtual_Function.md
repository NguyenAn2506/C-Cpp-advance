# Virtual function (OOP - Polymorphism - Runtime)
***
Như bài trước đã học thì ta đã thấy được tác hại rất lớn từ việc dùng up và down casting.

Vậy nếu không dùng up/down casting thì dùng gì để có thể lấy dữ liệu đã được class cha ép kiểu khác với class con

=> dùng từ khóa virtual
***
## 1. Khái niệm
***
-	Virtual là 1 từ khóa sử dụng để đi kèm với hàm (hàm này được khai báo trong class cha)
-	Hàm ảo là một hàm thành viên được khai báo trong class cha với từ khóa virtual.
-	Khi một hàm là virtual, nó có thể được ghi đè (override) trong class con để cung cấp cách triển khai riêng.
-	Khi 1 hàm trong class cha đi kèm với từ khóa virtual thì nó sẽ được gọi là 1 hàm ảo. Khi gọi một hàm ảo thông qua một con trỏ hoặc tham chiếu đến lớp con, hàm sẽ được quyết định dựa trên đối tượng thực tế mà con trỏ hoặc tham chiếu đang trỏ tới chứ không dựa vào kiểu của con trỏ.
***
## 1.1. Ví dụ
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

        virtual void display(){
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

        void display() override
        {     
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

    DoiTuong *dt,dt1;
    dt = &sv1;
    dt->display();
    cout<<endl;

    dt = &dt1;
    dt->display();
    cout<<endl;

    return 0;
}

```
kết quả: ra tương tự với kết quả của up/down casting
```cpp
ten: Trung
id: 1
chuyen nganh: TDH

ten:
id: 4
```

●	Khi con trỏ dt này gọi thì nó sẽ không dựa vào kiểu con trỏ DoiTuong của nó nữa (không gọi hàm display từ class DoiTuong nữa), mà nó sẽ dựa vào những đối tượng thực tế nó đang quản lý
●	Nên khi mà dt = &sv1 (dt quản lý sv1) và gọi 1 hàm nào đó trong class SinhVien thì nó sẽ tự động đến class SinhVien để mà gọi ra
●	Ứng với 3 thời điểm khác nhau thì dt quản lý 3 con trỏ khác nhau => đây cũng được gọi là tính đa hình
●	Quá trình xác định đối tượng của dt thì nó sẽ xảy ra trong khi mà chương trình đang chạy ( đa hình runtime)
***
## 1.2. So sánh giữa việc ké thừa class con và class cha (có và không có dùng virtual)  (overload / override)

Khi class con kế thừa class cha (trong class cha không có hàm nào đang dùng virtual)

●	thì sẽ được gọi là overload
●	Overload có nghĩa là tái sử dụng các hàm trong class cha, ngoài ra là có thể mở rộng ra các tính năng của nó 

Còn khi class con kế thừa class cha (trong class cha có hàm đang dùng virtual)

●	Không được gọi là overload nữa mà gọi là override (phân việt với overload của kế thừa)
●	khi mà kế thừa những hàm ảo từ class cha thì không được phép thêm 1 tham số (không được thay thế hình dạng của class cha), nghĩa là nếu hàm virtual trong class cha đang mang kiểu vỏi thì trong class con kế thừa cx phải mang kiểu void, hoặc là có/ không có tham số

***
## 3. Override và tính đa hình Run - time
***
Override là việc ghi đè hàm ảo ở class con bằng cách định nghĩa lại nó. 

Khi một hàm ảo được ghi đè, hành vi của nó sẽ phụ thuộc vào kiểu của đối tượng thực tế, chứ không phải kiểu của con trỏ hay tham chiếu.

Tính đa hình Run-time xảy ra khi quyết định gọi hàm nào (phiên bản của class cha hay class con) được đưa ra tại thời điểm chạy, không phải lúc biên dịch, giúp mở rộng chức năng. Điều này giúp chương trình linh hoạt hơn, cho phép việc mở rộng chức năng mà không cần sửa đổi mã nguồn hiện tại.
***

## 4. Pure Virtual Function
***
Hàm thuần ảo là một hàm ảo không có phần định nghĩa trong class cha, được khai báo với cú pháp = 0 và khiến class cha trở thành class trừu tượng, nghĩa là không thể tạo đối tượng từ class này.

### 4.1. ví dụ (Vấn đề khi dùng pure virtual)
***
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
        
        // /* khai báo hàm ảo */
        // virtual void display(){             
            // cout << "ten: " << ten << endl;
            // cout << "id: " << id << endl;
        // }

        /* khai báo hàm thuần aỏ */
        virtual void display() = 0;
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

        void display() override
        {     
            // DoiTuong::display();
            cout << "ten: " << ten << endl;
            cout << "id: " << id << endl;
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

    DoiTuong *dt, dt1;

    dt = &sv1;
    dt->display();
    cout<<endl;

    dt = &dt1;          // lỗi tại đây
    dt->display();
    cout<<endl;

    return 0;
}
```
Kết qủa lỗi: 
![Image](https://github.com/user-attachments/assets/45298367-983b-478b-ac9c-69e9064fb218)

●	Khi mà 1 class có ít nhất 1 hàm thuần ảo thì nó sẽ biens class đó thành class trừu tượng (nghĩa là có 1 hàm bên trong chưa rõ rang, chưa có nội dung cụ thể)
●	Minh chỉ khai báo các đối tượng khi những hàm, class đó đã được khai báo đầy đủ nội dung
●	Phân biệt tính trừu tượng và class trừu tượng 
●	Tuy rằng không khai báo được biến thuộc kiểu class cha, nhưng có thể khai báo 1 con trỏ thuộc kiểu class cha 
●	Vì con trỏ có thể trỏ đến những đối tượng khác (sv1, hs1, gv1), mà những đối tượng này đa được khai báo đầy đủ rồi còn dt 1 thì chưa

### 4.2. ví dụ (giải quyết vấn đề)
***

```cpp
int main(int argc, char const *argv[])
{
    SinhVien sv1;
    sv1.setName("Trung");
    sv1.setChuyenNganh("TDH");
    // sv1.display();

    cout << endl;

    DoiTuong *dt;

    dt = &sv1;          // bỏ dt1 đi
    dt->display();
    cout<<endl;
    
    return 0;
}
```

Kết quả:
```cpp
ten: Trung
id: 1
chuyen nganh: TDH
```

***
## 5. đa kế thừa (làm cách khác so với bài 16 OOP)
***
Trong bài 16, là sử dụng cách truy xuất theo path từng class, để đến được hàm của class mong muốn. Tuy nhiên trong bài đó có 1 cái nhược là vẫn không truy xuất được A (do trùng lặp class) => khá dài dòng

=> Sử dụng từ khóa virtual
=> sử dụng virtual cho việc kế thừa class chứ không còn dùng cho các hàm nữa

Đa kế thừa trong C++ cho phép một class kế thừa từ nhiều class khác.

Đa kế thừa thường dùng để kết hợp các chức năng từ nhiều class.

Ví dụ:
```cpp
/**
 * nâng cấp đa kế thừa ở bài OOP (bài 16)
 */

#include <iostream>

using namespace std;

class A
{
    public:
        A() { cout<< "Constructor A" << endl; }
        void displayA() { cout << "Display class A" << endl; }
};

class B : virtual public A
{
    public:
        B() { cout<< "Constructor B" << endl; }
        void displayB() { cout << "Display class B" << endl; }
};

class C : virtual public A
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

    d.displayA();       // release diamond problems

    // d.B::displayA();
    // d.C::displayA();
    // d.A::displayA();
    return 0;
}
```

●	Do virtual giúp cho ta tạo 1 phiên bản class mà nó đang kế thừa mà thôi
●	Vậy khi mà B C kế thừa thì không còn phân biệt ra 2 phiên bản của A nữa, mà h đã gộp thành 1 rồi  
●	Nên có thể gọi trực tiếp mà không cần qua tên của các class này

=> giúp khắc phục lỗi diamond problem

=> việc làm đưa virtual này vào được gọi là kế thừa ảo

Khi nhiều lớp cha có các phương thức hoặc thuộc tính trùng tên, việc gọi chúng từ lớp con có thể gây ra sự nhầm lẫn.

Khi một lớp con kế thừa từ hai lớp cha, mà hai lớp cha này đều cùng kế thừa từ cùng một lớp khác. Tình huống này tạo ra cấu trúc hình thoi (diamond), do đó được gọi là vấn đề "Diamond".

### 5.1. khai niệm kế thừa ảo
***
Kế thừa ảo giúp tránh vấn đề diamond problem trong đa kế thừa.
Chỉ có một bản sao duy nhất của lớp cơ sở chung được kế thừa.
Kế thừa ảo giúp quản lý các lớp liên quan đến phần cứng và giao tiếp. Điều này giúp tránh trùng lặp tài nguyên và quản lý hiệu quả trong hệ thống nhúng.
Kế thừa ảo thì không xảy ra ở quá trình runtime mà nó xảy ra ở quá trình biên dịch (compile time)

***
