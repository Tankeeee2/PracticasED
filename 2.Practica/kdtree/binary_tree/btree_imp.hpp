/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <sstream>

#include "btree.hpp"

template <class T>
bool BTree<T>::is_empty() const
{
    bool ret_v = false;
    // TODO

    //
    return ret_v;
}

template <class T>
BTree<T>::BTree()
{
    // TODO

    //
    assert(is_empty());
}

template <class T>
BTree<T>::BTree(const T &it)
{
    // TODO

    //
    assert(!is_empty());
    assert(item() == it);
    assert(left().is_empty());
    assert(right().is_empty());
}

template <class T>
BTree<T>::BTree(std::istream &in) noexcept(false)
    : BTree<T>()
{
    // TODO
    // Remember: throw std:runtime_error exception with text
    //"Wrong input format." when an input format error is found.

    //
}

template <class T>
T BTree<T>::item() const
{
    assert(!is_empty());
    T ret_v;
    // TODO

    //
    return ret_v;
}

template <class T>
BTree<T> BTree<T>::left() const
{
    assert(!is_empty());
    BTree<T> subtree;
    // TODO
    // Hint: use the private constructor given a root node.

    //
    return subtree;
}

template <class T>
BTree<T> BTree<T>::right() const
{
    assert(!is_empty());
    BTree<T> subtree;
    // TODO
    // Hint: use the private constructor given a root node.

    //
    return subtree;
}

template <class T>
std::ostream &BTree<T>::fold(std::ostream &out) const
{
    // TODO

    //
    return out;
}

template <class T>
void BTree<T>::create_root(const T &it)
{
    assert(is_empty());
    // TODO

    //
    assert(!is_empty());
    assert(item() == it);
    assert(left().is_empty());
    assert(right().is_empty());
}

template <class T>
void BTree<T>::set_item(const T &new_it)
{
    assert(!is_empty());
    // TODO

    //
    assert(item() == new_it);
}

template <class T>
void BTree<T>::set_left(const BTree<T> &new_left)
{
    assert(!is_empty());
    // TODO

    //
    assert(left().root() == new_left.root());
}

template <class T>
void BTree<T>::set_right(const BTree<T> &new_right)
{
    assert(!is_empty());
    // TODO

    //
    assert(right().root() == new_right.root());
}

template <class T>
BTree<T>::BTree(const typename BTNode<T>::Ref &n)
{
    // TODO

    //
    assert(root() == n);
}

template <class T>
typename BTNode<T>::Ref BTree<T>::root() const
{
    typename BTNode<T>::Ref node;
    // TODO

    //
    return node;
}

template <class T>
void BTree<T>::set_root(const typename BTNode<T>::Ref &new_root)
{
    // TODO

    //
    assert(root() == new_root);
}

template <class T>
BTree<T>::BTree(const BTree<T> &other)
{
    set_root(other.root());
}

template <class T>
BTree<T>::BTree(BTree<T> &&other)
{
    set_root(other.root());
}

template <class T>
BTree<T> &BTree<T>::operator=(const BTree<T> &other)
{
    set_root(other.root());
    return *this;
}

template <class T>
BTree<T> &BTree<T>::operator=(BTree<T> &&other)
{
    set_root(other.root());
    return *this;
}
