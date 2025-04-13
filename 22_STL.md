# Standard Template Library
***
## Giới thiệu
***
Standard Template Library ( STL) là một tập hợp các thư viện thiết kế để hỗ trợ lập trình tổng quát (generic programming). 

STL C++ cung cấp một tập hợp các template classes và functions để thực hiện nhiều loại cấu trúc dữ liệu và các thuật toán phổ biến. 

1 số cấu trúc dữ liệu như ngăn xếp stack, hàng đợi queue, ở C không có thư viện nên mình phải tự triển khai ns nhưng C++ thì mình có thể tự triển khai bằng class và template. Tuy nhiên ở C++ có thiết kế sẵn thư viện để người dùng
	
STL đã trở thành một phần quan trọng của ngôn ngữ C++ và làm cho việc lập trình trở nên mạnh mẽ, linh hoạt và hiệu quả.

Một số thành phần chính của STL:
- Containers (Cấu trúc dữ liệu) : (vector, … slide 2 ghi rõ )
- Iterators (Bộ lặp)
- Algorithms (Thuật toán)
- Functors & Lambda
***
## Container
***
Một container là một cấu trúc dữ liệu chứa nhiều phần tử theo một cách cụ thể. STL (Standard Template Library) cung cấp một số container tiêu biểu giúp lưu trữ và quản lý dữ liệu. 

Một vài containers phổ biến:
- Vector (mảng + template)
- List 
- Map (JSON)
- Array 
- stack, queue
***
## Phần 1: Vector
***
### 1.1.	Đặc điểm 
***
Vector là 1 trong những container quqan trọng nhất trong STL của C++. Nó cung cấp 1 mảng động với khả năng thay đổi kích thước 1 cách linh hoạt 

- std::vector là là một mảng động (dynamic array) trong C++. Nó tự động quản lý bộ nhớ, có thể tăng kích thước khi thêm phần tử mới, và cho phép truy cập ngẫu nhiên như mảng thông thường.
- Truy cập ngẫu nhiên: Việc truy cập các phần tử của vector có thể được thực hiện bằng cách sử dụng chỉ số
- Hiệu suất chèn và xóa; chèn và xóa phần tử ở cuối vector có hiệu suất tốt. Tuy nhiên chèn và xóa ở vị trí bất kỳ có thể đòi hỏi di chuyển 1 số phần tử
Vector thực chất là 1 mảng đưuọc cấp phát động kết hợp template để tạo thành thư viện

### 1.2.	Cú pháp khai báo
***
Vector được thiest kế dưới dạng 1 class (thay vì là 1 mảng động) vì class mới có thể có các hàm bên trong để sử dụng 

Cú pháp khai báo:
```cpp
// cách 0
vector<data_type> name;  // vector rỗng
// cách 1
vector<data_type> name(size);  // size là số lượng phần tử khởi tạo và giá trị khởi tạo mặc định là 0
// cách 2
vector<data_type> name(size, value);  // value: giá trị khởi tạo cho các phần tử
// cách 3
vector<data_type> name = {1, 2, 3, 4, 5};
```
#### Ví dụ 1: Khai báo cách 1
ở đay vec như là 1 đối tượng vậy vì vector vốn là 1 class 
```cpp
int main(int argc, char const *argv[])
{
    vector<int> vec(5); // cách 2: 5 phần tử -> 20 bytes
    
    return 0;
}
```
Khi khởi tạo thì ban đầu giá trị mặc định là 0
```cpp
int main(int argc, char const *argv[])
{
    vector<int> vec(5); // cách 2
    for(int i= 0; i<5; i++)
    {
        cout << vec[i] << " ";
    }
    return 0;
}
```
Kết quả
```cpp
0 0 0 0 0
```
#### Ví dụ 2: Khai báo cách 2

