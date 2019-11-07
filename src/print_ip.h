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
 * @param size шаблонный параметр - размер кортежа
 * @param T шаблонный параметр - тип кортежа
 * @param last шаблонный параметр - условие для выода символа '.' 
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

