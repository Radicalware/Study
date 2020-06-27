#pragma once

//#define _ITERATOR_DEBUG_LEVEL 0;

/*
*|| Copyright[2018][Joel Leagues aka Scourge]
*|| Scourge /at\ protonmail /dot\ com
*|| www.Radicalware.net
*|| https://www.youtube.com/channel/UCivwmYxoOdDT3GmDnD0CfQA/playlists
*||
*|| Licensed under the Apache License, Version 2.0 (the "License");
*|| you may not use this file except in compliance with the License.
*|| You may obtain a copy of the License at
*||
*|| http ://www.apache.org/licenses/LICENSE-2.0
*||
*|| Unless required by applicable law or agreed to in writing, software
*|| distributed under the License is distributed on an "AS IS" BASIS,
*|| WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*|| See the License for the specific language governing permissions and
*|| limitations under the License.
*/


#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>   
#include <cstdint>
#include <cstring>
#include <assert.h>
#include <initializer_list>
#include <iterator>
#include <regex>
#include <type_traits>

// ----------------------------------------------------------------------
#include "Iterator.h" // An Adapted Project on github.com/Radicalware
// If you can get Slicer to work as an object, please let me know
// Currently, it is in the form of a vct::vertex<T> function call.
// ----------------------------------------------------------------------

namespace vct // Value Control Template Library
{
	template<typename T>
	class vertex : public Iterator<T>
	{
	private:
		T* m_array = nullptr;

		size_t m_capacity = 0;
		size_t m_size = 0;
		std::string m_seperator = "";

		typename iterator m_start = m_array;
		typename iterator m_finish = m_array;


		template<typename ITR>
		inline void priv_insert(size_t insert_loc, size_t insert_size, \
			ITR other_it, ITR other_stop, size_t start_size);

		void del_objs(size_t del_count);
		void del_last_obj();
		void del_obj(size_t idx = 1);

		template<typename A>
		inline void copier(const A& other);

		template<typename A>
		inline bool cmp(const A& other);

	public:
		void update_iterator() {
			set_array(&m_array);
			set_size(&m_size);
		}

		// basic constructors
		vertex() {  }
		inline vertex(size_t size);
		inline vertex(size_t size, T item);
		inline vertex(const T* array, size_t size);
		inline vertex(std::initializer_list<T> lst);
		vertex(const vct::vertex<T>& other) { (*this) = other; }
		vertex(const std::vector<T>& other) { (*this) = other; }

		// destruction
		void clear() { this->~vertex(); }
		inline ~vertex();

		// modifiers
		inline void operator=(const vct::vertex<T>& other);
		inline void operator=(const std::vector<T>& other);

		inline bool operator==(const vct::vertex<T>& other);
		inline bool operator==(const std::vector<T>& other);
		inline bool operator!=(const vct::vertex<T>& other);
		inline bool operator!=(const std::vector<T>& other);

		inline void erase(size_t start_counter = 0, size_t end = 1);
		inline void erase(iterator start_it, iterator end_it);

		//		append
		void push_back(T value) { this->operator <<(value); } // standard C++
		void push(T value) { this->operator <<(value); } // shorthand
		void append(T value) { this->operator <<(value); } // python
		void vct::vertex<T>::operator<<(const T& value);           // ruby
		// '<<' inserts a new element
		// '+'  adds two vectors together
		void vct::vertex<T>::operator+(const vct::vertex<T>& value);

		//		prepend
		void push_front(T value) { this->insert(0, value); }
		void prepend(T value) { this->insert(0, value); }
		inline void insert(const size_t start_loc, const T& single);
		// template<typename A>  // -- > replace "const vct::vertex<T>" with "const A&"
		inline void insert(size_t insert_loc, const vct::vertex<T>& other);
		// template<typename A>
		inline void insert(size_t insert_loc, const vct::vertex<T>&& other);
		inline void insert(iterator target_loc, \
			iterator start_loc, iterator end_loc);
		inline void insert(iterator target_loc, \
			const_iterator start_loc, const_iterator end_loc);

		// Getters
		T operator[](size_t loc) { return m_array[loc]; }
		template<typename N>
		inline T at(N loc);
		inline  T front(size_t loc = 0);
		inline  T back(size_t loc = 0);

		// Misc
		void    print();
		std::string    str();

		vct::vertex<T>& joiner(const std::string& sep);
		vct::vertex<T>& joiner(std::string&& sep);
		vct::vertex<T>& joiner(const char& sep);
		vct::vertex<T>& joiner(char&& sep);

		std::string	join(const std::string& sep);
		std::string	join(std::string&& sep);
		std::string	join(const char& sep);
		std::string	join(char&& sep);

