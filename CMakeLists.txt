cmake_minimum_required(VERSION 3.15)
project(kernel)

set(CMAKE_CXX_FLAGS "--target=i686-pc-none-elf -fno-stack-protector -march=i686 -Wall -O0 -fPIC -nodefaultlibs -Wpedantic -Wextra -Wdeprecated -ffreestanding -fno-builtin -nostdlib")
add_compile_options("-mno-red-zone")
add_compile_options("-fno-exceptions")
add_compile_options("-fno-rtti")
file(GLOB_RECURSE kernelboot
    "source/kernel/*.hpp"
    "source/kernel/*.cpp"
)
add_library(kernel STATIC ${kernelboot})