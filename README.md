# EN61

A graphics/game engine written in c++20.

# Compilation

* Download sources:
  ```bash
  git clone git@github.com:en61/en61.git
  cd en61/
  ```

* Compile library:
  ```bash
  mkdir build && cd build
  cmake .. && make # for static library
  cmake -DDYNAMIC=ON .. && make # for dynamic library
  ```

* Compile sandbox:
  ```bash
  cd sandbox/
  mkdir build && cd build
  cmake .. && make
  ./sandbox
  ```

# Used libraries
* [**glfw3**](https://github.com/glfw/glfw)
* [**glad**](https://github.com/Dav1dde/glad)
* [**glm**](https://github.com/g-truc/glm)
* [**stb**](https://github.com/nothings/stb)
