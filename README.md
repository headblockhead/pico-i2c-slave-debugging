# Pico-i2c-slave-debugging

[![Nix Flake](https://img.shields.io/badge/NIX%20FLAKE-5277C3.svg?logo=NixOS&logoColor=white)](https://nixos.org) [![xc compatible](https://xcfile.dev/badge.svg)](https://xcfile.dev)

Related to issues found during the production of the [Slab keyboard project](https://github.com/headblockhead/slab).

## Building

This project uses [Nix](https://nixos.org), run `nix develop` for a development environmnt, `nix build` to build the firmware and use `nix flake check` to check tests are passing.

## Tasks

> [!IMPORTANT]
> You must be in the `nix develop` shell for these tasks to work!

### upload-first
Directory: ./build
Requires: build

Builds and uploads the 1st firmware to the 1st Pico.

```bash
export PICO_DIR=`findmnt -S LABEL=RPI-RP2 -o TARGET -fn`
cp ./first-board/first-board.uf2 $PICO_DIR
```

### upload-second
Directory: ./build
Requires: build

Builds and uploads the 2nd firmware to the 2nd Pico.

```bash
export PICO_DIR=`findmnt -S LABEL=RPI-RP2 -o TARGET -fn`
cp ./second-board/second-board.uf2 $PICO_DIR
```

### build
Directory: ./build

Builds the keyboard firmware with development outputs.

```bash
cmake -DCMAKE_BUILD_TYPE=Debug .. 
cmake --build . -j 16
cp compile_commands.json ../ # Copies the autocomplete information for ccls.
```

### clean

Deletes the contents of the build directory.

```bash
rm -rf ./build
mkdir build
```
