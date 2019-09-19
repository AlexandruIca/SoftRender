#ifndef KEYS_HPP
#define KEYS_HPP
#pragma once

namespace softrender {

///
/// \brief Contains key codes that map directly to the underlying \p SDLK_
///        equivalents.
///
/// The reason this is a struct that contains only static variables instead
/// of being an enum is to get rid of the \p SDL.h include that would be
/// necessary.
///
struct key
{
    static int const vk_unknown;
    static int const vk_return;
    static int const vk_escape;
    static int const vk_backspace;
    static int const vk_tab;
    static int const vk_space;
    static int const vk_exclaim;
    static int const vk_quotedbl;
    static int const vk_hash;
    static int const vk_percent;
    static int const vk_dollar;
    static int const vk_ampersand;
    static int const vk_quote;
    static int const vk_leftparen;
    static int const vk_rightparen;
    static int const vk_asterisk;
    static int const vk_plus;
    static int const vk_comma;
    static int const vk_minus;
    static int const vk_period;
    static int const vk_slash;
    static int const vk_0;
    static int const vk_1;
    static int const vk_2;
    static int const vk_3;
    static int const vk_4;
    static int const vk_5;
    static int const vk_6;
    static int const vk_7;
    static int const vk_8;
    static int const vk_9;
    static int const vk_colon;
    static int const vk_semicolon;
    static int const vk_less;
    static int const vk_equals;
    static int const vk_greater;
    static int const vk_question;
    static int const vk_at;
    static int const vk_leftbracket;
    static int const vk_backslash;
    static int const vk_rightbracket;
    static int const vk_caret;
    static int const vk_underscore;
    static int const vk_backquote;
    static int const vk_a;
    static int const vk_b;
    static int const vk_c;
    static int const vk_d;
    static int const vk_e;
    static int const vk_f;
    static int const vk_g;
    static int const vk_h;
    static int const vk_i;
    static int const vk_j;
    static int const vk_k;
    static int const vk_l;
    static int const vk_m;
    static int const vk_n;
    static int const vk_o;
    static int const vk_p;
    static int const vk_q;
    static int const vk_r;
    static int const vk_s;
    static int const vk_t;
    static int const vk_u;
    static int const vk_v;
    static int const vk_w;
    static int const vk_x;
    static int const vk_y;
    static int const vk_z;
    static int const vk_capslock;
    static int const vk_f1;
    static int const vk_f2;
    static int const vk_f3;
    static int const vk_f4;
    static int const vk_f5;
    static int const vk_f6;
    static int const vk_f7;
    static int const vk_f8;
    static int const vk_f9;
    static int const vk_f10;
    static int const vk_f11;
    static int const vk_f12;
    static int const vk_printscreen;
    static int const vk_scrolllock;
    static int const vk_pause;
    static int const vk_insert;
    static int const vk_home;
    static int const vk_pageup;
    static int const vk_delete;
    static int const vk_end;
    static int const vk_pagedown;
    static int const vk_right;
    static int const vk_left;
    static int const vk_down;
    static int const vk_up;
};

} // namespace softrender

#endif // !KEYS_HPP
