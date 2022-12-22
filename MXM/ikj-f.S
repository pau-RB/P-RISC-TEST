.equ msz,32
.equ thd,4
.equ str,4*msz/thd

.data
.align 2
sync:
	.word 0
	.word 0
	.word 0

.align 2
.text
.globl mxm
###### mat times mat ######
mxm:
1:
	auipc	t6,%pcrel_hi(sync)
	addi	t6,t6,%pcrel_lo(1b)

fork:
	.word	0x0240000b
	addi	a1,a1,str
	addi	a2,a2,str
	.word	0x0180000b
	addi	a1,a1,str
	addi	a2,a2,str
	.word	0x00c0000b
	addi	a1,a1,str
	addi	a2,a2,str

task:
	li		t3,msz
for_i:
	li		t4,msz
for_k:
	lw		t0,0(a0)
	li		t5,msz/thd
for_j:
	lw		t1,0(a1)
	lw		t2,0(a2)
	mul		t1,t0,t1
	add 	t2,t2,t1
	sw		t2,0(a2)

	addi	a1,a1,4				# ++j
	addi	a2,a2,4
	addi	t5,t5,-1
	bnez	t5,for_j

	addi	a0,a0,4				# ++k
	addi	a1,a1,(+str*(thd-1))
	addi	a2,a2,(-str)
	addi	t4,t4,-1
	bnez	t4,for_k

	addi	a1,a1,(-2*msz*msz)	# ++i
	addi	a1,a1,(-2*msz*msz)
	addi	a2,a2,(+4*msz)
	addi	t3,t3,-1
	bnez	t3,for_i

join:
	.word	0x000F810b
	.word	0x004F810b
	.word	0x008F810b

	ret