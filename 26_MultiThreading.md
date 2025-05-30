# Multithreading
***
## 1. Process
***
Process (tiến trình) là một đơn vị thực thi độc lập, 1 chương trình đang chạy trên hệ thống, có không gian địa chỉ bộ nhớ riêng. 

Mỗi process chạy trong một không gian bộ nhớ tách biệt, và việc giao tiếp giữa các process thường khó khăn và yêu cầu các phương thức như IPC (Inter-Process Communication).

Bản chất của process là 1 chương trình đang chạy trên hệ thống hoặc 1 tập hợp các công việc được thực hiện trên máy tính, có phân vùng RAM riêng, có thể sử dụng những phần cứng bên dưới (bàn phím, chuột,..). Vì mỗi chương trình có vùng RAM riêng các chương trình không thể truy cập RAM lẫn nhau

Mỗi process có thể tương tác với những phần cứng bên ngoài (bàn phím, chuột,  camera, ...).

Mỗi tiến trình có thể bao gồm một hoặc nhiều luồng (thread) của việc thực hiện công việc.

![Image](https://github.com/user-attachments/assets/029145a6-ae68-4fd5-9fda-cdd2efbc7dcd)
***
## 2. Thread
***
### 2.1. Khái niệm
***
Thread là đơn vị nhỏ hơn của một process, còn được gọi là "luồng". Một process có thể chứa nhiều thread, và các thread này chia sẻ cùng không gian địa chỉ bộ nhớ của process đó.

Các luồng trong cùng một tiến trình có thể chia sẻ cùng một không gian bộ nhớ và các tài nguyên khác của tiến trình, bao gồm cả biến toàn cục và biến cục bộ.

![Image](https://github.com/user-attachments/assets/a33d8916-2d19-417b-8a94-847fa35d985d)

Bản chất đa luồng cũng là tuần tự nhưng phân chia thời gian ở các task.

### 2.2. Tạo và khởi chạy 1 thread
***
```cpp
thread task1(test1, 1000);     // task1: đại diện cho luồng 1

thread task2(test2, 3000);     // task2: đại diện cho luồng 2
```
Cú pháp tổng quát
```cpp
std::thread thread_id (function, args…)
```

- task1, task2: là các object thuộc class thread. Mỗi object sẽ tương ứng với một luồng được tạo ra và mỗi một luồng sẽ thực thi một hàm hay tác vụ nào đó.
- Tham số 1: địa chỉ hàm hoặc lambda muốn thực thi trong luồng.
- Tham số 2, 3, …: tham số truyền vào của hàm.  

**Ví dụ:**
Thư viện chính là thread, còn thư viện chrono được sử dụng cho việc delay
```cpp
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void delay(uint32_t time){
    this_thread::sleep_for(chrono::seconds(time));
}

void test1(uint32_t time){
    int i = 0;
    while (1){
        cout << "task 1, i = " << i++ << endl;
        delay(time);
    }
}

void test2(uint32_t time){
    int i = 0;
    while (1){
        cout << "task 2, i = " << i++ << endl;
        delay(time);
    }
}

int main(int argc, char const *argv[])
{
    thread task1(test1, 1);     // t1: đại diện cho luồng 1
    thread task2(test2, 2);     // t2: đại diện cho luồng 2

    /* luồng chính giúp chương trình chạy liên tục */
    while(1){
        cout << "This is main\n";
        delay(1);
    }

    return 0;
}
```
***
### 2.3. Quản lý Thread
***
#### 2.3.1. join()
***
```cpp
    task1.join();
    task2.join();
```
Phương thức join() được sử dụng để chờ cho một luồng kết thúc. Khi gọi join() trên một luồng, nó đảm bảo rằng luồng hiện tại sẽ không tiếp tục thực hiện cho đến khi luồng được join() hoàn tất. Điều này hữu ích khi bạn cần chắc chắn rằng một luồng đã hoàn thành công việc trước khi tiếp tục với luồng chính.

Mỗi luồng chỉ có thể gọi method join() duy nhất 1 lần. Nếu gọi nhiều lần sẽ gây ra lỗi.

Nếu một luồng đã được join(), nó không còn khả năng tham gia (joinable) nữa.

Ví dụ
```cpp
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void delay(uint32_t time){
    this_thread::sleep_for(chrono::seconds(time));
}

void test1(uint32_t time){
    int i = 0;
    for (int j = 0; j < 10; j++){
        cout << "task 1, i = " << i++ << endl;
        delay(time);
    }
}

void test2(uint32_t time){
    int i = 0;
    for (int j = 0; j < 10; j++){
        cout << "task 2, i = " << i++ << endl;
        delay(time);
    }
}

int main(int argc, char const *argv[])
{
    thread task1(test1, 1);     // t1: đại diện cho luồng 1
    thread task2(test2, 2);     // t2: đại diện cho luồng 2

    task1.join();
    task2.join();

    /* luồng chính giúp chương trình chạy liên tục */
    while(1){
        cout << "This is main\n";
        delay(1);
    }

    return 0;
}
```
***
#### 2.3.2. detach()
***
Phương thức detach() tách luồng khỏi luồng chính và cho phép nó chạy độc lập. 

Khi một luồng được tách ra, luồng chính không chờ luồng đó kết thúc nữa.

Sau khi gọi detach(), khi luồng chính kết thúc, những luồng khác cũng sẽ kết thúc theo.

Không thể join() một luồng đã được detach(). Nếu một luồng đã được tách ra, nó không còn khả năng tham gia (joinable) nữa.

Ví dụ
```cpp
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
void delay(uint32_t time){
    this_thread::sleep_for(chrono::seconds(time));
}
void test1(uint32_t time){
    int i = 0;
    for (int j = 0; j < 5; j++){
        cout << "task 1, i = " << i++ << endl;
        delay(time);
    }
}
void test2(uint32_t time){
    int i = 0;
    for (int j = 0; j < 5; j++){
        cout << "task 2, i = " << i++ << endl;
        delay(time);
    }
}
int main(int argc, char const *argv[])
{
    thread task1(test1, 1);     // t1: đại diện cho luồng 1
    thread task2(test2, 2);     // t2: đại diện cho luồng 2

    task1.detach();
    task2.detach();

    /* luồng chính giúp chương trình chạy liên tục */
    int i = 0;
    while(1){
        cout << "This is main, i = " << i++ << endl;
        delay(1);
    }
    return 0;
}
```
***
#### 2.3.3. joinable()
***
Kiểm tra xem một thread đã kết thúc hoặc đã gọi join() hay chưa. 

Nếu chưa thì trả về true, khi này ta có thể bắt đầu khởi chạy thread. 

Ngược lại, nếu thread đã kết thúc rồi thì trả về false.
***

## 3. Thread Synchronous (Đồng bộ hóa các luồng)
***
### 3.1. Atomic Operator
***
#### 3.1.1. Khái niệm:
Giả sử có một chương trình đo nhiệt độ từ cảm biến và cập nhật giá trị vào một biến (biến toàn cục) chia sẻ:
- Luồng 1 (luồng đọc cảm biến): Liên tục đọc dữ liệu từ cảm biến và cập nhật vào biến nhiệt độ.
- Luồng 2 (luồng ghi dữ liệu): Đọc giá trị từ biến nhiệt độ để thực hiện các thao tác khác, ví dụ như lưu vào file hoặc hiển thị trên giao diện.
- Nếu sử dụng std::lock_guard hoặc std::unique_lock, mỗi khi luồng đọc cảm biến muốn ghi giá trị mới vào biến nhiệt độ, nó sẽ phải khóa mutex, và khi luồng ghi muốn đọc giá trị từ biến, nó cũng phải khóa mutex. Khi cả hai luồng cần truy cập biến cùng lúc, sẽ xảy ra hiện tượng chờ đợi (blocking), làm chậm chương trình.

Trong trường hợp này, việc sử dụng std::atomic có thể là giải pháp tốt hơn so với sử dụng mutex. 

std::atomic là một cơ chế trong C++ được thiết kế để thực hiện các thao tác trên các biến mà các thao tác này không thể bị gián đoạn bởi các luồng khác. Điều này giúp đảm bảo tính nhất quán của dữ liệu và tránh tình trạng xung đột khi nhiều luồng cùng truy cập và thay đổi dữ liệu chia sẻ.

Mỗi đối tượng std::atomic<T> chỉ bảo vệ một biến duy nhất thuộc kiểu T, chẳng hạn std::atomic<int>, std::atomic<double>,  std::atomic<bool>, std::atomic<void*>,... đảm bảo rằng các thao tác trên biến đó sẽ không bị gián đoạn và sẽ hoàn thành hoàn toàn trước khi bất kỳ luồng nào khác có thể thực hiện thao tác trên cùng biến đó.

Ví dụ
```cpp
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> sharedCounter(0);

void incrementTask(int iter)
{
    for(int i = 0; i<iter; i++)
    {
        cout << ++sharedCounter << endl;
    }
}

// đọc giá trị hiện tại
// tăng 1 đơn vị
// ghi giá trị mới vào vùng nhớ

// luồng t1: đọc giá trị: 100
// luồng t2: đọc giá trị: 101

int main(int argc, char const *argv[])
{
    thread t1(incrementTask, 10000);
    thread t2(incrementTask, 20000);

    t1.join();
    t2.join();

    cout << "Final result: " << sharedCounter << endl;
    return 0;
}
```

Kết quả
```cpp
1 đến 30000
```
=> không bị mất dữ liệu nữa, vì bây giờ đã đảm bảo tính nhất quán
***
### 3.2. Mutex
***
#### 3.2.1. Khái niệm
***
Mutex (Mutual Exclusion): Là một đối tượng đồng bộ hóa cung cấp cơ chế để giới hạn truy cập tài nguyên chỉ cho một luồng tại một thời điểm. 

Khi một luồng khóa (lock) mutex, các luồng khác phải chờ cho đến khi mutex được mở khóa (unlock) mới có thể tiếp tục truy cập tài nguyên.

Trạng thái của mutex: Một mutex có hai trạng thái chính:
- Khóa (locked): Khi một luồng đã chiếm giữ mutex.
- Mở khóa (unlocked): Khi không có luồng nào chiếm giữ mutex, các luồng khác có thể tiếp tục khóa nó.

**std::mutex** được định nghĩa trong thư viện <mutex>. Các phương thức cơ bản bao gồm:
- lock(): Khóa mutex. Nếu mutex đã bị khóa bởi một luồng khác, luồng hiện tại sẽ bị chặn (block) cho đến khi mutex được mở khóa.
- unlock(): Mở khóa mutex. Điều này cho phép các luồng khác có thể tiếp tục khóa mutex.
- try_lock(): Thử khóa mutex. Nếu mutex chưa bị khóa, nó sẽ khóa mutex và trả về true. Nếu đã bị khóa bởi một luồng khác, nó sẽ không chặn luồng hiện tại mà trả về false.

Ví dụ: 
```cpp
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0;
mutex mtx;

void increment(int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        mtx.lock();     // Khóa mutex trước khi truy cập biến chia sẻ
        ++counter;      // Thao tác trên biến chia sẻ
        mtx.unlock();   // Mở khóa mutex sau khi truy cập
    }
}

int main() {
    const int num_iterations = 10;

    thread t1(increment, num_iterations);
    thread t2(increment, num_iterations);

    t1.join();
    t2.join();

    cout << "Final counter value: " << counter << endl;

    return 0;
}
```
Kết quả
```cppp
Final counter value: 20
```

#### 3.2.2. Lock guard 
***
std::lock_guard là một lớp RAII (Resource Acquisition Is Initialization) 

tự động khóa mutex khi được tạo 

tự động mở khóa khi đối tượng bị hủy (ra khỏi phạm vi).

Ví dụ
```cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

mutex mtx;

void delay(uint32_t time){
    this_thread::sleep_for(chrono::seconds(time));
}

void display(int id){
    while (1){
        lock_guard<mutex> lock(mtx);
        cout << "This is task display: " << id << endl;
        delay(1);
    }
}

int main(int argc, char const *argv[])
{
    thread t1(display, 1);
    thread t2(display, 2);
    thread t3(display, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
```
Kết quả
```cpp
This is task display: 1
This is task display: 1
This is task display: 1
This is task display: 1
This is task display: 3
This is task display: 2
This is task display: 2
This is task display: 2
This is task display: 2
This is task display: 3
This is task display: 3
This is task display: 3
```

#### 3.2.3. Unique Lock
***
std::unique_lock tự động khóa mutex khi được tạo nhưng cung cấp tính linh hoạt hơn std::lock_guard, cho phép mở khóa thủ công hoặc tự động mở khóa khi ra khỏi phạm vi, hoặc thử khóa với thời gian chờ.

***

### 3.3. Condition Variables
***
#### 3.3.1. Khái niệm
***
Thao tác với cảm biến:
- Luồng đọc dữ liệu (read).
- Luồng xử lý dữ liệu (process).
- 2 luồng đều sử dụng chung 1 tài nguyên (dữ liệu cảm biến - atomic).
- Đảm bảo luồng đọc phải đi trước luồng xử lý (thứ tự) (mutex không dảm bảo được việc này).

Khi hai hoặc nhiều luồng cần giao tiếp và đồng bộ hóa với nhau, condition variable là một lựa chọn thích hợp trong C++. 

std::condition_variable cho phép một luồng chờ cho đến khi một điều kiện cụ thể được đáp ứng, và một luồng khác có thể thông báo khi điều kiện đó được thỏa mãn. Điều này rất hữu ích trong việc giao tiếp và đồng bộ hóa dữ liệu giữa các luồng.

Cung cấp 3 hàm:
- wait().
- notify_one().
- notify_all().

#### 3.3.2. Cách hoạt động
***
**a)	Một luồng chờ (wait) cho đến khi có tín hiệu từ một luồng khác:**
-	Luồng này sẽ chờ trong trạng thái chờ điều kiện, tránh lãng phí tài nguyên CPU.
-	Để sử dụng wait(), cần có một std::unique_lock<std::mutex> và một đối tượng std::condition_variable, vì nó phải tạm thời mở khóa mutex để các luồng khác có thể truy cập vào mutex và thay đổi điều kiện. Sau khi điều kiện được thỏa mãn và luồng được đánh thức, std::unique_lock sẽ tự động khóa lại mutex để đảm bảo tính nhất quán trước khi tiếp tục.
-	Lưu ý: std::lock_guard không hỗ trợ mở khóa và khóa lại mutex như vậy. Khi một std::lock_guard được tạo, nó sẽ giữ mutex cho đến khi đối tượng bị hủy (khi ra khỏi phạm vi), do đó không phù hợp để sử dụng với wait.

**b)	Một luồng khác thông báo rằng điều kiện đã được đáp ứng:**
-	notify_one(): Chỉ đánh thức một luồng đang chờ.
-	notify_all(): Đánh thức tất cả các luồng đang chờ.

