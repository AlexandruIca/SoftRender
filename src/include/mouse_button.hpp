#ifndef MOUSE_BUTTON_HPP
#define MOUSE_BUTTON_HPP
#pragma once

///
/// \file
///

namespace softrender {

///
/// \brief Buttons for which presses/releases can be handled.
///
/// It's a struct containing only static members for the same reason \ref key
/// is.
///
struct mouse_button
{
    static int const left;
    static int const right;
    static int const middle;
};

} // namespace softrender

#endif // !MOUSE_BUTTON_HPP
