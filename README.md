# HW_02_hello_world
Для обучения модулей ядра 

Сначала скачиваем заголовки ядра

sudo apt update && sudo apt install linux-headers-$(uname -r)


make // компилируем модуль


sudo dmesg -W // запуск мониторинга логов ядра


sudo insmod hello.ko // загрузить модуль


sudo rmmod hello.ko // выгрузить модуль
