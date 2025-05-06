# Design Pattern
***
## I. Khái niệm Design Pattern
***
Design Patterns là các giải pháp tổng quát cho các vấn đề phổ biến trong phát triển phần mềm. Chúng là một dạng "công thức" giúp các lập trình viên xử lý các tình huống thường gặp trong quá trình thiết kế. (code mẫu hướng dẫn cho lập trình viên)

Một số vấn đề thường gặp:
- Khó kiểm soát việc tạo đối tượng.
- Khó mở rộng hoặc thay đổi hành vi.
- Giao tiếp giữa các modules phức tạp.
- Lặp code hoặc logic tương tự nhau.

Logic xử lý và giao diện người dùng (UI) bị trộn lẫn.

## II. Phân loại Design Pattern
***
Design Patterns thường được chia thành các loại sau:
- Creational Patterns (Mẫu khởi tạo): Quản lý việc khởi tạo đối tượng (VD: Singleton, Factory).
- Structural Patterns (Mẫu cấu trúc): Tổ chức cấu trúc của các lớp và đối tượng (VD: Decorator, Adapter, Composite).
- Behavioral Patterns (Mẫu hành vi): Xác định cách các đối tượng tương tác với nhau (VD: Observer, MVP,  MVC, Strategy).

## Phần 1: Singleton Pattern 
***
### 1.1.	Đặt vấn đề 
***
**Đặt vấn đề**: Khi lập trình với GPIO (ODR), Timer,... nó sẽ có địa chỉ cố định. Khi khởi tạo nhiều object thì object sẽ vào những địa chỉ trên để ghi giá trị. Khi khởi tạo nhiều object thì tốn nhiều tài nguyên trên RAM. Vậy có cách nào chỉ khởi tạo một lần duy nhất, không cần tốn bộ nhớ cấp phát khi sử dụng lại hay không?

### 1.2.	Khái niệm
***
Singleton là một mẫu thiết kế thuộc nhóm Creational (mẫu khởi tạo), nó đảm bảo rằng một class chỉ có một đối tượng duy nhất được tạo ra, và cung cấp một phương thức để truy cập đến đối tượng đó từ bất kỳ đâu trong chương trình.

Singleton thường sử dụng cho những hệ thống chỉ cần một phiên bản duy nhất như: kết nối cơ sở dữ liệu, bộ nhớ đệm (cache), logger để ghi log, hoặc cấu hình hệ thống.

### 1.3. Các thành phần chính
***
Các thành phần chính của Singleton:

- Private Constructor: 
    - Đảm bảo rằng không ai có thể khởi tạo đối tượng từ bên ngoài class.
- Static Instance: 
    - Đối tượng tĩnh duy nhất của class.
    - Không thể tạo ra nhiều hơn một đối tượng của class Singleton.
- Static Method: 
    - Phương thức để truy cập đến đối tượng duy nhất từ mọi nơi trong chương trình.

### 1.4. Ví dụ: khởi tạo 1 đối tượng duy nhất
***
Ý nghĩa là khi tạo lần đầu tiên thì nó phải lưu được giá trị địa chỉ của lần đầu tiên, để khi tạo lần 2 thì mình đem địa chỉ đó ra lưu tiếp
-	Phải tạo con trỏ để lưu
-	Kiểm tra con trỏ lưu trữ địa chỉ có đang null không, không thì về trả về giá trị địa chỉ cũ, còn có thì cấp phát địa chỉ mới

```cpp
// singleton: chỉ tạo 1 đối tượng duy nhất

class GPIO
{
    private:
        GPIO(){}

        static GPIO *instance;      // vì hàm create_obj đang là static

    public:
        // static void create_obj()     // trả về địa chỉ nên không dùng void được
        static GPIO* create_obj()
        {
            // GPIO *gpio = new GPIO();
            if(instance == nullptr)
            {
                instance = new GPIO();      // 0x01
            }
            return instance;    // 0x01
        }
};

// khởi tạo static cho instance
GPIO *GPIO::instance = nullptr;

int main(int argc, char const *argv[])
{
    // GPIO gpio1, gpio2, gpio3;  
    GPIO::create_obj();     // 0x01
    GPIO::create_obj();
    GPIO::create_obj();
    GPIO::create_obj();
    return 0;
}
```
### 1.5. Ưu. nhược điểm của Singleton
***
#### Ưu điểm
- Tiết kiệm bộ nhớ
- Truy cập bộ nhớ dễ dàng

