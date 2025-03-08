# goto – setjmp.h 

## 1. goto

- Thông thường trong 1 chương trình chính, thì luồng chương trình sẽ chạy theo kiểu polling (chạy tuần tự từ trên xuống dưới), nếu muốn biết được luồng chương trình đang ở đâu thì ta có thể sử dụng theo cách đặt 1 biến để có thể kiểm soát luồng chương trình nhưng với cách này thì phải cấp phát thêm 1 bộ nhớ để chứa biến đó làm tiêu tốn thêm bộ nhớ. Để tránh điều này xảy ra thì ta có thể sử dụng 1 từ khóa goto để có điều biến được luồng chương trình

### 1.1. khái niệm và cú pháp

- goto cho phép chương trình nhảy đến một nhãn (label) đã được đặt trước đó trong cùng một hàm.
- Cú pháp:
```C
goto <label> 
	// code
<label>:
```
- Điều kiện của label: Label đó phải được đặt trong cùng 1 hàm

ví dụ
```c
#include <stdio.h>
int main(int argc, char const *argv[])
{
    int i = 0;
    start:
		if(i>=5) goto end;
		printf("%d\n",i);
		i++;
    	goto start;
    end:
    	printf("The end\n");
    return 0;
}
```

## ứng dụng từ khóa goto
- Thoát khỏi vòng lặp nhiều cấp độ
	+ có thể dùng break, nhưng phải dùng nhiều lần
	+ Dùng từ khóa goto thì sẽ giải quyết được vấn đề
- Điều hướng chương trình
- ứng dụng trong led ma trận


## 2. thư viện SETJMP.h

- thư viện này cung cấp hai hàm chính là setjmp() và longjmp(). Cả hai hàm này (chính xác hơn là macro) thường được sử dụng để thực hiện xử lý ngoại lệ trong C
- Khác với goto thì chỉ có thể nhảy chương trình trong chỉ 1 hàm. 
  Thì thư viện setjmp.h sẽ giúp cho việc nhảy chương trình từ hàm này sang hàm khác

### 2.1. hàm setjmp()

- Cú pháp:  
```C
setjmp(<jmp_buf>)
```
- Trong đó: typedef int jmp_buf[16]
- Công dụng: lưu trạng thái hiện tại của chương trình (trạng thái tại vị trí nó đứng)
- Setjmp trả về 1 giá trị kiểu int, nên thông thường cần phải khai báo 1 biến kiểu int để lấy được giá trị của nó
- Khi mà gọi hàm setjmp lần đầu tiên thì nó sẽ trả về 0 

ví dụ
```C
jmp_buf buf;

setjmp(buf);
```

### 2.2. hàm longjmp()

- cú pháp: 
```C
longjmp(int *, int)
```
- Chức năng: nhảy về lại vị trí đã được lưu bởi setjmp
- Ví dụ: 
```C
#include <stdio.h>
#include <setjmp.h>
jmp_buf buf;
int exception = 0;
void func2()
{
    printf("This is function 2\n");
    longjmp(buf, 2);
}
void func1()
{
    exception = setjmp(buf);            // lần đầu , trả về = 0
    if (exception == 0)
    {
        printf("This is function 1\n");
        printf("exception = %d\n", exception);
        func2();
    }
    else if (exception == 2)
    {
        printf("exception = %d\n", exception);
    }
}
int main(int argc, char const *argv[])
{
    func1();
    return 0;
}
```
- Tham số đầu tiên dùng để nhảy về câu lệnh setjmp(buf) (dòng 18)
- Tham số thứ 2 là giá trị của setjmp, 
  + lần đầu tiên thì setjmp = 0
  + kể từ lần thứ 2 thì giá trị của setjmp sẽ phụ thuộc vào longjmp, longjmp cho giá trị là bao nhiêu thì setjmp sẽ có giá trị = giá trị đó



### 2.3. ứng dụng của thư viện setjmp.h

- Được sử dụng để kiểm tra lỗi (debug, giống vs assert)

- Sự khác nhau giữa assert và setjmp (ưu nhược điểm)
	+ Assert thì có lỗi sai là dừng chương trình(nhược điểm), và sẽ cho biết được vị trí mà chương trình dừng (ưu điểm)
	+ Còn với setjmp thì chỉ thông báo lỗi ở đâu, còn những chỗ khác vẫn chạy bình thường (ưu), nhược là không biết được vị trí cụ thể
