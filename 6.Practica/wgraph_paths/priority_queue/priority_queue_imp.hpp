#pragma once
// Directiva que evita que el archivo se incluya múltiples veces en tiempo de compilación.

#include <priority_queue.hpp>
// Incluye la definición de la clase PriorityQueue que está implementada en este archivo.

// Método que verifica si la cola de prioridad está vacía.
template <class T>
bool PriorityQueue<T>::is_empty() const
{
    // TODO: fixme
    return heap_.is_empty(); // Simplemente delega la comprobación al heap interno.
    //
}

// Método que devuelve el número de elementos en la cola de prioridad.
template <class T>
size_t PriorityQueue<T>::size() const
{
    size_t ret_v = 0; // Variable para almacenar el tamaño a retornar.
    // TODO
    ret_v = heap_.size(); // Se asigna el tamaño usando el heap interno.
    //
    assert(!heap_.is_empty() || ret_v == 0); // Si el heap está vacío, el tamaño debe ser 0.
    return ret_v; // Se retorna el tamaño.
}

// Constructor que inicializa la cola de prioridad con un vector y un comparador.
template <class T>
PriorityQueue<T>::PriorityQueue(std::vector<T> &values, Comp const &comp)
    : heap_(values, comp) // Inicializa el heap interno con el vector y el comparador.
{
    assert(is_empty()); // Verifica que la cola de prioridad esté vacía después de construirla.
}

// Destructor de la cola de prioridad (no realiza ninguna acción especial).
template <class T>
PriorityQueue<T>::~PriorityQueue() {}

// Método que devuelve el primer elemento (el de mayor prioridad).
template <class T>
const T &PriorityQueue<T>::front() const
{
    // TODO: fixme
    return heap_.item(); // El elemento con mayor prioridad está en la raíz del heap.
    //
}

// Método para insertar un nuevo elemento en la cola de prioridad.
template <class T>
void PriorityQueue<T>::enqueue(const T &new_v)
{
#ifndef NDEBUG
    size_t old_size = size(); // Guarda el tamaño actual para validación posterior.
#endif
    // TODO
    heap_.insert(new_v); // Inserta el nuevo elemento en el heap.
    //
    assert(size() == old_size + 1); // Comprueba que el tamaño ha aumentado en 1.
}

// Método para eliminar el elemento de mayor prioridad.
template <class T>
void PriorityQueue<T>::dequeue()
{
    assert(!is_empty()); // No se puede eliminar si está vacía.
#ifndef NDEBUG
    size_t old_size = size(); // Guarda el tamaño actual para validación posterior.
#endif
    // TODO
    heap_.remove(); // Elimina el elemento con mayor prioridad del heap.
    //
    assert(size() == old_size - 1); // Comprueba que el tamaño ha disminuido en 1.
}
