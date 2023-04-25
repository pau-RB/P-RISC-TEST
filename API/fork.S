.align 2
.text
.globl fork_sync
fork_sync:
	mv 		t0,ra
	mv		t1,sp
	mv		t2,s11
1:
	auipc	ra,%pcrel_hi(child_return)
	addi	ra,ra,%pcrel_lo(1b)
	mv		sp,a7
	mv		s11,a6
	sw		zero,0(a6)
	.word	0x0007808b					#forkr a5
	mv 		ra,t0
	mv		sp,t1
	mv		s11,t2
	ret
child_return:
	sw		a0,4*10(s11)
	sw		a1,4*11(s11)

	.word	0x000D810b					#join 0(s11)

	lw		x1,4*1(s11)
	lw		x2,4*2(s11)

	lw		x8,4*8(s11)
	lw		x9,4*9(s11)

	lw		x18,4*18(s11)
	lw		x19,4*19(s11)
	lw		x20,4*20(s11)
	lw		x21,4*21(s11)
	lw		x22,4*22(s11)
	lw		x23,4*23(s11)
	lw		x24,4*24(s11)
	lw		x25,4*25(s11)
	lw		x26,4*26(s11)
	lw		x27,4*27(s11)

	ret