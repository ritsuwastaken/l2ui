# 🛠️ L2UI · ![build status](https://github.com/ritsuwastaken/l2ui/actions/workflows/build.yml/badge.svg)

## Description
`l2ui.dll` is a simple lib, useful for injecting multiple custom DLLs into the L2 process.

## Download
Get the latest version from [Releases](https://github.com/ritsuwastaken/l2ui/releases).

## Usage
1. Place `l2ui.dll` into the `system` folder.
2. Create a `libraries` folder within the `system` folder.
3. Place the required libraries into the `libraries` folder.
4. Run L2.

## Build
```shell
# Configure the project
cmake . -B 'build' -G 'Visual Studio 17 2022' -A Win32
# Build the project
cmake --build 'build' --config Release
```

`l2ui.dll` will be in `./build/Release`
