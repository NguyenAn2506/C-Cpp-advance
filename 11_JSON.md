# JSON
***
## 11.1. khái niệm JSON
***
JSON là viết tắt của "JavaScript Object Notation" (Ghi chú về Đối tượng JavaScript). Đây là một định dạng truyền tải dữ liệu phổ biến trong lập trình và giao tiếp giữa các máy chủ và trình duyệt web, cũng như giữa các hệ thống khác nhau.
JSON được thiết kế để dễ đọc và dễ viết cho con người, cũng như dễ dàng để phân tích và tạo ra cho máy tính. Nó sử dụng một cú pháp nhẹ dựa trên cặp key - value, tương tự như các đối tượng và mảng trong JavaScript. Mỗi đối tượng JSON bao gồm một tập hợp các cặp "key" và "value", trong khi mỗi mảng JSON là một tập hợp các giá trị
***
## 11.2. các định dạng trong JSON
***
JSON có thể được định dạng dưới dạng Object và mảng
### 11.2.1. JSON dưới dạng object
```c
{ 
  "name": "John Doe",
  "age": 30,
  "city": "New York",
  "isStudent": false,
  "grades": [85, 90, 78]
}
```
-	Key là “name” và Value là “John Doe”
-	Các cặp Key và value sẽ được ngăn cách nhau bới dấu : (dấu 2 chấm)
-	Các Cặp key value sẽ được cách nhau bới dấu ,  (phẩy)
-	các Key đều ở dạng chuỗi, còn value thì tùy thuộc kiểu dữ liệu
### 11.2.2. JSON dưới dạng mảng
```c
[
  {
    "name": "John Doe",
    "age": 30,
    "city": "New York",
    "occupation": "Software Engineer",
    "isStudent": false
  },
  {
    "name": "Jane Smith",
    "age": null,
    "city": "Los Angeles",
    "contact": {
      "email": "jane.smith@example.com",
      "phone": "555-1234"
    }
  },
  {
    "name": "Bob Johnson",
    "age": 35,
    "city": "Chicago"
  },
  20, 3.14, "Hello World", true, null, [80, 70, 90]
]
```
Khác với mảng thông thường là các phần tử trong mảng thông thường thì đều cùng 1 kiểu dữ liệu, nhưng mảng trong JSON thì có thể là bất kì kiểu dữ liệu nào

=> Không quy định các phần tử có chung 1 định dạng

