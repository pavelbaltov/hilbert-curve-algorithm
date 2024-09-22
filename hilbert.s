.data
.balign 4
startingPointsX: .word 0,0,1,1
startingPointsY: .word 0,1,1,0	

.text
.balign 4
.global hilbert
	hilbert:
	/* x19 - degree */
	/* x20 - coord_t* x */
	/* x21 - coord_t* y */
	/* x1 - i */
	/* x2 - j */
	/* x3 - totalPoints */
	/* x4 - startingPointsX[] */
	/* x5 - startingPointsY[] */
	/* q6 - currentCoordinateX */
	/* q7 - currentCoordinateY */

	stp x19, x30, [sp, #-32]!
	stp x20, x21, [sp, 16]

/* moving arguments to callee-save registers */
	mov x19, x0
	mov x20, x1
	mov x21, x2

/* get address of both arrays - startingPointsX/Y */
	ldr x4, =startingPointsX 
	ldr x5, =startingPointsY 

/*calculate totalPoints */
	mov x10, 1
	mov x3, x19, lsl 1  /* x3 = degree * 2*/
	lsl  x3, x10, x3

/* set i for the biggest loop */
	mov x1, #0

	b .check_LoopAllPoints

.LoopAllPoints:

/* determines starting points */

	ldr q6, [x4] 
	ldr q7, [x5]

	mov x2, 1 /* j */
	b .check_LoopCalculatePoints

.LoopCalculatePoints:
	mov x8, x2, lsl 1 
	lsr x8, x1, x8
	and x8, x8, #3 /* that's current quadrant */

    	mov x9, 1 
	lsl x9, x9, x2  /*  that's length */

	ins v10.4s[0], w9
	ins v10.4s[1], w9
	ins v10.4s[2], w9
	ins v10.4s[3], w9 

	cmp x8, 0 /* if it's in 0th Quadrant - swaps X, Y */
	b.ne .LEqualsOne
		stp q7, q6, [sp, -32]
		ldp q6, q7, [sp, -32]

		b .LendOfIf
.LEqualsOne:
	cmp x8, 1 /* if it's in 1th Quadrant - adds to Y */
	b.ne .LEqualsTwo
		add v7.4s, v7.4s, v10.4s
		b .LendOfIf
.LEqualsTwo:
	cmp x8, 2 /* if it's in 2nd Quadrant - add to both X and Y */
	b.ne .LEqualsThree
		add v6.4s, v6.4s, v10.4s
		add v7.4s, v7.4s, v10.4s
		b .LendOfIf
.LEqualsThree:
	cmp x8, 3 /* if it's in 3rd Quadrant - as in 0th Quadrant but also flips horizontally, adds to X */
		movi v11.4s, #1
		sub v12.4s, v10.4s, v11.4s
		sub v15.4s, v12.4s, v6.4s
		sub v14.4s, v12.4s, v7.4s
		
		stp q14, q15, [sp, -32]
		ldp q6, q7, [sp, -32]

		add v6.4s, v6.4s, v10.4s

.LendOfIf:
	add x2, x2, #1

.check_LoopCalculatePoints:
	cmp x2, x19
	b.lt  .LoopCalculatePoints

	mov x10, x1, lsl 2
	str q6, [x20, x10]
	str q7, [x21, x10]
	add x1, x1, #4

.check_LoopAllPoints:
	cmp x1, x3
	blt .LoopAllPoints

.LEnd:
	ldp x20, x21, [sp, 16]
	ldp x19, x30, [sp], 32
	ret
