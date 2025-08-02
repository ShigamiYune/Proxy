# Proxy
Làm property get/set như {get; set;} của C#

mẫu sử dụng
``` c++
#include "Proxy.hpp"
class MyClass{
    public: Proxy(
          int, my_int, MyClass,
          DGET(my_int),
          DSET(my_int),
          0)

    public: Proxy(
        float, my_float, MyClass,
        {
        //logic getter
        std::cout << "geting float" << std::endl;
        return my_float.get_data();
        },
        {
        //logic setter
        std::cout << my_float.get_data() << std::endl;
        my_float.set_data(value);
        std::cout << my_float.get_data() << std::endl;
        },
        0)
};

int main(){
    MyClass my_class;
    int i = my_class.my_int;
    float f = my_class.my_float;
    std::cout << std::endl;
    float f = my_class.my_float.get();
    std::cout << std::endl;

    my_class.my_int = 1;
    my_class.my_float = 1.0f;

    std::cout << my_int << std::endl;
    std::cout << my_float << std::endl;
    return 0;
}
```

get_data() : là hàm sẽ trả về dữ liệu nguyên gốc (chưa áp dụng logic getter)

get() : là hàm sẽ trả về dữ liệu sau khi áp dụng logic getter

my_float : biến này vẫn có thể sử dụng như 1 float bình thường(vẫn có thể nhận hoặc gán binh thường)

nếu my_float là 1 class hoặc struct thì để truy cập biến thành viên của nó bạn cần sử dụng toán tử ->, đồng thời my_float sẽ gặp giới hạn về operator

toán tử -> : có chức năng tương tự như get()


set_data() : là hàm gán trực tiếp dữ liệu mới vào dữ liệu nguyên gốc (chưa áp dụng logic setter)

set() : là hàm sẽ trả về dữ liệu sau khi áp dụng logic getter

nhược điểm:
- không thể sử dụng cho class là virtual inheritance
- không thể sử dụng cho class có alignment tuỳ chỉnh