### 11.2.3. So sánh định dạng cảu struct và JSON
**giống nhau**
đều lưu trữ các phần tử khác nhau (có các kiểu dữ liệu khác nhau)
**khác nhau**
- **Struct:** những thành phần của nó cần phải được quy định trước
- **JSON:** bao gồm những thông tin khác nhau, không cần quy định trước
### 11.2.4. Khai báo định dạng cho JSON
```c
typedef enum {
    JSON_NULL,      /**< Giá trị Null..............> */
    JSON_BOOLEAN,   /**< kiểu boolean (true/false).> */
    JSON_NUMBER,    /**< kiểu số (int/double)......> */
    JSON_STRING,    /**< kiểu chuỗi  ..............> */
    JSON_ARRAY,     /**< kiểu mảng   ..............> */
    JSON_OBJECT     /**< kiểu object ..............> */
} JsonType;
```
### 11.2.5. Lưu trữ giá trị cho JSON
•	Tiếp theo ta cần tạo ra 1 kiểu dữ liệu để cài đặt các cấu hình dữ liệu bên trong json
•	Dữ liệu này sẽ có 2 việc chính là gán giá trị và định dạng của chuỗi
•	Để làm chuyện đó cần tạo 1 cấu trúc, và sử dụng 1 union bên trong cấu trúc này, việc gắn union vào trong struct này là để tách biệt địa chỉ cho mỗi thành phần kiểu dữ liệu, đặc biệt đối với kiểu dữ liệu mảng và object thì cần dùng 1 struct vì 2 loại này cần các thành phần liên quan
•	Đối với kiểu mảng thì cần có 1 danh sách để lưu trữ giá trị của mảng và cần có biến để lưu số lượng các phần tử
•	Đối với object thì cần có 1 danh sách để lưu trữ key, 1 danh sách lưu trữ giá trị value và cũng cần có biến để lưu số lượng các cặp key-value 
```c
typedef struct JsonValue {
    JsonType type;                      /**< Kiểu dứ liệu của giá trị JSON >*/
    union {
        int     boolean;                /**< Giá trị Boolean >*/
        double  number;                 /**< Giá trị số >*/
        char    *string;                /**< Chuỗi ký tự >*/
        
        struct {
            struct JsonValue *values;   /**< Danh sách phần tử trong mảng > */
            size_t count;               /**< Số lượng phần tử trong mảng > */
        } array;

        struct {
            char **keys;                /**< Danh sách key trong object: ["key1", "key2",...] > */
            struct JsonValue *values;   /**< Danh sách giá trị tương ứng > */
            size_t count;               /**< Số lượng cặp key-value trong object > */
        } object;

    } value;
} JsonValue;
```
### 11.2.6. tạo các giá trị cho JSON (test)
Để có thể tạo các giá trị JSON bằng cách thủ công thì:
-	Cần cấp phát các ô địa chỉ cho các chuỗi JSON đó
-	Tiếp theo cần gán kiểu dữ liệu JSON
-	Sau đó gán giá trị vào các ô địa chỉ đó
```c
/*
{
  "name": "John Doe",
  "age": 30.1234,
  "city": "New York",
  "isStudent": true,
  "grades": [85, 90, 78]
}
*/

void creat()
{
    JsonValue *json_str = (JsonValue*)malloc(sizeof(JsonValue));

    json_str->type = JSON_OBJECT;
    json_str->value.object.count = 5;

    json_str->value.object.keys = (char**)malloc(json_str->value.object.count * sizeof(char*));
    json_str->value.object.values = (JsonValue*)malloc(json_str->value.object.count * sizeof(JsonValue));

    // tạo cặp key-value 1
    json_str->value.object.keys[0] = "name";
    json_str->value.object.values[0].type = JSON_STRING;
    json_str->value.object.values[0].value.string = "John Doe";

    // tạo cặp key-value 2
    json_str->value.object.keys[1] = "age";
    json_str->value.object.values[1].type = JSON_NUMBER;
    json_str->value.object.values[1].value.number = 30.1234;

    // tạo cặp key-value 3

    // tạo cặp key-value 4

    // tạo cặp key-value 5
    json_str->value.object.keys[4] = "grades";
    json_str->value.object.values[4].type = JSON_ARRAY;
    json_str->value.object.values[4].value.array.count = 3;

    // trong struct array có 2 phần tử là count (đã gán giá trị) và 
    // values là 1 danh sách nữa nên cần phải cấp phát động lại
    json_str->value.object.values[4].value.array.values = (JsonValue*)malloc(json_str->value.object.values[4].value.array.count * sizeof(JsonValue));
    json_str->value.object.values[4].value.array.values[0].type = JSON_NUMBER;

    // phần tử đầu tiên trong mảng
    json_str->value.object.values[4].value.array.values[0].value.number = 85;
}
```
## 11.3. xử lý dữ liệu trong JSON
### 11.3.1. hàm bỏ qua các kí tự khoảng trắng trong chuỗi JSON
Để bỏ qua các kí tự khoảng trắng thì ta cần lặp qua kí tự khoảng trắng đó, thông thường thì kí tự này chỉ là 1 kí tự nên chỉ cần lặp qua 1 kí tự là được
```c
static void skip_whitespace(const char **json) {
    while (isspace(**json)) {
        (*json)++;
    }
}
```
### 11.3.2. Phân tích giá trị NULL trong JSON
Tương tự với hàm bỏ qua các kí tự khoảng trắng nên ta sẽ lặp qua giá trị NULL, tức là 4 kí tự
```c
JsonValue *parse_null(const char **json) {
    skip_whitespace(json);
    JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));

    if (strncmp(*json, "null", 4) == 0) {      // kiểm tra chuỗi có kí tự NULL không
        value->type = JSON_NULL;    
        *json += 4;     // skip qua Null (4 byte)
        return value;
    }

    free(value);    
    return NULL;
}
```
### 11.3.3. phân tích giá trị boolean (True/Flase) từ chuỗi JSON
Cũng tương tự với 2 hàm trên thì với giá trị True (4 kí tự) và False (5 kí tự). cần lặp qua các kí tự tương ứng
```c
JsonValue *parse_boolean(const char **json) {
    skip_whitespace(json);
    JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));

    if (strncmp(*json, "true", 4) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = true;
        *json += 4;
    } else if (strncmp(*json, "false", 5) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = false;
        *json += 5;   
    } else {
        free(value);
        return NULL;
    }
    return value;
}
```
### 11.3.4. Phân tích giá trị number từ chuỗi JSON
Đối với giá trị number thì
-	Cần phải biến đổi giá trị số thành giá trị chuỗi
-	Khai báo 1 con trỏ để lưu trữ vị trí cuối cùng (*end) của chuỗi số (ví dụ “12345” => “5”)
-	Nếu địa chỉ con trỏ end khác với địa chỉ của json thì
-	Cấp phát các ô nhớ và lưu vào 1 con trỏ
-	Gán kiểu con trỏ mới cấp phát là kiểu số
-	Gán giá trị mới vào con trỏ value
-	Gán địa chỉ cuối cùng thành địa chỉ json
-	Trả về biến value 

