#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <unistd.h> //write fonkk için
#include <stdarg.h> //argümanların kütüphanesi

int ft_printf(const char *format, ...);
int ft_format(va_list *arg, char format);
int ft_check(char str);
int ft_putchar(char c);
int ft_string(char *str);
int ft_int(int number);
int ft_unsigned(unsigned int number);
int ft_hex(unsigned int number , char format);
int ft_point(unsigned long int number, int mod);



#endif
