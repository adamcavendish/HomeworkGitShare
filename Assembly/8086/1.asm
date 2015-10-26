assume cs:power

power segment
	mov eax, 2
	add eax, eax
	add eax, eax
	
	mov eax, 4C00H
	int 21H
power ends

end