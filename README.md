# Simple Snake (C++)

A personal C++ learning project: rebuilding a simple Snake game from scratch with a more thoughtful design, modern tooling, and a deeper understanding of software engineering.

This project is inspired by one of the first games I ever managed to compile years ago. Back then, it was mostly about trial, error, and excitement. This time, the goal is different: **to learn deeply and build deliberately**.

---

## 🎯 Project Goals

This repository exists primarily as a **learning and exploration space**, not a finished product.

Some of the goals behind this project:

* Revisit **C++** with a more mature mindset
* Practice **software design**, not just "making it work"
* Explore **game architecture fundamentals**
* Apply lessons learned from years of working mostly in **web development**
* Embrace modern development workflows, including **AI-assisted tooling**

---

## 🧠 Design Approach

Compared to the original version from years ago, this implementation focuses on clearer structure and separation of concerns:

* Clear separation between **game loop**, **tick/update**, and **rendering**
* Event-driven interactions
* Explicit handling of **ownership, lifetime, and polymorphism** in C++
* Pluggable rendering layer

  * Terminal-based (TUI)
  * GUI using **Raylib**
* Rule-based architecture is planned and currently a high-priority TODO

The aim is not complexity for its own sake, but **intentional design decisions** that can be reasoned about, changed, and improved over time.

---

## 🚧 Project Status

This project is **ongoing**.

Features, structure, and architecture are expected to evolve as I continue exploring better approaches and deeper C++ concepts. Breaking changes are possible, and experimentation is encouraged.

---

## 📋 Prerequisites

Before building the project, make sure you have the following installed:

* **C++ compiler** with C++20 support or newer

  * GCC / Clang recommended
* **CMake** ≥ 3.16
* **Raylib** (for GUI rendering)
* A Unix-like environment (Linux or macOS recommended)

> The project is developed primarily on Linux. Other platforms may work but are not actively tested yet.

---

## 📦 Dependencies

* **Raylib**
  Used for the GUI renderer implementation.

This project already includes CMake configurations to fetch and link Raylib during the build process, no need for manual installation.

Alternatively, you can install Raylib via your system's package manager and adjust the CMake configuration accordingly.

---

## ⚙️ Setup

Clone the repository:

```bash
git clone https://github.com/Xrayya/simple-snake-cpp.git
cd simple-snake-cpp
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

This project uses an **out-of-source build** to keep the repository clean.

---

## 🧩 Building the Project

### Debug Build

Recommended for development and exploration:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### Release Build

Recommended for running the game with optimizations enabled:

```bash
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-release
```

The resulting binary will be generated inside the `build/` and/or `build-release/` directory.

---

## ▶️ Running

After building, run the executable from the build directory:

```bash
./snake
```

(Exact binary name may vary depending on configuration.)

---

## 📝 Notes

* The TUI and GUI renderers are designed to be **swappable**
* Architecture and APIs are expected to evolve
* This project prioritizes **clarity and learning** over backward compatibility
