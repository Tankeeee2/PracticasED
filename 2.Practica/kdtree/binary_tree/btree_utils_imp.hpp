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
#include <queue>

#include <btree_utils.hpp>

template <class T>
int compute_height(const BTree<T> &t)
{
    int height = 0;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.

    //
    return height;
}

template <class T>
size_t compute_size(const BTree<T> &t)
{
    size_t ret_val = 0;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.

    //
    return ret_val;
}

template <class T, typename Processor>
bool prefix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.

    //
    return retVal;
}

template <class T, class Processor>
bool infix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.

    //
    return retVal;
}

template <class T, class Processor>
bool postfix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.

    //
    return retVal;
}

template <class T, class Processor>
bool breadth_first_process(const BTree<T> &tree, Processor &p)
{
    bool go_on = true;
    // TODO
    // Hint: think about which data structure can help you to do this kind
    //   of traversal.

    //
    return go_on;
}

template <class T>
std::ostream &
print_prefix(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use a prefix_process to process the tree with this lambda.
    // Remember: the lambda must return true.

    //
    return out;
}

template <class T>
std::ostream &
print_infix(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use an infix_process to process the tree with this lambda.
    // Remember: the lambda must return true.

    //
    return out;
}

template <class T>
std::ostream &
print_postfix(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use a postfix_process to process the tree with this lambda.
    // Remember: the lambda must return true.

    //
    return out;
}

template <class T>
std::ostream &
print_breadth_first(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use a breadth_first_process to process the tree with this lambda.
    // Remember: the lambda must return true.

    //
    return out;
}

template <class T>
bool search_prefix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the prefix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.

    //
    return found;
}

template <class T>
bool search_infix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the infix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.

    //
    return found;
}

template <class T>
bool search_postfix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the postfix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.

    //
    return found;
}

template <class T>
bool search_breadth_first(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the breadth_first_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.

    //
    return found;
}

template <class T>
bool check_btree_in_order(const BTree<T> &tree)
{
    bool ret_val = true;
    // TODO
    // Hint: You can create a lambda function with a parameter to compare it with
    //  the last the value seen.
    //  Use the lambda with the infix_process.

    //
    return ret_val;
}

template <class T>
bool has_in_order(const BTree<T> &tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));
    bool ret_val = false;
    // TODO

    //
    return ret_val;
}

template <class T>
void insert_in_order(BTree<T> &&tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));
    // TODO

    //
    assert(has_in_order<T>(tree, v));
}

template <class T>
void insert_in_order(BTree<T> &tree, T const &v)
{
    insert_in_order(std::move(tree), v);
}