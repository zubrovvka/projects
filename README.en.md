<div align="center">

# University C++ Projects

**Lab assignments, coursework and internship project · ETU "LETI", Saint Petersburg · 2022–2023**

[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)](https://en.cppreference.com/w/cpp/17)
[![Qt 6](https://img.shields.io/badge/Qt-6-41CD52?logo=qt&logoColor=white)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-3.16%2B-064F8C?logo=cmake&logoColor=white)](https://cmake.org/)
[![CI](https://github.com/zubrovvka/projects/actions/workflows/ci.yml/badge.svg)](https://github.com/zubrovvka/projects/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

[Русская версия](README.md)

<img src="palette-extractor/docs/images/screenshot.png" alt="Palette Extractor — Qt app that extracts an image's colour palette" width="720">

<sub>Palette Extractor — the Qt application from the internship project</sub>

</div>

---

## Contents

| # | Project | Topic | Highlights |
|:-:|---------|-------|------------|
| 1 | [**Shunting-yard**](algorithms-and-data-structures/01-shunting-yard/) | Infix → Reverse Polish Notation | Hand-written `List<T>` (stack) and `dynamic_array<T>` templates, operator precedence, `sin`/`cos`, parentheses |
| 2 | [**TimSort & QuickSort**](algorithms-and-data-structures/02-timsort-quicksort/) | Sorting algorithms | TimSort from scratch (minrun → insertion sort → merge), Hoare quicksort, timing |
| 3 | [**AVL tree**](algorithms-and-data-structures/03-avl-tree/) | Self-balancing BST | Insert, delete, all four rotations, pre/in/post-order and BFS traversals, ASCII visualisation |
| 4 | [**Graphs: DFS, BFS, Kruskal**](algorithms-and-data-structures/coursework-graph-mst/) · *coursework* | Graph algorithms | Adjacency matrix parser, traversals, minimum spanning tree with a disjoint-set union |
| 5 | [**Palette Extractor**](palette-extractor/) · *internship* | Image processing, GUI | Qt 6 Widgets app: finds the 6 dominant colours of a PNG/JPG/BMP using perceptual colour distance, exports the palette |

Every project folder has its own `README.md` with the task statement, algorithm notes and sample runs (in Russian).

## Quick start

Console projects (1–4) build with a single command on Linux, macOS and Windows:

```bash
git clone https://github.com/zubrovvka/projects.git
cd projects
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Binaries land in `build/algorithms-and-data-structures/<project>/`:

```bash
./build/algorithms-and-data-structures/01-shunting-yard/shunting-yard
./build/algorithms-and-data-structures/02-timsort-quicksort/sorting
./build/algorithms-and-data-structures/03-avl-tree/avl-tree
(cd build/algorithms-and-data-structures/coursework-graph-mst && ./graph-mst)
```

The Qt application needs Qt 6 and is enabled with a flag:

```bash
cmake -S . -B build -DBUILD_PALETTE_EXTRACTOR=ON -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x/gcc_64
cmake --build build
```

A prebuilt Windows x64 package of Palette Extractor is available in [`palette-extractor/dist/`](palette-extractor/dist/).

## Repository layout

```
.
├── algorithms-and-data-structures/     # "Algorithms and Data Structures" course
│   ├── 01-shunting-yard/               # lab 1 — Reverse Polish Notation
│   ├── 02-timsort-quicksort/           # lab 2 — sorting
│   ├── 03-avl-tree/                    # lab 3 — AVL tree
│   └── coursework-graph-mst/           # coursework — graphs (DFS/BFS/Kruskal)
│       ├── src/
│       └── examples/                   # sample input files
├── palette-extractor/                  # internship — Qt application
│   ├── src/                            # sources (CMake + qmake)
│   ├── docs/                           # internship report, screenshots
│   ├── examples/                       # sample image
│   └── dist/                           # prebuilt Windows package
├── CMakeLists.txt                      # root build
├── .clang-format                       # unified code style
└── .github/workflows/ci.yml            # Linux + Windows builds
```

## Toolchain

- **Language:** C++17
- **Build:** CMake ≥ 3.16 (a qmake `.pro` file is kept for the Qt project as well)
- **GUI:** Qt 6 Widgets
- **Style:** `clang-format` (config in the root), `.editorconfig`
- **CI:** GitHub Actions — GCC on Ubuntu and MSVC on Windows

## Authors

- **[zubrovvka](https://github.com/zubrovvka)** — lab assignments and coursework
- The internship project was a team effort: **V. Zyryanov, V. Kolpachev, S. Moskvin** (group 1374), supervised by Yu. Prokopovich

## License

[MIT](LICENSE)
