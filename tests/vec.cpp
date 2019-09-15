#include <utility>

#include "test_helpers/test_helpers.hpp"
#include "vec.hpp"

TEST("vec2i")
{
    softrender::vec2i d{};

    ASSERT(d.x == 0);
    ASSERT(d.y == 0);

    softrender::vec2i v{ 4, 3 };

    ASSERT(v[0] == 4);
    ASSERT(v[1] == 3);
    ASSERT_THROWS(auto res = v[2] + v[3] + v[-1]);
    ASSERT(v.x == 4);
    ASSERT(v.y == 3);
    ASSERT(v == softrender::vec2i{ 4, 3 });
    ASSERT(v != softrender::vec2i{ 3, 4 });
    // ASSERT(static_cast<int>(v.norm()) == 5);

    softrender::vec2i v2{ v };

    ASSERT(v2 == v);

    softrender::vec2i v3{ std::move(v) };

    ASSERT(v3 == v2);
    ASSERT(v3 * 2 == v3 + v2);
    ASSERT(v3 * 2.f == softrender::vec2i{ 8, 6 });
    ASSERT(v3 * 2.0 == softrender::vec2i{ 8, 6 });
    ASSERT(v3 - v2 == softrender::vec2i{ 0, 0 });
}

TEST("vec2f")
{
    softrender::vec2f v{ 2.3f, 1.5f };
    ASSERT(static_cast<int>(v[0] + v[1]) == 3);
    ASSERT(static_cast<int>(v.x + v.y) == 3);

    softrender::vec2f v2{ 17.7f, 18.5f };

    auto tmp = v2 + v;
    ASSERT(static_cast<int>(tmp.x) == 20);
    ASSERT(static_cast<int>(tmp.y) == 20);

    auto tmp2 = v2 - v;
    ASSERT(static_cast<int>(tmp2.x) == 15);
    ASSERT(static_cast<int>(tmp2.y) == 17);
}

TEST("vec2d")
{
    softrender::vec2d v{ 2.3, 1.5 };
    ASSERT(static_cast<int>(v[0] + v[1]) == 3);
    ASSERT(static_cast<int>(v.x + v.y) == 3);

    softrender::vec2d v2{ 17.7, 18.5 };

    auto tmp = v2 + v;
    ASSERT(static_cast<int>(tmp.x) == 20);
    ASSERT(static_cast<int>(tmp.y) == 20);

    auto tmp2 = v2 - v;
    ASSERT(static_cast<int>(tmp2.x) == 15);
    ASSERT(static_cast<int>(tmp2.y) == 17);
}

TEST("vec3i")
{
    softrender::vec3i d{};

    ASSERT(d.x == 0);
    ASSERT(d.y == 0);
    ASSERT(d.z == 0);

    softrender::vec3i v{ 1, 2, 3 };

    ASSERT(v.x == 1);
    ASSERT(v.y == 2);
    ASSERT(v.z == 3);
    ASSERT(v[0] == v.x);
    ASSERT(v[1] == v.y);
    ASSERT(v[2] == v.z);
    ASSERT_THROWS(auto res = v[3] + v[4] + v[-2]);
    ASSERT(v.x + v.y + v.z == 6);
    ASSERT(v == softrender::vec3i{ 1, 2, 3 });
    ASSERT(v != softrender::vec3i{ 3, 2, 1 });
    ASSERT(v + softrender::vec3i{ 4, 5, 6 } == softrender::vec3i{ 5, 7, 9 });

    softrender::vec3i v2{};

    v2 = v;

    ASSERT(v2 == v);

    softrender::vec3i v3{};

    v3 = std::move(v);

    ASSERT(v3 == v2);
    auto tmp = v3 * 2.f;
    ASSERT(static_cast<int>(tmp.x) == 2);
    ASSERT(static_cast<int>(tmp.y) == 4);
    ASSERT(static_cast<int>(tmp.z) == 6);
    ASSERT(v3 - v2 == softrender::vec3i{ 0, 0, 0 });
    ASSERT(v3 * v2 == 14);
    ASSERT(static_cast<int>(softrender::vec3i{ 3, 4, 0 }.norm()) == 5);
    ASSERT(softrender::vec3i{ 1, 0, 0 }.normalize() ==
           softrender::vec3i{ 1, 0, 0 });
}

TEST("vec3f")
{
    softrender::vec3f v{ 1.f, 2.f, 3.f };

    ASSERT(static_cast<int>(v.x + v.y + v.z) == 6);
    ASSERT(static_cast<int>(v[0] + v[1] + v[2]) == 6);
}

TEST("vec3f")
{
    softrender::vec3f v{ 1., 2., 3. };

    ASSERT(static_cast<int>(v.x + v.y + v.z) == 6);
    ASSERT(static_cast<int>(v[0] + v[1] + v[2]) == 6);
}
