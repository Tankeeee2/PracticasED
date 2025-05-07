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

#include <vector2d.hpp>

// TODO: implement the interface for the proposed ADT.

template <class T>
Vector2D<T>::Vector2D()
{
    // TODO

    //
    assert(x() == 0);
    assert(y() == 0);
}

template <class T>
Vector2D<T>::Vector2D(T const &x_v, T const &y_v)
{
    // TODO

    //
    assert(x() == x_v);
    assert(y() == y_v);
}

template <class T>
Vector2D<T>::~Vector2D() {}

template <class T>
T const &
Vector2D<T>::x() const
{
    // TODO
    T fixme{};
    return fixme;
    //
}

template <class T>
T const &
Vector2D<T>::y() const
{
    // TODO
    T fixme{};
    return fixme;
    //
}

template <class T>
void Vector2D<T>::set_x(T const &x_v)
{
    // TODO

    //
    assert(x() == x_v);
}

template <class T>
void Vector2D<T>::set_y(T const &y_v)
{
    // TODO

    //
    assert(y() == y_v);
}

template <class T>
void Vector2D<T>::add(const Vector2D<T> &o)
{
#ifndef NDEBUG
    T old_x = x();
    T old_y = y();
#endif
    // TODO

    //
    assert(x() == (old_x + o.x()));
    assert(y() == (old_y + o.y()));
}