```cpp
int main(int argc, char const *argv[])
{
    // vector<int> vec(5); // cách 2
    vector<int> vec(5, 2); // cách 3
    for(int i= 0; i<5; i++)
    {
        cout << vec[i] << " ";
    }
    return 0;
}
```
Kết quả 
```cpp
2 2 2 2 2 
```
#### Ví dụ 3: Khai báo cách 3
Với những cách trên thì có nhược điểm là các phần tử khai báo đều có giá trị là như nhau
```cpp
int main(int argc, char const *argv[])
{
    // vector<int> vec(5); // cách 1
    // vector<int> vec(5, 2); // cách 2
    vector<int> vec = {1,2,3,4,5};  // cách 3

    vec.at(0) = 20;
    vec.at(2) = 50;

    // for(int i= 0; i<5; i++)
    for(int i= 0; i<vec.size(); i++)
    {
        cout << vec[i] << " ";   // or vec.at(i)
    }
    return 0;
}
```
kết quả 
```cpp
20 2 50 4 5
```
***
### 1.3. Phương thức của vector
***
#### 1.3.1. Một số method của vector
***
| Method | Chức năng |
| -----| -----|
| at()	| truy cập để đọc hoặc thay đổi giá trị phần tử của vector. (đọc và ghi) |
| size()	| trả về kích thước của vector. |
| resize()	| thay đổi kích thước của vector. |
| begin()	| Trả về một **iterator** trỏ đến địa chỉ phần tử **đầu tiên** của vector. |
| end()	| Trả về một iterator trỏ đến địa chỉ **sau phần tử cuối cùng** của vector. |

##### Ví dụ 1: hàm size() và at()
```cpp
int main(int argc, char const *argv[])
{
    // vector<int> vec(5); // cách 2
    vector<int> vec(5, 2); // cách 3

    vec.at(0) = 20;
    vec.at(2) = 50;

    // for(int i= 0; i<5; i++)
    for(int i= 0; i<vec.size(); i++)
    {
        cout << vec[i] << " ";   // or vec.at(i)
    }
    return 0;
}
```
##### Ví dụ 2: hàm resize()
```cpp
int main(int argc, char const *argv[])
{
    // vector<int> vec(5); // cách 1
    // vector<int> vec(5, 2); // cách 2
    vector<int> vec = {1,2,3,4,5};  // cách 3

    vec.at(0) = 20;
    vec.at(2) = 50;

    vec.resize(7);      // giống realloc ở C

    // for(int i= 0; i<5; i++)
    for(int i= 0; i<vec.size(); i++)
    {
        cout << vec[i] << " ";   // or vec.at(i)
    }
    return 0;
}
```
Kết quả
```cpp
20 2 50 4 5 0 0
```
#### 1.3.2. Duyệt vector
***
có 3 cách duyệt vector
```cpp
// cách 1: for thông thường
for (int i = 0; i < v.size(); ++i)      // cách thông thường
    cout << v[i] << " ";
// cách 2: for cải tiến
for (int x : v)   // for cải tiến - C++11
    cout << x << " ";
// cách 3: Iterator
for (auto it = v.begin(); it != v.end(); ++it)
    cout << *it << " ";
```
##### Ví dụ 1: for cải tiến
```cpp
int main(int argc, char const *argv[])
{
    vector<int> vec = {1,2,3,4,5};  // cách 3

    vec.at(0) = 20;
    vec.at(2) = 50;

    vec.resize(7);      // giống realloc ở C

    for(int i= 0; i<vec.size(); i++)
    {
        cout << vec[i] << " ";   // or vec.at(i)
    }

    cout << endl;
    for(int i : vec)
    {
        // cout << vec.at(i) << " ";   
        // lỗi terminate called after throwing an instance of 'std::out_of_range'
        // what():  vector::_M_range_check: __n (which is 20) >= this->size() (which is 7)
        cout << i << " "; 
    }

    return 0;
}
```
Lúc này i không còn là chỉ số nữa, i bây h khi duyệt qua thì i sẽ đóng vai trò như là giá trị của phần tử đó luôn

Kết quả
```cpp
20 2 50 4 5 0 0 
20 2 50 4 5 0 0
```

