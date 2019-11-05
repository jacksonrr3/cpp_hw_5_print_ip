#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <list>


//доп структруа для определения принадлежности аргумента к контейнеру
template <typename T>
struct is_cont {
	static const bool value = false;
};

template <typename T>
struct is_cont<std::vector<T>> {
	static const bool value = true;
};

template <typename T>
struct is_cont<std::list<T>> {
	static const bool value = true;
};


template <typename T>
typename std::enable_if_t<std::is_integral<T>::value, void>
print_ip(const T& ip_addr) {
	for (size_t size = sizeof(T); size > 0;) {
		std::cout << ((ip_addr >> (8*(--size)))&0xFF);
		if (size) { std::cout << "."; }
	}
	std::cout << std::endl;
}

template <typename U>
typename std::enable_if_t<is_cont<U>::value, void>
print_ip(const U& ip_cont) {
	for (auto it = ip_cont.begin(), it_end = ip_cont.end(); it != it_end;) {
		std::cout << *it;
		if (++it != it_end) { std::cout << "."; }
	}
	std::cout << std::endl;
}


void print_ip(const std::string& ip_addr)
{
	std::cout << ip_addr << std::endl;
}




int main()
{
	char c = -1;
	short sh = 0;
	int i = 2130706433;
	int64_t l = 8875824491850138409;
	std::string s = { "192.168.10.1" };
	std::vector<int> v1 = {2134, 345456, 0, 4545};
	std::list<short> l1 = { 123, 123, 456, 67 };

	print_ip(c);
	print_ip(sh);
	print_ip(i);
	print_ip(l);
	print_ip(s);
	print_ip(v1);
	print_ip(l1);

	return 0;
}