```c
JsonValue *parse_number(const char **json) {
    skip_whitespace(json);
    char *end;          // lưu vị trí cuối cùng (chuỗi số) ("12345")
                                            // str -> double
    double num = strtod(*json, &end);       // double strtod(const char *str, char **endptr);
    if (end != *json) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NUMBER;
        value->value.number = num;
        *json = end;
        return value;
    }
    return NULL;
}
```
### 11.3.5. Phân tích giá trị chuỗi từ chuỗi JSON
Để phân tích 1 giá trị chuỗi thì
-	Skip qua các kí tự khoảng trắng
-	Nếu giá trị tại chuỗi json bằng với kí tự \” thì
    -   Skip qua 1 kí tự 
    - Khai báo con trỏ lưu trữ giá trị  địa chỉ đầu tiên của chuỗi json
    - Lặp qua các kí tự của chuỗi đến khi gặp kí tự NULL ở cuối chuỗi
    - Nếu gặp kí tự NULL thì
    - Khai báo 1 biến để tính toán độ dài bị thừa của chuỗi qua phép tính chuỗi hiện tại – chuỗi ban đầu
    - Sau đó cấp phát ô nhớ cho độ dài bị thừa đó
    - Sau đó sao chép dữ liệu mới vào trong chuỗi str và thêm kí tự NULL vào cuối chuỗi
    - Gán giá trị chuỗi str vào trong biến value và trả về kết quả của hàm là giá trị value
