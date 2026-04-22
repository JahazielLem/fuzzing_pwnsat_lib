# ccsds_lib
CCSDS C Implementations


# Requirements
```shell
# Macos
brew install llvm

export CC=/opt/homebrew/opt/llvm/bin/clang
export CXX=/opt/homebrew/opt/llvm/bin/clang++

# Linux
sudo apt install -y clang
export CC=/usr/lib/llvm-16/bin/clang
export CXX=/usr/lib/llvm-16/bin/clang++
```

# Compile

```shell
$CC -g -O1 -fsanitize=fuzzer,address,undefined \
    -I./include \
    src/spp/spp.c \
    fuzzing/fuzz_spp_unpack.c \
    -o fuzz_spp

```


# Start

```shell
./fuzz_spp_unpack -dict=fuzzing/spp.dict 
```