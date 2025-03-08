# Bài 10: Linked List
***
## 10.1.	Khái niệm Linked List
***
Linked list là một cấu trúc dữ liệu trong lập trình máy tính, được sử dụng để tổ chức và lưu trữ dữ liệu. Một linked list bao gồm một chuỗi các "nút" (nodes), mỗi nút chứa một giá trị dữ liệu và một con trỏ (pointer) đến nút tiếp theo trong chuỗi.
Và các node này không liền kề với nhau (khác với mảng là các địa chỉ là liền kề)
**Ví dụ: các địa chỉ của các node là ngẫu nhiên**
- Node 1 là 0x01 
- Node 2 là 0xcf 
- …
Và các node này cần phải dược liên kết với nhau thì mới có thể tạo nên 1 danh sách liên kết
*** 
## 10.2.	Liên kết các node
Để mà liên kết các node lại với nhau thif:
-	mỗi node chứa 1 giá trị dữ liệu và 1 con trỏ (lưu trữ địa chỉ) liên kết đến node tiếp theo trong danh sách
### 10.2.1.	Khởi tạo node
```c
// khởi tạo 1 node mới         
node* createNode(int data)          // trả về 1 địa chỉ
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}
```
***
## 10.3.	các thao tác với node trong danh sách liên kết 
***
### 10.3.1.	thêm 1 node ở đầu danh sách
![Image](https://github.com/user-attachments/assets/0c5c579b-8a43-495b-8325-a6b142675450)
**ý nghĩa:**
-	tạo 1 node mới 
-	gán con trỏ next của node mới thành địa chỉ của node kế tiếp 
-	gán node mới thành node đầu tiên trong danh sách
```c
// thêm 1 node vào đầu danh sách (push_front)
void push_front(Node **head, int data)
{
    Node *new_node = createNode(data);

    if(*head == NULL)   // danh sách đang rỗng
    {
        *head = new_node;
    }
    else        // NULL -> &head
    {
        new_node -> next = *head;       // *head = & node 1         (thành node 2)
        *head = new_node;           // gán cho newcode thanh node đầu tiên (node 1)
    }
}
```
### 10.3.2.	Hàm hiển thị các node 
Do không biết số lượng các node nên cần phải dùng vòng lặp while
```c
// hàm hiển thị danh sách hiện tại
void display(Node *head)            // Hàm này chỉ để đọc nên chỉ cần dùng pointer level 1
{
    int index = 0;
    if(head == NULL)
    {
        printf("Khong co node nao\n");
    }
    else        // duyệt qua từng node
    {           // do các node không liền kề nhau nên dùng while
        while(head != NULL)         // duyệt qua đến phần tử cuối cùng
        {
            printf("Node %d: %d\n", index, head -> data);
            index++;
            head = head->next;          // trỏ tới next tiếp theo khi head không băng NULL
        }
    }
}
```

### 10.3.3.	Thêm 1 node ở cuối danh sách
![Image-1](https://github.com/user-attachments/assets/dcc93940-72ab-4f3a-b2b4-99b215f76d4b)
**ý nghĩa**
-	Tạo 1 node mới 
-	Lặp qua từng node ở danh sách hiện tại, đến khi có node chứa con trỏ next là NULL thì dừng, Do không biết số lượng các node nên cần phải dùng vòng lặp while
-	Thay thế giá trị mà con trỏ next đang chứa thành địa chỉ của node mới.
-	Lúc này giá trị con trỏ next của node mới thêm là NULL (vòng lặp while dừng)

```c
// thêm 1 node vào cuôi danh sách
void push_back(Node **head, int data)
{
    Node *new_node = createNode(data);

    if(*head == NULL)   // danh sách đang rỗng
    {
        *head = new_node;
    }
    else 
    {
        Node *p = *head;
        while(p->next != NULL)  
        {
            p = p->next;
        }
        p -> next = new_node;
    }
}
```
### 10.3.4.	Đếm số lượng node trong list
```c
// đếm số lượng node trong list
int size(Node *head)           // đọc thôi không có nhu cầu xóa
{
    int count = 0;
    if(head == 0)   return 0;
    while(head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}
```
### 10.3.5.	Thêm 1 node bất kỳ vào trong list
![Image-2](https://github.com/user-attachments/assets/da6506d6-1364-4768-b551-7b6873737c1b)
**Ý nghĩa:**
-	Cần phải biết được ví trí cần thêm node là ở đâu => đánh dấu các node thông qua hàm size (10.4.4)
-	Tạo 1 node mới 
-	Lặp qua từng node kèm điều kiện dừng là ở trước vị trí cần chèn
-	Gán giá trị của con trỏ next thành địa chỉ của node tiêp theo và đặt địa chỉ cho node mới và node cũ
```c
// thêm 1 node vào 1 vị trí bất kỳ trong list
void insert(Node **head, int data, int position)
{
    if(position == 0 )              // ví trị đầu tiên trong list
    {
        push_front(head, data);
    }
    else if(position == (size(*head) - 1))  // vị trí cuối cùng trong list
    {
        push_back(head, data);
    }
    else                    // các vị trí còn lại
    {
        // tạo 1 Node mới
        Node *new_node = createNode(data);

        if(*head == NULL)   // danh sách đang rỗng
        {
            *head = new_node;
        }
        else 
        {
            // tạo node trung gian lưu vị trí node đầu tiên
            Node *p = *head;
            // khởi tạo biến lưu thứ tự các node 
            int index = 0;     // = 0 chứ không phải -1 : rơi vào trong TH có ít nhất 1 node nên không cần khai báo = -1
            while((p != NULL) && (index != (position-1)))  
            {
                p = p->next;
                index++;
            }
            if(index == position - 1 )
            {
                new_node -> next = p -> next;   // NULL -> 0xef
                p -> next = new_node;           // 0xef -> 0xa3
                
            }
        }
    }
}
```
### 10.3.6.	Xóa 1 node ở cuối danh sách
![Image-3](https://github.com/user-attachments/assets/3b998792-2621-4563-b4d7-5b874c323291)
**Ý nghĩa:**
-	Lặp qua từng node trong list đến node kề cuối thì dừng
-	Tiến hành giải phóng node cuối cùng
-	Và gán con trỏ next tại vị trí kề cuối là NULL
```c
// xóa node cuối cùng trong list
void pop_back(Node **head)
{
    if(*head == NULL)   printf("Khong co Node");
    else
    {
        Node *p = *head;
        int index = 0;
        while(p != NULL && index != size(*head) - 2)
        {
            index++;
            p = p->next;
        }
        if(index == size(*head)-2)
        {
            free(p->next);          // thu hồi node cuối cùng
            p-> next = NULL;        // thay đổi lại con trỏ next ở node kế cuối thành NULL
        }
    }   
}
```
### 10.3.7. Xóa 1 node ở đầu danh sách
![Image-5](https://github.com/user-attachments/assets/94fff965-8b47-4102-94ad-ae9c88a09714)
-	Kiểm tra danh sách rỗng
-	Lưu địa chỉ của node đầu tiên
-	Cập nhật head đến node tiếp theo
-	Giải phóng bộ nhớ node cũ

```c
// xoa node dau tien
void pop_front(Node **head)
{
    if(*head == NULL) printf("Khong co Node\n");
    else 
    {
        // tao bien trung gian luu vi tri node dau tien
        Node *p = *head;
        *head = (*head)->next;  // cap nhat head den node tiep theo
        free(p);
    }
}
```
### 10.3.8. Xóa node bất kỳ trong danh sách
![Image-6](https://github.com/user-attachments/assets/3e846ade-857b-4d20-8fda-30a6afb92a43)
-	Kiểm tra danh sách có rỗng không
-	2 TH đầu và cuối danh sách dùng hàm (10.4.6) , (10.4.7)
-	Lưu node đầu tiên
-	Lặp qua đến vị trí cần xóa, tăng thứ tự sau mỗi lần lặp
-	Thay đổi con trỏ next thành head (địa chỉ node) kế tiêp 

```c
// xoa 1 node tai mot vi tri bat ky
void erase(Node **head, int position)
{
    if(*head == NULL)   printf("Khong co Node");
    else if(position == 0)
    {
        pop_front(head);
    }
    else if(position == size(*head))
    {
        pop_back(head);
    }
    else
    {
        int index = 0;      // TH list co it nhat 1 node 
        Node *p = *head;    // luu node dau tien cho p
        Node *prev = NULL;
        while((p != NULL) && (index != position-1))   // lap qua tung node den khi dung tai ben trai node can xoa
        {
            prev = p;
            p = p->next;
            index++;
        }
        if(index == position -1)
        {
            prev->next = p->next;    // thay doi next thanh head ke tiep
            free(p);
        }
    }
}
```