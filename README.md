# generate-markdown-file

Code to export specified files in a folder to markdown

## generate-markdown-file-c

> [!IMPORTANT]
> This project depends on the [tomlc99](https://github.com/cktan/tomlc99.git) library.

### Usage

#### Build with Make

```bash
cd generate-markdown-file-c
make
```

#### Build with CMake

> [!NOTE]
> If you use the cmake command, install it.<br/>
> - [https://cmake.org/download/#latest](https://cmake.org/download/#latest)<br/>
> - [https://formulae.brew.sh/formula/cmake](https://formulae.brew.sh/formula/cmake)

```bash
mkdir build # Not necessary if build already exists
cd build
cmake ..
make install # An executable file(generate-markdown-file) is generated in generate-markdown-file-c.
```

#### Execution

> [!NOTE]
> - Specify the directory to write to by `<directory>`.
> - Specify the Markdown file to be output with `<output_file>`.
> - Specify the file to be processed in [config.toml](./generate-markdown-file-c/config.toml).

```bash
./generate_markdown_file -h
Usage: ./generate_markdown_file <directory> <output_file>
```

## generate-markdown-file-cpp

> [!IMPORTANT]
> This project depends on the [toml11](https://github.com/ToruNiina/toml11.git) library.

### Usage

#### Build with Make

```bash
cd generate-markdown-file-cpp
make
```

#### Build with CMake

> [!NOTE]
> If you use the cmake command, install it.<br/>
> - [https://cmake.org/download/#latest](https://cmake.org/download/#latest)<br/>
> - [https://formulae.brew.sh/formula/cmake](https://formulae.brew.sh/formula/cmake)

```bash
mkdir build # Not necessary if build already exists
cd build
cmake ..
make install # An executable file(generate-markdown-file) is generated in generate-markdown-file-cpp.
```

#### Execution

> [!NOTE]
> - Specify the directory to write to by `<directory>`.
> - Specify the Markdown file to be output with `<output_file>`.
> - Specify the file to be processed in [config.toml](./generate-markdown-file-cpp/config.toml).

```bash
./generate_markdown_file -h
Usage: ./generate_markdown_file <directory> <output_file>
```
