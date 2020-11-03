	.arch msp430g2553
	.p2align 1,0

	.data
S:
	.word 1

	.text
jt:
	.word default	; index 0
	.word green	; index 1
	.word red	; index 2

	.text
	.global switching_leds_assembly
switching_leds_assembly:
	mov &S, r12		; move S into r12
	cmp #3, r12		; S - 3 to check if in range
	jc default 		; did not work with jnc but is better with jc

	add r12, r12		; 2 x S
	mov jt(r12), r0		; spot in the jump table

green:
	cmp.b #1, &green_on	; check if green is on
	jz red			; go to red

	mov.b #1, &green_on	; turn on green light
	mov.b #0, &red_on	; turn off red light
	jmp end			; break

red:
	mov.b #0, &green_on	; turn off green light
	mov.b #1, &red_on	; turn on red light
	jmp end 		; break

default:
	mov.b #0, &green_on 	; turn off green
	mov.b #0, &red_on	; turn off red
	jmp end

end:
	ret			; end
	
