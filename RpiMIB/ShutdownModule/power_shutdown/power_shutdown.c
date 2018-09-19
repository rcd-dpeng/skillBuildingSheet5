#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Miles Kretschmer");

static unsigned int IRQnumber;

static irq_handler_t irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);

static int __init power_shutdown_init(void) {
	int result = 0;
	gpio_export(21, false);
	gpio_direction_input(21);
	IRQnumber = gpio_to_irq(21);
	result = request_irq(IRQnumber, (irq_handler_t) irq_handler, IRQF_TRIGGER_RISING, "irq_handler", NULL); 
	return 0;
}

static char * shutdown_argv[] = 
    { "/sbin/shutdown", "-h", "-P", "now", NULL };

static irq_handler_t irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs) {
	call_usermodehelper(shutdown_argv[0], shutdown_argv, NULL, UMH_NO_WAIT);
	return (irq_handler_t) IRQ_HANDLED;
}

static void __exit power_shutdown_exit(void) {
	free_irq(IRQnumber, NULL);
	gpio_unexport(21);
}

module_init(power_shutdown_init);
module_exit(power_shutdown_exit);
