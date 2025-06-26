# 42_ft_printf

## Proje Hakkında

Bu proje, C dilinde standart `printf` fonksiyonunun temel işleyişini anlamak ve kendi `ft_printf` fonksiyonumuzu yazmak amacıyla hazırlanmıştır. 

Desteklenen format belirteçleri:
- `%c` : Tek karakter
- `%s` : String
- `%p` : Pointer (adres)
- `%d`, `%i` : İşaretli tam sayı
- `%u` : İşaretsiz tam sayı
- `%x`, `%X` : Onaltılık sayı (küçük/büyük harf)
- `%%` : Yüzde işareti

---

## Proje Mantığı

- `ft_printf` fonksiyonu, aldığı format string üzerinde karakter karakter ilerler.
- `%` karakterini gördüğünde bir sonraki karakterin geçerli bir format belirteci olup olmadığını kontrol eder.
- Eğer geçerliyse, `va_list` kullanarak ilgili argümanı uygun tipte alır.
- Alınan argüman, tipiyle uyumlu yardımcı fonksiyona (`ft_int`, `ft_string`, `ft_hex` vb.) gönderilir.
- Yardımcı fonksiyonlar argümanı `write` fonksiyonuyla ekrana yazdırır ve yazdırılan karakter sayısını döner.
- `ft_printf` tüm yazdırılan karakterlerin toplam sayısını döner.

---

## Değişken Argümanlar (Variadic Functions)

`ft_printf`’in değişken sayıda argüman almasını sağlayan temel yapı `stdarg.h` kütüphanesindedir. Burada kullanılan makrolar:

- `va_list argv;`  
  Değişken argümanları tutan yapı.

- `va_start(argv, format);`  
  Değişken argümanların başlangıcını işaret eder.  
  Buradaki `format`, değişken argümanlardan önce gelen son parametredir.

- `va_arg(argv, type);`  
  Argüman listesinden sıradaki argümanı `type` tipinde alır.

- `va_end(argv);`  
  Argüman listesini temizler, fonksiyon sonunda çağrılır.

---

## Örnek Kod Parçası

```c
int ft_printf(const char *format, ...)
{
    va_list argv;
    int i = 0;
    int len = 0;

    va_start(argv, format);
    while (format[i])
    {
        if (format[i] == '%' && ft_check(format[i + 1]))
        {
            i++;
            len += ft_format(&argv, format[i]);
        }
        else
            len += ft_putchar(format[i]);
        i++;
    }
    va_end(argv);
    return len;
}