Ví dụ: 2 luồng giao tiếp dữ liệu

```cpp
#include <iostream>
#include <thread>               // tạo ra các luồng
#include <mutex>                // khóa dữ liệu khi có nhiều luồng cùng truy cập
#include <condition_variable>   // sử dụng biến điều kiện giúp đồng bộ hóa giữa các luồng
#include <chrono>               // quản lý thời gian
#include <atomic>

using namespace std;

void delay(uint32_t time){
    this_thread::sleep_for(chrono::seconds(time));
}

// int sensor_data = 0;
atomic<int> sensor_data(0);

bool check_data = false;

mutex mtx;

condition_variable cv;

void sensor_read()
{
    while (1){
        delay(2);
        unique_lock<mutex> lock(mtx);   // khóa luồng để truy cập ngoại vi
        sensor_data = rand() % 100;     // đọc dữ liệu
        check_data = true;              // set cờ lên 1
        cout << "Read data done!\n";
        lock.unlock();
        cv.notify_one();    // sử dụng condition variables
    }
}

void process_data()
{
    while (1)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []()->bool{return check_data;});    
        /***************************************************************
         * dùng để thoát khỏi vòng lặp while bên trong cấu trúc của wait
         ***************************************************************/ 
        cout << "Data: " << sensor_data << endl;
        check_data = false; 
        lock.unlock();
    }
}

int main(int argc, char const *argv[])
{
    thread task1(sensor_read);
    thread task2(process_data);

    task1.join();
    task2.join();

    return 0;
}
```
Kết quả
```cpp
Read data done!
Data: 41
Read data done!
Data: 67
Read data done!
Data: 34
Read data done!
Data: 0
Read data done!
Data: 69
```
***

