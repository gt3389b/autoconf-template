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
This does all of the commands in the next section for you.
```
./bootstrap.sh
```


## Help me do it manually
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

## Try it again
Want to start over?  Then go back to the original clone
```
git clean -d -f
```