		bool    empty() { return (m_size == 0); }
		T* data() { return m_data; }
		size_t  size() const { return m_size; }
		size_t  capacity() const { return m_capacity; }

		void    pop_back() { del_last_obj(); --m_size; }
		void    pop() { del_last_obj(); --m_size; }

		// -------------------------------------------------------
		// Radicalware Accessions

		bool	has_one(const T & input);
		bool	has_all(const T & input);

		bool	scan_all(const T & input);
		bool	scan_one(const T & input);

		bool	match_one(const T & item);
		bool	match_all(const T & input);

		vct::vertex<T> scans(const T & input);
		vct::vertex<T> matches(const T & input);

		vct::vertex<T> operator()(double x = NULL, double y = NULL, double z = NULL);
	};
};
// ==========================================================================
// *************************************************************************
// ==========================================================================

// >>>>>>>>>> constructors >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
template<typename T>
vct::vertex<T>::vertex(size_t size) : m_capacity(size) {
	m_array = nullptr;
	m_array = (T*)std::malloc(m_capacity * sizeof(T));

	this->update_iterator();
}

template<typename T>
vct::vertex<T>::vertex(size_t size, T item) : m_size(size) {
	m_array = nullptr;
	m_array = (T*)std::malloc(m_size * sizeof(T));

	for (size_t i = 0; i < m_size; i++) {
		new(m_array + i) T(item);
	}

	m_capacity = m_size;
	this->update_iterator();
}

template<typename T>
vct::vertex<T>::vertex(const T * array, size_t size) : m_size(size) {

	m_array = nullptr;
	m_array = (T*)std::malloc((m_size + 2) * sizeof(T));

	for (size_t i = 0; i < m_size; i++) {
		new(m_array + i) T();
		m_array[i] = T(array[i]);
	}

	m_capacity = m_size;
	this->update_iterator();
}

template<typename T>
vct::vertex<T>::vertex(std::initializer_list<T> lst) {
	m_size = lst.size();
	m_capacity = m_size;
	m_array = nullptr;
	m_array = (T*)std::malloc(m_size * sizeof(T));

	std::initializer_list<T>::iterator it = lst.begin();

	for (size_t i = 0; it != lst.end(); it++) {
		new(m_array + i) T();
		m_array[i] = *it;
		++i;
	}
	this->update_iterator();
}

// >>>>>>>>>> destructors >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


template<typename T>
vct::vertex<T>::~vertex() {

	if (m_size > 0 && m_size <= m_capacity) {
		// m_size > m_capacity prevents double free

		this->del_objs(m_size);

		std::free(m_array);
		m_array = nullptr;
	}
	else {
		std::free(m_array);
		m_array = nullptr;
	}
}
template<typename T>
void vct::vertex<T>::del_objs(size_t del_count) {
	for (; del_count > 0; del_count--) {
		m_array[m_size - del_count].~T();
	}
}
template<typename T>
void vct::vertex<T>::del_last_obj() {
	m_array[m_size - 1].~T();
}
template<typename T>
void vct::vertex<T>::del_obj(size_t idx) {
	m_array[idx].~T();
}
// >>>>>>>>>> modifyers >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template<typename T>
template<typename A>
void vct::vertex<T>::copier(const A & other) {
	if (!(this->cmp(other))) {

		bool overlap = true;
		if (m_size == 0) {
			m_array = (T*)std::malloc(other.capacity() * sizeof(T));
			overlap = false;
		}
		else if (other.capacity() > m_capacity) {
			m_array = static_cast<T*>(std::realloc(m_array, other.capacity() * sizeof(T)));
			overlap = false;
		}
		else {
			del_objs(m_size);
		}

		m_size = other.size();
		m_capacity = other.capacity();
		//std::copy(other.begin(), other.end(), m_array);

		typename A::const_iterator it = other.begin();
		typename A::const_iterator end = other.end();

		if (overlap) {
			size_t cursor = 0;
			for (; it != end; ++it) {
				m_array[cursor] = *it;
				++cursor;
			}
		}
		else {
			size_t cursor = 0;
			for (; it != end; ++it) {
				new(m_array + cursor) T;
				m_array[cursor] = *it;
				++cursor;
			}
		}

		this->update_iterator();
	}
}

template<typename T>
inline void vct::vertex<T>::operator=(const vct::vertex<T> & other)
{
	this->copier(other);
}

template<typename T>
inline void vct::vertex<T>::operator=(const std::vector<T> & other)
{
	this->copier(other);
}


