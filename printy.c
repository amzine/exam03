#include<unistd.h>
#include<stdarg.h>

int size;
void ft_putnbr(long d,int l,char *str)
{
    if(d >= l)
    {
        ft_putnbr(d / l,l,str);
    }
    write(1,&str[d % l],1);
    size++;
}

void ft_puthex(unsigned d,unsigned l,char *str)
{
    if(d >= l)
    {
        ft_puthex(d / l,l,str);
    }
    write(1,&str[d % l],1);
    size++;
}

int    ft_printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int i;
    i = 0;
    size = 0;
    int j;
    j = 0;
    while(format[i])
    {
        if(format[i] == '%')
        {
            i++;
            if(format[i] == 's')
            {
                char *str = va_arg(ap, char *);
                while(str[j])
                    j++;
                size = j + size;
                write(1, str, j);
                j = 0;
            }
            else if(format[i] == 'x')
            {
                int b = va_arg(ap, int);
                ft_puthex(b, 16 ,"0123456789abcdef");
            }
            else if(format[i] == 'd')
            {
                long long d = va_arg(ap, int);
                if(d < 0)
                {
                    d = d * -1;
                    write(1,"-",1);
                    size++;
                }
                ft_putnbr(d, 10 ,"0123456789");
            }
        }
        else
        {
            write(1,&format[i],1);
            size++;
        }
        i++;
    }
    va_end(ap);
    return(size);
}