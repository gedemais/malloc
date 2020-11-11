#!/bin/shqq
export DYLD_LIBRARY_PATH=. DYLD_INSERT_LIBRARIES="/Users/gedemais/Desktop/Projects/malloc/libmalloc.so" DYLD_FORCE_FLAT_NAMESPACE=1
$@
