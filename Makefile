APIDIR=API
MMIODIR=MMIO
MXMDIR=MXM

SRCDIR=src
DATDIR=data
BUILDDIR=build
DUMPDIR=dump
HEXDIR=hex

ELF2HEX=./elf2hex

RISCVCC32=riscv64-unknown-elf-gcc -O3 -march=rv32im -mabi=ilp32 -static -nostdlib -nostartfiles -fno-builtin -mcmodel=medany
RISCVOBJD=riscv64-unknown-elf-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init

MXM_SOURCES=$(notdir $(wildcard $(MXMDIR)/*.S))
MXM_ELF=$(addprefix $(BUILDDIR)/rv32-mxm-,$(basename $(MXM_SOURCES)))

S_SOURCES=$(notdir $(wildcard $(SRCDIR)/*.S))
S_ELF=$(addprefix $(BUILDDIR)/rv32-s-,$(basename $(S_SOURCES)))

C_SOURCES=$(notdir $(wildcard $(SRCDIR)/*.c))
C_ELF=$(addprefix $(BUILDDIR)/rv32-c-,$(basename $(C_SOURCES)))

# Top-level rules

all: data build
data: vec bivec mat
DATA: VEC BIVEC MAT
build: $(sort $(MXM_ELF) $(S_ELF) $(C_ELF))

# Build dependencies

$(ELF2HEX)/elf2hex:
	$(MAKE) -C $(ELF2HEX)

rv32-init.o: init.S
	$(RISCVCC32) -c init.S -o rv32-init.o

rv32-fork.o: $(APIDIR)/fork.S
	$(RISCVCC32) -c $(APIDIR)/fork.S -o $(APIDIR)/fork.o

rv32-wait.o: $(APIDIR)/wait.S
	$(RISCVCC32) -c $(APIDIR)/wait.S -o $(APIDIR)/wait.o

rv32-mmio.o: $(MMIODIR)/mmio.c
	$(RISCVCC32) -c $(MMIODIR)/mmio.c -o $(MMIODIR)/rv32-mmio.o

rv32-mxmhost.o: mxmhost.c
	$(RISCVCC32) -c mxmhost.c -o rv32-mxmhost.o

# Build small random data sets

vec: $(DATDIR)/vec.cc
	g++ $(DATDIR)/vec.cc -o $(DATDIR)/vec.out
	$(DATDIR)/vec.out $(DATDIR) 10 1000

bivec: $(DATDIR)/bivec.cc
	g++ $(DATDIR)/bivec.cc -o $(DATDIR)/bivec.out
	$(DATDIR)/bivec.out $(DATDIR) 10 1000

mat: $(DATDIR)/mat.cc
	g++ $(DATDIR)/mat.cc -o $(DATDIR)/mat.out
	$(DATDIR)/mat.out $(DATDIR) 10 32

# Build large random data sets

VEC: $(DATDIR)/vec.cc
	g++ $(DATDIR)/vec.cc -o $(DATDIR)/vec.out
	$(DATDIR)/vec.out $(DATDIR) 10   10000
	$(DATDIR)/vec.out $(DATDIR) 10  100000
	$(DATDIR)/vec.out $(DATDIR) 10 1000000

BIVEC: $(DATDIR)/bivec.cc
	g++ $(DATDIR)/bivec.cc -o $(DATDIR)/bivec.out
	$(DATDIR)/bivec.out $(DATDIR) 10   10000
	$(DATDIR)/bivec.out $(DATDIR) 10  100000
	$(DATDIR)/bivec.out $(DATDIR) 10 1000000

MAT: $(DATDIR)/mat.cc
	g++ $(DATDIR)/mat.cc -o $(DATDIR)/mat.out
	$(DATDIR)/mat.out $(DATDIR) 10  64
	$(DATDIR)/mat.out $(DATDIR) 10 128
	$(DATDIR)/mat.out $(DATDIR) 10 256
	$(DATDIR)/mat.out $(DATDIR) 10 512

# build actual tests

$(BUILDDIR)/rv32-mxm-%: $(ELF2HEX)/elf2hex rv32-init.o rv32-mmio.o $(MMIODIR)/mmio.ld rv32-mxmhost.o $(MXMDIR)/%.S
	mkdir -p $(BUILDDIR)
	mkdir -p $(DUMPDIR)
	mkdir -p $(HEXDIR)
	$(RISCVCC32) -c $(MXMDIR)/$*.S -o rv32-intermeidate.o
	$(RISCVCC32) -o $(BUILDDIR)/rv32-mxm-$* -T$(MMIODIR)/mmio.ld rv32-intermeidate.o rv32-init.o $(MMIODIR)/rv32-mmio.o rv32-mxmhost.o
	$(RISCVOBJD) $(BUILDDIR)/rv32-mxm-$* > $(DUMPDIR)/rv32-mxm-$*.dump
	$(ELF2HEX)/elf2hex $(BUILDDIR)/rv32-mxm-$* 0 16G $(HEXDIR)/rv32-mxm-$*.hex
	rm rv32-intermeidate.o

$(BUILDDIR)/rv32-s-%: $(ELF2HEX)/elf2hex $(SRCDIR)/%.S rv32-init.o rv32-mmio.o $(MMIODIR)/mmio.ld
	mkdir -p $(BUILDDIR)
	mkdir -p $(DUMPDIR)
	mkdir -p $(HEXDIR)
	$(RISCVCC32) -c $(SRCDIR)/$*.S -o rv32-intermeidate.o
	$(RISCVCC32) -o $(BUILDDIR)/rv32-s-$* -T$(MMIODIR)/mmio.ld rv32-intermeidate.o rv32-init.o $(MMIODIR)/rv32-mmio.o
	$(RISCVOBJD) $(BUILDDIR)/rv32-s-$* > $(DUMPDIR)/rv32-s-$*.dump
	$(ELF2HEX)/elf2hex $(BUILDDIR)/rv32-s-$* 0 16G $(HEXDIR)/rv32-s-$*.hex
	rm rv32-intermeidate.o

$(BUILDDIR)/rv32-c-%: $(ELF2HEX)/elf2hex $(SRCDIR)/%.c rv32-init.o rv32-mmio.o $(MMIODIR)/mmio.ld rv32-fork.o rv32-wait.o $(APIDIR)/api.h $(APIDIR)/fixedpoint.h
	mkdir -p $(BUILDDIR)
	mkdir -p $(DUMPDIR)
	mkdir -p $(HEXDIR)
	$(RISCVCC32) -c $(SRCDIR)/$*.c -o rv32-intermeidate.o
	$(RISCVCC32) -o $(BUILDDIR)/rv32-c-$* -T$(MMIODIR)/mmio.ld rv32-intermeidate.o rv32-init.o $(MMIODIR)/rv32-mmio.o $(APIDIR)/fork.o $(APIDIR)/wait.o
	$(RISCVOBJD) $(BUILDDIR)/rv32-c-$* > $(DUMPDIR)/rv32-c-$*.dump
	$(ELF2HEX)/elf2hex $(BUILDDIR)/rv32-c-$* 0 16G $(HEXDIR)/rv32-c-$*.hex
	rm rv32-intermeidate.o

# clean

clean:
	rm -f rv32-intermeidate.o rv32-init.o rv32-mxmhost.o $(APIDIR)/*.o $(MMIODIR)/*.o
	rm -rf build
	rm -rf dump
	rm -rf hex
	rm -rf $(DATDIR)/bivec_*_*.h
	rm -rf $(DATDIR)/vec_*_*.h
	rm -rf $(DATDIR)/mat_*_*.h
	rm -rf $(DATDIR)/*.out
