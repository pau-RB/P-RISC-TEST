.align 2
.text
.globl wait_sync
wait_sync:
	sw		x1,4*1(a0)
	sw		x2,4*2(a0)
	sw		x3,4*3(a0)
	sw		x4,4*4(a0)
	sw		x5,4*5(a0)
	sw		x6,4*6(a0)
	sw		x7,4*7(a0)
	sw		x8,4*8(a0)
	sw		x9,4*9(a0)


	sw		x12,4*12(a0)
	sw		x13,4*13(a0)
	sw		x14,4*14(a0)
	sw		x15,4*15(a0)
	sw		x16,4*16(a0)
	sw		x17,4*17(a0)
	sw		x18,4*18(a0)
	sw		x19,4*19(a0)
	sw		x20,4*20(a0)
	sw		x21,4*21(a0)
	sw		x22,4*22(a0)
	sw		x23,4*23(a0)
	sw		x24,4*24(a0)
	sw		x25,4*25(a0)
	sw		x26,4*26(a0)
	sw		x27,4*27(a0)
	sw		x28,4*28(a0)
	sw		x29,4*29(a0)
	sw		x30,4*30(a0)
	sw		x31,4*31(a0)

	.word	0x0005010b					#join 0(a0)

	lw		a1,4*11(a0)
	lw		a0,4*10(a0)

	ret