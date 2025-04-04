# Introduction to UML
***
## 1. UML là gì?
***
Ngôn ngữ mô hình hóa thống nhất (tiếng Anh: Unified Modeling Language, viết tắt thành UML) là một ngôn ngữ mô hình gồm các ký hiệu đồ họa mà các phương pháp hướng đối tượng sử dụng để thiết kế các hệ thống thông tin một cách nhanh chóng. 

UML (ngôn ngữ mô hình hóa thống nhất) là 1 ngôn ngữ dạng kiến trúc và nó được sử dụng như 1 phương thức giao tiếp
***
## 2. Tác dụng của UML trong phát triển phần mềm
***
Dưới đây là một số tác dụng chính của UML trong phát triển phần mềm:

### 2.1. Phân tích và thiết kế hệ thống
***
UML cho phép các nhà phát triển và các bên liên quan hình dung hệ thống thông qua các biểu đồ khác nhau, giúp hiểu rõ cấu trúc và hành vi của hệ thống trước khi bắt đầu quá trình lập trình. Điều này là cực kỳ quan trọng trong việc định hình yêu cầu và giảm thiểu rủi ro sai sót trong quá trình phát triển.

### 2.2. Tài liệu hóa hệ thống
***
UML cung cấp một phương tiện tiêu chuẩn để tài liệu hóa các yếu tố của hệ thống, bao gồm cấu trúc dữ liệu, logic kinh doanh, luồng công việc, và các tương tác giữa các đối tượng. Việc tài liệu hóa giúp đảm bảo rằng thông tin về hệ thống có thể được chia sẻ một cách dễ dàng và hiệu quả giữa các nhóm phát triển và bảo trì.

### 2.3. Giao tiếp
***
UML cung cấp một ngôn ngữ chung cho các nhà phát triển, kiến trúc sư, quản lý dự án, và các bên liên quan khác, giúp cải thiện giao tiếp và hiểu biết chung về hệ thống. Sử dụng UML giảm thiểu khả năng hiểu lầm và sai sót trong quá trình thiết kế và phát triển.

### 2.4. Quản lý rủi ro và đánh giá tác động
***
UML cho phép các nhà phát triển và quản lý dự án đánh giá tác động của các thay đổi trước khi chúng được thực hiện, giúp quản lý rủi ro một cách hiệu quả. Các biểu đồ UML giúp nhìn nhận trước được các vấn đề tiềm ẩn và tìm ra giải pháp trước khi chúng trở nên nghiêm trọng.
***
## 3. Cách xây dựng các mô hình trong UML
***
- Cách xây dựng các mô hình trong UML phù hợp mô tả các hệ thống thông tin cả về cấu trúc cũng như hoạt động. 
- Cách tiếp cận theo mô hình của UML giúp ích rất nhiều cho những người thiết kế và thực hiện hệ thống thông tin cũng như những người sử dụng nó; tạo nên một cái nhìn bao quát và đầy đủ về hệ thống thông tin dự định xây dựng. 
- Cách nhìn bao quát này giúp nắm bắt trọn vẹn các yêu cầu của người dùng; phục vụ từ giai đoạn phân tích đến việc thiết kế, thẩm định và kiểm tra sản phẩm ứng dụng công nghệ thông tin. 
- Các mô hình hướng đối tượng được lập cũng là cơ sở cho việc ứng dụng các chương trình tự động sinh mã trong các ngôn ngữ lập trình hướng đối tượng, chẳng hạn như ngôn ngữ C++, Java,... Phương pháp mô hình này rất hữu dụng trong lập trình hướng đối tượng. Các mô hình được sử dụng bao gồm Mô hình đối tượng (mô hình tĩnh) và Mô hình động.
***
## 4. Các loại UML hay dùng
***
UML sử dụng một hệ thống ký hiệu thống nhất biểu diễn các Phần tử mô hình (model elements). Tập hợp các phần tử mô hình tạo thành các Sơ đồ UML (UML diagrams). Có các loại sơ đồ UML chủ yếu sau:

- Sơ đồ lớp (Class Diagram)
- Sơ đồ đối tượng (Object Diagram)
- Sơ đồ tình huống sử dụng (Use Cases Diagram)
- Sơ đồ trình tự (Sequence Diagram)
- Sơ đồ cộng tác (Collaboration Diagram hay là Composite Structure Diagram)
- Sơ đồ trạng thái (State Machine Diagram)
- Sơ đồ thành phần (Component Diagram)
- Sơ đồ hoạt động (Activity Diagram)
- Sơ đồ triển khai (Deployment Diagram)
- Sơ đồ gói (Package Diagram)
- Sơ đồ liên lạc (Communication Diagram)
- Sơ đồ tương tác (Interaction Overview Diagram - UML 2.0)
- Sơ đồ phối hợp thời gian (Timing Diagram - UML 2.0)

