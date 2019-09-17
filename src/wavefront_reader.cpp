#include <iostream>
#include <sstream>
#include <utility>

#include "wavefront_reader.hpp"

namespace softrender {

auto wavefront_model_t::read_model(std::istream& t_file) -> void
{
    std::string line{};

    while(t_file) {
        std::getline(t_file, line);
        std::istringstream iss{ line };
        char ignore{ '\0' };

        switch(line[0]) {
        case 'v': {
            if(line[1] != ' ') {
                break;
            }

            iss >> ignore;

            vec3f vec;

            for(auto const i : { 0, 1, 2 }) {
                iss >> vec[i];
            }

            m_verts.push_back(vec);
            break;
        }
        case 'f': {
            if(line[1] != ' ') {
                break;
            }

            std::vector<int> faces;
            int ignore_int{ 0 };
            int index{ 0 };

            iss >> ignore;

            while(iss >> index >> ignore >> ignore_int >> ignore >>
                  ignore_int) {
                faces.push_back(index - 1);
            }

            m_faces.push_back(std::move(faces));
            break;
        }
        default: {
            break;
        }
        }
    }
}

wavefront_model_t::wavefront_model_t(std::string const t_file_path)
{
    std::ifstream in{ t_file_path };

    if(!in.good()) {
        std::cout << "Error opening wavefront model! Path given: ";
        std::cout << t_file_path << std::endl;
        return;
    }

    this->read_model(in);
}

auto wavefront_model_t::nverts() const noexcept -> int
{
    return static_cast<int>(m_verts.size());
}

auto wavefront_model_t::nfaces() const noexcept -> int
{
    return static_cast<int>(m_faces.size());
}

auto wavefront_model_t::vert(int const t_index) noexcept -> vec3f
{
    return m_verts[t_index];
}

auto wavefront_model_t::face(int const t_index) -> std::vector<int>
{
    return m_faces[t_index];
}

} // namespace softrender
