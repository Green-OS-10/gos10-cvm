# C Virtual Machine

## Introduction

The C Virtual Machine (CVM) is intended for writing and testing Green OS 10
applications before they are imported into Scratch sprites.

## Get started

### Build

Run `make` from the project root directory to build the `cvm` executable.

### Usage

Run `cvm <filename>.c` from the `bin` directory to build and run a C file.

## Project structure

Source files are located in the `src` directory. The entry point is at `main.c`.
Each C file documents its high level procedures.
