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
    int left = -1;
    int right = -1;
    if (!t.is_empty())
    {
        left = compute_height<T>(t.left()) + 1;
        right = compute_height<T>(t.right()) + 1;
    }
    if (right >= left)
    {
        height = right;
    }
    else
    {
        height = left;
    }
    return height;
}

template <class T>
size_t compute_size(const BTree<T> &t)
{
    size_t ret_val = 0;
    if (!t.is_empty())
    {
        ret_val = compute_size<T>(t.right()) + compute_size<T>(t.left()) + 1;
    }
    return ret_val;
}

template <class T, typename Processor>
bool prefix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    if (!tree.is_empty())
    {
        retVal = retVal && p(tree.item());
        retVal = retVal && prefix_process<T, Processor>(tree.left(), p);
        retVal = retVal && prefix_process<T, Processor>(tree.right(), p);
    }
    return retVal;
}

template <class T, class Processor>
bool infix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    if (!tree.is_empty())
    {
        retVal = retVal && infix_process<T, Processor>(tree.left(), p);
        retVal = retVal && p(tree.item());
        retVal = retVal && infix_process<T, Processor>(tree.right(), p);
    }
    return retVal;
}

template <class T, class Processor>
bool postfix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    if (!tree.is_empty())
    {
        retVal = retVal && postfix_process<T, Processor>(tree.left(), p);
        retVal = retVal && postfix_process<T, Processor>(tree.right(), p);
        retVal = retVal && p(tree.item());
    }
    return retVal;
}

template <class T, class Processor>
bool breadth_first_process(const BTree<T> &tree, Processor &p)
{
    bool go_on = true;
    std::queue<BTree<T>> q;
    q.push(tree);

    while (!q.empty() && go_on)
    {
        BTree<T> current = q.front();
        q.pop();

        if (!current.is_empty())
        {
            go_on = p(current.item());
            q.push(current.left());
            q.push(current.right());
        }
    }
    return go_on;
}

template <class T>
std::ostream &
print_prefix(std::ostream &out, const BTree<T> &tree)
{
    auto p = [&out](T n) mutable -> bool
    {
        out << n << " ";
        return true;
    };
    prefix_process<T>(tree, p);
    return out;
}

template <class T>
std::ostream &
print_infix(std::ostream &out, const BTree<T> &tree)
{
    auto p = [&out](T n) mutable -> bool
    {
        out << n << " ";
        return true;
    };
    infix_process<T>(tree, p);
    return out;
}

template <class T>
std::ostream &
print_postfix(std::ostream &out, const BTree<T> &tree)
{
    auto p = [&out](T n) mutable -> bool
    {
        out << n << " ";
        return true;
    };
    postfix_process<T>(tree, p);
    return out;
}

template <class T>
std::ostream &
print_breadth_first(std::ostream &out, const BTree<T> &tree)
{
    auto p = [&out](T n) mutable -> bool
    {
        out << n << " ";
        return true;
    };
    breadth_first_process<T>(tree, p);
    return out;
}

template <class T>
bool search_prefix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    auto p = [&found, it, &count](T item) mutable -> bool
    {
        count++;
        found = (it == item);
        return it != item;
    };
    prefix_process<T>(tree, p);
    return found;
}

template <class T>
bool search_infix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;

    auto p = [&found, it, &count](T item) mutable -> bool
    {
        count++;
        found = (it == item);
        return it != item;
    };
    infix_process<T>(tree, p);

    return found;
}

template <class T>
bool search_postfix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;

    auto p = [&found, it, &count](T item) mutable -> bool
    {
        count++;
        found = (it == item);
        return it != item;
    };
    postfix_process<T>(tree, p);

    return found;
}

template <class T>
bool search_breadth_first(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    auto p = [&found, it, &count](T item) mutable -> bool
    {
        count++;
        found = (it == item);
        return it != item;
    };
    breadth_first_process<T>(tree, p);
    return found;
}

template <class T>
bool check_btree_in_order(const BTree<T> &tree)
{
    bool ret_val = true;
    bool first = true;
    T prenum;
    auto p = [&first, &prenum](T value) mutable -> bool
    {
        if (first)
        {
            prenum = value;
            first = false;
            return true;
        }
        if (prenum < value)
        {
            prenum = value;
            return true;
        }
        return false;
    };
    ret_val = infix_process<T>(tree, p);
    return ret_val;
}

template <class T>
bool has_in_order(const BTree<T> &tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));
    bool ret_val = false;
    if (tree.is_empty())
    {
        return false;
    }
    if (v < tree.item())
    {
        ret_val = has_in_order(tree.left(), v);
    }
    else if (v > tree.item())
    {
        ret_val = has_in_order(tree.right(), v);
    }
    else if (v == tree.item())
    {
        return true;
    }
    return ret_val;
}

template <class T>
void insert_in_order(BTree<T> &&tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));

    if (tree.is_empty())
    {
        tree.create_root(v);
        return;
    }

    if (v < tree.item())
    {
        if (tree.left().is_empty())
        {
            tree.set_left(BTree<T>(v));
        }
        else
        {
            insert_in_order(tree.left(), v);
        }
    }
    else if (v > tree.item())
    {
        if (tree.right().is_empty())
        {
            tree.set_right(BTree<T>(v));
        }
        else
        {
            insert_in_order(tree.right(), v);
        }
    }

    assert(has_in_order<T>(tree, v));
}

template <class T>
void insert_in_order(BTree<T> &tree, T const &v)
{
    insert_in_order(std::move(tree), v);
}