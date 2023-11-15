#!/bin/bash

# We require clang-format v17. Other versions may produce different styles!

find .. -name fmod -prune -iname *.h -o -iname *.hpp -o -iname *.c -o -iname *.cpp -o -iname *.cuh -o -iname *.cu | xargs clang-tidy -fix-errors -p builddir/

find .. -name fmod -prune -iname *.h -o -iname *.hpp -o -iname *.c -o -iname *.cpp -o -iname *.cuh -o -iname *.cu | xargs clang-format -i
