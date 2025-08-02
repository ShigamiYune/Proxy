# Proxy
Make property get/set auto look-like C# in C++

template
``` c++
class MyClass{
    public: Proxy(
          int, my_int, MyClass,
          DGET(my_int),
          DSET(my_int),
          0)

    public: Proxy(
        float, my_float, MyClass,
        {
        std::cout << my_float.get_data() << std::endl;
        return my_float.get_data();
        },
        {
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

    my_class.my_int = 1;
    my_class.my_float = 1.0f;
    return 0;
}
```
