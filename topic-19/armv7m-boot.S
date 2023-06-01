/*! arm startup code according to
 * arm processor instruction set 
 * assembler directives
 */
Stack_Size      EQU     0x400; 
                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size

Heap_Size	EQU	0x200
		AREA HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem 	SPACE Heap_Size
__heap_limit

		__initial_sp

		AREA RESET, DATA, READONLY

		DCD __initial_sp
		DCD Reset_Handler
		DCD NMI_Handler
		DCD HardFault_Handler
		DCD MemManage_Handler
		DCD BusFault_Handler
		DCD UsageFault_Handler
		DCD 0
		DCD 0
		DCD 0
		DCD 0
		DCD SVC_Handler
		DCD DebugMon_Handler
		DCD 0
		DCD PendSV_Handler
		DCD SysTick_Handler

Reset_Handler:
		AREA |.text|, CODE, READONLY
		
		IMPORT SystemInit
		IMPORT __main

		LDR R0, =SystemInit 
		BLX R0 

		LDR R0, =__main 
		BLX R0

NMI_Handler:	
		NMI_Handler PROC
		EXPORT NMI_Handler [WEAK]
		B .
		ALIGN
		ENDP


