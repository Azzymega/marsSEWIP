
CFLAGS = --target=i686-pc-none-elf -march=i686 -ffreestanding -O0 -nostdlib -ggdb3 -g -fPIC -nodefaultlibs
LL = build/libkernel.a build/multiboot.o build/crs.o

main: multiboot link generateIso 

multiboot: source/kernel/boot/multiboot.s
	clang -c source/kernel/boot/multiboot.s $(CFLAGS) -o build/multiboot.o
	clang -c source/kernel/boot/crs.s $(CFLAGS) -o build/crs.o

link: build/linker.ld
	ld.lld -T build/linker.ld $(LL) -o myos.bin

generateIso: grub.cfg myos.bin grub.cfg 
#	copy "myos.bin" "build/boot/myos.bin"
#	copy "grub.cfg" "build/boot/grub/grub.cfg"
	qemu-system-i386 -kernel myos.bin
#	grub-mkimage -O i386-pc -o myos.iso -c grub.cfg -p build/boot/ Заменить на grub-mkrescure как только на Linux'e