## 4. Thread Asynchronous (Bất đồng bộ hóa các luồng)
***
### 4.1. Khái niệm
***
Bất đồng bộ (asynchronous programming) là một kỹ thuật lập trình cho phép thực hiện các tác vụ mà không cần chờ chúng hoàn thành trước khi tiếp tục thực hiện các tác vụ khác. Bằng cách này, chương trình có thể tận dụng tối đa tài nguyên hệ thống và cải thiện hiệu suất.

Chạy độc lập với các luồng khác, bao gồm luồng chính → Detach? 

Trong C++, lập trình bất đồng bộ cho phép chạy các tác vụ trong các luồng riêng biệt, xử lý các tác vụ mất thời gian (như I/O, tính toán nặng) mà không làm gián đoạn luồng chính. Các thành phần chính để hỗ trợ lập trình bất đồng bộ trong C++ bao gồm:
- std::async: Khởi chạy một tác vụ bất đồng bộ, trả về đối tượng .
- std::future: Được sử dụng để lưu trữ kết quả của một tác vụ sẽ hoàn thành trong tương lai.
- std::shared_future: Cho phép nhiều luồng cùng truy cập kết quả của một tác vụ bất đồng bộ.

***
### 4.2. Tạo và khởi chạy luồng bất đồng bộ
***
std::async là một hàm trong C++ (từ C++11 trở đi) tạo ra một luồng để thực thi một công việc (task) có thể chạy bất đồng bộ, dựa trên một hàm hoặc biểu thức lambda mà bạn cung cấp. 