template<typename T>
template<typename A>
inline bool vct::vertex<T>::cmp(const A & other) {
	if (m_size != other.size())
		return false;

	A::const_iterator o_start = other.begin();

	for (m_start = this->begin(); m_start != this->end();) {
		if (*m_start != *o_start)
			return false;
		++m_start;
		++o_start;
	}
	return true;
}

template<typename T>
inline bool vct::vertex<T>::operator==(const vct::vertex<T> & other)
{
	return this->cmp(other);
}

template<typename T>
inline bool vct::vertex<T>::operator==(const std::vector<T> & other)
{
	return this->cmp(other);
}

template<typename T>
inline bool vct::vertex<T>::operator!=(const vct::vertex<T> & other)
{
	return (!(this->cmp(other)));
}

template<typename T>
inline bool vct::vertex<T>::operator!=(const std::vector<T> & other)
{
	return (!(this->cmp(other)));
}


template<typename T>
void vct::vertex<T>::erase(size_t target, size_t end_loc) {

	end_loc = (end_loc >= m_size) ? (m_size - 1) : (end_loc);
	for (size_t tracker = target; tracker < end_loc; tracker++)
		m_array[tracker].~T();

	size_t del_size = end_loc - target;
	m_start = this->begin() + end_loc;

	for (; m_start < this->end(); ++m_start) {
		m_array[target] = *m_start;
		++target;
	}

	del_objs(del_size);
	m_size -= del_size;

}


// >>>>> erase is deleting the end objects, not the middle ones that actually get erased!!

template<typename T>
void vct::vertex<T>::erase(iterator start_it, iterator end_it) {
	size_t target = distance(this->begin(), start_it);
	size_t del_size = distance(start_it, end_it);

	if ((target + del_size) >= m_size) {
		--del_size;
	}

	for (size_t tracker = target; tracker < (target + del_size); tracker++)
		m_array[tracker].~T();

	for (; end_it < this->end(); ++end_it) {
		m_array[target] = *end_it;
		++target;
	}
	del_objs(del_size);
	m_size -= del_size;
}

template<typename T>
void vct::vertex<T>::operator<<(const T & value) {
	bool too_small = (m_capacity <= 4);
	if (m_capacity == 0) {
		m_array = nullptr;
		m_array = (T*)std::malloc(sizeof(T));

		//new(m_array + m_size) T(value);
		//m_array[m_size] = value;
		m_array[m_size] = *(new(m_array + m_size) T(value));
		
		m_size = 1;
		m_capacity = 1;
		this->update_iterator();

	}
	else if (too_small || (m_size > (m_capacity - 4))) { // if used size is greater than our capacity
		m_capacity += m_size; // basically double our capacity
		m_array = static_cast<T*>(std::realloc(m_array, m_capacity * sizeof(T))); // allocate our new double capacity
		new(m_array + m_size) T(value); // init our new object

		m_array[m_size] = value; // to our local location // TODO: TEST IF WE CAN DO WITHOUT
		m_size += 1; // we increase our size by our one object
		//this->update_iterator();
	}
	else {
		new(m_array + m_size) T(value);

		m_array[m_size] = value;
		m_size += 1;

	}
}

template<typename T>
void vct::vertex<T>::operator+(const vct::vertex<T> & other) {
	this->insert(m_size, other);
}

template<typename T>
void vct::vertex<T>::insert(const size_t start_loc, const T& single) {
	// THIS IS FOR A SINGLE ELEMENT INSERT

	size_t mod_loc = m_size;
	if (m_size >= m_capacity) {
		m_capacity += m_size;
		m_array = static_cast<T*>(std::realloc(m_array, m_capacity * sizeof(T)));
	}

	typename iterator it = this->end(); --it;
	const typename iterator stop = this->begin() + start_loc;

	//stop += start_loc; // -1 will insert in front (one element to the left)

	// note: --it because size starts at 1 not 0;
	new(m_array + mod_loc) T;
	for (; it >= stop; --it) {
		m_array[mod_loc] = *it;
		--mod_loc;
	}
	del_obj(mod_loc);
	m_array[mod_loc] = single;
	m_size += 1;
}

template<typename T>
template<typename ITR>
void vct::vertex<T>::priv_insert(size_t insert_loc, size_t insert_size, \
	ITR other_it, ITR other_stop, size_t start_size) {

	m_start = this->end() - 1; // grabs the last (unused) element and the start of where we insert data
	insert_loc = (insert_loc >= m_size) ? (m_size - 1) : (insert_loc); 
	// give the last used addr if our insert location has a gap else we insert data inbetween
	m_finish = this->begin() + insert_loc;

	// save right-most elements
	size_t track_loc = m_size - 1 + insert_size;
	for (; m_start >= m_finish; --m_start) {
		new(m_array + track_loc) T;
		m_array[track_loc] = *m_start;
		(*m_start).~T(); // can only delete in locations where we previously had mem
		--track_loc;
	}

	// insert new elements
	for (; other_it < other_stop;) {
		if (insert_loc <= start_size) {
			del_obj(insert_loc);
		}
		else {
			new(m_array + insert_loc) T;
		}
		m_array[insert_loc] = *other_it;
		++other_it; ++insert_loc;
	}
	m_size += insert_size;
}

