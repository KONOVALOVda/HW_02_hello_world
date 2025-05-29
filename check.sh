#!/bin/bash

MODULE="hello_world"

# Проверка загрузки модуля
echo "Testing module $MODULE..."

# Загружаем модуль
sudo insmod $MODULE.ko || { echo "Failed to load module"; exit 1; }

# Проверяем сообщение в dmesg
if ! dmesg | grep -q "$MODULE: init"; then
    echo "Init message not found"
    sudo rmmod $MODULE
    exit 1
fi

# Проверяем параметры
SYSFS_PATH="/sys/module/$MODULE/parameters"
if [ ! -f "$SYSFS_PATH/idx" ] || [ ! -f "$SYSFS_PATH/ch_val" ] || [ ! -f "$SYSFS_PATH/my_str" ]; then
    echo "Parameters not found"
    sudo rmmod $MODULE
    exit 1
fi

# Проверяем, что my_str read-only
if sudo sh -c "echo 'test' > $SYSFS_PATH/my_str" 2>/dev/null; then
    echo "my_str is not read-only"
    sudo rmmod $MODULE
    exit 1
fi

# Выгружаем модуль
sudo rmmod $MODULE || { echo "Failed to unload module"; exit 1; }

# Проверяем сообщение выгрузки
if ! dmesg | grep -q "$MODULE: exit"; then
    echo "Exit message not found"
    exit 1
fi

echo "All tests passed!"
exit 0