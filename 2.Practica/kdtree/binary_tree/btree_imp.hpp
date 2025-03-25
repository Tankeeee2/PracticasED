/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
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
    ret_v = (this->_root == nullptr);
    //
    return ret_v;
}

template <class T>
BTree<T>::BTree()
{
    // TODO
    this->_root = nullptr;
    //
    assert(is_empty());
}

template <class T>
BTree<T>::BTree(const T &it)
{
    _root = BTNode<T>::create(it); // Usar el método estático create en lugar del constructor
    assert(!is_empty());
    assert(item() == it);
    assert(left().is_empty());
    assert(right().is_empty());
}

template <class T>
BTree<T>::BTree(std::istream &in) noexcept(false)
    : BTree<T>()
{
    std::string token;
    in >> token;
    if (token == "[]")
        return;
        
    if (token != "[")
        throw std::runtime_error("Wrong input format.");

    T item;
    in >> item;
    
    create_root(item);
    
    auto left_tree = BTree<T>(in); 
    set_left(left_tree);
    
    auto right_tree = BTree<T>(in);
    set_right(right_tree);
    
    in >> token;
    if (token != "]")
        throw std::runtime_error("Wrong input format.");
}

template <class T>
T BTree<T>::item() const
{
    assert(!is_empty());
    T ret_v;
    // TODO
    ret_v = this->_root->item();
    //
    return ret_v;
}

template <class T>
BTree<T> BTree<T>::left() const 
{
    assert(!is_empty());
    return BTree<T>(_root->left());
}

template <class T>
BTree<T> BTree<T>::right() const  // Aquí faltaba el tipo de retorno BTree<T>
{
    assert(!is_empty());
    return BTree<T>(_root->right());
}

template <class T>
std::ostream &BTree<T>::fold(std::ostream &out) const
{
    if (is_empty()){
        out << "[]";
    }
    else
    {
        out << "[ ";
        out << item();
        out << " ";
        left().fold(out);
        out << " ";
        right().fold(out);
        out << " ]";
    }
    return out;
}

template <class T>
void BTree<T>::create_root(const T &it)
{
    assert(is_empty());
    _root = BTNode<T>::create(it);
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
    this->_root->set_item(new_it);
    //
    assert(item() == new_it);
}

template <class T>
void BTree<T>::set_left(const BTree<T> &new_left)
{
    assert(!is_empty());
    _root->set_left(new_left._root);
    assert(left().root() == new_left.root());
}

template <class T>
void BTree<T>::set_right(const BTree<T> &new_right) 
{
    assert(!is_empty());
    _root->set_right(new_right._root);
    assert(right().root() == new_right.root());
}

template <class T>
BTree<T>::BTree(const typename BTNode<T>::Ref &n)
{
    _root = n; 
}

template <class T>
typename BTNode<T>::Ref BTree<T>::root() const
{
    return _root;
}

template <class T>
void BTree<T>::set_root(const typename BTNode<T>::Ref &new_root)
{
    _root = new_root;
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
