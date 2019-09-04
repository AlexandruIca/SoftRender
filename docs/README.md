# Quickstart

This creates a blank screen and exits either when you close the window or when
you press ESCAPE:
```cpp
#include "softrender.hpp"

int main()
{
    softrender::window_t window{ 1280, 720 };

    while(!window.closed()) {
        window.draw();
    }
}
```

To draw a red point in the middle of the screen:
```cpp
#include "softrender.hpp"

int main()
{
    softrender::window_t window{ 1280, 720 };

    while(!window.closed()) {
        window.draw_point(
            softrender::point_t{
                /*x=*/window.width() / 2, /*y=*/window.height() / 2
            },
            softrender::pixel_t{ 255, 0, 0 }
        );
        window.draw();
    }
}
```

To draw a line:
```cpp
#include "softrender.hpp"

int main()
{
    softrender::window_t window{ 1280, 720 };

    while(!window.closed()) {
        window.draw_line(
            softrender::point_t{ 320, 100 },
            softrender::point_t{ 40, 50 },
            softrender::pixel_t{ 255, 255, 255 }
        );
        window.draw();
    }
}
```

You can also not specify a color for drawing if you don't want to, the default
will be white:
```cpp
#include "softrender.hpp"

int main()
{
    softrender::window_t window{ 1280, 720 };

    while(!window.closed()) {
        window.draw_line(
            softrender::point_t{ 320, 100 },
            softrender::point_t{ 40, 50 }
        );
        window.draw();
    }
}
```

You can also use a prederined color(see more in the 'namespace' documentation):
```cpp
#include "softrender.hpp"

int main()
{
    softrender::window_t windnow{ 1280, 720 };

    while(!window.closed()) {
        window.draw_point(softrender::point_t{ 20, 30 }, softrender::yellow);
        window.draw();
    }
}
```
