///
/// \file
///

#include "softrender.hpp"

#include "SDL.h"

#include <cstdlib>
#include <iostream>
#include <string>

///
/// \brief Wrapper around **SDL_GetError**.
///
void sdl_error(std::string const& t_error)
{
    std::cout << "Error: " << t_error << "\n\t";
    std::cout << "SDL: " << SDL_GetError() << std::endl << std::endl;
}

int test()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdl_error("sdl could not be initialized");
        return EXIT_FAILURE;
    }

    std::cout << "It worked" << std::endl;

    SDL_Quit();

    return EXIT_SUCCESS;
}

