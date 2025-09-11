# Instalación de QEMU
	sudo apt-get update
	sudo apt-get install qemu-user qemu-user-static gdb-multiarch build-essential
	sudo apt install binutils-aarch64-linux-gnu
	sudo apt install gcc-aarch64-linux-gnu

## Primera Terminal
	aarch64-linux-gnu-as -o hello_world.o hello_world.s
	aarch64-linux-gnu-ld -o hello_world hello_world.o

## Realizar la ejecución del codigo ensamblador
	qemu-aarch64 ./hello_world

## Realizar la depuracion del codigo ensamblador
	qemu-aarch64 -g 1234 ./hello_world

### Seguna terminal
	gdb-multiarch -q --nh \
	-ex 'set architecture aarch64' \
	-ex 'file hello_world' \
	-ex 'target remote localhost:1234' \
	-ex 'layout split' \
	-ex 'layout regs'
