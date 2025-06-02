/**
 * @file dijkstra_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <cassert>
#include <tuple>
#include <functional>
#include <limits>
#include <vector>
#include <list>
#include <queue>

#include <dijkstra_algorithm.hpp>
#include <priority_queue.hpp>

// Implementación del algoritmo de Dijkstra
template <class T>
void dijkstra_algorithm(Graph<T, float> &g,
                        typename Graph<T, float>::VertexRef const &source,
                        std::vector<size_t> &predecessors,
                        std::vector<float> &distances)
{
    assert(g.has(source));

    using Tuple = std::tuple<float, size_t, size_t>; // (dist, u_label, v_label)

    // Reset visited flags en vértices y aristas
    g.reset(false);

    // Preparar vectores
    size_t n = g.num_vertices();
    predecessors.assign(n, 0);
    distances.assign(n, std::numeric_limits<float>::infinity());

    size_t src = source->label();
    for (size_t i = 0; i < n; ++i) {
        predecessors[i] = i;
    }
    distances[src] = 0.0f;

    // Min-heap de tuplas: orden lexicográfico, primero distancia mínima
    std::priority_queue<
        Tuple,
        std::vector<Tuple>,
        std::greater<Tuple>
    > pq;

    // Iniciar con la fuente
    pq.emplace(0.0f, src, src);

    while (!pq.empty()) {
        auto [dist_u, u_label, v_dummy] = pq.top();
        pq.pop();

        auto u = g.vertex(u_label);
        if (u->is_visited()) continue;
        u->set_visited(true);

        auto u_iter = g.get_iterator(u);
        for (auto eit = g.edges_begin(u_iter); eit != g.edges_end(u_iter); ++eit) {
            auto e = *eit;
            auto v = e->other(u);
            size_t v_label = v->label();
            if (v->is_visited()) continue;

            float w = e->item();
            float alt = dist_u + w;
            // Relajación, en caso de empate elegir predecessor menor
            if (alt < distances[v_label] || (alt == distances[v_label] && u_label < predecessors[v_label])) {
                distances[v_label] = alt;
                predecessors[v_label] = u_label;
                pq.emplace(alt, v_label, 0); // v_dummy no usado en pop
            }
        }
    }
}

// Construcción de camino mínimo a partir de 'predecessors'
inline std::list<size_t>
dijkstra_path(size_t src, size_t dst,
              std::vector<size_t> const &predecessors)
{
    assert(src < predecessors.size());
    assert(dst < predecessors.size());
    assert(predecessors[src] == src);

    std::list<size_t> path;
    // Si destino inalcanzable
    if (dst != src && predecessors[dst] == dst)
        return path;

    for (size_t u = dst; ; u = predecessors[u]) {
        path.push_front(u);
        if (u == src) break;
    }
    return path;
}
