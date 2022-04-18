.syntax unified
.thumb
.text

@ Simbolos exportados
.global asm_svc
.global asm_sum
.global asm_zeros
.global asm_productoEscalar32
.global asm_productoEscalar16
.global asm_productoEscalar12
.global asm_productoEscalar12Sat
.global asm_filtroVentana10
.global asm_pack32to16
.global asm_max
.global asm_downsampleN
.global asm_invertir

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_svc (void)
@
.thumb_func
    asm_svc:
        svc 0
        bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   uint32_t asmSum (uint32_t firstOperand, uint32_t secondOperand)
@
@ Parametros recibidos:
@   r0: firstOperand
@   r1: secondOperand
@
@ Valor de retorno:
@   r0: resultado de la suma de firstOperand y secondOperand
@
.thumb_func
    asm_sum:
        add r0, r1  @ r0 = r0 + r1
        bx lr       @ vuelve adonde fue llamada (especificamente, si "pc"
                    @ es la direccion, en el codigo del programa, de la
                    @ instruccion "bl asm_sum" usada para saltar a
                    @ esta funcion, entonces "lr" contiene ese "pc" + 4).
                    @ el valor de retorno debe quedar en el registro r0.
                    @ En este caso, r0 es el resultado de r0 + r1.

        @ Otras alternativas para el retorno
        @ mov pc,lr
        @ bx lr
        @ push {lr} ... pop {pc}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_zeros(uint32_t *vector, uint32_t longitud)
@
@ Parametros recibidos:
@   r0: vector
@   r1: longitud
@
.thumb_func
    asm_zeros:
    	mov r2, 0
    .asm_zeros_loop:
    	str r2, [r0], 4
    	subs r1, 1
    	bne .asm_zeros_loop
    	bx lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_productoEscalar32(uint32_t *vectorIn, uint32_t *vectorOut, uint32_t longitud, uint32_t escalar);
@
@ Parametros recibidos:
@   r0: vectorIn
@	r1: vectorOut
@   r2: longitud
@	r3: escalar
@
.thumb_func
    asm_productoEscalar32:
    	push {r4,r5}
    .asm_productoEscalar32_loop:
    	ldr r4, [r0], 4
    	mul r5, r4, r3
    	str r5, [r1], 4
    	subs r2, 1
    	bne .asm_productoEscalar32_loop
    	pop {r4,r5}
    	bx lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_productoEscalar16(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar);
@
@ Parametros recibidos:
@   r0: vectorIn
@	r1: vectorOut
@   r2: longitud
@	r3: escalar
@
.thumb_func
    asm_productoEscalar16:
    	push {r4,r5}
    .asm_productoEscalar16_loop:
    	ldrh r4, [r0], 2
    	ldrh r5, [r1]
    	mul r5, r4, r3
    	strh r5, [r1], 2
    	subs r2, 1
    	bne .asm_productoEscalar16_loop
    	pop {r4,r5}
    	bx lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_productoEscalar12(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar);
@
@ Parametros recibidos:
@   r0: vectorIn
@	r1: vectorOut
@   r2: longitud
@	r3: escalar
@
.thumb_func
    asm_productoEscalar12:
    	push {r4-r6}
    	mov r6, 0xFFF
    .asm_productoEscalar12_loop:
    	ldrh r4, [r0], 2
    	ldrh r5, [r1]
    	mul r5, r4, r3
    	and r5, r5, r6
    	strh r5, [r1], 2
    	subs r2, 1
    	bne .asm_productoEscalar12_loop
    	pop {r4-r6}
    	bx lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_productoEscalar12Sat(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar);
@
@ Parametros recibidos:
@   r0: vectorIn
@	r1: vectorOut
@   r2: longitud
@	r3: escalar
@
.thumb_func
    asm_productoEscalar12Sat:
    	push {r4-r6}
    	mov r6, 0xFFF
    .asm_productoEscalar12Sat_loop:
    	ldrh r4, [r0], 2
    	ldrh r5, [r1]
    	mul r5, r4, r3
    	usat r5, 12, r5
    	strh r5, [r1], 2
    	subs r2, 1
    	bne .asm_productoEscalar12Sat_loop
    	pop {r4-r6}
    	bx lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_filtroVentana10(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud);