template<typename T>
void vct::vertex<T>::insert(size_t insert_loc, const vct::vertex<T> & other) {
	size_t ovx_size = other.size();
	size_t start_size = m_size;
	if (m_capacity < m_size + ovx_size + 1) {
		m_capacity += ovx_size + 1;
		m_array = static_cast<T*>(std::realloc(m_array, m_capacity * sizeof(T)));
	}
	this->priv_insert(insert_loc, ovx_size, other.begin(), other.end(), start_size);
}

template<typename T>
void vct::vertex<T>::insert(size_t insert_loc, const vct::vertex<T> && other) {
	size_t start_size = m_size;
	if (m_capacity < m_size + other.size() + 1) {
		m_capacity += other.size() + 1;
		m_array = static_cast<T*>(std::realloc(m_array, m_capacity * sizeof(T)));
	}
	this->priv_insert(insert_loc, other.size(), other.begin(), other.end(), start_size);
}

template<typename T>
void vct::vertex<T>::insert(iterator target_loc, \
	iterator other_it, iterator other_stop) {

	size_t start_size = m_size;
	size_t insert_size = distance(other_it, other_stop);
	size_t insert_loc = distance(this->begin(), target_loc);
	if (m_capacity < m_size + insert_size + 1) {
		m_capacity = m_size + insert_size + 1;
		m_array = static_cast<T*>(std::realloc(m_array, m_capacity * sizeof(T)));
	}
	this->priv_insert(insert_loc, insert_size, other_it, other_stop, start_size);
}

template<typename T>
void vct::vertex<T>::insert(iterator target_loc, \
	const_iterator other_it, const_iterator other_stop) {

	size_t start_size = m_size;
	size_t insert_size = distance(other_it, other_stop);
	size_t insert_loc = distance(this->begin(), target_loc);
	if (m_capacity < m_size + insert_size + 1) {
		m_capacity += insert_size + 1;
		m_array = static_cast<T*>(std::realloc(m_array, m_capacity * sizeof(T)));
	}
	this->priv_insert(insert_loc, insert_size, other_it, other_stop, start_size);

}

// >>>>>>>>>> Getters >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
template<typename T>
template<typename N>
T  vct::vertex<T>::at(N loc) {
	// use at() when you need safty or want to identify
	// value from a reverse direction obj.at(-1) for last element
	if (loc < 0)
		loc = static_cast<N>(m_size) + loc;

	size_t int_loc = static_cast<size_t>(loc);
	if (int_loc > m_size) {
		throw 1;
	}
	else {
		return m_array[int_loc];
	}
}

template<typename T>
T  vct::vertex<T>::front(size_t loc) {
	return m_array[loc];
}

template<typename T>
T  vct::vertex<T>::back(size_t loc) {
	return m_array[m_size - 1 - loc];
}

template<typename T>
void vct::vertex<T>::print() {
	for (size_t i = 0; i < m_size; i++) {
		if (i != m_size)
			cout << m_array[i] << m_seperator;
		else
			cout << m_array[i];
	}
}

template<typename T>
std::string vct::vertex<T>::str() {
	std::ostringstream out;
	for (size_t i = 0; i < m_size; i++) {
		if (i != m_size) {
			out << m_array[i];
			out << m_seperator;
		}
		else {
			out << m_array[i];
		}
	}
	return out.str();
}
template<typename T>
vct::vertex<T>& vct::vertex<T>::joiner(std::string && sep) {
	m_seperator = sep;
	return *this;
}
template<typename T>
vct::vertex<T>& vct::vertex<T>::joiner(const std::string & sep) {
	m_seperator = sep;
	return *this;
}
template<typename T>
vct::vertex<T>& vct::vertex<T>::joiner(char&& sep) {
	m_seperator = std::to_string(sep);
	return *this;
}
template<typename T>
vct::vertex<T>& vct::vertex<T>::joiner(const char& sep) {
	m_seperator = std::to_string(sep);
	return *this;
}

