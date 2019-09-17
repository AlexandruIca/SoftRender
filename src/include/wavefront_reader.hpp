#ifndef WAVEFRONT_READER_HPP
#define WAVEFRONT_READER_HPP
#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "vec.hpp"

namespace softrender {

///
/// \brief Helper for reading wavefront.obj models.
///
class wavefront_model_t
{
private:
    std::vector<vec3f> m_verts;
    std::vector<std::vector<int>> m_faces;

    auto read_model(std::istream& t_file) -> void;

public:
    wavefront_model_t() = default;
    ///
    /// \param t_file_path A path to the '.obj' model. If the file is not found
    ///                    or the file is not valid a message will be shown on
    ///                    the screen.
    ///
    wavefront_model_t(std::string const t_file_path);
    wavefront_model_t(wavefront_model_t const&) = default;
    wavefront_model_t(wavefront_model_t&&) = default;
    ~wavefront_model_t() noexcept = default;

    ///
    /// \returns Number of vertices in the specified .obj file.
    ///
    auto nverts() const noexcept -> int;
    ///
    /// \returns Number of faces.
    ///
    auto nfaces() const noexcept -> int;
    ///
    /// \returns The vertex at index \p t_index.
    ///
    auto vert(int const t_index) noexcept -> vec3f;
    ///
    /// \returns The indexes of the vertices that make the face at index \p
    ///          t_index.
    ///
    auto face(int const t_index) -> std::vector<int>;
};

} // namespace softrender

#endif // !WAVEFRONT_READER_HPP
