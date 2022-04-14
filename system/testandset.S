	.text
	.globl	test_and_set

/**
 * test_and_set: assume it's called with test_and_set(&lock);
 * @param lock pointer to a mutex_t variable
 *
 * TODO - add a comment each line describing its action
 */
test_and_set:
	cli					#disable interrupts
	pushl	%ebx		# preserve contents of the %ebx register, which is about to be modified
	movl	8(%esp), %ebx	# TODO copy contents from %ebx to %esp 
	movl	$1, %eax	# TODO store a 1 in register %eax
	xchg	%eax, (%ebx)	# TODO exchange the 1 with what is in %ebx
	popl	%ebx		# TODO restore contents of %ebx into its register (from top of stack)
	sti			#enable interrupts
	ret			# TODO return to line that called test_and_set