```c
JsonValue *parse_string(const char **json) {
    skip_whitespace(json);

    if (**json == '\"') {
        (*json)++;                      // start và *json trỏ vào cung 1 dia chi 
        const char *start = *json;      // luu gia tri dia chi dau tien cua json
        while (**json != '\"' && **json != '\0') {
            (*json)++;
        }
        if (**json == '\"') {
            size_t length = *json - start; // 3
            char *str = (char *) malloc((length + 1) * sizeof(char));
            strncpy(str, start, length);      // sao chép length ký tự từ start vào str
            str[length] = '\0';

            JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
            value->type = JSON_STRING;
            value->value.string = str;
            (*json)++;
            return value;
        }
    }
    return NULL;
}
```
### 11.3.6. Phân tích giá trị mảng từ JSON
```c
JsonValue *parse_array(const char **json) {
    skip_whitespace(json);
    if (**json == '[') {
        (*json)++;
        skip_whitespace(json);

        JsonValue *array_value = (JsonValue *)malloc(sizeof(JsonValue));
        array_value->type = JSON_ARRAY;
        array_value->value.array.count = 0;
        array_value->value.array.values = NULL;

        /*
        double arr[2] = {};
        arr[0] = 30;
        arr[1] = 70;
        */

        while (**json != ']' && **json != '\0') {
            JsonValue *element = parse_json(json); // 70
            if (element) {
                array_value->value.array.count++;
                array_value->value.array.values = (JsonValue *)realloc(array_value->value.array.values, array_value->value.array.count * sizeof(JsonValue));
                array_value->value.array.values[array_value->value.array.count - 1] = *element;
                free(element);
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == ']') {
            (*json)++;
            return array_value;
        } else {
            free_json_value(array_value);
            return NULL;
        }
    }
    return NULL;
}
```
### 11.3.7. Phân tích giá trị object từ chuỗi JSON
```c
JsonValue *parse_object(const char **json) 
{
    skip_whitespace(json);
    if (**json == '{') 
    {
        (*json)++;          // skip qua { (1 BYTE)
        skip_whitespace(json);

        JsonValue *object_value = (JsonValue *)malloc(sizeof(JsonValue));
        object_value->type = JSON_OBJECT;
        object_value->value.object.count = 0;
        object_value->value.object.keys = NULL;
        object_value->value.object.values = NULL;

        while (**json != '}' && **json != '\0')     // lặp qua từng kí tự và đk dừng là gặp kí tự kết thúc ( } or NULL)
        {
            JsonValue *key = parse_string(json);
            if (key) 
            {
                skip_whitespace(json);
                if (**json == ':') 
                {
                    (*json)++;
                    JsonValue *value = parse_json(json);
                    if (value) 
                    {
                        object_value->value.object.count++;     // tăng lên 1 đơn vị
                        object_value->value.object.keys = (char **)realloc(object_value->value.object.keys, object_value->value.object.count * sizeof(char *));  // tăng vùng nhớ để lưu giá trị key
                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string;  // lưu trữ lại dữ liệu sau khi tăng vùng nhớ

                        object_value->value.object.values = (JsonValue *)realloc(object_value->value.object.values, object_value->value.object.count * sizeof(JsonValue));
                        object_value->value.object.values[object_value->value.object.count - 1] = *value;
                        free(value);
                    } 
                    else 
                    {
                        free_json_value(key);
                        break;
                    }
                } else 
                {
                    free_json_value(key);
                    break;
                }
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == '}') {
            (*json)++;
            return object_value;
        } else {
            free_json_value(object_value);
            return NULL;
        }
    }
    return NULL;
}
```
### 11.3.8. Phân tích tổng quát 1 giá trị JSON
JsonValue *parse_json(const char **json) { 
    while (isspace(**json)) {
        (*json)++;
    }

    switch (**json) {
        case 'n':
            return parse_null(json);
        case 't':
        case 'f':
            return parse_boolean(json);
        case '\"':
            return parse_string(json);
        case '[':
            return parse_array(json);
        case '{':
            return parse_object(json);
        
        // còn lại là số và các kí từ đặc biệt như ! @ # $ ...
        default:
            // 2 TH là số dương hoặc âm
            if (isdigit(**json) || **json == '-') // isdigit: '0', '1',...,'9'
            {   
                return parse_number(json);
            } 
            else // kí tự đặc biệt 
            {    
                // Lỗi phân tích cú pháp
                return NULL;
            }
    }
}
### 11.3.9. Hàm giải phóng bộ nhớ của cấu trúc JsonValue
```c
void free_json_value(JsonValue *json_value) {
    if (json_value == NULL) {
        return;
    }

    switch (json_value->type) {
        case JSON_STRING:
            free(json_value->value.string);
            break;

        case JSON_ARRAY:
            for (size_t i = 0; i < json_value->value.array.count; i++) {
                free_json_value(&json_value->value.array.values[i]);
            }
            free(json_value->value.array.values);
            break;

        case JSON_OBJECT:
            for (size_t i = 0; i < json_value->value.object.count; i++) {
                free(json_value->value.object.keys[i]);
                free_json_value(&json_value->value.object.values[i]);
            }
            free(json_value->value.object.keys);
            free(json_value->value.object.values);
            break;

        default:
            break;
    }
}
```
### 11.3.10. In nội dung JsonValue ra màn hình 
```c
void display(JsonValue* json_value){
    if (json_value != NULL && json_value->type == JSON_OBJECT) {
        // Truy cập giá trị của các trường trong đối tượng JSON
        size_t num_fields = json_value->value.object.count;
        // size_t num_fields2 = json_value->value.object.values->value.object.count;
        for (size_t i = 0; i < num_fields; ++i) {
            char* key = json_value->value.object.keys[i];
            JsonValue* value = &json_value->value.object.values[i];

            JsonType type = (int)(json_value->value.object.values[i].type);
            if(type == JSON_STRING){
                printf("%s: %s\n", key, value->value.string);
            }
            if(type == JSON_NUMBER){
                printf("%s: %f\n", key, value->value.number);
            }
            if(type == JSON_BOOLEAN){
                printf("%s: %s\n", key, value->value.boolean ? "True":"False");
            }
            if(type == JSON_OBJECT){
                printf("%s: \n", key);
                display(value);
            }
            if(type == JSON_ARRAY){
                printf("%s: ", key);
                for (int i = 0; i < value->value.array.count; i++)
                {
                   display(value->value.array.values + i);
                } 
                printf("\n");
            }
        }
    }
    else 
    {
            if(json_value->type == JSON_STRING){
                printf("%s ", json_value->value.string);
            }
            if(json_value->type == JSON_NUMBER){
                printf("%f ", json_value->value.number);
            }
            if(json_value->type == JSON_BOOLEAN){
                printf("%s ", json_value->value.boolean ? "True":"False");
            }
            if(json_value->type == JSON_OBJECT){
                printf("%s: \n", json_value->value.object.keys);
                display(json_value->value.object.values);        
            }
    }
}
```