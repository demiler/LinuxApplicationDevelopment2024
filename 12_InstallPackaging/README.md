# Build

```
autoreconf -fisv && ./configure && make
```

# Run freshly built

```
./src/avg
```

# View docs

```
make docs-serve
```

# Run tests

```
make check
```

# Install into temp location

```
tempdir=`mktemp -d`
autoreconf -fisv
./configure --prefix $tempdir
make all install
```

# Install package

```
autoreconf -fisv && ./configure && make
sudo make install
```

# Remove package

```
sudo make uninstall
```
