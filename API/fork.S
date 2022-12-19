.align 2
.text
.globl fork_sync
fork_sync:
	mv 		t0,ra
	mv		t1,sp
	mv		t2,s0
1:
	auipc	ra,%pcrel_hi(child_return)
	addi	ra,ra,%pcrel_lo(1b)
	mv		sp,a7
	mv		s0,a6
	sw		zero,0(a6)
	.word	0x0007808b					#forkr a5
	mv 		ra,t0
	mv		sp,t1
	mv		s0,t2
	ret
child_return:
	sw		a0,4*10(s0)
	sw		a1,4*11(s0)

	.word	0x0004010b					#join 0(s0)

	lw		x1,4*1(s0)
	lw		x2,4*2(s0)
	lw		x3,4*3(s0)
	lw		x4,4*4(s0)
	lw		x5,4*5(s0)
	lw		x6,4*6(s0)
	lw		x7,4*7(s0)

	lw		x9,4*9(s0)


	lw		x12,4*12(s0)
	lw		x13,4*13(s0)
	lw		x14,4*14(s0)
	lw		x15,4*15(s0)
	lw		x16,4*16(s0)
	lw		x17,4*17(s0)
	lw		x18,4*18(s0)
	lw		x19,4*19(s0)
	lw		x20,4*20(s0)
	lw		x21,4*21(s0)
	lw		x22,4*22(s0)
	lw		x23,4*23(s0)
	lw		x24,4*24(s0)
	lw		x25,4*25(s0)
	lw		x26,4*26(s0)
	lw		x27,4*27(s0)
	lw		x28,4*28(s0)
	lw		x29,4*29(s0)
	lw		x30,4*30(s0)
	lw		x31,4*31(s0)

	lw		s0,4*8(s0)

	ret