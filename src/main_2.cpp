#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <list>




//вспомогательная структура для печать адреса из кортежа
/**
 * @brief вспомогательная структура для печати адреса из кортежа
 *
 */
template <size_t size, typename T, bool last = true>
struct print_tuple {
	static void print(const T& tup) {
		
		//std::cout << "."; 
		print_tuple<size - 1, T, false>::print(tup);
		std::cout << std::get<size - 1>(tup);
	}
};


//специализация для вывода элементов, кроме последнего
/**
 * @brief специализация для вывода элементов, кроме последнего
 *
 */
template <size_t size, typename T>
struct print_tuple<size, T, false> {
	static void print(const T& tup) {
		print_tuple<size - 1, T, false>::print(tup);
		std::cout << std::get<size-1>(tup) << ".";
	}
};

//специализация для окончания рекурсии и для печати из пустого tuple.
/**
 * @brief специализация для окончания рекурсии
 *
 */
template <typename T>
struct print_tuple<0, T, false> {
	static void print(const T& tup) {
	}
}; 




//доп структруа для определения принадлежности аргумента к контейнеру
/**
 * @brief Дополнительная структура для определения принадлежности аргумента к типу контейнер
 *
 */
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

//доп структура для определения принадлежности аргумента к tuple
/**
 * @brief Дополнительная структура для определения принадлежности аргумента к типу std::tuple
 *
 */
template <typename ...Args>
struct is_tuple {
	static const bool value = false;
};

template <typename...Args>
struct is_tuple<std::tuple<Args...>> {
	static const bool value = true;
};



/**
 * @brief Шаблонная функция вывода в std::cout ip-адреса заданного в виде произвольного целого типа
 * @param T шаблонный параметр типа аргумента
 * @param ip_addr аргумент функции
 *
 */
template <typename T>
typename std::enable_if_t<std::is_integral<T>::value, void>
print_ip(const T& ip_addr) {
	for (size_t size = sizeof(T); size > 0;) {
		std::cout << ((ip_addr >> (8*(--size)))&0xFF);
		if (size) { std::cout << "."; }
	}
	std::cout << std::endl;
}

/**
 * @brief Шаблонная функция вывода в std::out ip-адреса заданного в виде контейнера std::vector или std::list
 * @param T шаблонный параметр типа аргумента
 * @param ip_addr аргумент функции
 *
 */
template <typename U>
typename std::enable_if_t<is_cont<U>::value, void>
print_ip(const U& ip_cont) {
	for (auto it = ip_cont.begin(), it_end = ip_cont.end(); it != it_end;) {
		std::cout << *it;
		if (++it != it_end) { std::cout << "."; }
	}
	std::cout << std::endl;
}

/**
 * @brief Функция вывода в std::out ip-адреса заданного в виде std::string
 * @param ip_addr аргумент функции
 *
 */
void print_ip(const std::string& ip_addr)
{
	std::cout << ip_addr << std::endl;
}

/**
 * @brief Функция вывода в std::out ip-адреса заданного в виде std::tuple
 * @param ip_addr аргумент функции
 *
 */
template <typename U>
typename std::enable_if_t<is_tuple<U>::value, void>
print_ip(const U& ip_tup) {
	print_tuple<std::tuple_size_v<U>, U>::print(ip_tup);
	std::cout << std::endl;
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
