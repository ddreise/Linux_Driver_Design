//required for compiling kernel modules (drivers)
//with module.h and kernel.h, you CANNOT compile with just gcc!!
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

//required for using the file_operations struct to register the open/close/read/write routines
#include <linux/fs.h>

//Prototyping the routines so to prepare for assembling the file_operation struct
static int mydev_open(struct inode *inode, struct file *filep);
static int mydev_release(struct inode *inode, struct file *filep);
static ssize_t mydev_write(struct file *filep, const char *buf, size_t count, loff_t *f_pos);
static ssize_t mydev_read(struct file *filep, char *buf, size_t count, loff_t *f_pos);

//This is the file_operation struct defined in fs.h to enable registering the routines.
struct file_operations mydev_fops =
{
	owner:		THIS_MODULE,
	open:		mydev_open,
	release:	mydev_release,
	read:		mydev_read,
	write:		mydev_write,
};

//Driver Requirement 1: Module Initializer (Constuctor) Routine.  Called when the module is installed via "insmod" command
static int __init init_mod(void) 
{
	int result;

	//The mock character device is created by shell command "mknod -m 0666 /dev/mydev c 240 0"
	if((result = register_chrdev(240, "mydev", &mydev_fops)) < 0) 
	{
		printk(KERN_ALERT "Test Module FAILED to Start: %d... \n", result);
		return -1;
	}
	else
	{
		printk(KERN_INFO "Test Module Started: %d... \n", result);
		return 0;
	}
}

//Driver Requirement 2: Module Remover (Destructor) Routine.  Called when the module is removed via "rmmod" command
static void __exit end_mod(void) //Module Destructor
{
	unregister_chrdev(240, "mydev");
	printk(KERN_ALERT "Test Module Ended... \n");
}

//Driver Requirement 3: Module Opener Routine.  Mapped to the native open() function call for opening the target device
static int mydev_open(struct inode *inode, struct file *filep) //Routine for opening the device
{
	printk(KERN_INFO "Device Opened... \n");
	return 0;
}

//Driver Requirement 4: Module Releaser Routine.  Mapped to the native close() function call for releasing the target device
static int mydev_release(struct inode *inode, struct file *filep) //Routine for closing the device
{
	printk(KERN_INFO "Device Closed... \n");
	return 0;
}

//Driver Requirement 5: Module Write Routine.  Mapped to the native write() function call for sending data into the target device
static ssize_t mydev_write(struct file *filep, const char *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_INFO "Writing to the device: %s... \n", buf);
	return 1;
}

//Driver Requirement 6: Module Read Routine.  Mapped to the native read() function call for receiving data from the target device.
static ssize_t mydev_read(struct file *filep, char *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_INFO "Reading from the device: %s... \n", buf);
	return 1;
}




//To register the constructor and destructor for this deiver module
module_init(init_mod);
module_exit(end_mod);


//Module Information
MODULE_LICENSE("GPL Only");
MODULE_AUTHOR("Scott Chen");
MODULE_DESCRIPTION("Test Driver Module");
