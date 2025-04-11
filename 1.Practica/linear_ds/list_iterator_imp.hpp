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
#include <list_iterator.hpp>

template <class T> ListIterator<T>::~ListIterator() {}

template <class T> bool ListIterator<T>::is_valid() const {
  return node_ != nullptr; // Cambiamos la validación
}

template <class T> ListIterator<T>::ListIterator() {
  node_ = nullptr;
  assert(!is_valid());
}

template <class T>
ListIterator<T>::ListIterator(typename DNode<T>::Ref const &n) {
  node_ = n;
}

template <class T> T const &ListIterator<T>::item() const {
  assert(is_valid() && !node_->is_dummy());
  return node_->item();
}

template <class T> ListIterator<T> ListIterator<T>::next(size_t dist) const {
  assert(is_valid());
  ListIterator<T> ret_v(*this);
  ret_v.goto_next(dist);
  return ret_v;
}

template <class T> ListIterator<T> ListIterator<T>::prev(size_t dist) const {
  assert(is_valid());
  ListIterator<T> ret_v(*this);
  ret_v.goto_prev(dist);
  return ret_v;
}

template <class T>
size_t ListIterator<T>::distance(ListIterator<T> const &other) const {
  size_t dist = 0;
  auto aux = *this;

  while (aux.node_ != nullptr && aux.node_ != other.node_) {
    auto next = aux.node_->next();
    if (next != nullptr && !next->is_dummy())
      dist++;
    aux.node_ = next;
  }

  return dist;
}

template <class T>
bool ListIterator<T>::operator==(ListIterator<T> const &o) const {
  return node_ == o.node_;
}

template <class T>
bool ListIterator<T>::operator!=(ListIterator<T> const &o) const {
  return !(*this == o);
}

template <class T> void ListIterator<T>::set_item(T const &it) {
  assert(is_valid());
  node_->set_item(it);
}

template <class T> void ListIterator<T>::goto_next(size_t dist) {
  while (dist > 0 && node_ != nullptr) // Modificamos la condición
  {
    node_ = node_->next();
    if (node_ != nullptr && !node_->is_dummy())
      dist--;
  }
}

template <class T> void ListIterator<T>::goto_prev(size_t dist) {
  while (dist > 0 && node_ != nullptr) // Modificamos la condición
  {
    node_ = node_->prev();
    if (node_ != nullptr && !node_->is_dummy())
      dist--;
  }
}

template <class T> typename DNode<T>::Ref ListIterator<T>::node() const {
  return node_;
}

template <class T>
void ListIterator<T>::set_node(typename DNode<T>::Ref const &n) {
  node_ = n;
  assert(node() == n);
}