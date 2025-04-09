# Class
***
## 1. Khái niệm class
***
Class Tương tự với struct và union. Nhưng trong struct union là chỉ chứa biến, còn class thì có thể chứa cả biến, chứa cả hàm

Trong C++, từ khóa "class" được sử dụng để định nghĩa một lớp, là một cấu trúc dữ liệu tự định nghĩa có thể chứa dữ liệu và các hàm thành viên liên quan. \

-	chỉ có duy nhất 1 cách duy nhất để khai báo 1 class (struct nhiều cách (cụ thể là 5 cách))

```cpp
class ClassName {
private:
    // Các thành phần riêng tư (private) chỉ có thể truy cập bên trong lớp
    // Dữ liệu thành viên, hàm thành viên, ...

protected:
    // Các thành phần bảo vệ (protected) tương tự như private, nhưng có thể truy cập từ lớp kế thừa

public:
    // Các thành phần công khai (public) được truy cập từ bên ngoài lớp
    // Dữ liệu thành viên, hàm thành viên, ...
    // Hàm thành viên và các phương thức khác có thể được định nghĩa tại đây
    // ...

};
```
***
## 2. phạm vi truy cập trong class
***
-	Class trong C++ thì mặc định không thể truy xuất từ bên ngoài class, nên trong nó sẽ được phân vùng là public và private và protected; private là không thể truy xuất từ bên ngoài và public thì có thể truy xuất từ bên ngoài; còn protected là kết hợp cả 2 phân vùng trên
-	Việc phân chia ra các vùng bên trong class. Mỗi phạm vi đều có đặc điểm riêng ứng với OOP của nó

***
### 2.1. phạm vi truy cập public

#### 2.1.1. Đặc điểm
-	Có thể truy cập trực tiếp từ bên ngoài lẫn cả bên trong class
Quy tắc đặt tên ở C++ khác với C thường:
-	Thuộc tính  <=> biến
-	Phương thức <=> hàm
-	Đối tượng  <=> gọi lại

#### 2.1.2. Các cách có thể truy xuất vào class:
Thì có các cách sau để có thể truy xuất đến giá trị của biến đó

**Cách 1:** **chỉ áp dụng cho bên trong class**

Cú pháp:
```c
<Tên class>::<Thành viên của class>
```
**Cách 2: nằm trong class, và chỉ cần tên thành viên**

Cú pháp:
```cpp
<tên thành viên của class>
```

Ví dụ
```cpp
void display()      // phương thức (method)
{
    cout << "Tuoi cua Sinh Vien la: " << SinhVien::age << endl; // cách 1
    cout << "Tuoi cua Sinh Vien la: " << age << endl;           // cách 2
    cout << "Ten cua SV: " << name << endl;
    cout << "Chuyen nganh: " << major << endl;
}
```

**Cách 3: truy cập thông qua các biến bên trong hoặc bên ngoài class**

Cú pháp:
```cpp
<Tên class> <tên đối tượng cần khai báo>;
<tên đối tượng>.<Thành viên class> = x;
```

Ví dụ:
```cpp
SinhVien sv1;
Sv1.age = 30;
```

Đặc biệt ta cũng có thể truy xuất đến các hàm được khai báo bên trong class

```cpp
class SinhVien
{
    public:
        int age;        // thuộc tính (property)
        void display()      // phương thức (method)
        {
            cout << "Tuoi cua Sinh Vien la: " << age << endl;
        }   
};
int main()
{
    SinhVien sv1;
    sv1.age = 23;
    sv1.display();
    cout << "Tuoi cua Sinh Vien la: " << sv1.age << endl;
} 
```

**Cách 4: khai báo bên ngoài class**
Để làm được việc này ta sử dụng dấu :: để truy xuất 