#### Nhược điểm:
-	Vi phạm quy tắc đơn trách nhiệm (SRP) (vì nó vừa phải tạo đối tượng mà còn phải quản lý đối tượng đó để người dùng không thể tạo nhiều đối tượng dược, và chỉ được tạo 1 lần duy nhất)
-	Khó mở rộng chương trình 
-	Vì đang dùng cấp phát động nên cần phải thu hồi địa chỉ đó, lứu ý là nó không có thu hồi tự động được thông qua destructor mà phải sử dụng 1 hàm static

***

## Phần 2: Observer Pattern
***
### 2.1. Đặt vấn đề
***
**Đặt vấn đề**: Ví dụ có 1 cảm biến đọc giá trị và có các hành động kèm theo là hiển thị LCD, điều khiển bật/tắt quạt,....thì có cách nào khi đọc dữ liệu cảm biến thì tự động cập nhật giá trị cho các hành động trên không?

### 2.2. Khái niệm
***
Observer là một mẫu thiết kế thuộc nhóm Behavioral (mẫu hành vi), nó định nghĩa một mối quan hệ phụ thuộc one-to-many giữa các đối tượng, nghĩa là khi một đối tượng thay đổi trạng thái (Subject), tất cả các đối tượng phụ thuộc (Observers) vào nó sẽ được tự động thông báo và cập nhật.

Kiến trúc:

