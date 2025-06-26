/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_darg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meesen <meesen@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:16:47 by meesen            #+#    #+#             */
/*   Updated: 2025/06/27 00:25:57 by meesen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_int(int number) //amaç int sayı yazdırmak
{
    int len;
    int count;

    len = 0; //yazdırılacak karakter sayısını başlatıyoruz
    if (number == 0)
        return (ft_putchar('0')); //sayı 0 = 0
    if (number == -2147483648)
        return (ft_string("-2147483648")); //INT_MIN özel direkt çıktı ver
    if (number < 0) // number negatifse
    {
        if (ft_putchar('-') == -1) // önce - yaz
            return (-1);           // yazdırmazsa hata dön 
        len++;                     // - için uzunluğur arttır   
        number *= -1;              // -*- = + ||  +*+= + -->mutlak değer
    }
    if (number >= 10) //10'dan büyükse birden fazla basamak vardır
    {
        count = ft_int(number / 10); // ondalık en yüksek basamak değerini yazdırmak için çağır
        if (count == -1) // çıktı vermezse hata
            return (-1);
        len += count; // yazdırılan karakter sayısını len ekle
    }
    if (ft_putchar("0123456789"[number % 10]) == -1) //son basamağı yazdırmaya başla, 0-9 arasında gez
        return (-1); //hata
    return (len + 1); // len= önceki basamakların sayısı +1 ise en son yazdırdığı karakterin sayısıdır, toplam yazdırılan karakter
}

int ft_unsigned(unsigned int number)
{
    int len; //yazdırılan karakter sayısı 
    int count; // karakter sayısı
    char *arr; //rakamların yerini tutan karakter dizimiz

    arr = "0123456789"; //onluk tabandaki rakamları atadık
    len = 0;
    if (number >= 10) //10'dan büyükse,önce daha yüksek basamakları yazdır
    {
        count = ft_unsigned(number / 10); //sayıyı 10'a böl en yüksek basamağı yazdır
        if (count == -1) //hat
            return (-1);
        len += count; // yazdırılan karakter sayısını len ekle
    }
    if (ft_putchar(arr[number % 10]) == -1) //son basamağa geldik , sayının modunu al ve çıkar eğer hata varsa -1
        return (-1); //hata
    return (len + 1); //Toplam karakter sayısı ,unutmayın arkadaşlar +1 son basamağın çıktısını bize verir çünkü dikkat ederseniz son basamakta yazdırğım countu len dizisimne eklemiyorum return ederek eklemiş oluyorum.
}

int ft_string(char *str) //strint (char *) olarak yazdırıyoryuz
{
    int i;

    i = 0;
    if (str == NULL) //stringim  içi boşsa null
        return (ft_string("(null)")); //null
    while (str[i]) // string null olana kadar devam
    {
        if (ft_putchar(str[i]) == -1) //her karakteri ekrana yazdır hata varsa -1
            return (-1); //hata 
        i++; //sonraki karaktere geç
    }
    return (i); //toplam yazdırdığımız karakter sayım döner,arkada decimal çıktı da string :)
}

int ft_hex(unsigned int number, char format)  //sayıyı hexadecimal (16'lık ) sistemde yazdırma
{
    int len; //yazdırılan karakter uzunluğu 
    int count; //recursive çağrılarda gelen uzunluk

    len = 0;
    if (number >= 16) // 16dan büyükse basamakları bölerek yazdır
    {
        count = ft_hex(number / 16, format); //sayının üst basamağını yaz
        if (count == -1) //hata
            return (-1);
        len += count; //yazdırılan karakteri len'e ekle || basılan karakteri say
    }
    if (format == 'X') //Büyük harf hexadecimal için fonk
    {
        if (ft_putchar("0123456789ABCDEF"[number % 16]) == -1) //16lık sistemde modunu al, hata varsa -1
            return (-1);// hata 
    }
    else if (format == 'x') // küçük harfli hexademicel
    {
        if (ft_putchar("0123456789abcdef"[number % 16]) == -1) //16'lık (0-9 --> 10 karakter, a-f --> 6 karakter,işletim sistemi 16lık için bunu kabul ediyor.) sistemde modunu al
            return (-1); //hata
    }
    else
        return (-1); //format geçersize -1
    return (len + 1); //yazdırılan basamak + son basamak çıktısı
}

int ft_point(unsigned long int number, int mod)
{
    int len; //karakter uzunluğı
    int count; //karakter sayısı

    len = 0;
    if (mod == 1) // ilk çağrılışta  "0x" yazdırmak için
    {
        if (ft_string("0x") == -1) // gelmezse -1
            return (-1);
        len += 2; // 0 , x iki karakter onları ekliyorum   
        mod = 0; //sonraki çağrılarda tekrar "0x" yazdırmasın diye sıfırladım
       
    }
    if (number >= 16) //sayıyı 16lık sistemde parçala&yaz
    {
        count = ft_point(number / 16, mod); //16 sisteme göre bölmeye başla (en yüksek basamaktan başlıyoruz!!)
        if (count == -1) //hata!!
            return (-1);
        len += count; // karakter sayısını len ekle
    }
    if (ft_putchar("0123456789abcdef"[number % 16]) == -1) //son basamağı 16lık sistemde modunu al hata verirse -1
        return (-1);
    return (len + 1); //toplam basamak değeri = len(karakter sayılar) + son basamak
}
