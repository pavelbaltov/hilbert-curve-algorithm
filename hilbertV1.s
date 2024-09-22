.data
.balign 4
startingPointsX: .word 0,0,1,1
startingPointsY: .word 0,1,1,0

.text
.balign 4
.global hilbertV1
    hilbertV1:
    /* x19 - degree */
    /* x20 - coord_t* x */
    /* x21 - coord_t* y */
    /* x1 - i */
    /* x2 - j */
    /* x3 - totalPoints */
    /* x4 - startingPointsX[] */
    /* x5 - startingPointsY[] */
    /* x6 - currentCoordinateX */
    /* x7 - currentCoordinateY */

    stp x19, x30, [sp, #-32]!
    stp x20, x21, [sp, 16]

    /* moving arguments to callee-save registers */
    mov x19, x0
    mov x20, x1
    mov x21, x2

    /* get address of both arrays - startingPointsX/Y */
    ldr x4, =startingPointsX
    ldr x5, =startingPointsY

    /* calculate totalPoints */
    lsl x3, x19, 1 /* x3 = degree * 2 */
    sub x3, x3, #1 /* x3 -= 1 */
    mov x10, 2
    lsl x3, x10, x3 /* totalPoints */

    /* set i for the biggest loop */
    mov x1, #0

    b .check_LoopAllPoints

.LoopAllPoints:
    /* determines starting points */
    and x8, x1, 3
    lsl x10, x8, 2
    ldr x6, [x4, x10]
    ldr x7, [x5, x10]

    mov x2, 1 /* j */
    b .check_LoopCalculatePoints

.LoopCalculatePoints:
    lsl x10, x2, 1 /* x10 = 2 * j */

    mov x11, 2
    sub x10, x10, 1
    lsl x11, x11, x10

    sdiv x10, x1, x11
    and x10, x10, 3 /* that's tmp */

    mov x11, 2
    sub x12, x2, 1
    lsl x11, x11, x12 /* that's length */

    cmp x10, 0
    b.ne .LEqualsOne
        mov x12, x6
        mov x6, x7
        mov x7, x12
        b .LendOfIf
.LEqualsOne:
    cmp x10, 1
    b.ne .LEqualsTwo
        add x7, x7, x11
        b .LendOfIf
.LEqualsTwo:
    cmp x10, 2
    b.ne .LEqualsThree
        add x6, x6, x11
        add x7, x7, x11
        b .LendOfIf
.LEqualsThree:
    cmp x10, 3
        sub x12, x11, 1
        sub x12, x12, x6

        sub x13, x11, 1
        sub x13, x13, x7

        mov x6, x13
        mov x7, x12
        add x6, x6, x11
.LendOfIf:
    add x2, x2, 1

.check_LoopCalculatePoints:
    cmp x2, x19
    b.lt  .LoopCalculatePoints

    lsl x10, x1, 2
    str x6, [x20, x10]
    str x7, [x21, x10]
    add x1, x1, 1

.check_LoopAllPoints:
    cmp x1, x3
    blt .LoopAllPoints

.LEnd:
    ldp x20, x21, [sp, 16]
    ldp x19, x30, [sp], 32
    ret