##### Ví dụ 2: hàm begin() và hàm end()
```cpp
/*
    1: 0x01 0x02 0x03 0x04 
    2:
    ...
    5: 0xa1 0xa2 0xa3 0xa4      0xa5
*/
```
Hàm begin sẽ đọc được địa chỉ của phần tử 1 (từ 0x01 đến 0x04) và trả về giá trị địa chỉ đầu tiên trong đó là 0x01
Còn hàm end sẽ trả về địa chỉ sau phần tử cuối cùng tức là 0xa5.
=> Cả begin và en đều trả về các giá trị iterator
=> Nôm na thì iterator là những con trỏ nên mình cần phải truyền vào địa chỉ và mình cần duyệt qua đại chỉ bắt đầu và đại chỉ kết thúc

```cpp
int main(int argc, char const *argv[])
{
    vector<int> vec = {1,2,3,4,5};  // cách 3

    vec.at(0) = 20;
    vec.at(2) = 50;

    vec.resize(7);      // giống realloc ở C

    // for(int i= 0; i<5; i++)
    for(int i= 0; i<vec.size(); i++)
    {
        cout << vec[i] << " ";   // or vec.at(i)
    }

    cout << endl;
    for(int i : vec)      // for cải tiến 
    {
        cout << i << " "; 
    }

    cout << endl;

    // for cách 3
    vector<int> :: iterator it;     // khai báo đối tượng dùng class iterator
    for(auto it = vec.begin(); it != vec.end(); it++)
    {
        cout << *it << " ";        // dải tham chiếu
    }

    return 0;
}
```

Kết quả
```cpp
20 2 50 4 5 0 0 
20 2 50 4 5 0 0
20 2 50 4 5 0 0
```

#### 1.3.3.	Một số method liên quan đến thêm/xóa phần tử của vector:
***
| Method | Chức năng |
| ---- | ---- |
| push_back()	| thêm phần tử vào vị trí cuối của vector. |
| pop_back()	| xóa phần tử ở vị trí cuối của vector. |
| insert()	| thêm phần tử vào vị trí bất kỳ. |
| erase()	| xóa phần tử ở vị trí bất kỳ hoặc xóa các phần tử trong phạm vi được chỉ định. |
| clear()	| xóa toàn bộ phần tử của vector. |

=> Không có các hàm tác động đến front 

##### Ví dụ 1: hàm push_back()
khi khai báo 1 vector rỗng thì không có giá trị nao trong đó cả và ta phải dùng các hàm push, pop, insert,... để thêm phần tử vào (mà còn không có hàm dành cho front nữa ) nhưng như thế thì nó khong liên kết chung vs nhau
```cpp
int main(int argc, char const *argv[])
{
    vector<int> vec;    // khai báo vector rỗng
    vec.push_back(1);   // 1
    vec.push_back(2);   // 1 2
    vec.push_back(3);   // 1 2 3 
    vec.push_back(4);   // 1 2 3 4 
    vec.push_back(5);   // 1 2 3 4 5

    for(int i= 0; i<vec.size(); i++)
    {
        cout << vec[i] << " ";   // or vec.at(i)
    }
    
    return 0;
}
```
Kết quả
```cpp
1 2 3 4 5 
```

##### Ví dụ 2: hàm insert()
hàm insert ở trong vector khác với insert trong single linked list, rằng ở đây là truyền vào địa chỉ chứ không phải là vị trí 

```cpp
int main(int argc, char const *argv[])
{
    vector<int> vec;    // khai báo vector rỗng
    vec.push_back(1);   // 1
    vec.push_back(2);   // 1 2
    vec.push_back(3);   // 1 2 3 
    vec.push_back(4);   // 1 2 3 4 
    vec.push_back(5);   // 1 2 3 4 5

    // vec.insert(0, 10);  // lỗi no matching
    vec.insert(vec.begin(), 10);        // push_front()
    vec.insert(vec.end(), 30);      // push_back()


    for(int i= 0; i<vec.size(); i++)
    {
        cout << vec[i] << " ";   // or vec.at(i)
    }

    return 0;
}
```
Kết quả
```cpp
10 1 2 3 4 5 30
```
###### Ví dụ 2.1 thêm vào ở vị trí bất kỳ
Nhưng đó là thêm ở đầu và cuối, nếu muốn thêm ở vị trí thử 2 3 4 thì mình có thể +1 lên cho vị trí thứ 2