![Image](https://github.com/user-attachments/assets/bb502668-b620-4c03-a362-3e82b5180ba8)

Mỗi loại phục vụ một mục đích cụ thể, có thể tạm chia UML thành 2 nhóm chính, chứa các loại UML hay dùng như sau:

- Behavior diagrams (Biểu đồ hành vi): Use case digram, activity diagram, sequence diagram.
- Structure diagrams (Biểu đồ cấu trúc): Class diagram, component diagram, deployment diagram.

### 4.1. Biểu đồ Use case (Use Case Diagram)
***
Use case diagram tập trung vào việc mô tả chức năng của hệ thống từ quan điểm của người dùng cuối. Nó hiển thị các tình huống sử dụng cụ thể (use case) và các actor liên quan, giúp làm rõ các yêu cầu và tương tác giữa người dùng và hệ thống, qua đó đảm bảo rằng sản phẩm phần mềm cuối cùng sẽ đáp ứng được nhu cầu thực tế.

Use case diagram thường được sử dụng trong giai đoạn thu thập yêu cầu và phân tích yêu cầu của dự án phần mềm.

#### 4.1.1. các thành phần chính của use case diagram
Use case diagram bao gồm 4 thành phần chính:

**a) Actor:**
- Actor: Đại diện cho một người dùng hoặc một hệ thống bên ngoài tương tác với hệ thống Actors có thể là người dùng cuối, hệ thống bên ngoài, hoặc quá trình tự động. Trong biểu đồ, một actor thường được biểu diễn bằng một hình người.
- tác nhân được kí hiệu là 
![Image](https://github.com/user-attachments/assets/fa125f26-3e3a-4bce-9da4-2b0d74b07de5)
**b) Use case**
- Use case: Một use case mô tả một chuỗi hành động mà hệ thống thực hiện để mang lại kết quả có giá trị cho một actor. Mỗi Use case thể hiện một chức năng cụ thể hoặc một quy trình công việc mà hệ thống cần phải thực hiện.
- các Use case được kí hiệu bằng hình Elips
![Image](https://github.com/user-attachments/assets/c66ca55a-d11b-4a19-bf6b-6bd075603626)
**c) Mối quan hệ:**
- Mối quan hệ: Mối quan hệ giữa các actors và use cases được mô tả thông qua 4 kiểu khác nhau là association, extend, include và generalization. Mối quan hệ này giúp làm rõ cách các actors tương tác với use cases và mối liên hệ giữa các use cases với nhau.
- mỗi quan hệ giữa các use case:
  + Association: thường được dùng để mô tả mối quan hệ giữa Actor và Use Case và giữa các Use Case với nhau
