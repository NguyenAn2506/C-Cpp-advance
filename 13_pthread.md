# Pthread
***
**đặt vấn đề**
thông thường khi run code thì trình biên dịch sẽ chạy theo kiểu polling (tức từ trên xuống dưới), nhưng trong thực tế thì việc chạy polling từng câu lệnh sẽ gây mất nhiều thời gian và độ chính xác không cao.
để có thể thực hiện 1 lúc nhiều nhiệm vụ khác nhau, ta nên sử dụng đa luồng
***
## 13.1. Khái niệm:
Thread (luồng) là đơn vị thực thi nhỏ nhất của một tiến trình (tasks). Mỗi tiến trình có thể chứa nhiều thread, và các thread này chạy song song với nhau.
Các thread trong cùng tiến trình chia sẻ tài nguyên với nhau nhưng sẽ có stack và bộ đếm chương trình riêng biệt.
***
## 13.2. thư viện Pthread
Pthread (POSIX Threads) là không phải thư viện tiêu chuẩn cho lập trình đa luồng trong C/C++:
-	Giúp bạn viết các chương trình có thể thực hiện nhiều tác vụ cùng lúc bằng cách chạy nhiều luồng (threads) song song. Điều này đặc biệt hữu ích trên các hệ thống có nhiều bộ xử lý hoặc bộ xử lý nhiều nhân, vì mỗi luồng có thể được phân bố cho các nhân khác nhau để chạy.
-	Xử lý nhiều công việc cùng lúc, giúp tăng tốc độ xử lý và phân tán công việc hiệu quả hơn.
![Image-1](https://github.com/user-attachments/assets/7c1f0b7b-cc7e-4f92-8cb8-c5feaf736765)
### 13.2.1. tạo mới 1 Thread
Sử dụng hàm pthread_create trong thư viện Pthread để khởi chạy một thread và chỉ định cho thread này thực thi một tác vụ cụ thể.
```c
pthread_create(pthread_t *th, const pthread_attr_t *attr, void *(* func)(void *), void *arg)
```
-	Tham số 1: một con trỏ kiểu pthread_t, đại diện cho một thread mới được tạo ra.
-	Tham số 2: một thuộc tính của thread, đặt là NULL nếu giữ thuộc tính mặc định.
-	Tham số 3: địa chỉ hàm muốn thực thi.
-	Tham số 4: một con trỏ đối số cho hàm thuộc kiểu void.
### 13.2.2. chờ 1 Thread kết thúc
```c
int pthread_join(pthread_t t, void **res)
```
-	Tham số 1: ID của thread mà bạn muốn chờ đợi.
-	Tham số 2: pointer to pointer mà kết quả trả về từ thread sẽ được lưu trữ. Nếu không cần kết quả, có thể đặt NULL .

**ví dụ**
```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *task1(void *data){
    static int i = 0;
    while(1){
        printf("count task1: %d\n", i++);
        sleep(1);
    }
}

void *task2(void *data){
    static int i = 0;
    while(1){
        printf("count task2: %d\n", i++);
        sleep(3);
    }
}

void *display(void *a){
    while(1){
        printf("%s\n", (char*) a);
        sleep(1);
    }
}

int main(int argc, char const *argv[]){
    char *ptr = "Hello";
    pthread_t t1, t2, t3;       // luồng 1 , luồng 2, luồng 3

    pthread_create(&t1, NULL, task1, NULL);
    pthread_create(&t2, NULL, task2, NULL);
    pthread_create(&t3, NULL, display, ptr);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    while(1){
        printf("Hello World\n");
        sleep(1);
    }

    return 0;
}
```
Dùng câu lệnh sau để chạy đoạn mã
```c
gcc -g -pthread <file.c> -o <tên file .exe>

./<tên file>
```
**kết quả**
```c
Hello
count task1: 18
count task1: 19
Hello
count task1: 20
Hello
count task2: 7
count task1: 21
Hello
```
=> nhận thấy kết quả không thấy hello world (trong while 1 của luồng main), vì bây h đang chờ t1 chờ t1 xong thì chờ t2, chờ xong rồi quay lại t1 nên nó không xuống được while của main 
=> Thư viện thread giúp thực hiện đa luồn khác nhau 1 cách //, mỗi luồng sẽ có 1 kết quả khác nhau 