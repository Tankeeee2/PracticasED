/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <sstream>
#include <cassert>
#include <cdarray.hpp>

template <class T>
size_t CDArray<T>::capacity() const
{
    return capacity_;
}

template <class T>
size_t CDArray<T>::size() const
{
    return size_;
}

template <class T>
bool CDArray<T>::is_empty() const
{
    return size_ == 0;
}

template <class T>
bool CDArray<T>::is_full() const
{
    return size_ == capacity_;
}

template <class T>
CDArray<T>::CDArray(size_t cap) : capacity_(cap), size_(0)
{
    assert(cap > 0);
    data_ = std::shared_ptr<T[]>(new T[cap]);
    assert(capacity() == cap);
    assert(is_empty());
    assert(size() == 0);
}

template <class T>
CDArray<T>::~CDArray()
{
    // No need to do anything since we are using smart pointers
}

template <class T>
CDArray<T>::CDArray(std::istream &in) noexcept(false) : CDArray(1)
{
    std::string token;
    while (in >> token)
    {
        std::istringstream iss(token);
        T value;
        if (!(iss >> value))
        {
            throw std::runtime_error("Wrong input format.");
        }
        push_back(value);
    }
}

template <class T>
std::ostream &CDArray<T>::fold(std::ostream &out) const
{
    for (size_t i = 0; i < size(); ++i)
    {
        out << get(i) << " ";
    }
    return out;
}

template <class T>
T const &CDArray<T>::get(size_t pos) const
{
    assert(pos < size());
    return data_[pos];
}

template <class T>
void CDArray<T>::set(size_t pos, T const &new_v)
{
    assert(pos < size());
    data_[pos] = new_v;
    assert(new_v == get(pos));
}

size_t cInc(size_t v, size_t size)
{
    return (v + 1) % size;
}

size_t cDec(size_t v, size_t size)
{
#ifndef NDEBUG
    size_t old_v = v;
#endif
    size_t ret_v = (v == 0) ? size - 1 : v - 1;
    assert(old_v == cInc(ret_v, size));
    return ret_v;
}

template <class T>
void CDArray<T>::push_front(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_front = is_empty() ? T() : get(0);
#endif
    if (is_full())
    {
        grow();
    }
    for (size_t i = size(); i > 0; --i)
    {
        data_[i] = data_[i - 1];
    }
    data_[0] = new_it;
    ++size_;
    assert(size() == old_size + 1);
    assert(get(0) == new_it);
    assert(old_is_empty || (get(1) == old_front));
}

template <class T>
void CDArray<T>::push_back(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_back = is_empty() ? T() : get(size() - 1);
#endif
    if (is_full())
    {
        grow();
    }
    data_[size_++] = new_it;
    assert(size() == old_size + 1);
    assert(get(size() - 1) == new_it);
    assert(old_is_empty || (get(size() - 2) == old_back));
}

template <class T>
void CDArray<T>::pop_front()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_front = size() > 1 ? get(1) : T();
#endif
    assert(!is_empty());
    for (size_t i = 0; i < size() - 1; ++i)
    {
        data_[i] = data_[i + 1];
    }
    --size_;
    assert(size() == old_size - 1);
    assert(is_empty() || get(0) == old_next_front);
}

template <class T>
void CDArray<T>::pop_back()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_prev_back = size() > 1 ? get(size() - 2) : T();
#endif
    assert(!is_empty());
    --size_;
    assert(size() == old_size - 1);
    assert(is_empty() || get(size() - 1) == old_prev_back);
}

template <class T>
void CDArray<T>::insert(size_t pos, T const &v)
{
    assert(pos >= 0 && pos <= size());
#ifndef NDEBUG
    size_t old_size = size();
    T old_back = get(size() - 1);
    T old_pos_v = get(pos);
#endif
    if (is_full())
    {
        grow();
    }
    for (size_t i = size(); i > pos; --i)
    {
        data_[i] = data_[i - 1];
    }
    data_[pos] = v;
    ++size_;
    assert(size() == old_size + 1);
    assert(get(pos) == v);
    assert(get(pos + 1) == old_pos_v);
    assert(get(size() - 1) == old_back);
}

template <class T>
void CDArray<T>::remove(size_t pos)
{
    assert(pos >= 0 && pos < size());
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_pos_v = (pos <= (size() - 2)) ? get(pos + 1) : T();
#endif
    for (size_t i = pos; i < size() - 1; ++i)
    {
        data_[i] = data_[i + 1];
    }
    --size_;
    assert(size() == old_size - 1);
    assert(pos == size() || get(pos) == old_next_pos_v);
}

template <class T>
void CDArray<T>::grow()
{
#ifndef NDEBUG
    size_t old_capacity = capacity();
    T old_front = get(0);
    T old_back = get(size() - 1);
#endif

    // Duplicar la capacidad
    size_t new_capacity = old_capacity * 2;

    // Crear un nuevo bloque de memoria con la nueva capacidad
    std::shared_ptr<T[]> new_data(new T[new_capacity]);

    // Copiar los elementos del arreglo antiguo al nuevo bloque de memoria
    for (size_t i = 0; i < size(); ++i)
    {
        new_data[i] = data_[i];
    }

    // Actualizar el puntero del arreglo para que apunte al nuevo bloque de memoria
    data_ = new_data;
    capacity_ = new_capacity;

    assert(capacity() == 2 * old_capacity);
    assert(get(0) == old_front);
    assert(get(size() - 1) == old_back);
}