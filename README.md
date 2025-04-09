# Prefer temporary addresses via `LD_PRELOAD`

If you want to use privacy addresses (of dubious value as they are) with your Linux browser, but want to continue to use stable addresses for everything else (like SSH, for which temporary addresses are incredibly annoying), this is the repo for you.

## Build

```makefile
make
make install
```

## Use

For example:

```sh
LD_PRELOAD=~/lib/prefertmpaddr.so firefox
```
