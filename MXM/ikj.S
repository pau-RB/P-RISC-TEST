.equ msz,32
.align 2
.text
.globl mxm
###### mat times mat ######
mxm:
	li		t3,msz
for_i:
	li		t4,msz
for_k:
	lw		t0,0(a0)
	li		t5,msz
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
	addi	a2,a2,(-4*msz)
	addi	t4,t4,-1
	bnez	t4,for_k

	addi	a1,a1,(-2*msz*msz)	# ++i
	addi	a1,a1,(-2*msz*msz)
	addi	a2,a2,4*msz
	addi	t3,t3,-1
	bnez	t3,for_i

	ret