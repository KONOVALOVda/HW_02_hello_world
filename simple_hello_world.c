#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void)
{
	printk("hello - Hello, Kernel!\n");  // \n - обязательно!
  pr_info("hello - but with log!\n"); 
  pr_err("hellooo!\n"); 
  pr_emerg("hellooo!\n"); 
  pr_alert("hellooo!\n"); 
  pr_crit("hellooo!\n"); 
  pr_err("hellooo!\n"); 
  pr_warn("hellooo!\n"); 
  pr_notice("hellooo!\n"); 
  pr_debug("hellooo!\n"); 
	return 0;
}

static void __exit my_exit(void)
{
	printk("hello - Goodbye, Kernel!\n"); // \n - обязательно!
  
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KonovalovDA");
MODULE_DESCRIPTION("A simple Hello World Linux Kernel Module for learn");
