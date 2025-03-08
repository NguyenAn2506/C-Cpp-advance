# Binary Search - MakeFile - Binary Tree
***
# I. search - sort algorithm 
***
## So sánh Binary và Linear Search
***
![Image](https://github.com/user-attachments/assets/76334ffb-707d-4803-8ae4-c5e5e6317a06)
+ Linear Search: Mỗi phần tử trong mảng sẽ được so sánh với tất cả các phần tử còn lại và số lần kiểm tra sẽ là kích thước của mảng trừ đi 1. Đối với mảng lớn có số lượng phần tử không xác định thì cách này sẽ tốn thời gian xử lý và giảm hiệu suất CPU

+ Binary Search: Giá trị cần tìm sẽ được so sánh vói phần tử ở giữa mảng thay vì tát cả phần tử, và giá trị mid này sẽ được cập nhật qua mỗi lần kiểm tra để thu hẹp phạm vi tìm kiếm, dẫn đến hiệu suất nhanh và hiệu quả hơn. Tuy nhiên cách này sẽ yêu cầu 1 mảng đã sắp xếp
***
## 12.1. thuật toán tìm kiếm 
***
Thuật toán dùng để tìm kiếm và trả về 1 giá trị nếu nó tồn tại trong 1 mảng đã được sắp xếp bằng cách so sánh giá trị cần tìm với giá trị ở chính giữa mảng
***
### 12.1.1. Tìm kiếm tuần tự (Linear Search)
Duyệt qua từng phần tử của mảng cho đến khi tìm thấy giá trị cần tìm.
Tốt cho mảng nhỏ hoặc chưa được sắp xếp.
Chậm khi mảng lớn.
```c
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++)
        if (arr[i] == key)
            return i;
    return -1;
}
```
### 12.1.2. thuật toán tìm kiếm nhị phân (Binary Search)
Chỉ áp dụng cho mảng đã sắp xếp!
Chia đôi mảng liên tục để tìm kiếm giá trị.
Nhanh hơn tìm kiếm tuần tự rất nhiều.
![Image-4](https://github.com/user-attachments/assets/07506105-0ed9-4ef8-bec9-82166c64e947)
**Cách làm:**
Tìm phần tử giữa mid = (low + high) / 2.
Nếu arr[mid] == key, trả về mid.
Nếu arr[mid] > key, tìm trong nửa trái (high = mid - 1).
Nếu arr[mid] < key, tìm trong nửa phải (low = mid + 1).
```c
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// phiên bản đệ quy
int binarySearchRecursive(int arr[], int low, int high, int key) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] == key) return mid;
    return (arr[mid] < key) 
        ? binarySearchRecursive(arr, mid + 1, high, key)
        : binarySearchRecursive(arr, low, mid - 1, key);
}

```
## 12.2. Thuật toán sắp xếp:
### 12.2.1. thuật toán sắp xếp nổi bọt (Bubble Sort)
- Lặp qua danh sách nhiều lần, đổi chỗ các phần tử nếu không đúng thứ tự.
- Mỗi lần duyệt, phần tử lớn nhất sẽ "nổi" lên cuối mảng.
- Tốt cho mảng gần như đã sắp xếp.
```c
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
```
# II. Makefile
MakeFile là 1 chương trình dùng để biên dịch và chạy chương trình mà không cần thao tác qua các câu lệnh gcc 

**Dùng các câu lệnh sau để thực hiện**
|STT|Cột 1|
|:---|:-----:|
|make | Build chương trình|
|make run hoặc là ./main | Chạy chương trình|
|make clean |	Xóa tát cả file thực thi (xóa hết .o và .exe)|

**Ưu điểm:** 
ở lần biên dịch đầu tiên, thì makefile sẽ build toàn bộ file. Nhưng ở những lần tiếp theo, nếu có thay đổi thì makefile sẽ chỉ build những file có sự thay đổi, nếu không có sự thay đổi nào thì báo không có sự thay đổi nào

# III. Binary Tree
## 12.4. Cấu trúc dữ liệu dạng cây (Tree)
Cấu trúc dữ liệu phân cấp (Tree) là một cấu trúc dữ liệu phi tuyến tính, trong đó các phần tử (được gọi là nút, hay node) được tổ chức theo một thứ bậc phân cấp. Cây là 1 trong những cấu trúc dữ liệu quan trọng, được sử dụng rộng rãi trong khoa học máy tính để biếu diễn cá quan hệ phân cấp, tìm kiếm, săp xếp và lưu trữ

## 12.5. Cây nhị phân (Binary Tree)
Là 1 cấu trúc cây mà mỗi nút (node) có tối đa 2 nút con, được gọi là nút con trái và nút con phải
### 12.5.1. Tính chất
-	không có quy tắc cụ thể và cách sắp xếp các phần tử
-	được dùng làm nền tảng để xây dựng các loại cây phức tạp hơn (ví dụ: BST, Heap)
### 12.5.2. Quy tắc xây dựng cây nhị phân
-	mỗi phần tử có trong array / list sẽ được ánh xạ đến 1 nút trong cây nhị phân
-	cách ánh xạ đến cây:
o	phần từ tại chỉ số i trong mảng sẽ là gốc của cây non
o	chỉ số của cây con trái: 2*i+1
o	chỉ số của cây con phải: 2*i+2

**ví dụ**
![Image-9](https://github.com/user-attachments/assets/83c31de9-047d-4b94-9de9-ff6e8b82b9f5)
### 12.5.3. ứng dụng 
-	biểu diễn các quan hệ phân cấp
-	biểu diễn các biểu thức toán học (cây biểu thức)
## 12.6.  cây tìm kiếm nhị phân (BST)
 Là 1 cây nhị phân với đặc điểm đặc biệt:
-	Mỗi nút trong cây:
o	Nút trái chứa các giá trị nhỏ hơn giá trị tại nút hiện tại
o	Nút phải chứa các giá trị lớn hơn hoặc bằng giá trị tại nút hiện tại 
![Image-3](https://github.com/user-attachments/assets/876bc4c0-6f59-4164-a368-8348fb57c5ad)
**Tính chất:**
-	Thứ tự sắp xếp: các phần tử được sắp xếp, cho phép tìm kiếm nhị phân hiệu quả
-	Duyệt cây in – order sẽ trả về dánh sách giá trị theo thứ tự tăng dần
![Image-10](https://github.com/user-attachments/assets/7a52f0c4-c260-4892-9a91-1abd48317f16)
### 12.6.1. them (chèn) node va sap xep tu be den lon
Đối với việc dùng cây nhị phân thì thường sử dụng cho list, nên ta cần tạo cấu trúc cho nó
Mà đối với node thì có 2 thành phần cấn được tạo là dữ liệu và 1 con trỏ next tro đến địa chỉ node tiếp theo
```c
typedef struct Node {
    int data;
    struct Node *next;
} Node;
```
-	Đâu tiên thì khi chèn node thì ta cần tạo được node (cấp phát động bộ nhớ, gán giá trị và đặt con trỏ next là NULL)
-	Nếu địa chỉ của node đầu tiên là NULL hoặc giá trị của node đó lớn hơn value (tức là đang cần gắn node này ở trước node có giá trị bé nhất đó (đnag muốn sắp xêp đó ní)) thì 
o	Gán địa chỉ con trỏ next bằng địa chỉ của node đầu
o	Sau đó gán cho node mới thêm đó thành node đâuz tiên trong danh sách
-	Khai báo 1 biến để gán địa chỉ của node đầu tiên đó
-	Tiến hành lặp qua các node với điều kiện con trỏ next không bằng NULL (tức đang ở node cuối cùng)  và giá trị data phải bé hơn value (lặp các node từ bé đến lớn) và gắn biến con trỏ current thành node hiện tại (tạo đưuọc 1 danh sách các node sắp xếp từ bé đến lớn)
-	Gán con trỏ next cho node hiện tại và node kết tiêp
```c
//them (chèn) node va sap xep tu be den lon
void add_node(Node **head, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    if (*head == NULL || (*head)->data >= value){ 
        new_node->next = *head;
        *head = new_node;
        return;
    }

     // vừa thêm node vừa sắp xếp node
    Node *current = *head;                 
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}
```
### 12.6.2. tạo cấu trúc của cây nhị phân
Cấu trúc của 1 cây nhị phân cần 3 thành phần là giá trị, địa chỉ bên trái điểm giữa, và địa chỉ bên phải điểm giữa
```c
typedef struct CenterPoint {
    int value;
    struct CenterPoint *left;
    struct CenterPoint *right;
} CenterPoint;
```
### 12.6.3. hàm tìm  điểm giữa bên trái và điểm giữa bên phải của danh sách đã được chia
```c
//tim diem giua phia ben trai va ben phai su dung de quy
CenterPoint *buildTree(Node *head, int start, int end) {
    if (head == NULL || start > end) {          // kiểm tra danh sách hiện tại có rỗng hay so sánh 2 chỉ số
        return NULL;
    }

    int mid = (start + end) / 2;
    Node *node = head;
    for (int i = start; i < mid; i++) {             // trả về địa chỉ của node chính giữa
        if (node->next == NULL) {
            break;
        }
        node = node->next;
    }

    // xây dựng cây
    CenterPoint *root = (CenterPoint *) malloc(sizeof(CenterPoint));
    root->value = node->data;
    root->left = buildTree(head, start, mid - 1);
    root->right = buildTree(node->next, mid + 1, end);

    return root;
}
```
### 12.6.4. hàm tìm điểm giữa (node chính giữa)
```c
//tim diem giua (node chính giữa)
CenterPoint *centerPoint(Node *head) {
    // duyệt qua từng node và đếm số lượng node
    int length = 0;
    Node *node = head;
    while (node != NULL) {
        node = node->next;
        length++;
    }

    return buildTree(head, 0, length - 1);      // truyền dữ liệu vừa tính được (vị trí đầu tiên, vị trí cuối cung)
}
```
### 12.6.5.  hàm tìm kiếm nhị phân
```c
//ham tim kiem nhi phan
CenterPoint *binarySearch(CenterPoint *root, int value) {
    static int loop = 0;
    loop++;
    printf("so lan lap: %d\n", loop);
    if (root == NULL) {
        return NULL;
    }

    if (root->value == value) {
        return root;
    }

    if (value < root->value) {
        return binarySearch(root->left, value);
    } else {
        return binarySearch(root->right, value);
    }
}
```
# IV. File Operation
Ngôn ngữ lập trình C cung cấp một số thư viện và hàm tiêu biểu để thực hiện các thao tác với file. 
File CSV (Comma-Separated Values) là một loại file văn bản được sử dụng để lưu trữ và truyền tải dữ liệu có cấu trúc dưới dạng bảng, trong đó các dữ liệu của các cột được phân tách bằng dấu phẩy (,) hoặc một ký tự ngăn cách khác.
## 12.7. mở file
Để mở một file, bạn có thể sử dụng hàm fopen(). Hàm này trả về một con trỏ FILE, và cần được kiểm tra để đảm bảo file đã mở thành công.
**cú pháp**
```c
FILE *file = fopen(const char *file_name, const char *access_mode);
```
**1 số chế độ khác**

![Image-11](https://github.com/user-attachments/assets/00dca002-76b8-41a3-9646-79d5be9892cf)
![Image-12](https://github.com/user-attachments/assets/ddfe0f3e-6b8f-4ee0-a0b0-3c78676370a0)
![Image-13](https://github.com/user-attachments/assets/0400b18c-2c04-4bef-a402-0ca7f8bf058f)
## 12.8. Đọc File
![Image-14](https://github.com/user-attachments/assets/98626d53-9d63-42e4-b313-8764132c5c2e)
![Image-15](https://github.com/user-attachments/assets/b5bec4c5-c7a2-405c-a9e5-b89a9d9ddfb9)

Một số hàm khác:
-	fclose(): Đóng File đã mở
-	feof(): Để kiểm tra địa chỉ hiện tại có phải ký tự cuối cùng của File hay chưa

