# Stack and Queue
***
***
Cấu trúc dữ liệu là cách tổ chức, và lưu trữ dữ liệu để chúng có thể được truy cập và sử dụng một cách hiệu quả, đóng vai trò quan trọng trong việc giải quyết các bài toán và tối ưu hóa thuật toán, vì nó ảnh hưởng trực tiếp đến tốc độ thực thi và tính phức tạp của chương trình.
**Cấu trúc dữ liệu được phân làm 2 loại chính:**
-	Cấu trúc dữ liệu tuyến tính (Linear Data Structure): mảng (Array), ngăn xếp (Stack), hàng đợi (Queue), danh sách liên kết (Linked List).
-	Cấu trúc dữ liệu phi tuyến tính (Non-linear Data Structure): đồ thị (Graphs), cây (Trees).
***
## 9.1. Stack
Stack (ngăn xếp) là một cấu trúc dữ liệu tuân theo nguyên tắc "Last In, First Out" (LIFO), nghĩa là phần tử cuối cùng được thêm vào stack sẽ là phần tử đầu tiên được lấy ra. 
**Các thao tác cơ bản trên stack bao gồm:**
-	"push" để thêm một phần tử vào đỉnh của stack	
```c
push  -> top ++
```
-	"pop" để xóa một phần tử ở đỉnh stack.			
```c
pop -> top --
```
-	"peek/top" để lấy giá trị của phần tử ở đỉnh stack.    
-	Kiểm tra Stack đầy: top = size – 1			
```c
top (max) = size -1 -> FULL
```
-	Kiểm tra Stack rỗng: top = -1			
```c
top = -1 -> EMPTY
```
![Image](https://github.com/user-attachments/assets/c4d3ae75-3d5d-4edb-bb63-48d4a4fc2ea5)
***
### 9.1.1. Cấu trúc của 1 stack bao gôm
```c
typedef struct
{
    int *item;  // cấp phát động, mảng lưu trữ giá trị các phần tử
    int size;   // số lượng phần tử tối đa
    int top;    // chỉ số lấy giá trị ở đỉnh
} Stack;
```
***
### 9.1.2. Hàm khởi tạo stack
Sử dụng hàm malloc để cấp phát các ô nhớ lưu trữ giá trị các phần tử
```c
void init(Stack *stack, int newsize)
{
    stack->size = newsize;
    stack->item = (int*)malloc(newsize * sizeof(int));
    stack->top = -1;
}
```
***
### 9.1.3.  hàm kiểm tra Stack rỗng và đầy
•	isEmpty: Kiểm tra nếu stack rỗng (top == -1).
•	isFull: Kiểm tra nếu stack đầy (top đạt giá trị size - 1).
```c
bool isEmpty(Stack stack)
{
    return (stack.top == -1 ? true:false);
}

bool isFull(Stack stack)
{
    return (stack.top == (stack.size - 1) ? true:false);
}
```
***
### 9.1.4. hàm thêm phần tử vào trong Stack 
push: Thêm một phần tử vào đỉnh của stack. Nếu stack chưa đầy, tăng top lên và gán value vào vị trí top mới. Nếu stack đầy, thông báo tràn stack.
```c
void push(Stack *stack, int data)       // vì thao tác trực tiếp vào trong stack nên dùng pointer
{
    if(isFull(*stack))              // kiểm tra số phần tử của stack đã đầy
    {
        printf("Stack đầy, không thể thêm phần tử vào trong Stack\n");
    }
    else
    {
        // stack->top++;
        // stack->item[stack->top] = data;   
        stack->item[++stack->top] = data;   // +1 giá trị hiện tại sau đó lưu vào data
    }
}
```
***
### 9.1.5. hàm lấy/xóa phần tử trong stack 
pop: Lấy và xóa phần tử trên đỉnh của stack. Nếu stack không rỗng, trả về giá trị tại top và giảm top đi 1. Nếu stack rỗng, thông báo stack underflow và trả về -1.
```c
int pop(Stack *stack)
{
    if(isEmpty(*stack))             // kiểm tra số phần tử của stack 
    {
        printf("Stack rỗng, thêm phần tử vào\n");
        return -1;
    }
    else
    {
        int val = stack->item[stack->top];  // đọc giá tị hiện tại của đỉnh
        stack->item[stack->top--] = 0;
        return val;                         
    }
}
```
***
### 9.1.6. đọc giá trị của phần tử
```c
int top(Stack stack)            // đọc giá trị của ô nhớ
{
    if(isEmpty(stack))
    {
        printf("Stack rỗng\n");
        return -1;
    }
    else 
    {
       return stack.item[stack.top]; 
    }
}
```
***
***
## 9.2. Queue
Queue là một cấu trúc dữ liệu tuân theo nguyên tắc "First In, First Out" (FIFO), nghĩa là phần tử đầu tiên được thêm vào hàng đợi sẽ là phần tử đầu tiên được lấy ra. 
**Các thao tác cơ bản trên hàng đợi bao gồm:**
-	“enqueue” (thêm phần tử vào cuối hàng đợi)
-	“dequeue” (lấy phần tử từ đầu hàng đợi). 
-	“front” để lấy giá trị của phần tử đứng đầu hàng đợi.
-	“rear” để lấy giá trị của phần tử đứng cuối hàng đợi.
-	Kiểm tra hàng đợi đầy/rỗng.
![Image-1](https://github.com/user-attachments/assets/4cba457d-724b-44cf-bb7c-2034c8da6e84)
**Queue có 3 dạng bao gồm:**
Queue có 3 dạng bao gồm:
-	Linear Queue
    -	Nếu hàng đợi đầy thì giá trị rear = size -1 → Queue Full
    -	Nếu hàng đợi rỗng thì front == -1 hoặc front > rear → Queue Empty
-	Circular Queue
    -	queue full: 	front == (rear + 1) % SIZE
    -	queue rỗng :  queue empty: 	front == -1
-	Priority Queue: 

***
### 9.2.1. Linear Queue
Ban đầu 2 giá trị là front và rear sẽ có giá trị = -1
![Image-7](https://github.com/user-attachments/assets/e136d72a-a612-490c-bff3-103027324b89)
-	Khi có 1 giá trị được đưa vào là enqueue thì cả front và rear sẽ được tăng lên 1 giá trị = 0
![Image-8](https://github.com/user-attachments/assets/95b3dc29-266f-4840-afe3-86f4cf8396f7)
-	cứ tiếp tục thêm dữ liệu vào queue thì rear cứ tăng lên
![Image-9](https://github.com/user-attachments/assets/23abe48b-1390-4280-b7cb-b1d342af10a7)
-	lúc này thì queue đã dầy 
-	để lấy giá trị (tức dequeue) thì front sẽ tăng lên 
![Image-10](https://github.com/user-attachments/assets/8b45dea5-a024-4cd0-b578-8fe45fe474f3)
#### a) cấu trúc của Queue
```c
typedef struct
{
    int *item;  // mảng lưu trữ giá trị các phần tử, cấp phát động
    int size;   // số lượng phần tử tối đa có thể đưa vào
    int front;  // chỉ số của phần tử đầu hàng đợi
    int rear;   // chỉ số của phần tử cuối hàng đợi
} Queue;
```
#### b) hàm khởi tạo Queue
•	Cấp phát bộ nhớ cho mảng items để chứa các phần tử trong hàng đợi, với kích thước là size.
•	Gán kích thước (size) cho hàng đợi.
•	Khởi tạo 2 chỉ số là đầu hàng đợi và cuối hàng đợi với giá trị ban đầu là -1

![Image-2](https://github.com/user-attachments/assets/5ae9bc04-52aa-4d6e-b0da-8981de72fa21)
```c
// khởi tạo hàng đợi
void initialize(Queue *queue, int size)
{
    queue->size  = size;
    queue->item  = (int*)malloc(size * sizeof(int));
    queue->front = queue->rear = -1;
}
```
#### c) hàm kiểm tra Queue có đang trống/ đầy
Nếu hàng đợi đầy thì giá trị rear = size -1 → Queue Full
Nếu hàng đợi rỗng thì front == -1 hoặc front > rear → Queue Empty
```c
// kiểm tra hàng đợi đầy
bool isFull(Queue queue)
{
    return (queue.rear == queue.size - 1);
}

// kiểm tra hàng đợi rỗng
bool isEmpty(Queue queue)
{
    return (queue.front == -1 || queue.front > queue.rear);
}
```
#### d) thêm 1 phần tử vào cuối hàng đợi
Sử dụng công thức enqueue → rear ++
```c
// thêm phần tử vào cuối hàng đợi
void enqueue(Queue *queue, int data)
{
    if (isFull(*queue))
    {
        printf("Hàng đợi đầy!\n");
        return;
    }
    else
    {
        if (queue->front == -1) 
            queue->front = queue->rear = 0;
        else 
            queue->rear++;
        queue->item[queue->rear] = data;
        printf("Enqueue data %d\n", data);
    }
}
```
#### e) xóa 1 phần tử ở đầu hàng đợi
Công thức: dequeue → front ++
```c
#define QUEUE_EMPTY -1

// xóa phần tử đầu hàng đợi
int dequeue(Queue *queue)
{
    if (isEmpty(*queue))
    {
        printf("Hàng đợi rỗng!\n");
        return QUEUE_EMPTY;
    }
    else
    {
        int dequeue_value = queue->item[queue->front];

        queue->item[queue->front] = 0;

        if (queue->front == queue->rear && queue->rear == queue->size - 1)
        {
            queue->front = queue->rear = -1;
        }
        else
        {
            queue->front++;
        }
        return dequeue_value;
    }
}
```
#### Kết luận:
Linear queue không có tính linh động, vì khi lấy phần tử ra lúc queue đầy thì sẽ không lấp lại được dữ liệu mới được mà phải lấy hết ra các phần tửu ở trong đó trước rồi mới thêm mới dữ liệu vào được
- Không tận dụng được toàn bộ những ô nhớ đã cấp phát
- Khắc phục là sử dụng hàng đợi vòng tròn
***
### 9.2.2. Circular Queue
•	Ta biết rằng 1 linear queue sẽ chỉ được enqueue sau khi queue đã đày bằng cách dequeue toàn bộ phần tử bên trong nó. vậy nên ta sẽ không thể enqueue phần tử mới khi bắt đầu dequeue. Chính vì vậy ta sẽ sử dụng co chế circular queue để giải quyết được vấn đề này
![Image-3](https://github.com/user-attachments/assets/852db6f9-d41d-4fdf-a8b8-91a763d5fc46)
•	Hình trên mô tả 1 queue được dequeue 3 phần tử và chỉ số front lúc này bằng 3 đang trỏ tới phần tử thứ 4. Trong khi đó chỉ số rear = size - 1. Lúc này cơ chế circular sẽ cho phép rear trỏ đến đầu hàng đợi để enqueue tiếp
![Image-4](https://github.com/user-attachments/assets/0bb7c5ba-eee5-442a-9ace-2fd51b63f102)
•	Lúc này ta sẽ có thể tiếp tục enqueue cho đến khi các ô trống được lắp đầy
![Image-5](https://github.com/user-attachments/assets/40a8a8aa-d6c6-4971-b2cb-fc33fe726972)
•	Khi con trỏ rear đạt đến cuối mảng, nếu có vị trí trống ở phía trước, nó sẽ quay vòng lại và bắt đầu từ đầu mảng.
•	Điều này tận dụng hiệu quả toàn bộ mảng và tránh lãng phí bộ nhớ.
#### a) hàm kiểm tra Queue trống hay đầy
Qua trên , ta có thể kết luận được. điều kiện để 1 circular queue full là:
trường hợp rear = size - 1 : thì front = 0
trường hợp rear khác size - 1: thì rear = front – 1
ta có công thức tổng quát như sau
Nếu Queue full thì 	
```c
front == (rear + 1) % SIZE
```
![Image-6](https://github.com/user-attachments/assets/ff3a55a1-d068-4542-a8d1-8c5ce5068aa5)
nếu Queue rỗng thì
```c
front == -1
```
```c
// kiểm tra hàng đợi rỗng
int queue_IsEmpty(Queue queue)
{
    return (queue.front == -1);
}

// kiểm tra hàng đợi đầy
int queue_IsFull(Queue queue)
{
    return (queue.rear + 1) % queue.size == queue.front;
}
```
#### b) hàm thêm phần tử vào cuối hàng đợi
```c
// thêm phần tử vào cuối hàng đợi
void enqueue(Queue *queue, int data)
{
    if (queue_IsFull(*queue))
    {
        // nếu queue đầy thì không cho thêm phần tử vào
        printf("Hàng đợi đầy!\n");
    }
    else
    {
        if (queue->front == -1)    // Queue empty: set 2 chỉ số vào ô đầu tiên
        {
            queue->front = queue->rear = 0;
        }
        else    // rear đang ở VT max (rear = front = size) => cần đưa rear về VT 0
        {
            queue->rear = (queue->rear + 1) % queue->size;  
        }
        queue->items[queue->rear] = data;
        printf("Enqueued %d\n", data);
    }
}
```
#### c) xóa phần tử ở đầu hàng đợi
```c
#define QUEUE_EMPTY -1

// xóa phần tử từ đầu hàng đợi
int dequeue(Queue *queue)
{
    if (queue_IsEmpty(*queue))
    {
        // nếu queue rỗng thì không cho xóa
        printf("Hàng đợi rỗng\n");
        return QUEUE_EMPTY;
    }
    else
    {
        int dequeue_value = queue->items[queue->front];
        if (queue->front == queue->rear && (queue->rear ==  queue->size - 1))   // queue full
        {
            queue->front = queue->rear = -1;
        }
        else
        {
            queue->front = (queue->front + 1) % queue->size;
        }
        return dequeue_value;
    }
}
```