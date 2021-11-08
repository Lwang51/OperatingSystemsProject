#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday {	
	int month;
	int day;
	int year;
	char *name;
	struct list_head list;
};


//The following defines and initializes a list_head object named birthday_list
static LIST_HEAD(birthday_list);

int simple_init(void) {
	struct birthday *ptr;	//for list traversal
	
	// Create a linked list containing five struct birthday elements
	// NOTE:THE NAME OF FIRST STRUCT BIRTHDAY SHOULD BE YOUR OWN NAME     
	struct birthday *Landon;
	struct birthday *Lin;
	struct birthday *YaoRong;
	struct birthday *Brandson;
	struct birthday *Monica;
    
	Landon = kmalloc(sizeof(*Landon), GFP_KERNEL);
	Landon -> name = "Landon";
	Landon -> day = 14;
	Landon -> month = 02;
	Landon -> year = 2000;
	INIT_LIST_HEAD(&Landon -> list);
    
	Lin = kmalloc(sizeof(*Lin), GFP_KERNEL);
	Lin -> name = "Lin   ";
	Lin -> day = 25;
	Lin -> month = 08;
	Lin -> year = 1999;
	INIT_LIST_HEAD(&Lin -> list);
    
	YaoRong = kmalloc(sizeof(*YaoRong), GFP_KERNEL);
	YaoRong -> name = "YaoRong";
	YaoRong -> day = 08;
	YaoRong -> month = 02;
	YaoRong -> year = 1994;
	INIT_LIST_HEAD(&YaoRong -> list);
    
	Brandson = kmalloc(sizeof(*Brandson), GFP_KERNEL);
	Brandson -> name = "Brandson";
	Brandson -> day = 07;
	Brandson -> month = 23;
	Brandson -> year = 2000;
	INIT_LIST_HEAD(&Brandson -> list);
    
	Monica = kmalloc(sizeof(*Monica), GFP_KERNEL);
	Monica -> name = "Monica";
	Monica -> day = 08;
	Monica -> month = 09;
	Monica -> year = 1992;
	INIT_LIST_HEAD(&Monica -> list);
	
	list_add_tail(&Lin -> list, &birthday_list);
	list_add_tail(&Landon -> list, &birthday_list);
	list_add_tail(&YaoRong -> list, &birthday_list);
	list_add_tail(&Brandson -> list, &birthday_list);
	list_add_tail(&Monica -> list, &birthday_list);
	
	printk(KERN_INFO "Loading Module\n");
	
	/* Traverse the linked list  */
	list_for_each_entry(ptr, &birthday_list, list) {
		printk("Name: %s \t Birthday: %d %d %d", ptr -> name, ptr -> month, ptr -> day, ptr -> year);
	}
	 
	return 0;
}

void simple_exit(void) {
	/* Remove the elements from the linked list and return the free memory back to the kernel */
	struct birthday *ptr, *next;
	
	printk(KERN_INFO "Cleaning and exiting module\n");
	
	list_for_each_entry_safe(ptr, next, &birthday_list, list) {
		//on each iteration ptr points to the next birthday struct
		printk("Removing: %s", ptr -> name);
		list_del(&ptr -> list);
		kfree(ptr);
	}
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Data Structures");
MODULE_AUTHOR("GSU_CSC4320_6320_TH_Fall2021");
