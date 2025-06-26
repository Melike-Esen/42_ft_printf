/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meesen <meesen@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:24:47 by meesen            #+#    #+#             */
/*   Updated: 2025/06/26 23:54:47 by meesen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Tek bir karakteri yazdırır, yazdırılan karakter sayısını döner.
int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

// Format karakterinin desteklenenlerden biri olup olmadığını kontrol eder.
int ft_check(char str)
{
    return (str == 'c' || str == 's' || str == 'p' || str == 'd' ||
            str == 'i' || str == 'u' || str == 'x' || str == 'X' ||
            str == '%');
}

// Karakter % olarak geldiğinde bir sonraki karakter kontrol edilir,bir sonraki karakteri de desteklemesi için ft_check döngüsü kuruyoruz.
//Desteledikten sonra da ft_format döngüsüne giriliyor. Buradaki va_arg sayesinde değişken argüman listesinden uygun türü çekip yazdırma yapıyor.
//Desteklemezse null döner.
int ft_format(va_list *argv, char format)
{
    if (format == 'c')
        return (ft_putchar(va_arg(*argv, int))); //tek karakter

    else if (format == 's')
        return (ft_string(va_arg(*argv, char *))); // string yani karakter dizisi

    else if (format == 'p')
        return (ft_point(va_arg(*argv, unsigned long), 1)); // işaretci adres

    else if (format == 'd' || format == 'i') // işrateli tam sayılar
        return (ft_int(va_arg(*argv, int)));

    else if (format == 'u')
        return (ft_unsigned(va_arg(*argv, unsigned int))); //işaretsiz tam sayılarda küçük harflerle 16'lık 

    else if (format == 'x' || format == 'X')
        return (ft_hex(va_arg(*argv, unsigned int), format)); //aynısı sadece bu sefer harfler büyük

    else if (format == '%')
        return (ft_putchar('%')); // yüzde işaretini yazdırıyorum

    return (0);  // Bu satır fonksiyon sonunda olmalı
}

int ft_printf(const char *format, ...) //yazdırılacak değer format, ... ise değişken sayıda argüman alabilmesidir.
{
    int i; //format str de gezmek için
    int len; // yazdırılan str toplam uzunluk
    int count; //her formatlı argv dönen karakter sayı
    va_list argv; //va_list türünde değişken argüman listemiz

    i = 0;
    len = 0;
    va_start(argv, format); //değişken argümanları saymaya başlıyoruz.
    while (format[i]) //format i'nin sonuna kadar gidicez
    {
        if (format[i] == '%' && ft_check(format[i + 1])) //% karakterimiz varsa ve ardından desteklenen karakter gelirse
        {
            i++; // format karakterini alıyoruz x,X,c,s vs...
            count = ft_format(&argv, format[i]); //değişken argümanlardan uygun türde olanı çek ve yazdır
            if (count == -1) //hata var, the end
            {
                va_end(argv); //çekilecek argüman listesini temize
                return (-1); //the end
            }
            len += count; // yazdırılan karakter sayısını ekle
        }
        else // % olmama durumunda
        {
            if (ft_putchar(format[i]) == -1) // hata var the end
            {
                va_end(argv); //değişken argüman liste temizle
                return (-1);
            }
            len++; //toplam karakter sayısı artar
        }
        i++; // döngü index artar
    }
    va_end(argv); //list argv tenizle
    return (len); //toplam yazdırılan karakter sayısını döndür
}

// Test için main fonksiyonu
int main(void)
{
    ft_printf("%s\n", "melike esen");
    ft_printf("Char: %c, Dec: %d, Hex: %x, Pointer: %p\n", 'A', 1234, 0xABCD, &main);
    return (0);
}
