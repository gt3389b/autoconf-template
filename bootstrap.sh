#! /bin/sh
mkdir m4
aclocal
autoconf
glibtoolize
autoheader
automake --add-missing

./configure
make
