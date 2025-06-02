/**
 * @file floyd_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <utility>
#include <limits>
#include <stack>
#include <floyd_algorithm.hpp>

#ifdef __VERBOSE__
extern int Verbose_level;
#endif

inline std::ostream &
print_floyd_I(std::ostream &out,
              IMatrix const &I)
{
    std::string blanks = "          ";
    std::string unders = "__________";
    size_t field_width = 4;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < I.cols(); ++i)
        out << std::setw(field_width) << i;
    out << std::endl;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < I.cols(); ++i)
        out << std::setw(field_width) << unders.substr(0, field_width);
    out << std::endl;
    for (size_t r = 0; r < I.rows(); ++r)
    {
        out << std::setw(field_width) << r << '|';
        for (size_t c = 0; c < I.cols(); ++c)
        {
            if (I[r][c] == -1)
                out << std::setw(field_width) << '-';
            else
                out << std::setw(field_width) << I[r][c];
        }
        out << std::endl;
    }
    return out;
}

inline std::ostream &
print_floyd_D(std::ostream &out,
              FMatrix const &D)
{
    std::string blanks = "          ";
    std::string unders = "__________";
    size_t field_width = 4;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < D.cols(); ++i)
        out << std::setw(field_width) << i;
    out << std::endl;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < D.cols(); ++i)
        out << std::setw(field_width) << unders.substr(0, field_width);
    out << std::endl;
    for (size_t r = 0; r < D.rows(); ++r)
    {
        out << std::setw(field_width) << r << '|';
        for (size_t c = 0; c < D.cols(); ++c)
        {
            if (D[r][c] == std::numeric_limits<float>::infinity())
                out << std::setw(field_width) << '-';
            else
                out << std::setw(field_width) << D[r][c];
        }
        out << std::endl;
    }
    return out;
}

/**
 * @brief Compute the weight matrix.
 *
 * Also compute two maps to convert between the vertex key and the index of the matrix.
 *
 * @tparam T Vertex item data type.
 * @param[in] g is the graph.
 * @param[out] D is the distances matrix.
 */
template <class T>
void compute_weight_matrix(Graph<T, float> const &g,
                           FMatrix &D)
{
    D.resize(g.num_vertices(), g.num_vertices(),
             std::numeric_limits<float>::infinity());

    // TODO: Initialize the distances matrix traversing the graph by vertex and edges.

    size_t n = g.num_vertices();

    // Para cada vértice u, recorremos sus aristas
    for(auto vit = g.vertices_begin(); vit != g.vertices_end(); ++vit) {
        auto u_ptr = *vit;
        size_t i = u_ptr->label();

        auto eit = g.edges_begin(g.get_iterator(u_ptr));
        auto eend = g.edges_end(g.get_iterator(u_ptr));
        for(; eit != eend; ++eit) {
            auto edge = *eit;
            auto v_ptr = edge->other(u_ptr);
            size_t j = v_ptr->label();
            D[i][j] = edge->item();
        }
    }

    //
}

template <class T>
void floyd_algorithm(Graph<T, float> const &g,
                     FMatrix &D,
                     IMatrix &I)
{
    compute_weight_matrix(g, D);
    I.resize(g.num_vertices(), g.num_vertices(), -1);

    // TODO: Codify the Floyd algorithm.

    size_t n = g.num_vertices();
    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            // Si no hay camino i→k, saltamos
            if (D[i][k] == std::numeric_limits<float>::infinity())
                continue;
            for (size_t j = 0; j < n; ++j) {
                float via_k = D[i][k] + D[k][j];
                if (via_k < D[i][j]) {
                    D[i][j] = via_k;
                    I[i][j] = static_cast<int>(k);
                }
            }
        }
    }

    //
}

std::list<size_t>
floyd_path(size_t src, size_t dst, IMatrix const &I)
{
    // Prec: distance (u,v) < inf
    std::list<size_t> path;

    // TODO: Find the path.
    // Hint: Think first. Is it necessary to build a binary tree? or it
    // is enough to do an first-depth search using an iterative approach with
    // a stack of pairs (u,v).

    if( I[src][dst] < 0 ) {
        path.push_back(src);
        if( src != dst ) {
            path.push_back(dst);
        }
        return path;
    }

    // Caso recursivo: tenemos un k intermedio
    size_t k = I[src][dst];

    std::list<size_t> first = floyd_path(src, k, I);

    std::list<size_t> second = floyd_path(k, dst, I);

    first.pop_back();

    first.insert(first.end(), second.begin(), second.end());

    path = first;

    //
    return path;
}
