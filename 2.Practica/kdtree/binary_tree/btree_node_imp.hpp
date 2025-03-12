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

#include <btree_node.hpp>

template <class T>
BTNode<T>::BTNode(T const &it, const BTNode<T>::Ref &l,
                  const BTNode<T>::Ref &r)
{
    // TODO

    //
    assert(item() == it);
    assert(left() == l);
    assert(right() == r);
}

template <class T>
typename BTNode<T>::Ref BTNode<T>::create(T const &it,
                                          const BTNode<T>::Ref &left,
                                          const BTNode<T>::Ref &right)
{
    return typename BTNode<T>::Ref(new BTNode<T>(it, left, right));
}

template <class T>
const T &BTNode<T>::item() const
{
    // TODO: implement this method with respect to your representation.
    T fixme;
    return fixme;
    //
}

template <class T>
typename BTNode<T>::Ref BTNode<T>::left() const
{
    typename BTNode<T>::Ref child;
    // TODO

    //
    return child;
}

template <class T>
typename BTNode<T>::Ref BTNode<T>::right() const
{
    typename BTNode<T>::Ref child;
    // TODO

    //
    return child;
}

template <class T>
void BTNode<T>::set_item(const T &new_it)
{
    // TODO

    //
    assert(item() == new_it);
}

template <class T>
void BTNode<T>::set_left(const BTNode<T>::Ref &new_child)
{
    // TODO

    //
    assert(left() == new_child);
}

template <class T>
void BTNode<T>::set_right(const BTNode<T>::Ref &new_child)
{
    // TODO

    //
    assert(right() == new_child);
}
