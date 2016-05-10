# autoconf-template
Simple autoconf example

## Initial steps

```
autoscan
```

mv configure.scan configure.ac

## Initial steps
mkdir m4

aclocal

autoconf

glibtoolize

autoheader

automake --add-missing

./configure

make

