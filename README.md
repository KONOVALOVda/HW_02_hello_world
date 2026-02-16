# HW_02_hello_world
Для обучения модулей ядра 

Сначала скачиваем заголовки ядра

sudo apt update
sudo apt install linux-headers-$(uname -r)

// компилируем модуль
make

// запуск мониторинга логов ядра
sudo dmesg -W

// загрузить модуль
sudo insmod hello.ko

// выгрузить модуль
sudo rmmod hello.ko
