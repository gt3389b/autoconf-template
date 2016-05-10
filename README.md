# autoconf-template
Simple autoconf example

## Initial steps

autoconf will create a a configure.ac for you.  In our example we already have one.  But you can create it for fun.
```
autoscan
```

Once you're comfortable with it, then move it into 'production'
```
mv configure.scan configure.ac
```

## Let's go
```
mkdir m4
```

```
aclocal
```

```
autoconf
```

```
glibtoolize
```

```
autoheader
```

```
automake --add-missing
```

```
./configure
```

```
make
```

