#ifndef SOFTRENDER_VEC_HPP
#define SOFTRENDER_VEC_HPP
#pragma once

#include <cmath>

namespace softrender {

///
/// \brief Vector with coordinates \p x and \p y.
///
template<typename T>
struct vec2
{
private:
    static constexpr auto m_default_value = static_cast<unsigned char>(0);

public:
    T x{ m_default_value };
    T y{ m_default_value };

public:
    vec2() noexcept = default;
    vec2(T const t_x, T const t_y) noexcept
        : x{ t_x }
        , y{ t_y }
    {
    }
    vec2(vec2 const&) noexcept = default;
    vec2(vec2&&) noexcept = default;
    ~vec2() noexcept = default;

    auto operator=(vec2 const&) noexcept -> vec2& = default;
    auto operator=(vec2&&) noexcept -> vec2& = default;

    auto operator==(vec2 const& t_other) noexcept -> bool
    {
        return x == t_other.x && y == t_other.y;
    }
    auto operator!=(vec2 const& t_other) noexcept -> bool
    {
        return !this->operator==(t_other);
    }

    auto operator[](int const t_index) -> T&
    {
        switch(t_index) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        default:
#ifdef SOFTRENDER_DEBUG
            throw "vec2 index out of range.";
#endif
            return x;
        }
    }
    auto operator[](int const t_index) const -> T const&
    {
        switch(t_index) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        default:
#ifdef SOFTRENDER_DEBUG
            throw "vec2 index out of range.";
#endif
            return x;
        }
    }

    auto operator+(vec2 const& t_other) const noexcept -> vec2
    {
        return vec2{ x + t_other.x, y + t_other.y };
    }
    auto operator-(vec2 const& t_other) const noexcept -> vec2
    {
        return vec2{ x - t_other.x, y - t_other.y };
    }

    auto operator*(int const t_factor) noexcept -> vec2
    {
        return vec2{ static_cast<T>(x * t_factor),
                     static_cast<T>(y * t_factor) };
    }
    auto operator*(float const t_factor) noexcept -> vec2
    {
        return vec2{ static_cast<T>(x * t_factor),
                     static_cast<T>(y * t_factor) };
    }
    auto operator*(double const t_factor) noexcept -> vec2
    {
        return vec2{ static_cast<T>(x * t_factor),
                     static_cast<T>(y * t_factor) };
    }
};

///
/// \brief Vector with coordinates \p x, \p y and \p z.
///
template<typename T>
struct vec3
{
private:
    static constexpr auto m_default_value = static_cast<unsigned char>(0);

public:
    T x{ m_default_value };
    T y{ m_default_value };
    T z{ m_default_value };

public:
    vec3() noexcept = default;
    vec3(T const t_x, T const t_y, T const t_z) noexcept
        : x{ t_x }
        , y{ t_y }
        , z{ t_z }
    {
    }
    vec3(vec3 const&) noexcept = default;
    vec3(vec3&&) noexcept = default;
    ~vec3() noexcept = default;

    auto operator=(vec3 const&) noexcept -> vec3& = default;
    auto operator=(vec3&&) noexcept -> vec3& = default;

    auto operator==(vec3 const& t_other) noexcept -> bool
    {
        return x == t_other.x && y == t_other.y && z == t_other.z;
    }
    auto operator!=(vec3 const& t_other) noexcept -> bool
    {
        return !this->operator==(t_other);
    }

    auto operator[](int const t_index) -> T&
    {
        switch(t_index) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        default:
#ifdef SOFTRENDER_DEBUG
            throw "vec3 index out of range.";
#else
            return x;
#endif
        }
    }
    auto operator[](int const t_index) const -> T const&
    {
        switch(t_index) {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        default:
#ifdef SOFTRENDER_DEBUG
            throw "vec3 index out of range.";
#endif
            return x;
        }
    }

    auto operator+(vec3 const& t_other) const noexcept -> vec3
    {
        return vec3{ x + t_other.x, y + t_other.y, z + t_other.z };
    }
    auto operator-(vec3 const& t_other) const noexcept -> vec3
    {
        return vec3{ x - t_other.x, y - t_other.y, z - t_other.z };
    }

    auto operator*(float const t_factor) const noexcept -> vec3
    {
        return this->operator*(static_cast<double>(t_factor));
    }
    auto operator*(double const t_factor) const noexcept -> vec3
    {
        return vec3{ static_cast<T>(x * t_factor),
                     static_cast<T>(y * t_factor),
                     static_cast<T>(z * t_factor) };
    }
    auto operator*(vec3 const& t_other) const noexcept -> T
    {
        return x * t_other.x + y * t_other.y + z * t_other.z;
    }

    ///
    /// \returns \f$\sqrt{x^2 + y^2 + z^2}\f$
    ///
    [[nodiscard]] auto norm() const noexcept -> double
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    ///
    /// Multiplies the vector with \f$\frac{1}{\sqrt{x^2 + y^2 + z^2}}\f$ by
    /// default.
    ///
    /// \param t_l Specify it to multiply by \f$\frac{t\_l}{\sqrt{x^2 + y^2 +
    ///            z^2}}\f$
    ///
    auto normalize(T const t_l = 1) noexcept -> vec3&
    {
        *this = (*this) * (t_l / this->norm());
        return *this;
    }
};

using vec2i = vec2<int>;
using vec2f = vec2<float>;
using vec2d = vec2<double>;

using vec3i = vec3<int>;
using vec3f = vec3<float>;
using vec3d = vec3<double>;

/**
 * \f[
 * A \times B =
 * \begin{vmatrix}
 *     x_A & y_A & z_A \\
 *     x_B & y_B & z_B \\
 *     i   & j   & k
 * \end{vmatrix} =
 * (y_A z_B - y_B z_A)\overrightarrow{i} -
 * (z_B x_A - x_B z_A)\overrightarrow{j} +
 * (x_A y_B - y_A x_B)\overrightarrow{k} =
 * V(
 *  y_A z_B - y_B z_A,
 *  x_B z_A - z_B x_A,
 *  x_A y_B - y_A x_B
 * )
 * \f]
 *
 * \returns The cross product of \p t_a and \p t_b.
 */
template<typename T>
[[nodiscard]] auto cross(vec3<T> const t_a, vec3<T> const t_b) noexcept
    -> vec3<T>
{
    return vec3<T>{ t_a.y * t_b.z - t_b.y * t_a.z,
                    t_b.x * t_a.z - t_b.z * t_a.x,
                    t_a.x * t_b.y - t_a.y * t_b.x };
}

} // namespace softrender

#endif
