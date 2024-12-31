# C++ Scalable Vector Graphics utilities library  .version 1.0
## File system explain
### Sources files-"src/"
- `svglib.hpp/svglib.cpp`:
  Includs all svg utilities provided, tested, and useable.
- `main.cpp/view.hpp/view.cpp`:
  A simple sfml program for displaying utilty results for testing purposes.
- `svgtran.hpp/svgtran.cpp`:
  Utilities for svg's transform attribute. **Note: not implemented**
### SVG files-"svgs/"
A list of simple svg file collected that this library supports and can work with for testing purposes.
### Others
- `make.bash`:
  Viewer program building command script for bash.
  
  To use, run `bash make.bash` in terminal in the root of the project folder.
- `svgviewer`:
  Linux executable for viewer program.

  To use, run `./svgviewer <path to your svg file>`, then expect an gui.
## How to use/build
**Note: all following instructions are designed for linux system, if you are using other systems, please only use them as an reference, as the process might be simular**
### Viewer
1. Make sure you have `sfml`(gui support), `tinyxml2`(xml info extract) and a proper c++ compiler installed.
2. To build, run `bash make.bash` in terminal in the root of the project folder.
   
   **Note: designed for gcc compiler only, please write your own if you are using otherwise**
3. Expect an executable be produced in the root of project folder named `svgviewer`

   To use, run `./svgviewer <path to your svg file>`, then expect an gui.
   
