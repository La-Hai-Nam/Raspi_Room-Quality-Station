#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <asm/delay.h> 
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/jiffies.h>


#define PROC_BUFFER_SIZE 255 

/* debounce time in ms */
#define DBNC_TIME 200


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maximilian Lausch, Htw-Berlin");

/* for measureing time (clock cycles) */
extern unsigned long volatile jiffies;
unsigned long old_jiffie = 0;

/* on / off information */
static int power_mode;

/* mode information (temperature, pressure, ...) */
static int measure_mode;


static struct proc_dir_entry *proc_file;
unsigned int irq_number_gpio_5;
unsigned int irq_number_gpio_6;


/* @brief This functionis called when the user wants to read the procfile
*
*  Writes the measurement mode number into the userbuffer
*
*  @return bytes written
*/
static ssize_t procfile_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos) 
{
	char buf[PROC_BUFFER_SIZE];
	int len = sprintf(buf,"%d", measure_mode);

	if(len >= PROC_BUFFER_SIZE) {
		printk("len bigger than max size \n");
		return -1;
	}

	printk("proc_read: %s\n", buf);


	/* write to the user buffer */
	if(*ppos >= len || copy_to_user(ubuf,buf,len)) {
		printk("copy_to_user failed\n");
		return 0;
	} 

	/* write to user buffer */	
//	if(copy_to_user(ubuf,buf,len)) {
//		printk("error writing to userbuffer \n");
//		return -EFAULT;
//	}

	/* update file offset */
	*ppos += len;

	return (ssize_t)len;
}

/* @breif This function is called when the user writes to the procfile
*
*  Get measurement mode number form userbuffer.
*
*  @return bytes read
*/
static ssize_t procfile_write(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos) {
	/* buffer that stores the content written to us */
	char buf[PROC_BUFFER_SIZE];
	long mes_test;

	/* check if we can write to buffer */
//	if(*ppos > 0 || count > PROC_BUFFER_SIZE) return -EFAULT;
	if(count > PROC_BUFFER_SIZE) {
		count = PROC_BUFFER_SIZE;
	}

	/* copy from user buffer into our buffer*/
	if(copy_from_user(buf,ubuf,count)) {
		printk("copy_from_user failed \n");
		return -EFAULT;
	}
	buf[count] = '\0';


	/* convert to int */
	if(kstrtol(buf, 10, &mes_test) != 0 ) {
		printk("kstrtol error\n");
	}

	printk("%d bytes written to me: %ld\n", count, mes_test);
	/* update measurement mode */
	measure_mode = (int)mes_test;
	
	*ppos += count;
	return (ssize_t)count;
}

/* @brief This function is called when lseek() is called on the filedescriptor
*
*  Changes the fileoffset
*
*  @return new offset
*/
static loff_t procfile_lseek(struct file *file, loff_t offset, int whence) {
	file->f_pos = offset;
	return offset;
}


/* holds the procfile operations */
static struct proc_ops fops = {
	.proc_read = procfile_read,
	.proc_write = procfile_write,
	.proc_lseek = procfile_lseek
};



/* @brief GPIO5 interrupt handler callback function
*
*  GPIO5 = Mode change button
*  Updates the measurement mode variable.
*  Debounces the button.
*/
static irq_handler_t gpio5_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs) {	
	static unsigned long flags = 0;
	
	/* for debouncing 
	* if we enter the interrupt handler again before the debounce period
	* is not over, we do nothing */
	if(jiffies - old_jiffie < DBNC_TIME) {
		return (irq_handler_t) IRQ_HANDLED;
	}

	old_jiffie = jiffies;
	
	local_irq_save(flags);

	printk("gpio 5 interrupt %d\n", measure_mode);
	measure_mode += 1;
	if(measure_mode >= 5) {
		measure_mode = 1;
	}

	local_irq_restore(flags);

	return (irq_handler_t) IRQ_HANDLED; 
}


/* @brief GPIO6 interrup handler callback function
*
*  GPIO6 = on/off button.
*  Updates power mode and measurement mode variable.
*  Debounces the button.
*/
static irq_handler_t gpio6_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs) {	
	static unsigned long flags = 0;

	/* for debouncing 
	* if we enter the interrupt handler again before the debounce period
	* is not over, we do nothing */
	if(jiffies - old_jiffie < DBNC_TIME) {
		return (irq_handler_t) IRQ_HANDLED;
	}

	old_jiffie = jiffies;
	
	local_irq_save(flags);

	printk("gpio 6 interrupt %d\n", power_mode);
	if(power_mode == 0) {
		measure_mode = 0;
		power_mode = 1;
	}			
	else if(power_mode == 1) {
		measure_mode = 5;
	}

	local_irq_restore(flags);

	return (irq_handler_t) IRQ_HANDLED; 
}


