/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <pattern.hpp>

Pattern::Pattern()
{
    // TODO

    //
    assert(dim() == 0);
    assert(class_label() == -1);
}

Pattern::Pattern(float *values, const size_t size, const int cl)
{
    assert(size > 0);
    // TODO

    //
    assert(dim() == size);
    assert(class_label() == cl);
}

Pattern::~Pattern()
{
    // TODO

    //
}

size_t Pattern::dim() const
{
    size_t d = 0;
    // TODO

    //
    return d;
}

int Pattern::class_label() const
{
    int cl = -1;
    // TODO

    //
    return cl;
}

const std::valarray<float> &
Pattern::values() const
{
    // TODO
    return std::valarray<float>(); // FIXME
    //
}

void Pattern::set_class_label(const int new_label)
{
    // TODO

    //
    assert(class_label() == new_label);
}

std::valarray<float> &
Pattern::values()
{
    // TODO
    std::valarray<float> fixme;
    return fixme;
    //
}

void Pattern::reset(float *values, const size_t size, const int cl)
{
    assert(size >= 0);
    // TODO

    //
    assert(dim() == size);
    assert(class_label() == cl);
}

std::ostream &operator<<(std::ostream &output, const Pattern &p)
{
    // TODO
    // Remember: format "[ class_label [ v0 v1 ... vn-1 ] ]"

    //
    return output;
}

std::istream &operator>>(std::istream &in, Pattern &p) noexcept(false)
{
    // TODO
    // Remember: input format is "[ class_label [ v_0 v_1 ... v_size-1 ] ]"

    //
    return in;
}

float distance_L2(const Pattern &a, const Pattern &b)
{
    assert(a.dim() == b.dim());
    float dist = 0.0;
    // TODO

    //
    assert(dist >= 0.0);
    return dist;
}

float distance_L1(const Pattern &a, const Pattern &b)
{
    assert(a.dim() == b.dim());
    float dist = 0.0;
    // TODO

    //
    assert(dist >= 0.0);
    return dist;
}

std::istream &
load_dataset(std::istream &input,
             std::vector<Pattern> &dts) noexcept(false)
{
    // TODO
    // Remember: input format is
    // "<size_t num_patterns> <size_t pattern_dimensions>
    // <p_0>
    // <p_1>
    // ...
    // <p_num_patterns-1>
    // "

    //
    return input;
}
