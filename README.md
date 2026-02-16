# HW_02_hello_world
Для обучения модулей ядра 

В simple_hello_world есть примеры вывода 

<img width="445" height="170" alt="image" src="https://github.com/user-attachments/assets/748a5a3e-eec8-46e5-855c-2c5ff5724081" />


# Запуск
Сначала скачиваем заголовки ядра

sudo apt update && sudo apt install linux-headers-$(uname -r)


make // компилируем модуль


sudo dmesg -W // запуск мониторинга логов ядра


sudo insmod hello.ko // загрузить модуль


sudo rmmod hello.ko // выгрузить модуль