/* @brief This function is called when the module is inserted / initilized
* 
*  Creates the procfile.
*  Sets up the gpios and gpio interrupts.
*
*/
static int gpio_irq_mod_init(void) {
	/* set power_mode to off */
	power_mode = 0;
	/* set measure mode to uninitilized */
	measure_mode = -1;

	
	/* create procfile */
	proc_file=proc_create("mydev",0777,NULL,&fops);
	if(proc_file == NULL) {
		printk("gpio_irq.ko: Error creating /proc file\n");
		return -ENOMEM;
	}


	/************************* GPOI IRQ INIT SECTION ******************************/
	/* request gpio 5 */
	if(gpio_request(5, "rpi-gpio-5")) {
		printk("gpio_irq.ko: Error: failed to request GPIO 5\n");
		return -1;
	}

	/* request gpio 6 */
	if(gpio_request(6, "rpi-gpio-6")) {
		printk("gpio_irq.ko: Error: failed to request GPIO 6\n");
		return -1;
	}

	/* Set GPIO 5 direction */
	if(gpio_direction_input(5)) {
		printk("gpio_irq.ko: Error: failed to set direction of GPIO 5\n");
		gpio_free(5);
		return -1;
	}

	/* set gpio 6 direction */
	if(gpio_direction_input(6)) {
		printk("gpio_irq.ko: Error: failed to set direction of GPIO 6\n");
		gpio_free(6);
		return -1;
	}

	/* Setup the interrupt for gpio 5*/
	irq_number_gpio_5 = gpio_to_irq(5);

	if(request_irq(irq_number_gpio_5, (irq_handler_t) gpio5_irq_handler, IRQF_TRIGGER_RISING, THIS_MODULE->name, NULL) != 0){
		printk("gpio_irq.ko: Error: failed to request IRQ for GPIO 5\n");
		gpio_free(5);
		return -1;
	}

	/* Setup the interrupt for gpio 6*/
	irq_number_gpio_6 = gpio_to_irq(6);

	if(request_irq(irq_number_gpio_6, (irq_handler_t) gpio6_irq_handler, IRQF_TRIGGER_RISING, THIS_MODULE->name, NULL) != 0){
		printk("gpio_irq.ko: Error: failed to request IRQ for GPIO 6\n");
		gpio_free(6);
		return -1;
	}
	return 0;
}

/* @brief This function is called when the module gets removed
*
*  frees all recources.
*/
static void gpio_irq_mod_exit(void)
{
	free_irq(irq_number_gpio_5, NULL);
	free_irq(irq_number_gpio_6, NULL);
	gpio_free(5);
	gpio_free(6);
	proc_remove(proc_file);
}

module_init(gpio_irq_mod_init);
module_exit(gpio_irq_mod_exit);


