// SPDX-License-Identifier: GPL-2-Clause
#include <hello1.h>

MODULE_AUTHOR("IO-11 Столярчук Микола");
MODULE_DESCRIPTION("Лабораторна робота 4");
MODULE_LICENSE("GPL");

static uint amount = 1; 

module_param(amount, uint, 0);
MODULE_PARM_DESC(amount, "Кількість виконань для лабораторної роботи 4\n"); 

static int __init initialize_hello_module(void) 
{
    pr_info("Модуль hello2 ініціалізується\n"); 
    print_hello(amount); 
    return 0;
}

static void __exit finalize_hello_module(void) 
{
    pr_info("Модуль hello2 завершується\n");
}

module_init(initialize_hello_module);
module_exit(finalize_hello_module);

