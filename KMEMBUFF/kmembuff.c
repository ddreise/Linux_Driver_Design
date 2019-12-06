// kmembuff.c
//
// Purpose: for kernel memory buffer driver creation and usage
//
// Daniel Dreise
// December 2, 2019
//
// Credit: Scott Chen


// required for compiling kernel modules (drivers)
// with module.h and kernel.h, you CANNOT compile with just gcc!!
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

//required for using the file_operations struct to register the open/close/read/write routines
#include <linux/fs.h>

// Defines
#define BUF_SZ 128

// Global variables
char *pbuf;
const char buffer[BUF_SZ];

//Prototyping the routines so to prepare for assembling the file_operation struct
static int kmembuff_open(struct inode *inode, struct file *filep);
static int kmembuff_release(struct inode *inode, struct file *filep);
static ssize_t kmembuff_write(struct file *filep, const char *buf, size_t count, loff_t *f_pos);
static ssize_t kmembuff_read(struct file *filep, char *buf, size_t count, loff_t *f_pos);

//This is the file_operation struct defined in fs.h to enable registering the routines.
struct file_operations kmembuff_fops =
{
	owner:		THIS_MODULE,
	open:		kmembuff_open,
	release:	kmembuff_release,
	read:		kmembuff_read,
	write:		kmembuff_write,
};

//Driver Requirement 1: Module Initializer (Constuctor) Routine.  Called when the module is installed via "insmod" command
static int __init init_mod(void) 
{
	int result;

	//The mock character device is created by shell command "mknod -m 0666 /dev/kmembuff c 240 0"
	// where 240 is the MAJOR, and 0 is the MINOR designator numbers (specifying what type of 
	// character driver it is.
	// --> use "rm -f /dev/kmembuff" to remove device
	if((result = register_chrdev(240, "kmembuff", &kmembuff_fops)) < 0) 
	{
		printk(KERN_ALERT "Test Module FAILED to Start: %d... \n", result);
		return -1;
	}
	else
	{
		printk(KERN_INFO "Test Module Started: %d... \n", result);

		
		// Buffer memory allocation
		pbuf = kmalloc(BUF_SZ, GFP_KERNEL);
		if (!pbuf) 
		{
			printk(KERN_ALERT "Memory allocation FAILED\n");
			return -1;
		}
		else // If memory allocation successful
		{
			printk(KERN_INFO "Memory allocated\n");
		}
		
		return 0;
	}
}

//Driver Requirement 2: Module Remover (Destructor) Routine.  Called when the module is removed via "rmmod" command
static void __exit end_mod(void) //Module Destructor
{
	
	if (pbuf == NULL)
	{
		printk(KERN_ALERT "No allocated memory to free\n");
	}
	else
	{
		kfree(pbuf);
		printk(KERN_INFO "Successfully freed memory\n");
	}
	
	unregister_chrdev(240, "kmembuff");

	printk(KERN_ALERT "Test Module Ended... \n");
}

//Driver Requirement 3: Module Opener Routine.  Mapped to the native open() function call for opening the target device
static int kmembuff_open(struct inode *inode, struct file *filep) //Routine for opening the device
{
	printk(KERN_INFO "Device Opened... \n");

	//Clear buffer
	//strcpy((char*)pbuf, "");

	// Point buffer to allocated memory
	//pbuf = buffer;
	return 0;
}

//Driver Requirement 4: Module Releaser Routine.  Mapped to the native close() function call for releasing the target device
static int kmembuff_release(struct inode *inode, struct file *filep) //Routine for closing the device
{
	printk(KERN_INFO "Device Closed... \n");
	return 0;
}

//Driver Requirement 5: Module Write Routine.  Mapped to the native write() function call for sending data into the target device
static ssize_t kmembuff_write(struct file *filep, const char *buf, size_t count, loff_t *f_pos)
{
	
	int i;

	printk(KERN_INFO "Writing to the device: %s... \n", buf);
	
	for (i = 0; i < (BUF_SZ - 1); i++){
		pbuf[i] = buf[i];
	}
	pbuf[BUF_SZ] = '\n';
	

	// Write to buffer
	//sprintf(tmp, "This is a test");
	//strcat(buffer, tmp);	

	// Point buffer to allocated memory
	//pbuf = buffer;

	


	//write(filep, buf, count);
	
	return 1;
}

//Driver Requirement 6: Module Read Routine.  Mapped to the native read() function call for receiving data from the target device.
static ssize_t kmembuff_read(struct file *filep, char *buf, size_t count, loff_t *f_pos)
{
	//int curr_length;	
	
	printk(KERN_INFO "Reading from the device: %s... \n", buf);

	//curr_length = strlen(pbuf);

	// Send to user space from kernel
	//printk(KERN_INFO "Sending device data to user space...\n");
	//copy_to_user(buf, pbuf, curr_length);
	return 1;
}




//To register the constructor and destructor for this deiver module
module_init(init_mod);
module_exit(end_mod);


//Module Information
MODULE_LICENSE("GPL Only");
MODULE_AUTHOR("Daniel Dreise");
MODULE_DESCRIPTION("Kernel Memory Buffer Driver");