Giả dụ như là
```cpp
/*
    1: 0x01 0x02 0x03 0x04 
    2:
    ...
    5: 0xa1 0xa2 0xa3 0xa4      0xa5
*/
```
Thì lúc này từ vị trí begin là vị trí đầu tiên của vector + 1 lên theo kiểu int là 4byte thì nó sẽ lên 0x05

```cpp
int main(int argc, char const *argv[])
{
    vector<int> vec;    // khai báo vector rỗng
    vec.push_back(1);   // 1
    vec.push_back(2);   // 1 2
    vec.push_back(3);   // 1 2 3 
    vec.push_back(4);   // 1 2 3 4 
    vec.push_back(5);   // 1 2 3 4 5

    // vec.insert(0, 10);  // lỗi no matching
    vec.insert(vec.begin(), 10);        // push_front()
    vec.insert(vec.end(), 30);      // push_back()
    vec.insert(vec.begin() + 1, 15);  
    vec.insert(vec.end() - 1, 40);       

    for(int i= 0; i<vec.size(); i++)
    {
        cout << vec[i] << " ";   // or vec.at(i)
    }

    return 0;
}
```

Kết quả
```cpp
10 15 1 2 3 4 5 40 30
```
##### Ví dụ 3: hàm pop_back() và erase()
Tương tự với 2 hàm push_back() và insert()
```cpp
int main(int argc, char const *argv[])
{
    vector<int> vec;    // khai báo vector rỗng
    vec.push_back(1);   // 1
    vec.push_back(2);   // 1 2
    vec.push_back(3);   // 1 2 3 
    vec.push_back(4);   // 1 2 3 4 
    vec.push_back(5);   // 1 2 3 4 5

    // vec.insert(0, 10);  // lỗi no matching
    vec.insert(vec.begin(), 10);        // push_front()
    vec.insert(vec.end(), 30);      // push_back()
    vec.insert(vec.begin() + 1, 15);  
    vec.insert(vec.end() - 1, 40);     
    // vector lúc này  10 15 1 2 3 4 5 40 30 

    vec.pop_back();
    vec.erase (vec.begin() + 2);

    for(int i= 0; i<vec.size(); i++)
    {
        cout << vec[i] << " ";   // or vec.at(i)
    }

    return 0;
}
```
Kết quả
```cpp
10 15 2 3 4 5 40
```
###### Ví dụ 3.1: xóa nhiều phần tử
Ngoài ra erase nngoaif việc xóa tại 1 vị trí bất kì thì nó còn giúp xóa nhiều phần tử cùng 1 lúc

Nhưng để làm được điều này thì trước đó phải quy định phạm vi trước khi xóa

```cpp
int main(int argc, char const *argv[])
{
    vector<int> vec;    // khai báo vector rỗng
    vec.push_back(1);   // 1
    vec.push_back(2);   // 1 2
    vec.push_back(3);   // 1 2 3 
    vec.push_back(4);   // 1 2 3 4 
    vec.push_back(5);   // 1 2 3 4 5

    // vec.insert(0, 10);  // lỗi no matching
    vec.insert(vec.begin(), 10);        // push_front()
    vec.insert(vec.end(), 30);      // push_back()
    vec.insert(vec.begin() + 1, 15);  
    vec.insert(vec.end() - 1, 40);     
    // 10 15 1 2 3 4 5 40 30 

    // vec.pop_back();
    // vec.erase (vec.begin() + 2);
    vec.erase(vec.begin(), vec.begin() + 3);

    for(int i= 0; i<vec.size(); i++)
    {
        cout << vec[i] << " ";   // or vec.at(i)
    }

    return 0;
}
```
Kết quả
```cpp
2 3 4 5 40 30
```
***
## Phần 2: Double Linked List
***