Cú pháp:
```cpp
class <tên class>
{
    public:
        Void create2();
};
void <tên class>::create2()
{
    cout << … ;
} 
```
Ví dụ
```cpp
class SinhVien 
{
    public:
        int age;        // thuộc tính (property)
        void display()      // phương thức (method)
        {
            cout << "Tuoi cua Sinh Vien la: " << age << endl;
        }
       void create()
        {
            SinhVien sv;
            sv.age = 20;
            sv.display();
        }
        void create2();
    private:
        int names;
};
void SinhVien::create2()
{
    cout << "Tuoi cua Sinh Vien la: " << age << endl; 
}
int main(int argc, char const *argv[])
{
    SinhVien sv1;
    sv1.age = 23;
    sv1.display();
    cout << "Tuoi cua Sinh Vien la: " << sv1.age << endl;

    return 0;
}
```
#### 2.1.3.  các hàm đặc biệt bên trong Class
##### **A.	constructor**
▪	Constructor trong C++ là một method sẽ được tự động gọi khi khởi tạo object.
▪	Constructor sẽ có tên trùng với tên của class., không có kiểu trả về
▪	Mục đích chính của constructor là khởi tạo dữ liệu ban đầu cho đối tượng.
Constructor sẽ tự động chạy nên ta sẽ có ứng dụng nó để tạo thông số ban đầu của các biến, thay vì phải khai báo lại bằng việc đặt biến class và gán giá trị
Constructor có thể để ở bất kì phạm vi nào (hiện tại đang ở public), còn nằm ở private hoặc protected, ứng với từng phạm vi thì sẽ có những chức năng khác nhau

**Phân loại constructor**

Constructor có 3 loại là:
-	Constructor không có tham số
-	Constructor có tham số không có giá trị mặc định
-	Constructor có tham số nhưng có giá trị mặc định

###### **a) Constructor không có tham số**

Cú pháp:
```cpp
class <tên class>
{
    public:
        <tên class>()
        {
            Khai báo thành viên mặc định
        }
};
int main()
{
    <Tên class> <biến khai báo>;
}  
```
Ví dụ:
```cpp
class SinhVien 
{
    public:
        // char * name;
        string name;
        string major;
        // int *ptr;
        // khai báo constructor không có tham số
        SinhVien()  
        {
            age = 20;
            name = "An";
            major  = "embedded";

            display();
        }void display()      // phương thức (method)
        {
            cout << "Tuoi cua Sinh Vien la: " << SinhVien::age << endl; // cách 1
            cout << "Ten cua SV: " << name << endl;
            cout << "Chuyen nganh: " << major << endl;
        }
}
int main(int argc, char const *argv[])
{
    SinhVien sv1;
}
```

Kết quả:
```cpp
Tuoi cua Sinh Vien la: 20
Ten cua SV: An
Chuyen nganh: Embedded
```

**Ưu điểm:** có thể giảm thiểu được việc khai báo nhiều lần trong main
**Nhược điểm:** Khi khởi tạo những đối tượng như sv1 sv2 sv3 thì những đối tượng này sẽ cùng mang thông tin cũ và giống hệt nhau 
=> 	Để khắc phục điểm yếu này cần dùng constructor có tham số

###### **b)	Constructor có tham số nhưng không có giá trị mặc định**

Cú pháp:
```cpp
class <tên class>
{
    public:
        <tên class> (các tham số được chỉ định)
        {
            Khai báo thành viên mặc định
        }
};
int main()
{
    <Tên class> <biến khai báo> (các đối số được chỉ định);
}  
```

Ví dụ:
```cpp
class SinhVien 
{
    public:
        string name;
        string major;
       // khai báo constructor có tham số - không có giá trị mặc định
        SinhVien(string newName, int newAge, string newMajor)  
        {
            name = newName;
            age = newAge;
            major  = newMajor;
        }
}
```

###### **c)	Constructor có tham số nhưng có giá trị mặc định**

