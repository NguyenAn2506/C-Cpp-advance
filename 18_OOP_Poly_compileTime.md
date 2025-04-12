# Đa hình compile time (OOP - Polymorphism – compile time)
***
Tiếp theo về tính đa hình compile time của tính đa hình trong OOP
***
## 1. Function Overloading
***
Như đã biết ở trong lập trình ngôn ngữ C đếu phân biêt các tên hàm, tên biến để có thể dễ quản lý, nên việc trùng tên khi đặt sẽ gây lỗi trong quá trình biên dịch

Nhưng ở trong C++ thì khác nó cho phép viết nhiều hàm có cùng tên với nhau nhưng phải khác nhau về số lượng tham số, hoặc kiểu dữ liệu của tham số của hàm, nó được gọi là nạp chồng hàm

### 1.1. khái niệm
***
●	Nạp chồng hàm (Function Overloading) là việc định nghĩa nhiều hàm cùng tên nhưng khác tham số trong cùng một phạm vi. 
●	Trình biên dịch sẽ chọn hàm phù hợp dựa trên kiểu và số lượng đối số khi gọi hàm.

### 1.2. Ví dụ
***
```cpp
void print(int a){ cout << "Integer: " << a << endl; }

void print(double b){ cout << "Double: " << b << endl; }

void print(string s){ cout << "String: " << s << endl; }

int main()
{
    print(5);
    print(3.14);
    print("Hello");
    return 0;
}
```
Như ví dụ trên thì đã khai báo tận 3 hàm print() nhưng mỗi hàm này đều khác về tham số hoặc là khác về số lượng tham số (đây là điều bắt buộc của nạp chồng hàm)

### 1.3. lưu ý 1
***
Vậy thì khi sử dụng thì làm sao để trình biên dịch phân biệt được đang gọi hàm nào ?. Để phân biệt thì sẽ dựa vào đối số được truyền vào và gọi hàm đó

=> 	Quá trình mà trình biên dịch xác định là hàm nào thì nó xảy ra ở quá trình biên dịch, cụ thể là ở tiền xử lý. (mặc dù không có macro nào hết)

Và điều này Chỉ áp dụng cho C++ thôi

### 1.4. lưu ý 2
***
Có 1 câu hỏi đặt ra là Bình thường khi viết hàm đều có quy định về tên hàm hoặc biến vậy thì việc sử dụng nạp chồng hàm được dùng để làm gì?

=>	Thường sử dụng khi ứng dụng viết cho các class, cụ thể là viết cho constructor luôn

=>	Tạo các constructor giống nhau vs công dụng khác nhau và việc sử dụng thì phụ thuộc vào đối tượng mình gọi ra

#### Ví dụ: tạo các constructor giống nhau nhưng công dụng khác nhau

```cpp
// 1 method có thể có nhiều input parameter, return type khác nhau
class TinhToan{
    private:
        int a;
        int b;
    public:
        int tong(int a, int b){
            return a+b;
        }
        double tong(int a, int b, int c, double d){
            return (double)a+b+c+d;
        }
        double tong(int a, double b){
            return (double)a+b;
        }
};

int main(int argc, char const *argv[])
{
    TinhToan th, th1, th2;
    cout << th.tong(2, 5) << endl;
    cout << th1.tong(2, 5, 7, 6.7) << endl;
    cout << th2.tong(2, 3.5) << endl;
    return 0;
}
```
***
## 2. Nạp chồng toán tử
***
Thông thường để thực hiện 1 phép toán trong số học hay logic thì ở trong C hay C++ ta có thể viết như sau
```cpp
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    int a = 10;
    int b = 10;
    int c= a+b;
    return 0;
}
```
Ta có thể sử dụng các phép toán số học hay các phép toán logic để thực hiện phép tính giữa các biến hay đối tượng với nhau 

