
	include vram.i

_text	segment	para public use32 'code'
	assume cs:CGROUP,ds:CGROUP

	;vram_uncc64(Rast_vram *v, Cbuf *csource)
	;set the color palette hardware from a compressed source 
	;of format:
	;WORD # of runs, run1, run2, ...,runn
	;each run is of form:
	;BYTE colors to skip, BYTE colors to set, r1,g1,b1,r2,g2,b2,...,rn,gn,bn
	public vram_uncc64
vram_uncc64 proc near
	push ebp
	mov ebp,esp
	push esi
	push edi
	push ebx

	xor eax,eax ;and hi bits of accumulator

	mov esi,[ebp+12]	;load the source compressed color data
	mov edi,0		;clear dest color index 
	lodsw
	mov ebx,eax   	;get the count of color runs
	test ebx,ebx
	jmp endcu
cu:
	lodsb		;get the colors to skip
	add edi,eax	;add to color index
	lodsb		;get the count of colors to set
	mov ecx,eax	;use it as a loop counter
	or  ecx,ecx	;test for zero
	jnz	set1c
	mov ecx,256
set1c:
	mov	edx,3c8h	;point dx to vga color control port
	mov eax,edi
	out dx,al	;say which color index to start writing to
	inc edi		;bump color index
	inc edx		;point port to vga color data
	;jmp s1		;stall as per IBM VGA tech spec to give hardware time to settle
s1:
	lodsb		;get red component
	out dx,al	;tell the video DAC where it's at
	;jmp s2		;stall some more for poor slow hardware
s2:
	lodsb		;same same with green component
	out dx,al
	;jmp s3
s3:
	lodsb		;same with blue
	out dx,al
	loop set1c

	dec ebx
endcu:
	jnz cu

	pop ebx
	pop edi
	pop esi
	pop	ebp
	ret	
vram_uncc64 endp

_text	ends
	end

