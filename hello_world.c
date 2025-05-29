#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/stat.h>
#include <linux/string.h>

#define MAX_LEN 13 // Length of "Hello, World!" + null terminator

static char my_str[MAX_LEN] = "Hello, World!";
static unsigned int current_idx = 0;

// Параметры модуля
static unsigned int idx = 0;
static char ch_val = 0;

// Функция для отображения my_str
static int my_str_show(char *buffer, const struct kernel_param *kp)
{
    return scnprintf(buffer, PAGE_SIZE, "%s\n", my_str);
}

static const struct kernel_param_ops my_str_ops = {
    .get = my_str_show,
};

// Обработчик для параметра idx
static int set_idx(const char *val, const struct kernel_param *kp)
{
    int ret = param_set_uint(val, kp);
    if (ret)
        return ret;
    
    if (idx >= MAX_LEN - 1) {
        pr_err("Index %u out of range (0-%u)\n", idx, MAX_LEN - 2);
        return -EINVAL;
    }
    
    return 0;
}

static const struct kernel_param_ops idx_ops = {
    .set = set_idx,
    .get = param_get_uint,
};

// Обработчик для параметра ch_val
static int set_ch_val(const char *val, const struct kernel_param *kp)
{
    int ret = param_set_byte(val, kp);
    if (ret)
        return ret;
    
    if (ch_val < 32 || ch_val > 126) {
        pr_err("Invalid character 0x%02x\n", ch_val);
        return -EINVAL;
    }
    
    if (idx < MAX_LEN - 1) {
        my_str[idx] = ch_val;
        if (idx >= current_idx) {
            current_idx = idx + 1;
            my_str[current_idx] = '\0';
        }
    }
    
    return 0;
}

static const struct kernel_param_ops ch_val_ops = {
    .set = set_ch_val,
    .get = param_get_byte,
};

// Объявляем параметры модуля
module_param_cb(idx, &idx_ops, &idx, 0644);
MODULE_PARM_DESC(idx, "Index in the string (0-12)");

module_param_cb(ch_val, &ch_val_ops, &ch_val, 0644);
MODULE_PARM_DESC(ch_val, "ASCII character to write (32-126)");

module_param_cb(my_str, &my_str_ops, NULL, 0444);
MODULE_PARM_DESC(my_str, "The constructed string (read-only)");

// Инициализация и завершение работы модуля
static int __init hello_init(void)
{
    pr_info("init\n");
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OldALoneFag");
MODULE_DESCRIPTION("A kernel module that builds 'Hello, World!' character by character");