@
@ Parametros recibidos:
@   r0: vectorIn
@	r1: vectorOut
@   r2: longitud
@
.thumb_func
    asm_filtroVentana10:
    	push {r4-r9}
    	mov r3, r0				@ init_pos	-> r3
    	mov r4, r0				@ filt_pos	-> r4
    	mov r5, r2				@ l			-> r5
    	mov r6, 0				@ res		-> r6
    	mov r7, 0
    	mov r8, 0
    	mov r9, 10
    .asm_filtroVentana10_loop:
    	add r7, r3, r2			@ r6 = init_pos + longitud
    	cmp r4, r6				@ if (filt_pos >= longitud)
    	it hs
    	movhs r4, r3			@ filt_pos = init_pos
    	ldrh r8, [r0], 2		@ r8 = *vectorIn++;
    	add r6, r8				@ res += r8
    	add r9, r4, 10			@ r9 = filt_pos + 10
    	cmp r0, r9				@ if (vectorIn >= (filt_pos + 10u))
    	udiv r6, r6, r9			@ res /= 10
    	strh r6, [r1], 2		@ *vectorOut++ = res;
    	add r4, 2				@ filt_pos++
    	mov r0, r4				@ vectorIn = filt_pos
    	subs r5, 1				@ l--
    	bne .asm_filtroVentana10_loop
    	pop {r4-r9}
    	bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_pack32to16(int32_t *vectorIn, int16_t *vectorOut, uint32_t longitud);
@
@ Parametros recibidos:
@   r0: vectorIn
@	r1: vectorOut
@   r2: longitud
@
.thumb_func
    asm_pack32to16:
    .asm_pack32to16_loop:
    	ldr r3, [r0], 4
    	lsr r3, r3, 16
    	strh r3, [r1], 2
    	subs r2, 1
    	bne .asm_pack32to16_loop
    	bx lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_max(int32_t *vectorIn, uint32_t longitud);
@
@ Parametros recibidos:
@   r0: vectorIn
@   r1: longitud
@
.thumb_func
    asm_max:
    	mov r2, 0x80000000
    .asm_max_loop:
    	ldr r3, [r0], 4
    	cmp r3, r2
    	it gt
    	movgt r2, r3
    	subs r1, 1
    	bne .asm_max_loop
    	bx lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_downsampleN(int32_t *vectorIn, int32_t *vectorOut, uint32_t longitud, , uint32_t N);
@
@ Parametros recibidos:
@   r0: vectorIn
@	r1: vectorOut
@   r2: longitud
@	r3: N
@
.thumb_func
    asm_downsampleN:
    	push {r4-r5}
    	mov r4, 0
    .asm_downsampleN_loop:
		add r4, 1
		ldr r5, [r0], 4
    	cmp r4, r3
    	ite lo
    	strlo r5, [r1], 4
    	movhs r4, 0
    	subs r2, 1
    	bne .asm_downsampleN_loop
    	pop {r4-r5}
    	bx lr

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_invertir(uint16_t *vectorIn, uint32_t longitud);
@
@ Parametros recibidos:
@   r0: vectorIn
@   r1: longitud
@
.thumb_func
    asm_invertir:
    	mov r2, 0				@ tmp = 0u;
    	mov r3, 0
    .asm_invertir_loop:
		ldrh r2, [r0]			@ tmp = *r0
		ldrh r3, [r0, r1]		@ r3 = *(vectorIn + longitud)
		strh r3, [r0]			@ *r0 = r3
		strh r2, [r0, r1]		@ *(vectorIn + longitud) = tmp
    	subs r1, 1
    	bne .asm_invertir_loop
    	bx lr
