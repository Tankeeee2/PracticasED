/**
 * @file a_star_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <tuple>
#include <limits>
#include <functional>

#include <a_star_algorithm.hpp>
#include <priority_queue.hpp>

template <class T, class Heuristic>
size_t
a_star_algorithm(Graph<T, float> &g,
                 typename Graph<T, float>::VertexRef &start,
                 typename Graph<T, float>::VertexRef &end,
                 Heuristic &H,
                 std::vector<size_t> &predecessors,
                 std::vector<float> &distances)
{
    assert(g.has(start));
    assert(g.has(end));

    /** @brief the Dijkstra tuple.
     * We use the tuple (dist,u's label,v's label) format to represent an edge.
     * Remember: tuples use lexicographic comparisons.
     */
    using Tuple = std::tuple<float, float, size_t, size_t>;

    size_t iterations = 0;
    g.reset(false);

    // TODO: initialize the predecessors and distances vectors.
    // Remember: each vertex is predecessor of itself with distance infinite.

    size_t n = g.num_vertices();
    predecessors.resize(n);
    distances.assign(n, std::numeric_limits<float>::infinity());

    for (size_t i = 0; i < n; ++i)
    {
        predecessors[i] = i;
    }

    std::vector<Tuple> empty;
    PriorityQueue<Tuple> q(empty, std::less<Tuple>());

    size_t start_label = start->label();
    size_t end_label = end->label();
    distances[start_label] = 0.0;
    q.enqueue({H(start, end), 0.0, start_label, start_label});

    g.reset(false);

    //

    // TODO: implement the A* algorithm.
    // Note: you can use std::priority_queue if you have not implemented
    // the ADT PriorityQueue.

    while (!q.is_empty() && !end->is_visited())
    {
        auto [f, g_cost, u_label, pred] = q.front();
        q.dequeue();

        auto u = g.vertex(u_label);
        if (!u->is_visited())
        {
            predecessors[u_label] = pred;
            distances[u_label] = g_cost;

            u->set_visited(true);
            auto e = g.edges_begin(g.get_iterator(u));
            auto e_end = g.edges_end(g.get_iterator(u));

            while (e != e_end)
            {
                auto edge = *e;
                auto v = edge->other(u);
                if (!v->is_visited())
                {
                    float new_f = distances[u_label] + edge->item() + H(v, end);
                    float new_cost = distances[u_label] + edge->item();
                    q.enqueue({new_f, new_cost, v->label(), u_label});
                }
                ++e;
            }
        }
        ++iterations;
    }

    //
    return iterations;
}

inline std::list<size_t>
a_star_path(size_t src, size_t dst,
            std::vector<size_t> const &predecessors)
{
    assert(src < predecessors.size());
    assert(dst < predecessors.size());
    assert(predecessors[src] == src);
    std::list<size_t> path;
    // TODO

    if (dst != src && predecessors[dst] == dst)
    {
        return {};
    }
    for (size_t u = dst; u != src; u = predecessors[u])
    {
        path.push_front(u);
    }
    path.push_front(src);

    //
    return path;
}
