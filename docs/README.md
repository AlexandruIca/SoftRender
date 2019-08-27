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