template<typename T>
std::string	vct::vertex<T>::join(std::string && sep) {
	m_seperator = sep;
	return this->str();
}
template<typename T>
std::string	vct::vertex<T>::join(const std::string & sep) {
	m_seperator = sep;
	return this->str();
}
template<typename T>
std::string	vct::vertex<T>::join(char&& sep) {
	m_seperator = std::to_string(sep);
	return this->str();
}
template<typename T>
std::string	vct::vertex<T>::join(const char& sep) {
	m_seperator = std::to_string(sep);
	return *this->str();
}
// Radicalware AccessionsH

template<typename T>
bool vct::vertex<T>::has_one(const T & input) {
	for (m_start = begin(); m_start != this->end(); ++m_start) {
		if (input == *m_start) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool vct::vertex<T>::has_all(const T & input) {
	for (m_start = begin(); m_start != this->end(); ++m_start) {
		if (input != *m_start) {
			return false;
		}
	}
	return true;
}

template<typename T>
bool vct::vertex<T>::match_one(const T & input) {
	std::regex pattern(input);
	for (m_start = begin(); m_start != this->end(); ++m_start) {
		if (std::regex_match(*m_start, pattern)) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool vct::vertex<T>::match_all(const T & input) {
	std::regex pattern(input);
	for (m_start = begin(); m_start != this->end(); ++m_start) {
		if (!std::regex_match(*m_start, pattern)) {
			return false;
		}
	}
	return true;
}


template<typename T>
bool vct::vertex<T>::scan_one(const T & input) {
	std::regex pattern(input);
	for (m_start = begin(); m_start != this->end(); ++m_start) {
		if (std::regex_search(*m_start, pattern)) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool vct::vertex<T>::scan_all(const T & input) {
	std::regex pattern(input);
	for (m_start = begin(); m_start != this->end(); ++m_start) {
		if (!std::regex_search(*m_start, pattern)) {
			return false;
		}
	}
	return true;
}

template<typename T>
vct::vertex<T> vct::vertex<T>::scans(const T & input) {
	std::regex pattern(input);
	vct::vertex<T> ret_patterns;

	for (m_start = this->begin(); m_start != this->end(); ++m_start) {
		if (std::regex_search(*m_start, pattern)) // ret whole item so re.h for findall not needed
			ret_patterns << *m_start;
	}
	if (ret_patterns.size()) {
		return ret_patterns;
	}
	else {
		ret_patterns << T();
		return ret_patterns;
	}
}

template<typename T>
vct::vertex<T> vct::vertex<T>::matches(const T & input) {
	std::regex pattern(input);
	vct::vertex<T> ret_patterns;

	for (m_start = this->begin(); m_start != this->end(); ++m_start) {
		if (std::regex_match(*m_start, pattern))
			ret_patterns << *m_start;
	}
	return ret_patterns;
}

template<typename T>
vct::vertex<T> vct::vertex<T>::operator()(double x, double y, double z) {

	vct::vertex<T> vxx(m_size);

	double vxx_size = static_cast<double>(m_size - 1);

	//double x = xx;
	//double y = yy;
	//double z = zz;

	if (z >= 0) {

		if (x < 0) { x += vxx_size; }

		if (!y) { y = vxx_size; }
		else if (y < 0) { y += vxx_size; }
		++y;

		if (x > y) { return vxx; }

		iterator iter = this->begin();
		iterator stop = this->begin() + static_cast<size_t>(y);

		if (z == 0) { // forward direction with no skipping
			for (iter += static_cast<size_t>(x); iter != stop; ++iter)
				vxx << *iter;
		}
		else { // forward direction with skipping
			double iter_insert = 0;
			--z;
			for (iter += static_cast<size_t>(x); iter != stop; ++iter) {
				if (!iter_insert) {
					vxx << *iter;
					iter_insert = z;
				}
				else {
					--iter_insert;
				}
			}
		}
	}
	else {
		z = (z * -1 - 1);
		if (!x) { x = vxx_size; }
		else if (x < 0) { x += vxx_size; }
		++x;

		if (!y) { y = 0; }
		else if (y < 0) { y += vxx_size; }

		if (y > x) { return vxx; }

		iterator iter = this->begin() + static_cast<size_t>(x) - 1;
		iterator stop = this->begin() + static_cast<size_t>(y) - 1;

		size_t iter_insert = 0;

		if (z == 0) {
			for (; iter != stop; --iter) {
				if (!iter_insert)
					vxx << *iter;
			}
		}
		else {
			for (; iter != stop; --iter) {
				if (!iter_insert) {
					vxx << *iter;
					iter_insert = static_cast<size_t>(z);
				}
				else {
					--iter_insert;
				}
			}
		}
	}

	return vxx;
}