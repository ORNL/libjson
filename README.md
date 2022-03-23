# libjson

Fast, easy to use C++ JSON library

*Note: Use of this project is not recommended at this time as it is not complete - lacking full unit testing, packaging/installation, and documentation.*

## Introduction

This C++ JSON library was created as an alternative to popular C++ JSON libraries (i.e. RapidJSON, nlohmann/JSON, etc.) with a goals of high performance parsing and data access, standard error handling, and ease of use. Libjson was created as part of the ORNL DataFed project (https://github.com/ORNL/DataFed).

Fast floating point parsing is implemented with Florian Loitsch's Grisu-algorithm and the code
was copy-pasted into this library (this will be changed to a dependency in a future version).

## Build

Libjson is built with Bazel (https://bazel.build) and can be built from the root directory as follows:

bazel build ...

### Unit Tests

Unit testing is built and run via Bazel, as follows:

bazel test ...

*Note that testing has not yet been extended to cover the full JSON specification.*

## Installation

TBD

(include {root}/library/libjson.hpp and link against {root}/bazel-bin/library/liblibjson.a (or .so)

## Usage

TBD