#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <asm/delay.h> 
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>


#define PROC_BUFFER_SIZE 255 


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maximilian Lausch, Htw-Berlin");


static int power_mode;
static int measure_mode;
static struct proc_dir_entry *proc_file;
unsigned int irq_number;


static ssize_t procfile_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos) 
{
	char buf[PROC_BUFFER_SIZE];
	int len = sprintf(buf,"%d:%d", measure_mode, power_mode);

	/* check if we need to keep writing to the user buffer */
	if(*ppos >= len || count < PROC_BUFFER_SIZE) return 0;

	/* write to user buffer */	
	if(copy_to_user(ubuf,buf,len)) return -EFAULT;

	/* update file offset */
	*ppos = len;

	return len;
}


static struct proc_ops fops = {
	.proc_read = procfile_read,
};


static irq_handler_t gpio5_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs) {
	measure_mode += 1;
	mdelay(20);

	return (irq_handler_t) IRQ_HANDLED; 
}

static int gpio_irq_mod_init(void) {
	/* just for testing */
	power_mode = 1;
	measure_mode = 2;	


	proc_file=proc_create("mydev",0666,NULL,&fops);
	if(proc_file == NULL) {
		printk("gpio_irq.ko: Error creating /proc file\n");
		return -ENOMEM;
	}


	/* GPOI IRQ INIT SECTION */
	/* request gpio 5 */
	if(gpio_request(5, "rpi-gpio-5")) {
		printk("gpio_irq.ko: Error: failed to request GPIO 5\n");
		return -1;
	}

	/* Set GPIO 5 direction */
	if(gpio_direction_input(5)) {
		printk("gpio_irq.ko: Error: failed to set direction of GPIO 5\n");
		gpio_free(5);
		return -1;
	}

	/* Setup the interrupt */
	irq_number = gpio_to_irq(5);

	if(request_irq(irq_number, (irq_handler_t) gpio5_irq_handler, IRQF_TRIGGER_RISING, THIS_MODULE->name, NULL) != 0){
		printk("gpio_irq.ko: Error: failed to request IRQ for GPIO 5\n");
		gpio_free(5);
		return -1;
	}

	return 0;
}

static void gpio_irq_mod_exit(void)
{
	free_irq(irq_number, NULL);
	gpio_free(5);
	proc_remove(proc_file);
}

module_init(gpio_irq_mod_init);
module_exit(gpio_irq_mod_exit);
