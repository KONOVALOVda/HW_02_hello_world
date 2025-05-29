# Путь к исходникам ядра (может потребоваться изменить)
KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build
# Текущая директория с исходниками
PWD := $(shell pwd)

# Имя модуля
obj-m := hello_world.o

# Цель по умолчанию — сборка модуля
all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

# Форматирование кода (нужен clang-format)
format:
	clang-format -i hello_world.c

# Проверка работы модуля
check:
	@./check.sh || (echo "Check failed"; exit 1)

# Очистка собранных файлов
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean

.PHONY: all format check clean