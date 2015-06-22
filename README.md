[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/vapourismo/luwra)

# Luwra
A header-only C++ library which provides a Lua wrapper with minimal overhead.

## Requirements
You need will need a C++14 compliant compiler and Lua 5.2 (or higher) installed.

 Platform            | Lua 5.1  | Lua 5.2 <sup>**1)**</sup> | Lua 5.3
---------------------|----------|---------------------------|---------
 Linux (clang++ 3.6) | untested | works                     | works
 Linux (g++ 5.1)     | untested | works                     | works
 Everything else     | untested | untested                  | untested

<sup>**1)**</sup> Inherits the integer quirks that come with Lua 5.2, that why the `types_numeric`
test case fails.

## Usage
Refer to the [wiki pages](https://github.com/vapourismo/luwra/wiki). In order to use the library
you must clone this repository and add its `lib/` folder to your include path.
