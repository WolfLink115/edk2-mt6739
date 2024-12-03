_Head:
	/* Set _Entry address */
	adr		x1, _Payload

	/* Jump to the real code */
	b		_Start

	/* Fake Linux kernel header */

_StackBase:
	/* Text Offset */
	.quad UEFI_BASE

_StackSize:
	/* Image Size */
	.quad UEFI_SIZE

	/* Flags */
	.quad 0

	/* Reserved */
	.quad 0

	/* Reserved */
	.quad 0

	/* Reserved */
	.quad 0

	/* ARM64 Magic */
	.ascii "ARM\x64"

	/* Reserved */
	.long 0

_Start:
        main:
        sub     sp, sp, #16
        mov     x0, 1991114752
        str     x0, [sp]
        str     wzr, [sp, 12]
        b       .L2
.L3:
        ldrsw   x0, [sp, 12]
        ldr     x1, [sp]
        add     x0, x1, x0
        mov     w1, -1
        strb    w1, [x0]
        ldrsw   x0, [sp, 12]
        add     x0, x0, 1
        ldr     x1, [sp]
        add     x0, x1, x0
        mov     w1, -1
        strb    w1, [x0]
        ldrsw   x0, [sp, 12]
        add     x0, x0, 2
        ldr     x1, [sp]
        add     x0, x1, x0
        mov     w1, -1
        strb    w1, [x0]
        ldrsw   x0, [sp, 12]
        add     x0, x0, 3
        ldr     x1, [sp]
        add     x0, x1, x0
        mov     w1, -1
        strb    w1, [x0]
        ldr     w0, [sp, 12]
        add     w0, w0, 4
        str     w0, [sp, 12]
.L2:
        ldr     w1, [sp, 12]
        mov     w0, 1179647
        cmp     w1, w0
        ble     .L3
        mov     w0, 0
        add     sp, sp, 16
        b _Dead
	mov		x4, x1
	ldr		x5, _StackBase
	cmp		x4, x5
	beq		_Entry
	ldr		x6,  _StackSize

_CopyLoop:
	ldp		x2, x3, [x4], #16
	stp		x2, x3, [x5], #16
	subs	x6, x6, #16
	b.ne	_CopyLoop
	ldr		x5, _StackBase

_Entry:
	br		x5

_Dead:
	/* We should never get here */
	b		_Dead

.text
.align 4

_Payload:
	/* Your code will get ran right after this binary */