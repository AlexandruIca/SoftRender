///
/// \file
///
/// \brief A header that contains documentation only.
///

///
/// \page download_and_setup Download & Setup
///
/// To get started using the library you first have to download it for your
/// platform(
/// [MacOS](https://github.com/AlexandruIca/SoftRender/releases/download/nightly/SoftRender-0.2-Darwin.tar.gz
/// ),
/// [Windows](https://github.com/AlexandruIca/SoftRender/releases/download/nightly/SoftRender-0.2-win64.zip
/// ), or
/// [Linux](https://github.com/AlexandruIca/SoftRender/releases/download/nightly/SoftRender-0.2-Linux.tar.gz
/// )).
/// After that you have to add the \p include folder to your compiler's path and
/// the \p lib folder to your compiler's link path and link with either the
/// static or shared version, whatever you choose. If you use CMake:
/// ```cmake
/// add_executable( my_exec ${YOUR_SOURCES} )
/// target_include_directories( my_exec PRIVATE ${PATH_TO_SOFTRENDER}/include/ )
/// link_directories( ${PATH_TO_SOFTRENDER}/lib/ )
/// target_link_libraries( my_exec PRIVATE SoftRender ) # Or SoftRender-shared
/// ```
///
