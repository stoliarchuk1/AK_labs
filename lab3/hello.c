#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("IO-11 Столярчук Микола");
MODULE_DESCRIPTION("Лабораторна робота 3");
MODULE_LICENSE("GPL");

static uint amount = 1;
module_param(amount, uint, 0664); 
MODULE_PARM_DESC(amount, "Кількість записів для обробки");

struct custom_data {
  struct list_head node;
  ktime_t time_stamp;
};

static LIST_HEAD(custom_list_head);

static int __init custom_init_function(void) 
{
  int counter;
  
  if (amount == 0) {
    pr_warn("amount дорівнює нулю\n"); 
  } else if (amount > 10) {
    pr_warn("amount більше ніж 10, встановлено максимальний ліміт\n");
    amount = 10;
  }

  for (counter = 0; counter < amount; counter++) { 
    struct custom_data *item = kmalloc(sizeof(struct custom_data), GFP_KERNEL);
    if (!item) {
      pr_err("Помилка виділення пам'яті\n");
      return -ENOMEM;
    }
    item->time_stamp = ktime_get();
    list_add_tail(&item->node, &custom_list_head);
    pr_info("Hello, world! %d\n", counter);
  }

  return 0;
}

static void __exit custom_exit_function(void) 
{
  struct custom_data *entry, *temp;
  int index = 0; 

  list_for_each_entry_safe(entry, temp, &custom_list_head, node) {
    pr_info("Запис %d; Часова мітка = %lld\n", index++, ktime_to_ns(entry->time_stamp));
    list_del(&entry->node);
    kfree(entry);
  }
  pr_info("Модуль успішно видалено\n");
}

module_init(custom_init_function);
module_exit(custom_exit_function);

