MAIN:
MOV 0xA0, #01B
LCALL DELAY
MOV 0xA0, #00B
LCALL DELAY
LJMP MAIN
 
DELAY:	MOV R7,#255		
D1:
	NOP
	PUSH 30H
	PUSH 31H
	MOV 30H,#2
	MOV 31H,#194
NEXT:
	DJNZ 31H,NEXT
	DJNZ 30H,NEXT
	POP 31H
	POP 30H
	DJNZ R7,D1
	RET
END