erl-popcnt
==========

Version: 0.1.0

A wrapper for GCCs and MSVC++ population count functions. This wrapper will return the number of bits that are set in a passed integer. This function will operate on 32 and 64-bit unsigned integers. In the event that the preprocessor does not identify the compiler as a GCC varient or MSVC++, the library will default to a provided function.

Usage
-----

The following example demonstrates the usage of this module:

```erlang
1> erl_popcnt:popcnt(123).
6
2> erl_popcnt:popcnt(2#1010101).
4
3> erl_popcnt:popcnt(16#ffff).   
16
4> erl_popcnt:popcnt(2049).   
2
```

Functions
---------

The following functions have been exposed:

 * ```erl_popcnt:popcnt/1``` return the number of bits that are set in a passed integer.

License
-------

This application is licensed under an [Apache 2.0 License](http://www.apache.org/licenses/LICENSE-2.0.html)

    Copyright 2014 David Ellefsen 

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.


