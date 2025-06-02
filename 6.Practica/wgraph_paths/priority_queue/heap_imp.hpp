/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
// Directiva que evita que el archivo se incluya múltiples veces en la compilación.

#include <exception>
// Incluye soporte para el manejo de excepciones estándar.

#include <cassert>
// Permite el uso de la función assert() para validar condiciones en tiempo de ejecución.

#include <algorithm>
// Incluye utilidades como std::swap y std::reverse.

#include <heap.hpp>
// Incluye el archivo de cabecera con la definición de la clase Heap.

// Función que devuelve el índice del nodo padre de un nodo en un heap.
inline size_t parent(size_t i)
{
    assert(i > 0); // El índice debe ser mayor que 0 para tener un padre.
    // TODO: fixme
    return (i - 1) / 2; // Fórmula para encontrar el índice del padre en un heap binario.
}

// Función que devuelve el índice del hijo izquierdo.
inline size_t left(size_t i)
{
    // TODO: fixme
    return 2 * i + 1; // Fórmula para calcular el índice del hijo izquierdo.
}

// Función que devuelve el índice del hijo derecho.
inline size_t right(size_t i)
{
    // TODO: fixme
    return 2 * i + 2; // Fórmula para calcular el índice del hijo derecho.
}

// Método privado que reordena el heap hacia arriba desde la posición i.
template <class T>
void Heap<T>::shift_up(size_t i)
{
    // TODO
    while (i > 0 && comp_((*values_)[i], (*values_)[parent(i)])) {
        // Mientras i no sea la raíz y el elemento actual sea menor que su padre (según el comparador), se intercambian.
        std::swap((*values_)[i], (*values_)[parent(i)]);
        i = parent(i); // Se actualiza i al índice del padre.
    }
}

// Método privado que reordena el heap hacia abajo desde la posición i.
template <class T>
void Heap<T>::shift_down(size_t i)
{
    // TODO
    size_t n = last_item_; // Número de elementos en el heap.
    while (true) {
        size_t l = left(i);  // Índice del hijo izquierdo.
        size_t r = right(i); // Índice del hijo derecho.
        size_t best = i;     // Supone que el mejor es el actual.

        if (l < n && comp_((*values_)[l], (*values_)[best])) {
            // Si el hijo izquierdo existe y es menor que el actual, se actualiza best.
            best = l;
        }
        if (r < n && comp_((*values_)[r], (*values_)[best])) {
            // Si el hijo derecho existe y es menor que el mejor hasta ahora, se actualiza best.
            best = r;
        }
        if (best != i) {
            // Si se encontró un hijo mejor, se intercambian y se repite desde la nueva posición.
            std::swap((*values_)[i], (*values_)[best]);
            i = best;
        } else {
            break; // Si ya está en su sitio, se termina.
        }
    }
}

// Comprueba recursivamente si a partir de una raíz el vector cumple las propiedades del heap.
template <class T>
bool Heap<T>::is_a_heap(size_t root) const
{
    bool ret_val = true;
    // TODO
    size_t l = left(root);  // Hijo izquierdo.
    size_t r = right(root); // Hijo derecho.

    if (l < last_item_) {
        // Si existe hijo izquierdo, se comprueba si el heap cumple con el hijo izquierdo.
        ret_val &= comp_((*values_)[root], (*values_)[l]) && is_a_heap(l);
    }
    if (r < last_item_) {
        // Si existe hijo derecho, se comprueba lo mismo.
        ret_val &= comp_((*values_)[root], (*values_)[r]) && is_a_heap(r);
    }
    return ret_val;
}

// Convierte el vector en un heap reorganizándolo desde el último padre hacia la raíz.
template <class T>
void Heap<T>::heapify()
{
    // TODO
    for (int i = (int)last_item_ / 2 - 1; i >= 0; --i) {
        // Se comienza desde el último nodo que tiene hijos y se ajusta el heap hacia abajo.
        shift_down(i);
    }
    assert(is_a_heap()); // Se asegura que después del proceso sigue siendo un heap válido.
}

// Constructor del heap que recibe un vector y un comparador.
template <class T>
Heap<T>::Heap(std::vector<T> &values, Comp const &comp) : values_(&values), comp_(comp)
{
    // TODO
    last_item_ = values.size(); // Número de elementos activos en el heap.
    heapify(); // Se asegura que el vector cumpla la propiedad de heap.

    assert(is_a_heap()); // Se comprueba que el heap es válido.
    assert(size() == values.size()); // Se asegura que el tamaño es correcto.
}

// Destructor (no realiza ninguna acción especial).
template <class T>
Heap<T>::~Heap()
{
}

// Verifica si el heap está vacío.
template <class T>
bool Heap<T>::is_empty() const
{
    // TODO: fixme
    return last_item_ == 0; // Si no hay elementos activos, está vacío.
}

// Devuelve el número de elementos en el heap.
template <class T>
size_t Heap<T>::size() const
{
    // TODO: fixme
    return last_item_;
}

// Devuelve el elemento mínimo (raíz del heap).
template <class T>
T const &Heap<T>::item() const
{
    assert(!is_empty()); // No se puede acceder al mínimo si el heap está vacío.
    // TODO: fixme
    return (*values_)[0]; // El mínimo está siempre en la raíz (índice 0).
}

// Inserta un nuevo elemento en el heap.
template <class T>
void Heap<T>::insert(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size(); // Guarda el tamaño antes de insertar para comprobación.
#endif
    // TODO
    if (last_item_ < values_->size()) {
        // Si hay espacio en el vector, se reutiliza.
        (*values_)[last_item_] = new_it;
    } else {
        // Si no, se añade al final del vector.
        values_->push_back(new_it);
    }
    ++last_item_; // Se incrementa el tamaño activo.
    shift_up(last_item_ - 1); // Se reordena el heap hacia arriba desde la nueva posición.

    assert(is_a_heap()); // Comprobación de validez del heap.
    assert(size() == old_size + 1); // El tamaño debe haber aumentado en uno.
}

// Elimina el elemento mínimo del heap.
template <class T>
void Heap<T>::remove()
{
#ifndef NDEBUG
    size_t old_size = size(); // Guarda el tamaño antes de eliminar.
#endif
    assert(!is_empty()); // No se puede eliminar si está vacío.
    // TODO
    std::swap((*values_)[0], (*values_)[last_item_ - 1]); // Intercambia la raíz con el último elemento.
    --last_item_; // Disminuye el tamaño del heap.
    shift_down(0); // Se reordena hacia abajo desde la raíz.

    assert(is_a_heap()); // Se verifica que el heap sigue siendo válido.
    assert(size() == old_size - 1); // Se asegura que el tamaño disminuyó en uno.
}

// Algoritmo de ordenación heapsort usando la clase Heap.
template <class T>
void heapsort(std::vector<T> &values, std::function<bool(T const &a, T const &b)> const &comp)
{
    // TODO
    Heap<T> heap(values, comp); // Se construye un heap a partir del vector.

    std::vector<T> sorted; // Vector temporal para almacenar los elementos ordenados.

    while (!heap.is_empty()) {
        sorted.push_back(heap.item()); // Se toma el mínimo actual.
        heap.remove(); // Se elimina del heap.
    }

    std::reverse(sorted.begin(), sorted.end()); // Se invierte ya que se extrajeron en orden inverso.
    values = sorted; // Se copia el vector ordenado al original.

#ifndef NDEBUG
    for (size_t i = 1; i < values.size(); ++i)
        assert(comp(values[i], values[i - 1])); // Verifica que el vector está ordenado.
#endif
}