//#include <linux/module.h>
//#include <linux/init.h>
//#include <linux/kernel.h>   
//#include <linux/proc_fs.h>
//#include <asm/uaccess.h>
//#include <asm/delay.h> 
//#include <linux/delay.h>
//#include <linux/gpio.h>
//#include <linux/interrupt.h>
//#include <linux/jiffies.h>
//#include <linux/minmax.h>
//
//#define PROC_BUFFER_SIZE 255 
//
///* debounce time in ms */
//#define DBNC_TIME 200
//
//
//MODULE_LICENSE("GPL");
//MODULE_AUTHOR("Maximilian Lausch, Htw-Berlin");
//
//
//extern unsigned long volatile jiffies;
//unsigned long old_jiffie = 0;
//
//static int power_mode;
//static int measure_mode;
//static struct proc_dir_entry *proc_file;
//unsigned int irq_number_gpio_5;
//unsigned int irq_number_gpio_6;
//
//
//static ssize_t procfile_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos) 
//{
//	char buf[PROC_BUFFER_SIZE];
//	size_t len = sprintf(buf,"%d", measure_mode);
//	int to_copy, not_copied;
//
//	if(len >= PROC_BUFFER_SIZE) {
//		printk("len bigger than max size \n");
//		return -1;
//	}
//
//	printk("proc_read: %s\n", buf);
//
//
//	to_copy = min(count, len);
//	not_copied=copy_to_user(ubuf, buf, to_copy);
//	if(not_copied != 0) {
//		printk("%d bytes not copied\n", not_copied);	
//	}
//
//	
//
//	/* write to the user buffer */
//	//if(*ppos >= len || copy_to_user(ubuf,buf,len)) {
//	//	printk("copy_to_user failed \n");
//	//	return 0;
//	//} 
//
//	/* write to user buffer */	
////	if(copy_to_user(ubuf,buf,len)) {
////		printk("error writing to userbuffer \n");
////		return -EFAULT;
////	}
//
//	/* update file offset */
//	//*ppos += len;
//
//	//return (ssize_t)len;
//	return (to_copy-not_copied);
//}
//
//static ssize_t procfile_write(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos) {
//	/* buffer that stores the content written to us */
//	char buf[PROC_BUFFER_SIZE];
//	long mes_test;
//
//	/* check if we can write to buffer */
////	if(*ppos > 0 || count > PROC_BUFFER_SIZE) return -EFAULT;
//	if(count > PROC_BUFFER_SIZE) {
//		count = PROC_BUFFER_SIZE;
//	}
//
//	/* copy from user buffer into our buffer*/
//	if(copy_from_user(buf,ubuf,count)) {
//		printk("copy_from_user failed \n");
//		return -EFAULT;
//	}
//	buf[count] = '\0';
//
//
//	if(kstrtol(buf, 10, &mes_test) != 0 ) {
//		printk("kstrtol error\n");
//	}
//
//	printk("%d bytes written to me: %ld\n", count, mes_test);
//	measure_mode = (int)mes_test;
//	
//	*ppos += count;
//	return (ssize_t)count;
//}
//
//static loff_t procfile_lseek(struct file *file, loff_t offset, int whence) {
//	file->f_pos = offset;
//	return 0;
//}
//
//
//static struct proc_ops fops = {
//	.proc_read = procfile_read,
//	.proc_write = procfile_write,
//	.proc_lseek = procfile_lseek
//};
//
//
//
//static irq_handler_t gpio5_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs) {	
//	static unsigned long flags = 0;
//	
//	if(jiffies - old_jiffie < DBNC_TIME) {
//		return (irq_handler_t) IRQ_HANDLED;
//	}
//
//	old_jiffie = jiffies;
//	
//	local_irq_save(flags);
//
//	printk("gpio 5 interrupt %d\n", measure_mode);
//	measure_mode += 1;
//	if(measure_mode > 5) {
//		measure_mode = 2;
//	}
//
//	local_irq_restore(flags);
//
//	return (irq_handler_t) IRQ_HANDLED; 
//}
//
//static irq_handler_t gpio6_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs) {	
//	static unsigned long flags = 0;
//	
//	if(jiffies - old_jiffie < DBNC_TIME) {
//		return (irq_handler_t) IRQ_HANDLED;
//	}
//
//	old_jiffie = jiffies;
//	
//	local_irq_save(flags);
//
//	printk("gpio 6 interrupt %d\n", power_mode);
////	if(power_mode == 0) {
////		measure_mode = 0;
////		power_mode = 1;
////	}			
////	else if(power_mode == 1) {
////		measure_mode = 5;
////	}
//	
//	measure_mode = 6;
//
//	local_irq_restore(flags);
//
//	return (irq_handler_t) IRQ_HANDLED; 
//}
//
//static int gpio_irq_mod_init(void) {
//	/* set power_mode to off */
//	power_mode = 0;
//	/* set measure mode to uninitilized */
//	measure_mode = 0;
//
//
//	proc_file=proc_create("mydev",0777,NULL,&fops);
//	if(proc_file == NULL) {
//		printk("gpio_irq.ko: Error creating /proc file\n");
//		return -ENOMEM;
//	}
//
//
//	/* GPOI IRQ INIT SECTION */
//	/* request gpio 5 */
//	if(gpio_request(5, "rpi-gpio-5")) {
//		printk("gpio_irq.ko: Error: failed to request GPIO 5\n");
//		return -1;
//	}
//
//	/* request gpio 6 */
//	if(gpio_request(6, "rpi-gpio-6")) {
//		printk("gpio_irq.ko: Error: failed to request GPIO 6\n");
//		return -1;
//	}
//
//	/* Set GPIO 5 direction */
//	if(gpio_direction_input(5)) {
//		printk("gpio_irq.ko: Error: failed to set direction of GPIO 5\n");
//		gpio_free(5);
//		return -1;
//	}
//
//	/* set gpio 6 direction */
//	if(gpio_direction_input(6)) {
//		printk("gpio_irq.ko: Error: failed to set direction of GPIO 6\n");
//		gpio_free(6);
//		return -1;
//	}
//
//	/* Setup the interrupt for gpio 5*/
//	irq_number_gpio_5 = gpio_to_irq(5);
//
//	if(request_irq(irq_number_gpio_5, (irq_handler_t) gpio5_irq_handler, IRQF_TRIGGER_RISING, THIS_MODULE->name, NULL) != 0){
//		printk("gpio_irq.ko: Error: failed to request IRQ for GPIO 5\n");
//		gpio_free(5);
//		return -1;
//	}
//
//	/* Setup the interrupt for gpio 6*/
//	irq_number_gpio_6 = gpio_to_irq(6);
//
//	if(request_irq(irq_number_gpio_6, (irq_handler_t) gpio6_irq_handler, IRQF_TRIGGER_RISING, THIS_MODULE->name, NULL) != 0){
//		printk("gpio_irq.ko: Error: failed to request IRQ for GPIO 6\n");
//		gpio_free(6);
//		return -1;
//	}
//	return 0;
//}
//
//static void gpio_irq_mod_exit(void)
//{
//	free_irq(irq_number_gpio_5, NULL);
//	free_irq(irq_number_gpio_6, NULL);
//	gpio_free(5);
//	gpio_free(6);
//	proc_remove(proc_file);
//}
//
//module_init(gpio_irq_mod_init);
//module_exit(gpio_irq_mod_exit);