Cú pháp:
```cpp
class <tên class>
{
    public:
        <tên class> (các tham số được chỉ định được gán giá trị mặc định)
        {
            Khai báo thành viên mặc định
        }
};
int main()
{
    <Tên class> <biến khai báo> (các đối số được chỉ định hoặc là bỏ trống);
}  
```

Ví dụ
```cpp
class SinhVien 
{
    public:
        // char * name;
        string name;
        string major;
        // int *ptr;
        
        // khai báo constructor có tham số - có giá trị mặc định
        SinhVien(string newName = "", int newAge = 8, string newMajor = "")  
        {
            name = newName;
            age = newAge;
            major  = newMajor;

            display();
        }
}
int main(int argc, char const *argv[])
{
   SinhVien sv1("An", 23, "HTN");
   SinhVien sv2("Que", 25, "elec");
   SinhVien sv3;
}

```

Kết quả
```cpp
Tuoi cua Sinh Vien la: 23
Ten cua SV: An
Chuyen nganh: HTN
Tuoi cua Sinh Vien la: 25
Ten cua SV: Que
Chuyen nganh: elec
Tuoi cua Sinh Vien la: 8
Ten cua SV:
Chuyen nganh:
```
Như có thể thấy ở trường hợp sinh viên thứ 3 không có khai báo giá trị nên sv3 sẽ lấy giá trị mặc định đã được khai báo ở constructor 

###### **d)	Constructor theo kiểu danh sách**

Cách này hay dùng

Cú phấp
```cpp
class <tên class>
{
    public:
        <tên class> (các tham số được chỉ định được gán giá trị mặc định)
              : đối tượng 1 (tham số 1), đối tượng 2 (tham số 2),…
        {
            Có thể khai báo hàm thực thi hoặc không cần khai báo cũng được
            Không cần phải khai báo các thành viên nữa (trên danh sách đã khai báo rồi)
        }
};
int main()
{
    <Tên class> <biến khai báo> (các đối số được chỉ định hoặc là bỏ trống);
}  
```

Ví dụ:
```cpp
class SinhVien 
{
    public:
        // char * name;
        string name;
        string major;
        // int *ptr;
        
        // initialization list
        SinhVien(string newName = "", int newAge = 8, string newMajor = "")  
            : name(newName), age(newAge), major(newMajor)
        {
            display();    // có thể có hoặc không
        }
}
int main(int argc, char const *argv[])
{
   SinhVien sv1("An", 23, "HTN");
   SinhVien sv2("Que", 25, "elec");
   SinhVien sv3;
}
```

=> kết quả cho ra tương tự với e) 
=> việc khai báo constructor như thế này giúp việc khởi tạo nhanh chóng hơn và tối ưu hơn

##### **B. Destructor**

▪	Destructor trong C++ là một method sẽ được tự động gọi trước khi object được giải phóng.
▪	Destructor sẽ có tên trùng với tên của class và thêm ký tự ~ ở phía trước tên, không có kiểu trả về
▪	Destructor chỉ có 1 dạng khai báo thôi, là dạng không có tham số

Cú pháp:
```cpp
class <tên class>
{
    public:
        <tên class> (các tham số được chỉ định được gán giá trị mặc định)
              : đối tượng 1 (tham số 1), đối tượng 2 (tham số 2),…
        {
            …..
        }
        ~ <tên class> ()
        {
              Gán các giá trị của các thành viên về lại 0 hoặc là không NULL
        }
};
int main()
{
    <Tên class> <biến khai báo> (các đối số được chỉ định hoặc là bỏ trống);
}  
```

Ví dụ:

```cpp
class SinhVien 
{
    public:
        // char * name;
        string name;
        string major;
        // int *ptr;
        
        // initialization list
        SinhVien(string newName = "", int newAge = 8, string newMajor = "")  
            : name(newName), age(newAge), major(newMajor)
        {
            display();    // có thể có hoặc không
        }

        // destructor
        ~SinhVien()
        {
            name = "";
            age = 0;
            major = "";
            // free(ptr);
            display();
        }
}
```