=>	Các toán tử + - * / hoặc là AND OR XOR NOT, nhưng những toán tử này thì mặc định là kiểu dữ liệu nguyên thủy, đã được định nghĩa và đã có sẵn trong C và C++ rồi

Nhưng nếu là thực hiện bên trong các kiểu dữ liệu tự định nghĩa thì sao (ví dụ như class, struct, union,...)

```cpp
class phanso
{

};

int main(int argc, char const *argv[])
{
    int a = 10;
    int b = 10;
    int c= a+b;
    phanso p1, p2;
    phanso p3 = p1+ p2;     // lỗi
    return 0;
}
```
kết quả: lúc này sẽ sinh lỗi

![Image](https://github.com/user-attachments/assets/8fa4a380-e89e-4a9e-8933-deb83a211ffd)

Điều này có nghĩa là những toán tử  này không mặc định cho những biến hoặc những object (không mặc định cho những kiểu dữ liệu tự định nghĩa ra)

Vậy để có thể sử dụng những toán tử này thì ta phải định nghĩa lại những toán tử này lại

=> sử dụng nạp chống toán tử

### 2.1. khái niệm
***
●	Nạp chồng toán tử (Operator Overloading) là việc định nghĩa lại cách hoạt động của các toán tử (+, -, , =, ==, <<, >>,...) cho các kiểu dữ liệu do người dùng định nghĩa (class/struct).

●	**Cú pháp:**
```cpp
<return_type> operator symbol (parameter)
{
    // logic của toán tử
}
```
Trong đó lưu ý ở parameter thì ta chỉ được phép đưa vào 1 giá trị tham số thôi. Vì đơn giản là do bản chất của toán học thì lúc nào cũng là phép tính giữa 2 thành phần nên không thể đưa nhiều hơn 1 tham số được

### 2.2. ví dụ: phép cộng 2 phân số 
***
Để thực hiện phép cộng 2 phân số ngoài việc viết trức tiếp phân số ra theo phép / giữa 2 số a và b thì nếu đưa vào class thì ta không thể dùng toán tử / để làm phân số được nữa

**Lúc này ta sẽ sử dụng phép nạp chồng toán từ để thực hiện**

```cpp
class phanso
{
    private:
        int tuso;
        int mauso;

    public:
        phanso(int tuso = 0, int mauso = 1): tuso(tuso), mauso(mauso){}

        phanso operator + (const phanso other) const  // phép cộng 2 phân số
        {
            phanso ketqua;
            ketqua.tuso = phanso::tuso * other.mauso + phanso::mauso * other.tuso;
            ketqua.mauso = phanso::mauso * other.mauso;
            return ketqua;
        }
        void display()
        {
            cout << "Tu so: " << tuso << " Mau so: "<< mauso << endl;
        }

}
```
trong hàm main
```cpp
int main(int argc, char const *argv[])
{
    phanso p1(1,2); 
    phanso p2(2,3);
    phanso p3 = p1 + p2;

    p1.display();
    p2.display();
    p3.display();
    return 0;
}
```
=> class phép cộng phân số sẽ được gọi khi đối tượng đầu tiên được gọi p1(1)

Kết quả
```cpp
Tu so: 1 Mau so: 2
Tu so: 2 Mau so: 3
Tu so: 7 Mau so: 6
```

●	Nếu làm phép cộng 3 phân số thì nó sẽ đi từng cặp chung vs nhau không ảnh hưởng gì 

●	Vì bản chất thì phép cộng 3 phân số a b c thì cũng phải tính a+b trước sau đó lấy kết quả + c nên không ảnh hưởng đến chương trình

```cpp
int main(int argc, char const *argv[])
{
    phanso p1(1,2); 
    phanso p2(2,3);
    phanso p3 = p1 + p2 + p2;

    p1.display();
    p2.display();
    p3.display();
    return 0;
}
```
Kết quả
```cpp
Tu so: 1 Mau so: 2
Tu so: 2 Mau so: 3
Tu so: 33 Mau so: 18
```

### 2.3. các toán tử có thể định nghĩa lại
***
Qua đó ta đã thấy được việc đưa các toán tử số học hay logic vào trong các kiểu dữ liệu tự định nghĩa thì phải định nghĩa lại toán tử đó

**các toán tử có thể định nghĩa lại bao gồm**
```cpp
+	–	*	/	%	^	&	|	~	!	= (gán)	<	>	+=	-=	*=
/=	%=	^=	&=	|=	<<	>>	>>=		<<=	==	!=	<=	>=	&&	||	++
—	->*	,	->	[]	()	new	delete	new[]	delete[]
```

Và các toán tử không thể định nghĩa
```cpp
Toán tử . (chấm)
Toán tử phạm vi ::
Toán tử điều kiện ?:
Toán tử sizeof
```
### 2.4. từ khóa const trong nạp chống toán tử
***
Như công dụng của từ khóa const thì nó không cho phép chỉnh sửa giá trị tại địa chỉ mà nó lưu trữ vậy trong nạp chồng toán tử nó sẽ có công dụng không cho phép thay đổi giá trị của đối số dã được đưa vào trong hàm, làm thay đổi giá trị của kết quả đầu ra

```cpp
    phanso operator + (const phanso other) const        // phép cộng 2 phân số
    {
        phanso ketqua;
        ketqua.tuso = phanso::tuso * other.mauso + phanso::mauso * other.tuso;
        ketqua.mauso = phanso::mauso * other.mauso;
        return ketqua;
    }

    phanso operator * (const phanso other) const       // phép nhân 2 phân số
    {
        phanso ketqua;
        ketqua.tuso = phanso::tuso * other.tuso;
        ketqua.mauso = phanso::mauso * other.mauso;
        return ketqua;
    }
```
=> Const Thường được sử dụng cho các hàm display và getter để tránh thay đổi giá trị khi đọc, còn setter thì bình thường vì mình dùng nó để thay đổi nên không cần dùng

***
## 3. con trỏ this
***
### 3.1. khái niệm và đặc điểm
***
this là một con trỏ ẩn (ẩn danh) có sẵn trong mọi hàm thành viên (method) của class. Nó trỏ đến đối tượng hiện tại mà hàm đang được gọi trên.

-	Con trỏ này không cần tạo ra, vì nó đã ngầm tạo ra khi gọi class rồi
-	Địa chỉ của con trỏ this là địa chỉ của đối tượng gọi nó ra 

| **Đặc điểm** | **Chi tiết** |
|---|---|
| Chỉ xuất hiện trong hàm thành viên | **this** chỉ tồn tại trong hàm thành viên của class, không có trong các hàm static hoặc hàm global.|
| Trỏ đến đối tượng hiện tại	| **this** là con trỏ trỏ đến đối tượng gọi hàm hiện tại. |
| Có kiểu là con trỏ đến class		| Trong class **Person**, thì this có kiểu là **Person*** |
| Là **constant pointer** | Không thể thay đổi giá trị của con trỏ (**Person const *this**) | 
| Phân biệt biến thành viên và tham số cùng tên | **this→** giúp truy cập chính xác biến trong class. |
| Không dùng được trong **static function** | **Vì static function không gắn với bất kỳ object nào ⇒ không có this.** |

### 3.2. Ví dụ: phép nhân 2 phân số
***
```cpp
class phanso
{
    private:
        int tuso;
        int mauso;

    public:
        phanso(int tuso = 0, int mauso = 1): tuso(tuso), mauso(mauso){}

        // setter
        void setTuso(int tuso)
        {
            phanso phanso;
            // this = &phanso;
            this-> tuso = tuso;
        }
        phanso operator * (phanso other)        // phép nhân 2 phân số
        {
            phanso ketqua;
            // ketqua.tuso = phanso::tuso * other.tuso;
            ketqua.tuso = this->tuso * other.tuso;
            ketqua.mauso = this->mauso * other.mauso;
            return ketqua;
        }

        void display()
        {
            cout << "Tu so: " << tuso << " Mau so: "<< mauso << endl;
        }
};

int main(int argc, char const *argv[])
{
    phanso p1(1,2); 
    phanso p2(2,3);
    phanso p4 = p1 * p2;

    p1.display();
    p2.display();
    p4.display();
    return 0;
}
```
Kết quả
```cpp
Tu so: 1 Mau so: 2
Tu so: 2 Mau so: 3
Tu so: 2 Mau so: 6
```

***
## 4. tham trị (Pas by Value)
***
●	Tham trị là cách truyền một bản sao của biến vào hàm. Mọi thay đổi trong hàm không ảnh hưởng đến biến gốc bên ngoài.

Ví dụ
```cpp
void modify(int x){ x = x + 10;}

int main()
{
    int a = 5;
    modify(a);
    cout << a << endl; // Output: 5
}
```
Lúc học ở C có 1 ví dụ là swap(int a, int b), thì thực chất nó chỉ là sao chép giá trị của biến gốc (không tác động trong biến gốc) => tham trị

Để tác động đến biến gốc thì dùng con trỏ swap(int *a, int *b), bản chất con trỏ này thì vẫn làm tốn 1 địa chỉ trên RAM

```cpp
swap(int *a, int *b) // 0x01 = 0xf1; 0x02 = 0xf2
```
Qua C++ thì có 1 cách khắc phục để tác động đến những biến gốc nhưng không làm tiêu tốn địa chỉ trên RAM 
=> **tham chiếu**
***
## 5. tham chiếu
***
### 5.1. Khái niệm
***
●	Tham chiếu là cách tạo ra một tên khác để truy cập cùng một vùng nhớ của một biến đã tồn tại.

**Cú pháp**
```cpp
type& referenceName = variable;
```
Bản chất là không sử dụng con trỏ nữa mà sử dụng 1 tên khác 

Thay dấu * thành dấu &

**Trong đó**
- type: kiểu dữ liệu
- &: ký hiệu cho tham chiếu (khác với con trỏ)
- referenceName: tên tham chiếu
- variable: biến đã khai báo

#### Ví dụ 1
```cpp
int a = 10;
int& ref = a; // ref là một tham chiếu đến a
ref = 20;
std::cout << a << std::endl; // Kết quả: 20
```

hoặc 1 ví dụ khác
```cpp
void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}
```

#### Ví dụ 2: sử dụng trong class phân số => kết quả không thay đổi
```cpp
phanso operator + (const phanso &other) const        // phép cộng 2 phân số
        {
            phanso ketqua;
            ketqua.tuso = phanso::tuso * other.mauso + phanso::mauso * other.tuso;
            ketqua.mauso = phanso::mauso * other.mauso;
            return ketqua;
        }

        phanso operator * (const phanso &other) const       // phép nhân 2 phân số
        {
            phanso ketqua;
            ketqua.tuso = phanso::tuso * other.tuso;
            ketqua.mauso = phanso::mauso * other.mauso;
            return ketqua;
        }
```

### **Lưu ý:**

Mặc dù có tính năng nổi trội như vậy nhưng tham chiếu lại có 1 điều yếu đó là ta không thể gán giá trị mặc định trong setter hay constructor nữa 

vì bản chất của tham chiếu là không tạo thêm 1 bộ nhớ khác trên RAM mà khi tạo và không thể ghi giá trị trực tiếp (nó là địa chỉ)

![Image](https://github.com/user-attachments/assets/d869aca1-1e1c-4e79-8eb3-1fe6d77d253b)

Nên khi cần giá trị mặc định như hình trên thì không dùng tham chiếu còn nếu không cần giá trị mặc định thì dùng tham chiếu cho tiết kiệm bộ nhớ



