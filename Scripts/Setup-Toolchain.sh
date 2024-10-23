OUT_PATH=$HOME/DariusOS

export PREFIX="${OUT_PATH}/Opt/Cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

TEMP_PATH=/tmp/DariusOS
THREAD_COUNT=12

# BINUTILS
wget https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz -P ${TEMP_PATH}/ToolChain
tar xf ${TEMP_PATH}/ToolChain/binutils-2.42.tar.xz -C ${TEMP_PATH}/ToolChain
mkdir -p ${OUT_PATH}/Src
cd ${OUT_PATH}/Src
mkdir -p Build-Binutils
cd Build-Binutils
${TEMP_PATH}/ToolChain/binutils-2.42/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j${THREAD_COUNT}
make install -j${THREAD_COUNT}

# GCC
wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.xz -P ${TEMP_PATH}/ToolChain
tar xf ${TEMP_PATH}/ToolChain/gcc-13.2.0.tar.xz -C ${TEMP_PATH}/ToolChain
mkdir -p ${OUT_PATH}/Src
cd ${OUT_PATH}/Src
which -- $TARGET-as || echo $TARGET-as is not in the PATH
mkdir -p Build-Gcc
cd Build-Gcc
${TEMP_PATH}/ToolChain/gcc-13.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc -j${THREAD_COUNT}
make all-target-libgcc -j${THREAD_COUNT}
make install-gcc -j${THREAD_COUNT}
make install-target-libgcc -j${THREAD_COUNT}