Kết quả
```cpp
Tuoi cua Sinh Vien la: 0
```

##### **C.	Getter và setter**

2 hàm này mục đích sử dụng là để thay thế hàm display Các hàm getter và setter để truy cập và sử dụng (cho dù nó đang ở khu vực private hoặc là protected)

Điều này giúp cho việc truy cập và thay đổi giá trị của thành viên có thể được thực hiện, phục vụ rất nhiều với các phạm vi private và protected, đây là 2 phạm vi chỉ có thể truy cập ở class và không thể truy cập từ bên ngoài

Cấu trúc của getter và setter cũng đơn giản, chỉ cần return giá trị mới là được

Ví dụ
```cpp
// setter method
void setName(string newName){
    name = newName;
}

// getter method
string getName()
{
    return name;
}
```

##### **D.	Từ khóa Static**
Như đã biết thì static là để dùng giới hạn các biến nằm trong file hiện tại hoặc là trong hàm hiện tại, để không lọt ra được bên ngoài cho các hàm khác hay file khác có thể sử dụng

Trong class, các thành phần của các đối tượng sẽ được cấp phát 1 địa chỉ khác nhau 

Vậy nếu muốn khai báo biến x đó, chỉ có 1 địa chỉ duy nhất thì sao 

Để làm được thì chỉ cần sử dụng static property

Khi một property trong class được khai báo với từ khóa static, thì tất cả các object sẽ dùng chung địa chỉ của property này.

Cú pháp:
```cpp
Class <tên class>
{
   Public:
      Static int x;     // static property
}
Int <tên class>::x;
Int main()
{
    <tên class><tên biến cần khai báo>;
    <tên biến cần khai báo>.x = value;
}
```
●	Lưu ý rằng khi dùng static thì biến static này không còn phụ thuộc vào các đối tượng Sinhvien sv1, sv2, sv3 nữa (tức không cấp phát địa chỉ theo đối tượng), mà chỉ có duy nhất 1 địa chỉ cấp phát thôi 
●	Được sư dụng chung với đối tượng khác nhau, cơ chế cấp phát 1 vùng nhớ riêng biệt ra so với các biến còn lại 
●	Có thể cấp phát ở toàn cục, nhưng phải cấp phát trước khi mà hàm main chạy
●	Nếu cục bộ thì không cần cấp phát như trên (trong ví dụ ID sẽ có cái này )

Ví dụ:
```cpp
class SinhVien
{
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
    // static method
    static void show()
    {
        x = 100;
        // name = "An";
    }
}

int SinhVien::x;   // cấp phát địa chỉ cho static x

main()
{
    sv1.x = 100;
    cout << sv1.x << endl;
    cout << "Dia chi sv1: "<< &(sv1.x) << endl;
    cout << "Dia chi sv2: "<< &(sv2.x) << endl;
    cout << "Dia chi sv3: "<< &(sv3.x) << endl;
    SinhVien::show();

}
```

Kết quả

```c
100
Dia chi sv1: 0x408020
Dia chi sv2: 0x408020
Dia chi sv3: 0x408020
```

**Kết luận từ khóa static**

Khi một method trong class được khai báo với từ khóa static:

▪	Method này độc lập với bất kỳ đối tượng nào của lớp.
▪	Method này có thể được gọi ngay cả khi không có đối tượng nào của class tồn tại.
▪	Method này có thể được truy cập bằng cách sử dụng tên class thông qua toán tử :: .
▪	Method này có thể truy cập các static property và các static method bên trong hoặc bên ngoài class.
▪	Method có phạm vi bên trong class và không thể truy cập con trỏ đối tượng hiện tại.
***

### 2.2. phạm vi truy cập private 
(được tích hợp vào bài OOP bài 16)
***
### 2.3. phạm vi truy cập protected 
(được tích hợp vào bài OOP bài 16)
***
## 3. Binary Search
***