![Image](https://github.com/user-attachments/assets/7544bf96-4a05-4f5c-b084-4db2e8c1b537)

Các object nhỏ phải được đăng kí lên trên subject thì mới có thể update được dữ liệu mới từ subject

### 2.3. Các thành phần chính
***
Có 4 thành phần chính: 

**Subject**

- Đối tượng giữ trạng thái và chịu trách nhiệm thông báo cho các Observer về sự thay đổi.
- Cung cấp phương thức để thêm, xóa, và thông báo Observer.

**Observer**

- Một interface (class) chung định nghĩa phương thức cập nhật dữ liệu.
- Observer sẽ thực hiện hành động khi nhận được thông báo từ Subject.

=> Subject và Observer là 1 interface liên hệ lẫn nhau, hay nói 1 cách khác thì chúng là những hàm thuần ảo, mà hàm thuẩn ảo thì chưa biết chính xác nội dung nên phải định nghĩa ra, cần phải có những class con kế thừa để định nghĩa (Concrete)

**Concrete Observer**

- Là các class kế thừa từ Observer và thực hiện phương thức cập nhật dữ liệu.
- Các class này sẽ nhận thông báo từ Subject và xử lý thông tin.
	
**Concrete Subject**

- Là class triển khai cụ thể của Subject.
- Chứa logic để quản lý danh sách Observer và trạng thái của Subject.

### 2.4. Class Diagram
***
![Image](https://github.com/user-attachments/assets/20d3aed0-aeb0-4648-bdff-650c24ffa237)

### 2.5. Ví dụ
***
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Interface for Observers
class IObserver
{
    public:
        virtual void update(double temp, double humidity) = 0;
};

// Interface for Subject
class ISubject 
{
    protected:
        virtual void notifyObserver() = 0;
    public:
        virtual void registerObserver(IObserver * o) = 0;
        virtual void removeObserver(IObserver * o) = 0;
};

//  Triển khai các phương thức của Subject
class SensorManager  : public ISubject
{
    private:
        double temperature = 0;
        double humidity = 0;
        vector <IObserver *> observers;
    protected:
        void notifyObserver() 
        {
            for(const auto & ob : observers)
            {
                ob->update(temperature, humidity);
            }
        }
    public:
        void registerObserver(IObserver * o) 
        {
            observers.push_back(o);
        }
        void removeObserver(IObserver * o) 
        {
            // tìm ra đối tượng => xóa
            auto observer = find(observers.begin(), observers.end(), o);

            if(observer != observers.end())
            {
                observers.erase(observer);
            }
        }
        void setData(double temp,  double humi)
        {
            temperature = temp;
            humidity = humi;
            notifyObserver();
        }
};

// Triển khai các Observer 
// Display on LCD
class Display : public IObserver
{
    public: 
        void update(double temp, double humidity)
        {
            cout<< "Display: Temperature: " <<  temp << " - Humidity: " << humidity << endl;
        }
};

// Logger Data
class Logger : public IObserver
{
    public: 
        void update(double temp, double humidity)
        {
            cout<< "Logger: Temperature: " <<  temp << " - Humidity: " << humidity << endl;
        }
};

int main(int argc, char const *argv[])
{
    SensorManager *sensor = new SensorManager();

    Display *display = new Display();
    Logger *logger = new Logger();

    // đăng kí màn hình và logger
    sensor->registerObserver(display);
    sensor->registerObserver(logger);

    sensor->setData(100, 50);
    sensor->setData(25,50);

    sensor->removeObserver(display);
    sensor->setData(30,20);
    return 0;
}
```

Kết quả
```cpp
Display: Temperature: 100 - Humidity: 50
Logger: Temperature: 100 - Humidity: 50
Display: Temperature: 25 - Humidity: 50
Logger: Temperature: 25 - Humidity: 50
Logger: Temperature: 30 - Humidity: 20
```

### 2.6. Đặc điểm chính 
***
**Mối quan hệ giữa Subject và Observer:**
- Subject giữ một danh sách các Observer. 
- Các Observer đăng ký nhận thông báo từ Subject khi có sự thay đổi trạng thái. 
- Observer có thể thêm, xóa hoặc cập nhật trong danh sách này.

**Tự động thông báo (Push Notification):**
- Khi trạng thái của Subject thay đổi, nó sẽ tự động thông báo cho tất cả các Observer đã đăng ký. 
- Các Observer không cần chủ động kiểm tra trạng thái của Subject mà sẽ nhận thông báo ngay khi có thay đổi.

**Tính linh hoạt và mở rộng:**
- Observer Pattern cho phép dễ dàng thêm hoặc xóa các Observer mà không cần thay đổi Subject.
- Observer có thể dễ dàng ngừng nhận thông báo từ Subject bằng cách hủy đăng ký, giúp kiểm soát tốt hơn việc quản lý tài nguyên và sự kiện trong hệ thống.

**Nhiều Observer có thể theo dõi một hoặc nhiều Subject:**
- Nhiều Observer có thể cùng theo dõi một Subject. Điều này cho phép cùng một sự kiện trong Subject có thể ảnh hưởng đến nhiều đối tượng khác nhau.
- Một Observer có thể đăng ký để nhận thông báo từ nhiều Subject khác nhau, và mỗi Subject sẽ thông báo cho Observer khi có sự thay đổi liên quan.

### 2.7. Ưu, nhược điểm của Observer Pattern
***
#### Ưu điểm
-	Được tách biệt ra Subject và Observer, có phụ thuộc nhưng độc lập với nhau
-	Dễ mở rộng hơn

=> Tuân thủ nguyên tắc OCP, ISP
=> Vì Subejct được sử dụng chung nên không vi phạm quy tắc SRP (đơn trách nhiệm)
	
#### Nhược điểm
-	Cập nhật nhiều nên tốn tài nguyên (Nhiều observer thì subject sẽ phải cập nhật liên tục)
-	Gây ra memory leak (do các obsserver dùng cấp phát động để tạo nên khi mà xóa đi thì nó có thể nhảy vào vùng nhớ không xác định, khắc phục thì sẽ được học trong bài smart pointer)

***

## Phần 3: Decorator Pattern
***
### 3.1. Đặt vấn đề
***
Khi làm việc với thiết bị ngoại vi, ví dụ như cảm biến nhiệt độ, đôi khi bạn sẽ cần thêm tính năng mới vào cảm biến này mà không muốn thay đổi mã nguồn gốc hoặc cấu trúc của nó. Chẳng hạn, cảm biến nhiệt độ ban đầu chỉ trả về giá trị nhiệt độ, nhưng bạn lại muốn:

●	Ghi lại dữ liệu nhiệt độ vào log để có thể xem lại sau này.
●	Kiểm tra xem nhiệt độ có vượt ngưỡng an toàn không.
●	Hiệu chỉnh nhiệt độ nếu cảm biến không chính xác hoàn toàn.

Một cách phổ biến để thêm tính năng là tạo các lớp con kế thừa từ lớp cảm biến gốc, sau đó viết lại hoặc thêm tính năng mới vào từng lớp con (làm vậy để tránh vi phạm quy tắc OCP). Tuy nhiên, nếu làm vậy, bạn sẽ phải tạo rất nhiều lớp kế thừa khác nhau, dẫn đến mã nguồn phức tạp, khó kiểm soát và bảo trì. 

Hoặc là nếu có nhiều class / Interface khác nhau nhưng đều cần các tính năng giống nhau thì ta lại phải viết các hàm kế thừa với nội dung giống nhau cho 2 class cha đó (thành ra là lại lặp code)

Làm thế nào để thêm các hành vi mới vào đối tượng hiện có mà không cần thay đổi cấu trúc của nó hoặc tạo ra các lớp con mới (không chỉ thêm cho 1 đối tượng cụ thể nữa, mà là thêm đối tượng cho 1 Interface / class mà chưa biết trước được) ?

### 3.2. Khái niệm
***
●	Decorator Pattern là một mẫu thiết kế thuộc nhóm structural patterns, cho phép thêm các chức năng hoặc hành vi mới cho một đối tượng mà không cần thay đổi cấu trúc của lớp đối tượng đó. 

●	Decorator Pattern giúp mở rộng tính năng của các đối tượng bằng cách bao bọc (wrapping) chúng trong các lớp decorator đặc biệt.

### 3.3. Các thành phần chính
***
Gồm có 4 thành phần chính:

**Component:** Định nghĩa giao diện (interface) chung cho các đối tượng mà Decorator và đối tượng thực tế (Concrete Component) đều tuân theo.

**Concrete Component:** Lớp triển khai cụ thể của Component. Đây là đối tượng gốc cần được thêm chức năng (decorated).

**Decorator:** 
- Lớp cơ sở trừu tượng cho tất cả các Decorator. Nó chứa một tham chiếu tới một Component (thường là con trỏ hoặc đối tượng) để thêm chức năng vào.
- Thực hiện ủy quyền (delegation) để gọi các phương thức từ Component.

**Concrete Decorator:** Các lớp cụ thể kế thừa từ Decorator để thêm chức năng mới cho Component (triển khai các tính năng cho đối tượng).

### 3.4. Class Diagram
***
![Image](https://github.com/user-attachments/assets/e7732afd-9d47-4ee4-980d-69ec2084f6fb)

Các decorator không vi phạm quy tắc đơn trách nhiệm vì các hàm function() đều được gọi lại từ Component nên trách nhiệm của Decorator chỉ là additional_function() thôi

### 3.5. Ví dụ
***
```cpp
#include <iostream>
#include <string>
using namespace std;

// Interface cho đối tượng cần thêm tính năng
class IShape
{
    protected:
        string color;

    public:
        IShape(const string &color_ = "black") : color(color_) {}

        virtual void draw() const = 0;

        virtual double calculateArea() const= 0;
};

// Concrete Component
class Circle : public IShape
{
    private:
        double radius;

    public:
        Circle(double r, const string &color_ = "blue")
            : radius(r), IShape(color_) {}

        void draw() const override
        {
            cout << "Drawing a Circle in color " << color << endl;
        }

        double calculateArea() const override
        {
            return 3.14 * radius * radius;
        }
};

//  class quản lý những tính năng chung 
class ShapeDecorator : public IShape
{
    protected:
        IShape *wrapShape;

    public:
        ShapeDecorator(IShape * shape) : wrapShape(shape) {}

        // gọi lại các tính năng đã có sẵn, sau đó mới thêm mới
        virtual void draw() const override
        {
            wrapShape->draw();
        }
        virtual double calculateArea() const override
        {
            return wrapShape->calculateArea();
        }
};

// thiết kế các tính năng mới
class Border : public ShapeDecorator
{
    private:
        double borderWidth;
    public:
        Border(IShape * shape, double width)
            : ShapeDecorator(shape), borderWidth(width) {}

        void draw() const override
        {
            wrapShape->draw();
            drawBorder();
        }
        void drawBorder() const
        {
            cout << " with border width of " << borderWidth << endl; 
        }
};

class Shadow : public ShapeDecorator
{
    private:
        string shadowColor;
    public:
        Shadow(IShape * shape, string color)
            : ShapeDecorator(shape), shadowColor(color){}
        void draw() const override
        {
            wrapShape->draw();
            drawShadow();
        }
        void drawShadow() const
        {
            cout << " with shadow with color " << shadowColor << endl;
        }
};

int main(int argc, char const *argv[])
{
    IShape *shape = new Circle(5);      // chỉ có 2 tính năng

    shape->draw();
    cout << shape->calculateArea();

    cout<< endl;

    shape = new Shadow(shape, "yellow");    // có 3 tính năng (2 tính năng trước + 1 tính năng mới)
    shape = new Border(shape, 2);           // có 4 tính năng (3 tính năng trước + 1 tính năng mới)

    shape->draw();
    return 0;
}
```
Kết quả
```cpp
Drawing a Circle in color blue
78.5
Drawing a Circle in color blue
 with shadow with color yellow
 with border width of 2
```
### 3.6. Đặc điểm chính
***
**Tính linh hoạt:** Decorator Pattern cho phép thêm hành vi mới vào đối tượng một cách linh hoạt mà không làm thay đổi các đối tượng khác.

**Tính mở rộng:** Decorator Pattern cho phép mở rộng tính năng mà không cần thay đổi mã gốc.

**Dễ bảo trì:** Bạn có thể dễ dàng bổ sung hoặc thay thế các tính năng bằng cách thay đổi các decorator mà không ảnh hưởng đến các lớp khác.

**Giảm sự phức tạp của kế thừa:** Thay vì tạo ra nhiều lớp con để mở rộng hành vi, Decorator Pattern cho phép kết hợp các hành vi một cách linh hoạt bằng cách xếp chồng các decorator.

### 3.7. Ưu, nhược điểm của Decorator Pattern
***
**Ưu điểm:**
-	Do tuân theo quy tắc đóng mở nên nó sẽ dễ mở rộng những tính năng thêm vào
-	Tái sử dụng lại nhiều lần

**Nhược điểm**
-	Phải tuân theo thứ tự đề ra thêm vào, không linh hoạt
-	Lồng nhiều lớp với nhau  đọc bị rối, phức tạp

***

## Phần 4: Factory Pattern
***
Factory Pattern được nằm trong cùng nhóm với Singleton trong nhóm Creational Patterns: tức là quản lý việc khởi tạo đối tượng. Tuy nhiên thì Singleton là khởi tạo cho 1 đối tượng, còn Factory Pattern thì nó cung cấp cơ chế chung để khởi tạo đối tượng

### 4.1.	Đặt vấn đề:
***
**Đặt vấn đề:** Giả sử bạn có một hệ thống làm việc với nhiều loại cảm biến như cảm biến nhiệt độ, độ ẩm, và áp suất. Mỗi loại cảm biến sẽ có một cách khởi tạo và đọc dữ liệu riêng. Nếu chúng ta cần viết mã cho mỗi loại cảm biến, sẽ phải nhớ tên cụ thể của từng loại và cách khởi tạo chúng. Làm sao để tạo ra một cơ chế chung để khởi tạo cho các loại cảm biến?

### 4.2.	Khái niệm
Factory Pattern là một mẫu thiết kế thuộc nhóm Creational patterns, cho phép bạn ẩn đi việc khởi tạo đối tượng cụ thể, thay vào đó cung cấp một cơ chế chung để khởi tạo. 

Khi thực hiện 1 class để thực hiện cho công việc thì đối tượng sẽ truy cập vào class để sử dụng các phần tử đẻ sử dụng hoặc đọc code nhưng nếu ta không muốn dối tượng đọc được chi tiết bên trong class thì sao? Ta chỉ cần thực hiện 1 class khác ở bên ngoài, và class này dùng để khởi tạo đối tượng cho các class khác => ẩn đi việc khởi tạo đối tượng cụ thể

```cpp
#include <iostream>

class Temperature
{
    // chỉ tiết của đối tượng
};

class Sensor
{
    // khởi tạo đối tượng
};

int main(int argc, char const *argv[])
{
    Temperature *temp = new Temperature();
    return 0;
}
```
Factory Pattern chia làm 3 loại:

- Simple Factory
- Factory Method
- Abstract Factory

### 4.3. Simple Factory
***
#### 4.3.1. Khái niệm:
***
Simple Factory không khởi tạo trực tiếp các đối tượng mà sử dụng một phương thức hoặc một lớp trung gian (Factory) để quyết định loại đối tượng nào sẽ được khởi tạo dựa trên tham số đầu vào hoặc logic cụ thể.

#### 4.3.2. Thành phần chính
***
Các thành phần chính:

- **Product:** interface mà các class con sẽ kế thừa.
- **Concrete Product:** Các lớp con cụ thể được tạo ra từ Product.
- **Factory:** Một class hoặc hàm đảm nhiệm việc tạo ra các đối tượng.

#### 4.3.3. Class Diagram
***
![Image](https://github.com/user-attachments/assets/328698b2-4534-430f-a1a1-d044282baf5d)

#### 4.3.4. Ví dụ:
***
```cpp
#include <iostream>
#include <string>

using namespace std;

// Abstract class
class Sensor{
    public:
        virtual void readData() = 0;
};

// Temperature class
class TemperatureSensor : public Sensor{
    public:
        void readData() override {
            cout<<"reading temp data: "<<endl;
        }
};

// Humidity class
class HumiditySensor : public Sensor{
    public:
        void readData() override {
            cout<<"reading humidity data: "<<endl;
        }
};

// Factory class (Creator)
class SensorFactory{
    public:
        static Sensor* createSensor(const string& sensorType){
            if(sensorType == "temp"){
                return new TemperatureSensor();     // trả về đối tượng TemperatureSensor
            }
            else if (sensorType == "humi"){
                return new HumiditySensor();        // trả về đối tượng PressureSensor
            }
            else{
                return nullptr;                     // trả về con trỏ null
            }
        }
};

int main(int argc, char const *argv[])
{
    Sensor* sensor = SensorFactory::createSensor("humi");
    sensor->readData();
    return 0;
}
```

Kết quả
```cpp
reading humidity data:
```

Khi người dùng tạo đối tượng, người dùng chỉ biết được các tham số cần truyền vào thôi còn chi tiết bên trong thì người dùng không biết được => ẩn đi 

#### 4.3.5. Đặc điểm chính
***
- **Tính trừu tượng:** Factory Pattern ẩn đi chi tiết về cách các đối tượng được tạo ra, giúp chương trình tách biệt giữa việc khởi tạo đối tượng và việc sử dụng đối tượng đó.
- **Tính mở rộng:** Factory Pattern giúp hệ thống dễ dàng mở rộng khi cần thêm các lớp con mới mà không làm ảnh hưởng đến mã nguồn hiện có.
- **Tính linh hoạt:** Khi hệ thống cần thay đổi hoặc thêm mới các đối tượng cụ thể, chúng ta chỉ cần cập nhật factory mà không cần sửa đổi mã nguồn chính.
- **Giảm sự phụ thuộc:** Factory Pattern giúp mã nguồn giảm sự phụ thuộc vào các lớp cụ thể, từ đó tăng tính module và khả năng tái sử dụng.

#### 4.3.6. Ưu, nhược điểm của Simple Factory
***
##### Ưu điểm
-	Đơn giản, dễ triển khai

##### Nhược điểm
-	Vi phạm quy tắc OCP (quy tắc đóng mở)
-	Khó mở rộng do đều phải thông qua 1 class khởi tạo đối tượng
-	Phải biết được số lượng cảm biến cụ thể rồi mới có thể sử dụng được => chỉ sử dụng cho những hệ thống nhỏ 

### 4.4. Factory Method
***
Như ở 4.3. thì single Factory thì chỉ sử dụng cho những hệ thống nhỏ, và biết được cụ thể số lượng cảm biến, nhưng nếu đối với các hệ thống phức tạp thì số lượng cảm biến không biết trước được thì sao? 

=> Sử dụng Factory method 

#### 4.4.1. Khái niệm
***
Factory Method được dùng để tạo đối tượng mà không chỉ định chính xác lớp cụ thể sẽ được tạo ra, thay vào đó để cho các lớp con quyết định lớp nào sẽ được khởi tạo.

#### 4.4.2. Các thành phần chính
***
- **Product:** Giao diện chung cho tất cả object được tạo.
- **Concrete Product:** Các lớp con cụ thể được tạo ra từ Product.
- **Creator:** Khai báo phương thức khởi tạo đối tượng.
- **Concrete Creator:** triển khai phương thức trên để tạo ra đối tượng cụ thể.

#### 4.4.3. Class Diagram
***
![Image](https://github.com/user-attachments/assets/49785f12-d9d5-493f-ae55-5158b0f9dcf1)

#### 4.4.4. Ví dụ
***
```cpp
#include <iostream>
using namespace std;

// Interface for Sensor
class ISensor
{
    public:
        virtual void read_data() = 0;
};

// Temperature
class Temperature : public ISensor
{
    public:
        void read_data()
        {
            cout << "reading temperature data\n";
        }
};

// Pressure
class Pressure : public ISensor
{
    public:
        void read_data()
        {
            cout << "reading pressure data\n";
        }
};

// Humidity
class Humidity : public ISensor
{
    public:
        void read_data()
        {
            cout << "reading humidity data\n";
        }
};

// Class chứa cơ chế khởi tạo đối tượng
class SensorFactory
{
    public:
        virtual ISensor* createSensor() = 0;
};

// Class đảm nhận triển khai đối tượng Temperature
class TempFactory : public SensorFactory
{
    public:
        ISensor* createSensor()
        {
            return new Temperature();
        }
};

// Class đảm nhận triển khai đối tượng Pressure
class PressFactory : public SensorFactory
{
    public:
        ISensor* createSensor()
        {
            return new Pressure();
        }
};

// Class đảm nhận triển khai đối tượng Humidity
class HumiFactory : public SensorFactory
{
    public:
        ISensor* createSensor()
        {
            return new Humidity();
        }
};

int main()
{
    SensorFactory *create = new TempFactory();
    ISensor *sensor = create->createSensor();
    sensor->read_data();

    create = new PressFactory();
    sensor = create->createSensor();
    sensor->read_data();

    return 0;
}
```

Kết quả
```cpp
reading temperature data
reading pressure data
```

#### 4.4.5.	Ưu nhược điểm của Factory Method
***
##### Ưu điểm 
- dễ mở rộng
- sử dụng trong hệ thống lớn
##### Nhược điểm
- làm tăng số lượng class
- Phức tạp trong sử dụng

***

## Phần 5: MVP Pattern
***
Các Design Pattern thường được sử dụng: MVP, MVC, MVVP,..

### 5.1. Đặt vấn đề
***
Giả sử bạn phát triển một ứng dụng nhúng đơn giản cho màn hình cảm ứng để điều khiển thiết bị, trong đó giao diện người dùng (UI) bao gồm các nút điều khiển thiết bị và logic điều khiển trực tiếp được viết chung với giao diện. 

Vì thế, khi bạn cần thay đổi cách giao diện hiển thị hoặc cách thiết bị phản ứng với lệnh, bạn phải sửa cả mã giao diện lẫn mã điều khiển. Điều này có thể dễ gây lỗi, đặc biệt khi dự án lớn lên, vì các thành phần logic và giao diện không được tách biệt rõ ràng. Làm sao để khắc phục?

### 5.2. Khái niệm:
***
- MVP (Model - View - Presenter) là một mẫu thiết kế thuộc nhóm Behavioral, phổ biến trong lập trình giao diện người dùng (UI) và phát triển ứng dụng. 
- MVP tách biệt các thành phần của ứng dụng thành ba phần chính: Model, View, và Presenter. Cấu trúc này giúp dễ dàng quản lý, kiểm thử, và bảo trì mã nguồn.

### 5.3. Các thành phần chính
***
**Model**: Chứa logic liên quan đến dữ liệu của ứng dụng, bao gồm các đối tượng, cơ sở dữ liệu, và giao tiếp với các API khác.

**View**: Hiển thị giao diện (Interface) và nhận tương tác từ người dùng (như nhập liệu, bấm nút). 

**Presenter**: Là cầu nối giữa Model và View, chịu trách nhiệm xử lý logic, điều phối dữ liệu từ Model đến View và ngược lại.

![Image](https://github.com/user-attachments/assets/e46bd2aa-6095-4993-bc36-80ae9b0f83b1)

### 5.4. Đặc điểm chính
***
Đặc điểm của MVP Pattern:
- **Tách biệt logic và giao diện**: Presenter chứa logic của ứng dụng, giúp View chỉ tập trung vào hiển thị.
- **Presenter không biết đến giao diện cụ thể**: Presenter chỉ tương tác với View thông qua một interface, giúp việc kiểm thử và thay đổi giao diện trở nên dễ dàng.
- **Thích hợp cho ứng dụng có giao diện phức tạp**: MVP rất hữu ích khi giao diện cần tương tác với nhiều dữ liệu và các thành phần phức tạp.

### 5.5. Luồng hoạt động
***
Luồng hoạt động của MVP Pattern:
- Người dùng tương tác với giao diện người dùng (View).
- View chuyển sự kiện này cho Presenter.
- Presenter xử lý yêu cầu bằng cách lấy dữ liệu từ Model.
- Model xử lý dữ liệu và trả về kết quả cho Presenter.
- Presenter tiếp tục cập nhật View với dữ liệu đã xử lý từ Model.

![Image](https://github.com/user-attachments/assets/d09c9d0c-b1a7-4567-9517-34b2a29f4bbf)

### 5.6. Ví dụ: Quản lý thông tin sinh viên
***
```cpp
#include <iostream>
#include <string>

using namespace std;

class SinhVienModel{
    private:
        string name;
        int age;
        string studentId;

    public:
        SinhVienModel(const string& name, int age, const string& studentId): name(name), age(age), studentId(studentId){}

        // setter method
        void setName(const string& newName){
            name = newName;
        }

        void setAge(int newAge){
            age = newAge;
        }

        void setStudentId(const string& newStudentId){
            studentId = newStudentId;
        }

        // getter method
        string getName() const{
            return name;
        }

        int getAge() const{
            return age;
        }

        string getStudentId() const{
            return studentId;
        }
};

class SinhVienView{
    public:
        void displayStudentInfo(const string& name, int age, const string& studentId){
            cout << "Thông tin sinh viên:" << endl;
            cout << "Tên: " << name << endl;
            cout << "Tuổi: " << age << endl;
            cout << "Mã số sinh viên: " << studentId << endl;
        }

        void inputStudentInfo(string& name, int& age, string& studentId){
            cout << "Nhập thông tin sinh viên:" << endl;

            cout << "Tên: ";
            getline(cin, name);

            cout << "Tuổi: ";
            cin >> age;
            cin.ignore();  // Bỏ qua ký tự newline trong buffer

            cout << "Mã số sinh viên: ";
            getline(cin, studentId);
        }
};

class SinhVienPresenter{
    private:
        SinhVienModel& model;
        SinhVienView&  view;

    public:
        SinhVienPresenter(SinhVienModel& m, SinhVienView& v): model(m), view(v){}

        void updateStudentInfo(){
            string name;
            int age;
            string studentId;
           
            view.inputStudentInfo(name, age, studentId);
            model.setName(name);
            model.setAge(age);
            model.setStudentId(studentId);
        }

        void showStudentInfo(){
            view.displayStudentInfo(model.getName(), model.getAge(), model.getStudentId());
        }
};

int main()
{
    // Tạo model, view và presenter
    SinhVienModel model("Tuấn", 20, "HTN123");
    SinhVienView view;
    SinhVienPresenter presenter(model, view);

    int choice;
    do{
        cout << "\n1. Hiển thị thông tin sinh viên" << std::endl;
        cout << "2. Cập nhật thông tin sinh viên" << std::endl;
        cout << "3. Thoát" << std::endl;
        cout << "Nhập lựa chọn: ";
        cin >> choice;
        cin.ignore(); // Bỏ qua ký tự newline trong buffer
       
        switch (choice){
            case 1:
                presenter.showStudentInfo();
                break;
               
            case 2:
                presenter.updateStudentInfo();
                break;

            case 3:
                cout << "Thoát chương trình." << endl;
                break;

            default:
                cout << "Lựa chọn không hợp lệ!" << endl;
        }
       
    } while (choice != 3);

    return 0;
}
```

kết quả
```cpp
1. Hien thi thong tin sinh vien
2. Cap nhat thong tin sinh vien
3. Thoat
Nhap lua chon: 1
Thong tin sinh vien:
Ten: Tuß║Ñn
Tuoi: 20
Ma so sinh vien: HTN123

1. Hien thi thong tin sinh vien
2. Cap nhat thong tin sinh vien
3. Thoat
Nhap lua chon: 2
Nhap thong tin sinh vien:
Ten: An
Tuoi: 23
Ma so sinh vien: 105200398

1. Hien thi thong tin sinh vien
2. Cap nhat thong tin sinh vien
3. Thoat
Nhap lua chon: 1
Thong tin sinh vien:
Ten: An
Tuoi: 23
Ma so sinh vien: 105200398

1. Hien thi thong tin sinh vien
2. Cap nhat thong tin sinh vien
3. Thoat
Nhap lua chon: 3
Thoat chuong trinh.
```