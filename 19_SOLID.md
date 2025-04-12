# Các nguyên tắc thiết kế hướng đối tượng (SOLID)
***
## 1. Giới thiệu:
***
●	SOLID là tập hợp 5 nguyên tắc thiết kế phần mềm giúp tạo ra mã nguồn dễ bảo trì, mở rộng và linh hoạt hơn. (ngoài ra còn có dễ kiểm thử hay debug)

![Image](https://github.com/user-attachments/assets/eec6f288-52fe-4a79-94dd-03c7702003c0)
***
## 2. Nguyên tắc đơn trách nhiệm (SRP)
***
### 2.1. Khái niệm
***
S - Single Responsibility Principle (SRP) - Nguyên tắc đơn trách nhiệm

- Mỗi phần của chương trình chỉ nên làm một việc duy nhất. Nếu một phần có nhiều nhiệm vụ, nó sẽ khó bảo trì và dễ gây lỗi khi thay đổi.. (cần phải tách nó ra thành nhiều class khác)
- Giúp mã nguồn dễ bảo trì, dễ mở rộng và dễ kiểm thử hơn.
![Image](https://github.com/user-attachments/assets/4447f8f2-9ae5-4a95-9235-51e9cf30cb03)

### 2.2. Ví dụ:
***
#### Ví dụ 1:
khi sử dụng class như thế này:
```cpp
class Sensor
{
    public:
        // Xử lý dữ liệu
        void processData(){}
       
        // Lưu trữ dữ liệu
        void saveData(){}

        // Gửi dữ liệu đi
        void sendData(){}
};
```
=> sẽ bị vi phạm về nguyên tắc SRP do đưa tất cả hàm vào trong cùng 1 class

**Sửa lại dùng SRP : Dùng SRP để tách 1 class có nhiều hàm thành nhiều class khác nhau**

```cpp
// Class xử lý dữ liệu
class Process
{
    public:
        void processData(){}
};

// Class lưu trữ dữ liệu
class Save
{
    public:
        void saveData(){}
};

// Class gửi dữ liệu
class Send
{
    public:
        void sendData(){}
};
```
#### Ví dụ 2:
```cpp
class SpeedSensor{
    public:
        double getSpeed(){ return 40; }
};   
class EngineController{
    public:
        void adjustSpeed(double speed){
            if (speed <= 40){
                cout << "Tăng tốc độ động cơ" << endl;
            } else if (speed >= 100){
                cout << "Giảm tốc độ động cơ" << endl;
            }
        }
};   
int main(){
    SpeedSensor speedSensor;
    double speed = speedSensor.getSpeed();
    EngineController engine;
    engine.adjustSpeed(speed);
    return 0;
} 
```
***
## 3. Nguyên tắc đóng mở (OCP)
***
### 3.1. Khái niệm:
***
O - Open/Closed Principle (OCP) - Nguyên tắc đóng mở

- Cho phép mở rộng nhưng không sửa đổi mã cũ. Khi cần thêm tính năng mới, hãy thêm mã mới thay vì chỉnh sửa mã hiện có.
- Tránh sửa đổi mã nguồn cũ, giúp phần mềm ổn định hơn.

### 3.2. Ví dụ
***
#### Ví dụ 1: 
Khi đã xây xong 1 ngôi nhà, thì khi muốn xây thêm 1 phần nữa khác để làm gì đó thì ta chỉ cần xây thêm và không cần động lại vào ngôi nhà đã xây

![Image](https://github.com/user-attachments/assets/4fe04d54-1a91-4ec7-bbf3-2d0d5b39e395)

#### Ví dụ 2:
có một hệ thống cảnh báo tốc độ, ban đầu chỉ hỗ trợ cảnh báo bằng âm thanh. Nếu muốn thêm cảnh báo bằng đèn LED, ta phải sửa code trong sendAlert(), vi phạm OCP.

```cpp
class SpeedAlert
{
    public:
        void sendAlert(double speed)
        {
            if (speed > 100)
            {
                cout << "Cảnh báo: Vượt quá tốc độ!" << endl;
            }
        }
};
```
Để giải quyết vấn đề này thì ta sẽ phải dùng hàm thuần ảo (override) tức là kế thừa kết hợp với sử dụng đa hình runtime

```cpp
class Device_Alert{
    public:
        virtual void sendAlert(double speed) = 0;
};
class Sound_Alert : public Device_Alert{
    public:
        void sendAlert(double speed) override{
            if (speed > 100){
                cout << "Cảnh báo: Vượt quá tốc độ! (Âm thanh)" << endl;
            }
        }
};
class LED_Alert : public Device_Alert{
    public:
        void sendAlert(double speed) override{
            if (speed > 100){
                cout << "Cảnh báo: Vượt quá tốc độ! (Đèn LED)" << endl;
            }
        }
};

void handleSpeedAlert(Device_Alert *alert, double speed){ alert->sendAlert(speed); }
   
int main(){
    Sound_Alert sound;
    LED_Alert led;
    handleSpeedAlert(&sound, 80);
    handleSpeedAlert(&led, 120);
    return 0;
}
```
#### Ví dụ 3:
Từ 1 class payment có 1 hàm phân thành nhiều chức năng sử dụng chung với 1 hàm
```cpp
class Payment
{
    public:
        void processPayment(string type)
        {
            if (type == "CreditCard")  
            {
                /* Xử lý thẻ tín dụng */
            }
            else if (type == "PayPal")
            {
                /* Xử lý PayPal */
            }
        }
};
```
Ta mở rộng ra thành nhiều claas khác nhau với những chức năng khác nhau
```cpp
class PaymentMethod
{
    public:
        virtual void pay() = 0;
};
   
class CreditCard : public PaymentMethod
{
    public:
        void pay() override { /* Xử lý thẻ tín dụng */ }
};
   
class PayPal : public PaymentMethod
{
    public:
        void pay() override { /* Xử lý PayPal */ }
};
```
***
## 4. Nguyên tắc thay thế Liskov
***
Thông thường khi làm 1 class ta có thể tóm gọn các chức năng cho 1 đối tượng được kế thừa

Ví dụ: ta có 1 class tên Vehicle để viết chung cho tất cả các phương tiện

![Image](https://github.com/user-attachments/assets/59d81d18-eece-450e-807c-933ee8e9a553)

Nhưng với từng phương tiện thì sẽ có 1 chức năng riêng biệt khác nhau nên không để chung vô 1 class như thế này được => cần phải tách cha thành class khác nhau cho từng đối tượng
### 4.1. Khái niệm
***
L - Liskov Substitution Principle (LSP) - Nguyên tắc thay thế Liskov

- Một lớp con có thể thay thế lớp cha mà không làm thay đổi tính đúng đắn của chương trình, phải duy trì được những tính năng của class cha.
- Đảm bảo tính kế thừa không phá vỡ hành vi của hệ thống.

### 4.2. Ví dụ
***
#### Ví dụ 1:
Có class cha với cacs đối tượng được khai báo, trong class con được kế thừa từ class ch, mặc dù các đối tượng được kế thừa từ class cha thì ta lại thay đổi giá trị của các đối tượng như hình => gây sai logic của class cha vì class cha được gán giá trị là w và h trước đó => gây phá vỡ hành vi hệ thống

```cpp
class Rectangle{
    private:
        int width, height;

    public:
        virtual void setWidth(int w){
            width  = w;
        }

        virtual void setHeight(int h){
            height = h;
        }
};

class Square : public Rectangle{
    public: 
        void setWidth(int w)  override{
            width = height = w;
        }

        void setHeight(int h) override{
            width = height = h;
        }
};
```
Sửa lại như sau: dùng 1 hàm thuần ảo tổng quát và đưa các class con kế thừa class tổng quát
```cpp
class Shape{
    public:
        virtual int getArea() = 0;
};
   
class Rectangle : public Shape {
    private:
        int width, height;

    public:
        void setDimensions(int w, int h){
            width = w; height = h;
        }

        int getArea() override{
            return width * height;
        }
};

class Square : public Shape {
    private:
        int side;

    public:
        void setSide(int s){
            side = s;
        }
       
        int getArea() override{
            return side * side;
        }
};
```
#### Ví dụ 2:
Ví dụ sau bị sai về hành vi khi kế thừa từ class cha
```cpp
class Car{
    public:
        virtual void refuel(){
            cout << "Đổ xăng" << endl;
        }
};
   
class ElectricCar : public Car{
    public:
        void refuel() override{
            // Xe điện không thể đổ xăng
            cout << "Xe điện không dùng xăng!" << endl;
        }
};

```
Sửa lại như sau: dùng hàm thuần ảo để tạo class tổng quát và class con cho từng loại kế thừa từ claas tổng quát và mở rộng cho đún đối tượng đó 

```cpp
#include <iostream>

using namespace std;

class Vehicle
{
    public:
        virtual void rechargeOrRefuel() = 0;
};
   
class GasCar : public Vehicle
{
    public:
        void rechargeOrRefuel() override
        {
            cout << "Đổ xăng" << endl;
        }
};

class ElectricCar : public Vehicle
{
    public:
        void rechargeOrRefuel() override
        {
            cout << "Sạc pin" << endl;
        }
};
   
int main()
{
    Vehicle* v1 = new GasCar();
    v1->rechargeOrRefuel();
   
    Vehicle* v2 = new ElectricCar();
    v2->rechargeOrRefuel();
    return 0;
}
```
***
## 5. Nguyên tắc phân tách giao diện (ISP)
***
Phương pháp này sẽ liên hệ với pp Liskov ở trên, mỗi đối tượng có 1 chức năng khác nhau mà trong class cha thì đều khai báo những hàm để sử dụng cho các đối tượng => nên tách các hàm đău các hàm thành class khác nhau

![Image](https://github.com/user-attachments/assets/634ddd55-255b-409d-8864-68d83e0c1507)

### 5.1. Khái niểm:
***
I - Interface Segregation Principle (ISP) - Nguyên tắc phân chia interface

- Một class không nên bị ép buộc triển khai những phương thức mà nó không sử dụng.
- Tránh việc các class con phải cài đặt các phương thức không liên quan

### 5.2. Ví dụ:
***
#### Ví dụ 1:
Class cha đang lưu trữ toàn bộ các hàm được sử dụng chung cho nhiều đối tượng 

```cpp
class IVehicle
{
    public:
        virtual void drive() = 0;       // phương tiện có thể lái
        virtual void refuel() = 0;      // tiếp nhiên liệu
        virtual void loadCargo() = 0;   // chở hàng hóa
};

class Bike : public IVehicle
{
    public:
        void drive() override
        {
            cout << "Lái xe đạp" << endl;
        }

        void refuel() override {}       // Không hợp lý với xe đạp
        void loadCargo() override {}       
}
```
Sửa lại: tách các hàm ra cho các đối tượng
```cpp
// Interface cho phương tiện có thể lái
class IDriveable{
    public:
        virtual void drive() = 0;
};
   
// Interface cho phương tiện có thể lái
class IFuelable{
    public:
        virtual void refuel() = 0;
};

// Interface cho phương tiện có thể lái
class ICargo{
    public:
        virtual void loadCargo() = 0;
};

// Xe ô tô
class Car : public IDriveable, public IFuelable, public ICargo{
public:
    void drive() override{ cout << "Lái ô tô" << endl; }

    void refuel() override{ cout << "Đổ xăng" << endl; }

    void loadCargo() override{ cout << "Chở hàng" << endl; }
};

// xe đạp
class Bike : public IDriveable, public ICargo{
    public:
        void drive() override{ cout << "Lái xe đạp" << endl; }

    void loadCargo() override{ cout << "Chở hàng" << endl; }
};
```
=> Nguyên tắc này khá giống nguyên tắc đơn trách nhiệm (tức là mỗi class là 1 nhiệm vụ riêng)
=> Vì bản chất của nguyên tắc này là mở rộng từ 1 class nên cũng giống với nguyên tắc đóng mở
***
## 6. Nguyên tắc đảo ngược phụ thuộc (DIP)
***
### 6.1. Khái niệm:
***
D - Dependency Inversion Principle (DIP) - Nguyên tắc đảo ngược sự phụ thuộc

- Các phần quan trọng trong chương trình không nên dựa trực tiếp vào chi tiết cụ thể mà nên dựa vào một giao diện chung. Điều này giúp phần mềm linh hoạt hơn, dễ mở rộng và thay đổi mà không làm ảnh hưởng đến các phần khác.
- Ví dụ: thay vì một công tắc chỉ bật được đèn, ta làm nó điều khiển bất kỳ thiết bị nào bằng cách dùng một giao diện chung.

=> Nguyên tắc này thực chất là kết hợp với tất cả những nguyên tắc trước đó 

### 6.2. Ví dụ:
***
#### Ví dụ 1:
```cpp
class LightBulb
{
    public:
        void turnOn() { /* Bật đèn */ }
};

class Switch
{
    private:
        LightBulb bulb;
       
    public:
        void operate() { bulb.turnOn(); }
};   
```
đoạn code không vi phạm bất cứ nguyên tắc nào ở trên 

nhưng các class ở đây chỉ điều khiển cho 1 đối tượng mà thôi nên ta có thể biến những class này thành 1 class cha để có thể giúp điều khiển chung cho nhiều đối tượng khác nhau

Sửa lại như sau
```cpp
class Device{
    public:
        virtual void turnOn() = 0;
};
class LightBulb : public Device{
    public:
        void turnOn() override { /* Bật đèn */ }
};
class Fan : public Device{
    public:
        void turnOn() override { /* Bật quạt */ }
};
class Switch{
    private:
        Device *device;

    public:
        Switch(Device *d) : device(d){}
        void operate() { device->turnOn(); }
};
```

#### Ví dụ 2:
```cpp
class SpeedSensor
{
    public:
        double getSpeed() { return 80.0; }
};
   
class SpeedController
{
    private:
        SpeedSensor sensor;

    public:
        void control()
        {
            if (sensor.getSpeed() > 100)
            {
                cout << "Giảm tốc độ" << endl;
            }
        }
};
```
Sửa lại như sau
```cpp
#include <iostream>
using namespace std;

class ISensor{
    public:
        virtual double getSpeed() = 0; // Interface cảm biến tốc độ
};

// Cảm biến tốc độ từ bánh xe
class SpeedSensor : public ISensor{
    public:
        double getSpeed() override { return 80.0; } // Giả lập tốc độ từ bánh xe
};

// Cảm biến tốc độ từ GPS
class GPSSpeedSensor : public ISensor{
    public:
        double getSpeed() override { return 85.5; } // Giả lập tốc độ từ GPS
};

class SpeedController{
    private:
        ISensor* sensor; // Sử dụng interface, có thể thay thế bất kỳ cảm biến nào

    public:
        SpeedController(ISensor* s) : sensor(s){}

        void control(){
            double speed = sensor->getSpeed();

            cout << "Tốc độ hiện tại: " << speed << " km/h" << endl;

            if (speed > 100)
            {
                cout << "Cảnh báo: Giảm tốc độ!" << endl;
            }
        }
};

int main(){
    SpeedSensor *wheelSensor = new SpeedSensor();
    GPSSpeedSensor *gpsSensor = new GPSSpeedSensor();

    cout << "Kiểm tra với cảm biến bánh xe:" << endl;
    SpeedController controller1(wheelSensor);
    controller1.control();

    cout << "\nKiểm tra với cảm biến GPS:" << endl;
    SpeedController controller2(gpsSensor);
    controller2.control();
    return 0;
}
```
## Tổng kết 
**Tóm tắt các nguyên tắc của SOLID**

- SRP giúp chia nhỏ thành nhiều module.
- OCP giúp mở rộng mà không sửa đổi cái cũ.
- LSP đảm bảo lớp con kế thừa không phá vỡ chương trình.
- ISP giúp interface gọn gàng.
- DIP giúp kết nối các module qua abstraction.

## Mối liên hệ 
![Image](https://github.com/user-attachments/assets/9b9288f5-1e25-4b03-b041-8d9e61641c1d)