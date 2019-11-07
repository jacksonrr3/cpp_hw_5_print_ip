#pragma once
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <list>
#include <tuple>


//доп структура проверки элементов tuple на совпадение типов
/**
 * @brief вспомогательная структура для проверки совпадения типов элементов кортежа 
 * 
 */
template <typename T, typename...Args>
struct is_same_tuple_args;

template <typename T>
struct is_same_tuple_args<std::tuple<T, T>> {
	static const bool value = true;
};

template <typename T, typename ... Args>
struct is_same_tuple_args<std::tuple<T, T, Args...> > {
	static const bool value = (true && is_same_tuple_args<std::tuple<T, Args...> >::value);
};

template <typename T, typename U, typename ... Args>
struct is_same_tuple_args<std::tuple<T, U, Args...> > {
	static const bool value = false;
};


//доп структура для определения принадлежности аргумента к контейнеру
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
template <typename...Args>
struct is_tuple {
	static const bool value = false;
};

template <typename...Args>
struct is_tuple<std::tuple<Args...>> {
	static const bool value = true;
	//static const bool value = true && is_same_tuple_args<std::tuple<Args...>>::value; //вынес проверку типов элементов кортежа в функцию печати
};



//вспомогательная структура для печать адреса из кортежа
/**
 * @brief вспомогательная структура для печати адреса из кортежа
 * size шаблонный параметр - размер кортежа
 * T шаблонный параметр - тип кортежа
 * last шаблонный параметр - условие для выода символа '.' 
 * @param tup аргумент функции print_tuple::print
 *
 */
template <size_t size, typename T, bool last = true>
struct print_tuple {
	static void print(const T& tup) {
		print_tuple<size - 1, T, false>::print(tup);
		std::cout << std::get<size - 1>(tup);
	}
};

template <size_t size, typename T> //специализация для вывода элементов кроме первого и последнего
struct print_tuple<size, T, false> {
	static void print(const T& tup) {
		print_tuple<size - 1, T, false>::print(tup);
		std::cout << std::get<size - 1>(tup) << ".";
	}
};

template <typename T> //специализация для окончания рекурсии и дял пчеати из пустого tuple.
struct print_tuple<0, T, false> {
	static void print(const T&) {
	}
};



/**
 * @brief Шаблонная функция вывода в std::cout ip-адреса заданного в виде произвольного целого типа
 * T шаблонный параметр типа аргумента
 * @param ip_addr аргумент функции
 *
 */
template <typename T>
typename std::enable_if_t<std::is_integral<T>::value, void>
print_ip(const T& ip_addr) {
	for (size_t size = sizeof(T); size > 0;) {
		std::cout << ((ip_addr >> (8 * (--size))) & 0xFF);
		if (size) { std::cout << "."; }
	}
	std::cout << std::endl;
}

/**
 * @brief Шаблонная функция вывода в std::cout ip-адреса заданного в виде контейнера std::vector или std::list
 * T шаблонный параметр типа аргумента
 * @param ip_cont аргумент функции
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
 * @brief Функция вывода в std::cout ip-адреса заданного в виде std::string
 * @param ip_addr аргумент функции
 *
 */
void print_ip(const std::string& ip_addr)
{
	std::cout << ip_addr << std::endl;
}


/**
 * @brief Функция вывода в std::cout ip-адреса заданного в виде std::tuple, с проверкой условия одинаковых типов кортежа
 * U шаблонный параметр типа аргумента
 * @param ip_tup аргумент функции
 *
 */
template <typename U>
typename std::enable_if_t<is_tuple<U>::value, void>
print_ip(const U& ip_tup) {
	if (!is_same_tuple_args<U>::value) { std::cout << "Error types!"; }
	else { print_tuple<std::tuple_size<U>::value, U>::print(ip_tup); }
	std::cout << std::endl;
}