![Image](https://github.com/user-attachments/assets/5b2d07f7-170a-4092-99d1-65047df39802)
  ví dụ quan hệ association
![Image](https://github.com/user-attachments/assets/22f1cd85-2c3e-40d2-bb90-a2bd171b6313)
  + Include: là quan hệ giữa các Use Case với nhau, nó mô tả việc một Use Case lớn được chia ra thành các Use Case nhỏ để dễ cài đặt (module hóa) hoặc thể hiện sự dùng lại.
![Image](https://github.com/user-attachments/assets/beae3c31-4cdd-4a0b-92e7-ca7cbd1e1a71)
  ví dụ quan hệ include
![Image](https://github.com/user-attachments/assets/9ee9977e-c68f-4e3c-a511-d18084a58864)
  + Extent: Extend dùng để mô tả quan hệ giữa 2 Use Case. Quan hệ Extend được sử dụng khi có một Use Case được tạo ra để bổ sung chức năng cho một Use Case có sẵn và được sử dụng trong một điều kiện nhất định nào đó.
![Image](https://github.com/user-attachments/assets/7a40effc-9024-48ef-bac3-d2e10e64bb01)
  Ví dụ quan hệ extent
![Image](https://github.com/user-attachments/assets/0575d979-21d2-481a-98e9-fd07eea31077)
  + Generalization: được sử dụng để thể hiện quan hệ thừa kế giữa các Actor hoặc giữa các Use Case với nhau.
![Image](https://github.com/user-attachments/assets/fb28d912-94ec-4d7c-b0cb-3dfaa2a1c0d3)
  Ví dụ quan hệ Generalization
![Image](https://github.com/user-attachments/assets/0e32f1e9-29f1-4971-b859-8918379c9a81)
**d) Hệ thống:**
- Hệ thống: Là ranh giới chỉ ra phạm vi của hệ thống đang được mô tả. Mọi use case đều nằm bên trong ranh giới của hệ thống, và các actor thì nằm bên ngoài.

#### 4.1.2. các bước cơ bản để tạo use case diagram
Các bước cơ bản để tạo use case diagram bao gồm:

Phân tích yêu cầu của hệ thống
Xác định actors: Xác định ai sẽ sử dụng hệ thống, bao gồm cả người dùng cuối và các hệ thống khác có tương tác.
Xác định use cases: Liệt kê tất cả các chức năng mà hệ thống phải cung cấp cho các actors. Điều này bao gồm cả việc mô tả chi tiết các bước thực hiện cho mỗi chức năng.
Mô tả mối quan hệ: Mô tả các mối quan hệ giữa các use cases (như extend và include) và giữa actors và use cases thông qua các ký hiệu cụ thể (được gọi là notation).
Vẽ biểu đồ: Sử dụng các biểu tượng tiêu chuẩn để vẽ actors, use cases, và mô tả các mối quan hệ giữa chúng.
#### 4.1.3. ví dụ về use case diagram
Để mô tả cách tạo use case diagram, tôi sẽ lấy ví dụ về hệ thống cho mượn sách.

Dưới đây là những requirement của hệ thống:

- Mô hình kinh doanh chủ yếu từ việc cho mượn sách.
- Người dùng phải đăng ký thẻ thành viên để thuê sách, với mức phí làm thẻ dựa trên các gói Basic, Standard và Premium. Người dùng có thể thanh toán bằng tiền mặt hoặc qua ví điện tử.
- Khi người dùng đăng ký mượn sách, nếu sách đã bị thành viên khác mượn, hệ thống sẽ ghi nhận lại và thông báo qua email và tin nhắn khi sách được hoàn trả.
- Khi người dùng đăng ký mượn sách, nếu sách không tồn tại trong hệ thống thì hệ thống sẽ ghi nhận và thông báo qua email và tin nhắn khi sách được nhập về.
- Thủ thư là người tiếp nhận các yêu cầu đăng ký thành viên, mượn/trả sách.
- Hệ thống sẽ gửi email đề xuất các đầu sách phù hợp cho từng thành viên.

Từ những requirement trên, chúng ta thấy hệ thống bao gồm có 3 actor: thành viên (member), thủ thư (librarian) và hệ thống (system).

**Các use case của hệ thống bao gồm:**

- Đăng ký thẻ thành viên (Register for a membership card)
- Thanh toán (Payment) bằng tiền mặt (With cash) hoặc bằng ví điện tử (With eWallet).
- Mượn sách (Borrow book)
- Trả sách (Return book)
- Đăng ký mượn sách chưa có trong cửa hàng (Pre-register if book is not available).
- Đặt hàng sách mới (Restock book).
- Thông báo sách được trả qua email (Notify return timings via email).
- Thông báo sách được trả qua tin nhắn (Notify return timings via phone message).
- Thông bao sách mới đã về qua email (Notify restock timings via email).
- Thông bao sách mới đã về qua tin nhắn (Notify restock timings via phone message).

Tôi vẽ được use case diagram như hình dưới. Trong đó, hình chữ nhật màu xanh lá biểu diễn cho hệ thống. Các hình elip màu trắng nằm trong hình chữ nhật xanh lá là các use case của hệ thống. Hình người là các actor. Người dùng trong hệ thống sẽ có 2 loại là member và librarian.
![Image](https://github.com/user-attachments/assets/4d8badb6-935b-46a2-a619-c0a2bd8f67bb)

### 4.2. Biểu đồ lớp (class Diagram)
***
Class diagram là một trong những loại biểu đồ UML phổ biến nhất, cung cấp cái nhìn tổng quan về cấu trúc của hệ thống. Nó mô tả các class, properties, method và mối quan hệ giữa chúng, như kế thừa và liên kết, giúp xác định rõ cấu trúc và thiết kế của phần mềm.

#### 4.2.1. các thành phần chính của class diagram
Class diagram bao gồm 3 thành phần chính:
**a) Class**
- Class: Được biểu diễn bằng một hình chữ nhật chia làm ba phần: tên class, thuộc tính, và phương thức.
![Image](https://github.com/user-attachments/assets/3ec2ebd1-6182-4b83-8e3d-2d7ec75d4e7f)
**b) Interface**
- Interface: Được biểu diễn tương tự như class nhưng với từ khóa «interface».

**c) Mối quan hệ** 
- Mối quan hệ: Mối quan hệ giữa các class và interface được mô tả thông qua 6 kiểu khác nhau là association, inheritance , implementation, dependency, aggregation và composition.
- Liên kết (Association)
  + Mối liên hệ ngữ nghĩa giữa hai hay nhiều lớp chỉ ra sự liên kết giữa các thể hiện của chúng
  + Mối quan hệ về mặt cấu trúc chỉ ra các đối tượng của lớp này có kết nối với các đối tượng của lớp khác.
![Image](https://github.com/user-attachments/assets/7dc9f3aa-90a8-4bd6-8772-07a4612a8550)
  Bội số quan hệ: là số lượng thể hiện của một lớp liên quan tới một thể hiện của lớp khác. Với mỗi liên kết, có hai bội số quan hệ cho hai đầu của liên kết.
  Ví dụ:
![Image](https://github.com/user-attachments/assets/7f875e0f-b896-4902-b74b-9c859b574c70)
  Với mỗi đối tượng của Professor, có nhiều Course Offerings có thể được dạy. Với mỗi đối tượng của Course Offering, có thể có 1 hoặc 0 Professor giảng dạy.

- Biểu diễn bội số quan hệ:
![Image](https://github.com/user-attachments/assets/a079a198-ca3b-4e2b-bf8d-ad8ca7cc6b0f)
- Kết tập (Aggregation)

    + Là một dạng đặc biệt của liên kết mô hình hóa mối quan hệ toàn thể-bộ phận (whole-part) giữa đối tượng toàn thể và các bộ phận của nó.
    + Kết tập là mối quan hệ “là một phần” (“is a part-of”).
    + Bội số quan hệ được biểu diễn giống như các liên kết khác
    ![Image](https://github.com/user-attachments/assets/8015ec87-dbe4-40e1-9b13-aca40009cd53)
    + Cấu thành (Composition) là :Một dạng của kết tập với quyền sở hữu mạnh và các vòng đời trùng khớp giữa hai lớp
    + Whole sở hữu Part, tạo và hủy Part.
    + Part bị bỏ đi khi Whole bị bỏ, Part không thể tồn tại nếu Whole không tồn tại.
    ![Image](https://github.com/user-attachments/assets/f1ca0f4c-7aa9-4cde-be99-d836c3d68b42)
- Sự khác nhau giữa Association, Aggregation và Composition
  ![Image](https://github.com/user-attachments/assets/ccd4a77d-9f76-462b-98a4-85f899a139a9)
- Tổng quát hóa (Generalization)

    + Mối quan hệ giữa các lớp trong đó một lớp chia sẻ cấu trúc và/hoặc hành vi với một hoặc nhiều lớp khác
    + Xác định sự phân cấp về mức độ trừu tượng hóa trong đó lớp con kế thừa từ một hoặc nhiều lớp cha
        ▫ Đơn kế thừa (Single inheritance)
        ▫ Đa kế thừa (Multiple inheritance)
    + Là mối liên hệ “là một loại” (“is a kind of”)
    + Lớp trừu tượng và lớp cụ thể (Abstract and Concrete Class)
    ![Image](https://github.com/user-attachments/assets/422be72b-77a1-4ab3-9b94-637a245db181)
#### 4.2.2. gói
Nếu đang mô hình hóa một hệ thống lớn hoặc một lĩnh vực nghiệp vụ lớn, thì không thể tránh khỏi, sẽ có nhiều phân loại khác nhau trong mô hình của bạn. Việc quản lý tất cả các lớp có thể là một nhiệm vụ khó khăn, do vậy UML cung cấp một phần tử tổ chức được gọi là gói. Các gói cho phép các nhà tạo mô hình tổ chức các phân loại của mô hình thành các vùng tên, là một kiểu giống như các thư mục trong một hệ thống tệp. Việc phân chia một hệ thống thành nhiều gói làm cho hệ thống trở nên dễ hiểu, đặc biệt là nếu từng gói đại diện cho một phần cụ thể của hệ thống

Có hai cách để vẽ các gói trên sơ đồ. Không có quy tắc để xác định xem ký pháp nào sẽ được sử dụng, ngoại trừ việc tuân theo phán xét riêng của bạn về việc ký pháp nào là dễ đọc các sơ đồ lớp mà bạn đang vẽ nhất. Cả hai cách sẽ bắt đầu bằng một hình chữ nhật lớn với một hình chữ nhật nhỏ hơn (phiếu) nằm ở phía trên cùng bên trái nó, như trong . Nhưng nhà tạo mô hình phải quyết định cách thể hiện các thành viên của gói như thế nào, ví dụ như sau:
![Image](https://github.com/user-attachments/assets/a3418424-91a9-43c2-8cda-d0cd13bc1f12)
Nếu nhà tạo mô hình quyết định hiển thị các thành viên của gói bên trong hình chữ nhật lớn, thì tất cả các thành viên4 sẽ phải được đặt trong hình chữ nhật đó. Cũng vậy, tên của gói cần được đặt trong hình chữ nhật nhỏ hơn của gói Nếu nhà tạo mô hình quyết định hiển thị các thành viên của gói bên ngoài hình chữ nhật lớn, thì tất cả các thành viên sẽ được hiển thị trên sơ đồ cần phải được đặt ở bên ngoài hình chữ nhật ấy. Để cho thấy phân loại nào thuộc về gói, thì một đường thẳng sẽ được vẽ từ từng phân loại đến một vòng tròn có dấu cộng (+) bên trong vòng tròn gắn liền với gói.
![Image](https://github.com/user-attachments/assets/3c695b14-7a24-4009-9aae-d9615d0973e0)

**Tổng kết**
các ký hiệu trong class diagram
![Image](https://github.com/user-attachments/assets/caa93c3a-a389-42e7-8b51-d72931d058db)

#### 4.2.2. các bước cơ bản để tạo class diagram

Các bước cơ bản để tạo class diagram bao gồm:

- Phân tích yêu cầu của hệ thống
- Xác định class và interface: Xác định class và interface từ yêu cầu của hệ thống.
- Xác định thuộc tính và phương thức: Liệt kê tất cả các thuộc tính và phương thức mà class/interface phải cung cấp dựa vào chức năng và nhiệm vụ của chúng.
- Mô tả mối quan hệ: Mô tả các mối quan hệ giữa các class (như extend và include) và giữa class và interface thông qua các ký hiệu cụ thể (được gọi là notation).
- Vẽ biểu đồ: Sử dụng các biểu tượng tiêu chuẩn để vẽ class, interface và mô tả các mối quan hệ giữa chúng.

#### 4.2.3. Ví dụ về class diagram
Sử dụng bài toán thiết kế hệ thống cho mượn sách ở ví dụ về use case diagram ở mục 3.1.3 để vẽ class diagram.
![Image](https://github.com/user-attachments/assets/96f390f9-d56d-4123-9a84-5e55ce89c445)


### 4.3. Component diagram
***
Component diagram được sử dụng để biểu diễn các thành phần phần mềm khác nhau và mối quan hệ giữa chúng trong hệ thống. Biểu đồ này chủ yếu tập trung vào các khía cạnh vật lý của hệ thống phần mềm, bao gồm việc triển khai và tổ chức của code, thư viện, và các mô-đun.
#### 4.3.1. các thành phần chính của component diagram
Component diagram bao gồm 3 thành phần chính:

- Component: Được biểu diễn bằng một hình chữ nhật có biểu tượng bốn hình chữ nhật nhỏ ở góc. Mỗi thành phần đại diện cho một mô-đun của code hoặc một nhóm các chức năng có liên quan, ví dụ như một thư viện, một gói phần mềm, hoặc một dịch vụ web.
- Interface: Mô tả một tập các hoạt động mà một component cung cấp hoặc yêu cầu từ các component khác. Interface được biểu diễn bằng một hình chữ nhật nhỏ hoặc một hình lục giác đính kèm bên ngoài thành phần.
- Quan hệ phụ thuộc: Mô tả sự phụ thuộc giữa các thành phần, chẳng hạn như khi một thành phần sử dụng dịch vụ hoặc chức năng từ thành phần khác.

#### 4.3.2. các bước cơ bản để tạo component diagram
Các bước cơ bản để tạo component diagram bao gồm:

- Phân tích yêu cầu của hệ thống
- Xác định component và interface: Xác định class và interface từ yêu cầu của hệ thống.
- Mô tả mối quan hệ: Mô tả các mối quan hệ giữa các class (như extend và include) và giữa class và interface thông qua các ký hiệu cụ thể (được gọi là notation).
- Vẽ biểu đồ: Sử dụng các biểu tượng tiêu chuẩn để vẽ component, interface và mô tả các mối quan hệ giữa chúng.

#### 4.3.3. Ví dụ về component diagram
Ví dụ về component diagram cho BookService và RequestService.
![Image](https://github.com/user-attachments/assets/7dc49318-ff59-45ea-b69b-545cedfd0f68)

### 4.4. Sequence diagram
***
Sequence diagram chủ yếu tập trung vào cách các đối tượng trong hệ thống tương tác với nhau theo thời gian. Nó mô tả trình tự các thông điệp được trao đổi giữa các đối tượng để thực hiện một chức năng, là công cụ hữu ích để phân tích và thiết kế luồng điều khiển.

#### 4.4.1. Các thành phần chính của sequence diagram
Component diagram bao gồm 4 thành phần chính:

- Object or class: Được biểu diễn bằng một hình chữ nhật trên cùng của một cột và có tên đối tượng bên trong. Mỗi đối tượng có một cột thời gian (lifeline) xuống dưới, biểu diễn trên trục dọc.
![Image](https://github.com/user-attachments/assets/46587f31-3b11-42a9-af85-16750b530246)
- Lifeline: Một đường thẳng dọc biểu diễn sự tồn tại của đối tượng trong quá trình tương tác.
![Image](https://github.com/user-attachments/assets/67c0fb89-b71e-4788-8e13-76089041cf88)
- Message: Các thông điệp hoặc hành động được truyền từ đối tượng này sang đối tượng khác, biểu diễn bằng mũi tên. Thông điệp có thể là đồng bộ (solid line), bất đồng bộ (dashed line), hoặc trả về (dotted line).
![Image](https://github.com/user-attachments/assets/d351ad18-70ae-499a-8423-44a4c1883b14)
- Activation: Một hình chữ nhật nhỏ trên lifeline chỉ thời gian một đối tượng thực hiện một hành động nào đó.
  + Xử lí bên trong đối tượng (biểu diễn bằng các đoạn hình chữ nhật rỗng nối với các đường đời đối tượng)
    ![Image](https://github.com/user-attachments/assets/98ebf915-1d66-4c0f-9ac6-3394a2373bc6)

#### 4.3.2. các loại thông điệp trong biểu đồ tuần tự
**a) Thông điệp đồng bộ (Synchronous Message)**

Thông điệp đồng bộ cần có một request trước hành động tiếp theo.
![Image](https://github.com/user-attachments/assets/c57dd42e-37e9-42a4-b165-aaa39892154d)
**b) Thông điệp không đồng bộ (Asynchronous Message)**

Thông điệp không đồng bộ không cần có một request trước hành động tiếp theo.
![Image](https://github.com/user-attachments/assets/162f7a39-8a2c-49a9-936d-247fbe88373f)
**c) Thông điệp chính mình (Self Message)**

Là thông điệp mà đối tượng gửi cho chính nó để thực hiện các hàm nội tại.
![Image](https://github.com/user-attachments/assets/fcecba01-fa2c-4e1f-a58e-0860c3c29c87)
**d) Thông điệp trả lời hoặc trả về (Reply or Return Message)**

Là thông điệp trả lời lại khi có request hoặc sau khi kiểm tra tính đúng đắn của một điều kiện nào đó. Ví dụ thông điệp loại này như tin nhắn trả về là success hoặc fail
![Image](https://github.com/user-attachments/assets/04eca633-d426-4bc8-9735-d88b7135ab4f)

**e) Thông điệp tạo mới (Create Message)**

Là thông điệp được trả về khi tạo mới một đối tượng.
![Image](https://github.com/user-attachments/assets/3a02b148-b73a-4f1a-8118-e567214de8aa)

**f) Thông điệm xóa (Delete Message)**

Là thông điệp được trả về khi xóa một đối tượng.
![Image](https://github.com/user-attachments/assets/bde1e94e-4cf2-462f-a993-a8d16152b739)
#### 4.4.3. các bước cơ bản để tạo sequence diagram
Các bước cơ bản để tạo sequence diagram bao gồm:
- Phân tích yêu cầu của hệ thống
- Xác định object: Xác định các object từ yêu cầu của hệ thống.
- Mô tả lifeline của object: Vẽ một lifeline dọc cho mỗi đối tượng đã xác định. Lifeline biểu diễn sự tồn tại của một đối tượng trong quá trình tương tác được mô tả.
- Xác định message: Xác định tất cả các message (hoặc hành động) diễn ra giữa các object trong quá trình và thêm chúng vào biểu đồ. Message được biểu diễn dưới dạng mũi tên giữa các lifeline. Mỗi message nên có tên và được sắp xếp theo trình tự thời gian từ trên xuống dưới.
- Mô tả activation: Activation biểu diễn khoảng thời gian một đối tượng thực hiện một công việc nào đó. Nếu cần, bạn có thể thêm các hình chữ nhật nhỏ trên lifeline để mô tả thời gian thực thi của một hành động hoặc quy trình.
- Vẽ biểu đồ: Sử dụng các biểu tượng tiêu chuẩn để vẽ object, lifeline, message, activation và mô tả các mối quan hệ giữa chúng.

#### 4.4.3. Ví dụ về sequence diagram
**a) Ví dụ 1:**

Đây là ví dụ sequence diagram cho luồng tìm kiếm sách và mượn sách.

- Luồng tìm kiếm sách: User tương tác với giao diện FE để tìm kiếm sách. FE gọi request tới BE server. BE server kiểm tra membership của user, nếu có membership thì trả về thông tin sách trong DB.
- Luồng mượn sách: User tương tác với giao diện FE để tạo request mượn sách. Tương tự, FE gọi request tới BE server. BE server kiểm tra membership của user, nếu có membership, tiếp tục check xem sách có tồn tại trong hệ thống hoặc chưa được người khác mượn, nếu ok thì tạo request mượn sách cho user.

![Image](https://github.com/user-attachments/assets/5195b538-4761-403a-82ae-8a77455208dc)

**b) Ví dụ 2**

Sơ đồ tuần tự của chức năng đăng nhập.Xem xét đối tượng tài khoản sau đây

![Image](https://github.com/user-attachments/assets/8d0f61ef-a260-4ebd-9a51-c1c2f1001944)

Trong sơ đồ trên có 3 đối tượng là : người dùng, hệ thống và tài khoản. Luồng xử lí của chức năng đăng nhập có thể diễn giải như sau.
- Người dùng gửi yêu cầu đăng nhập đến hệ thống.
- Hệ thống yêu cầu người dùng nhập email và mật khẩu.
- Người dùng nhập email và mật khẩu.
- Hệ thống gửi email và mật khẩu của người dùng để kiểm tra.
- Tài khỏan kiểm tra thông tin email và password có đúng hay không.
- Tài khoản trả về kết qủa kiểm tra cho hệ thống.
- Hệ thống trả về thông báo cho người dùng.

### 4.5. State Diagram
#### 4.5.1. Giới thiệu về biểu đồ trạng thái
Biểu đồ trạng thái là dạng biểu đồ mô tả các trạng thái có thể có và sự chuyển đổi giữa các trạng thái đó khi có các sự kiện tác động của một đối tượng.

Đối với các đối tượng có nhiều trạng thái thì biểu đồ trạng thái là sự lựa chọn tốt nhất giúp chúng ta có thể hiểu rõ hơn về hệ thống.

#### 4.5.2. Các thành phần của biểu đồ trạng thái
- Trạng thái bắt đầu: (Initial State)
![Image](https://github.com/user-attachments/assets/853888b1-f856-464c-87cb-a2678e3d341a)
- Trạng thái kết thúc: (Final State)
![Image](https://github.com/user-attachments/assets/4011de01-c378-4a8c-a021-c4a1ab222176)

Trong biểu đồ, đường mũi tên chỉ ra sự biến đổi từ một trạng thái sang trạng thái khác.
- Sự kiện (Event) hoặc Chuyển đổi (Transition)
![Image](https://github.com/user-attachments/assets/120a0098-c1f5-43a9-9d10-0e8c8c37e6ab)
- Trạng thái đối tượng (State)
![Image](https://github.com/user-attachments/assets/a7b0c4da-7dca-4319-a49c-9dedee7fc621)
#### 4.5.3. Ví dụ:
Biểu đồ trạng thái thể hiện lớp Sach trong một hệ thống quản lí thư viện điện tử:
![Image](https://github.com/user-attachments/assets/a61b516f-0a0f-4eda-8d70-e61f5f65161b)
Biểu đồ trạng thái của lớp Sach trên có thể diễn tả lại như sau: Biểu đồ có 5 trạng thái thái chính là sẵn sàng cho mượn, đã có người mượn, hết hạn lưu hành, đã mượn, mất. và hai trạng thái phụ là trạng thái khởi tạo và trạng thái kết thúc.
- Sách khởi tạo ở trạng thái "sẵn sàng cho mượn" .
- Sách chuyển từ trạng thái "sẵn sàng cho mượn" sang trạng thái "Đã mượn" khi có người mượn sách.
- Sách chuyển từ trạng thái "sẵn sàng cho mượn" sang trạng thái "Hết hạn lưu hành" khi có quyết định hết hạn lưu hành.
- Sách "đã có người mượn" chuyển sang trạng thái "Hết hạn lưu hành" khi có quyết định hết hạn lưu hành.
- Sách chuyển từ trạng thái "hết hạn lưu hành" sang trạng thái "lưu trữ" khi có quyết định lưu trữ .
- Sách chuyển từ trạng thái "đã có người mượn" sang trạng thái "mất" khi làm mất.
- Sách chuyển từ trạng thái "đã có người mượn" sang trạng thái "sẵn sàng cho mượn" khi trả sách.

### 4.6. Biểu đồ hoạt động (Activity Diagram)
***
#### 4.6.1. Giới thiệu biểu đồ hoạt động
Biểu đồ hoạt động là biểu đồ mô tả các bước thực hiện, các hành động, các nút quyết định và điều kiện rẽ nhánh để điều khiển luồng thực hiện của hệ thống. Đối với những luồng thực thi có nhiều tiến trình chạy song song thì biểu đồ hoạt động là sự lựa chọn tối ưu cho việc thể hiện. Biểu đồ hoạt động khá giống với biểu đồ trạng thái ở tập các kí hiệu nên rất dễ gây nhầm lẫn. Khi vẽ chúng ta cần phải xác định rõ điểm khác nhau giữa hai dạng biểu đồ này là biểu đồ hoạt động tập trung mô tả các hoạt động và kết qủa thu được từ việc thay đổi trạng thái của đối tượng còn biểu đồ trạng thái chỉ mô tả tập tất cả các trạng thái của một đối tượng và những sự kiện dẫn tới sự thay đổi qua lại giữa các trạng thái đó.
#### 4.6.2. Các thành phần của biểu đồ hoạt động
- Trạng thái khởi tạo hoặc điểm bắt đầu (Initial State or Start Point)
![Image](https://github.com/user-attachments/assets/a1a46f5f-0cb8-4f25-8d20-64cecbb237b3)
- Hoạt động hoặc trạng thái hoạt động (Activity or Action State)
![Image](https://github.com/user-attachments/assets/badfbfe2-d224-4556-b14e-40846ed1da74)

Hoạt động và sự chuyển đổi hoạt động được ký hiệu và cách sử dụng hoàn toàn giống như trạng thái trong biểu đồ trạng thái đã nêu ở trên.

- Nút quyết định và rẽ nhánh

Nút rẽ nhánh trong biểu đồ hoạt động được kí hiệu bằng hình thoi màu trắng.
![Image](https://github.com/user-attachments/assets/09a8ce1b-4d18-4ba6-8a1c-c5c4a516155a)

- Thanh tương tranh hay thanh đồng bộ

Có thể có nhiều luồng hành động được bắt đầu thực hiện hay kết thúc đồng thời trong hệ thống.

Thanh đồng bộ kết hợp:
![Image](https://github.com/user-attachments/assets/215dd4e4-59e6-4abd-b002-637d77d59c22)
Thanh đồng bộ chia nhánh:
![Image](https://github.com/user-attachments/assets/ad0003ad-40d0-4aa2-be2b-b1e6c88b5c56)

- Cạnh gián đoạn (Interrupting Edge)
![Image](https://github.com/user-attachments/assets/5cdf8521-222f-4b93-9b1d-6459180976fa)
- Luồng hoạt động (Action Folow)
![Image](https://github.com/user-attachments/assets/3fe086cb-ca7f-4abd-b022-543af7601ea0)
- Phân làn (Swimlanes)

Phân làn trong biểu đồ sử dụng là những đường nét đứt thẳng đứng theo các đối tượng. Phần kí hiệu này thường được sử dụng để làm rõ luồng hoạt động của các đối tượng riêng biệt.

- Thời gian sự kiện (Time Event)
![Image](https://github.com/user-attachments/assets/9da4f5fa-87a4-4601-8bff-84322bc646db)

- Gửi và nhận tín hiệu (Sent and Received Signals)
![Image](https://github.com/user-attachments/assets/7e6f93d2-38f6-42fe-b2d8-443dda9240ff)
- Trạng thái kết thúc hoặc điểm cuối (Final State or End Point)
![Image](https://github.com/user-attachments/assets/bd999770-b109-42cb-a3fb-fd140cae5af8)

#### 4.6.3. Ví dụ

**VD1:Biểu đồ hoạt động rút tiền tại cây ATM:**

![Image](https://github.com/user-attachments/assets/05cfdd5e-73ab-4b2f-b795-5b62a2167c37)

Như trên hình vẽ ta thấy có ba hoạt động cùng diễn ra là xác nhận thẻ, xác nhận mã số PIN và xác nhận số tiền rút.Chỉ khi sử dụng biểu đồ hoạt động mới có thể miêu tả được các hoạt động song song như vậy.

**VD2: Biểu đồ hoạt động thể hiện một qúa trình đặt hàng.**
![Image](https://github.com/user-attachments/assets/294550cf-b614-49a1-8706-24f2d673315f)
