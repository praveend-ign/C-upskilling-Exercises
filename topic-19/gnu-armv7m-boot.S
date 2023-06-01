/*! startup code according to gnu assembler
 *  and ld scripts syntax for arm cortex processors
 */
	.syntax     unified
	.arch       armv7-m
	
	.section .stack
	.align  3
/*! set default stack size */
	.equ    Stack_Size, 0x00000400
__StackTop:
	.size   __StackTop, . - __StackTop

	.section .heap
	.align  3
/*! set default heap size */
	.equ    Heap_Size, 0x00000C00
	.globl  __HeapBase
        .globl  __HeapLimit
__HeapBase:
        .if     Heap_Size
        .space  Heap_Size
        .endif
        .size   __HeapBase, . - __HeapBase
__HeapLimit:
        .size   __HeapLimit, . - __HeapLimit

        .section .vectors
        .align  2
        .globl  __Vectors

__Vectors:
        .long   __StackTop            /*! Top of Stack */
        .long   Reset_Handler         /*! Reset Handler */
        .long   NMI_Handler           /*! NMI Handler */
        .long   HardFault_Handler     /*! Hard Fault Handler */
        .long   MemManage_Handler     /*! MPU Fault Handler */
        .long   BusFault_Handler      /*! Bus Fault Handler */
        .long   UsageFault_Handler    /*! Usage Fault Handler */
        .long   0                     /*! Reserved */
        .long   0                     /*! Reserved */
        .long   0                     /*! Reserved */
        .long   0                     /*! Reserved */
        .long   SVC_Handler           /*! SVCall Handler */
        .long   DebugMon_Handler      /*! Debug Monitor Handler */
        .long   0                     /*! Reserved */
        .long   PendSV_Handler        /*! PendSV Handler */
        .long   SysTick_Handler       /*! SysTick Handler */

	.size   __Vectors, . - __Vectors

	.globl  Reset_Handler
	.type   Reset_Handler, %function
/*! Reset handler function executed immediately
 *  after pressing reset button.
 *  it copies data segment from 
 *  read only memory to RAM.
 *  and then copies the bss segment 
 */
Reset_Handler:
/*! __etext: LMA of start of the section to copy from. it 
 *  indicates usually end of text
 *  __data_start__: VMA of start of the section to copy to.
 *  __data_end__: VMA of end of the section to copy to
 */
	ldr     r1, =__etext
        ldr     r2, =__data_start__
        ldr     r3, =__data_end__

.loop1:
        cmp     r2, r3
        ittt    lt
        ldrlt   r0, [r1], #4
        strlt   r0, [r2], #4
        blt     .loop1

/*! fill bss section with zeros */
	ldr     r1, =__bss_start__
        ldr     r2, =__bss_end__

        movs    r0, 0
.loop2:
        cmp     r1, r2
        itt     lt
        strlt   r0, [r1], #4
        blt     .loop2

/*! load text section into memory. 
 *  text section starts after the
 *  end of vector table
 */
	ldr     r1, =__eVectors__
        ldr     r2, =__text_start__
        ldr     r3, =__text_end__
.loop3:
        cmp     r2, r3
        ittt    lt
        ldrlt   r0, [r1], #4
        strlt   r0, [r2], #4
        blt     .loop3

/*! C routine which initializes system clock
 */
bl      SystemInit

/*! __START routine is defined in crt0.o library module 
 * after initializing some library routines, it jumps
 * to main() function of c program
 */ 
bl      __START

	.size   Reset_Handler, . - Reset_Handler
	
	.weak   Default_Handler
        .type   Default_Handler, %function
Default_Handler:
    bkpt #0
        b       .
        .size   Default_Handler, . - Default_Handler

	.macro  def_irq_handler handler_name
        .weak   \handler_name
        .set    \handler_name, Default_Handler
        .endm

        def_irq_handler NMI_Handler
        def_irq_handler HardFault_Handler
        def_irq_handler MemManage_Handler
        def_irq_handler BusFault_Handler
        def_irq_handler UsageFault_Handler
        def_irq_handler SVC_Handler
        def_irq_handler DebugMon_Handler
        def_irq_handler PendSV_Handler
        def_irq_handler SysTick_Handler
	
	.end