Kết quả của công việc này được trả về dưới dạng std::future, kiểu dữ liệu cho phép truy xuất giá trị của tác vụ sau khi nó hoàn tất.

Cú pháp:
```cpp
std::future<T> std::async(std::launch policy, Callable&& func, Args&&... args);
```

policy: chế độ chạy:
- std::launch::async: hàm sẽ chạy ngay lập tức trên một luồng mới.
- std::launch::deferred: hàm chỉ chạy khi kết quả của std::future được yêu cầu (lazy evaluation), nghĩa là khi bạn gọi future.get().

func:  Hàm hoặc biểu thức lambda cần thực hiện bất đồng bộ.

args: Các tham số truyền vào func (nếu có).

***
### 4.3. Truy cập két quả của luồng bất đồng bộ
***
Khi std::async được gọi, một tác vụ bất đồng bộ được tạo ra và vùng bộ nhớ cho kết quả sẽ được cấp phát động (trên heap).

std::future hoặc std::shared_future sẽ nắm quyền quản lý kết quả này và giữ một con trỏ đến vùng nhớ chứa kết quả.

Khi get()được gọi, giá trị được trả về từ bộ nhớ này. 
- Nếu là std::future, get() sẽ chỉ có thể gọi một lần. 
- Nếu là std::shared_future, get() có thể gọi nhiều lần.

***
### 4.4. Kiểm tra trạng thái luồng bất đồng bộ 
***
**a)	std::future::wait()**
wait() sẽ tạm dừng luồng hiện tại cho đến khi giá trị trong std::future sẵn sàng, tức là tác vụ bất đồng bộ đã hoàn thành.

wait() không nhận tham số thời gian chờ và cũng không trả về std::future_status. Nó chỉ đơn giản là chờ cho đến khi tác vụ hoàn tất.

Sử dụng wait():
- Khi bạn muốn chờ đợi cho một tác vụ bất đồng bộ hoàn thành mà không cần quan tâm đến thời gian chờ cụ thể.
- Khi bạn muốn đảm bảo rằng tác vụ bất đồng bộ đã hoàn thành trước khi thực hiện các bước tiếp theo trong chương trình.

**b)	std::future::wait_for()**
wait_for() chờ đợi một khoảng thời gian cụ thể (rel_time) để kiểm tra xem tác vụ bất đồng bộ đã hoàn thành hay chưa. Thời gian này được chỉ định bằng một đối tượng "std::chrono::duration" hoặc "std::chrono::sleep".

**Giá trị trả về:** Trả về một giá trị thuộc kiểu "std::future_status", có thể là:
- "std::future_status::ready": Tác vụ đã hoàn thành trong khoảng thời gian chỉ định.
- "std::future_status::timeout": Tác vụ chưa hoàn thành trong khoảng thời gian chỉ định.
- "std::future_status::deferred": Tác vụ được khởi chạy ở chế độ trì hoãn (launch::deferred) và sẽ chỉ được thực thi khi có lệnh gọi đến get() hoặc wait().
