/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:28:38 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/05 17:28:43 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static inline int	ft_has_percent(const char *fmt)
{
	while (*fmt != '\0')
	{
		if (*fmt == '%')
			return (1);
		fmt++;
	}
	return (0);
}

static inline int	ft_check(const char *fmt)
{
	if (ft_has_percent(fmt))
		return (1);
	while (*fmt != '\0')
		if (ft_pf_c_in_str(*fmt, "_cspdiouxXf"))
			return (1);
		else if (ft_pf_c_in_str(*fmt, "_ *.+-#%lLh0123456789"))
			fmt++;
		else
			return (0);
	return (0);
}

static int			ft_pf_putstr_aux(char *str, const char **format)
{
	int ret;

	ret = ft_strlen(str);
	write(1, str, ret);
	free(str);
	(*format) += ret;
	return (ret);
}

int					ft_pf_pad(const char **str)
{
	int			i;
	t_pf_infos	*inf;
	const char	*s;
	char		pad;

	i = -1;
	s = *str;
	inf = ft_pf_initiate_attributes();
	inf->bkp = ft_abs(ft_atoi(s + 1)) - 1;
	while (*++s != '\0' && ft_pf_c_in_str(*s, "_ .+-#%lLh0123456789"))
		ft_pf_get_attributes(inf, s);
	inf->conversion = *s++;
	pad = (inf->zero == 1) ? '0' : ' ';
	if (inf->justify == 1)
		write(1, &(inf->conversion), 1);
	while (++i < inf->bkp)
		write(1, &pad, 1);
	if (inf->justify == -1)
		write(1, &(inf->conversion), 1);
	*str = s;
	free(inf);
	return (ft_max(0, inf->bkp) + 1);
}

int					ft_printf(const char *format, ...)
{
	char	*f;
	int		ret;
	va_list	list;

	ret = 0;
	va_start(list, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (ft_check(format + 1))
				ret += ((*(format + 1) == '%') && (format += 2)
					? (int)write(1, "%", 1) : ft_pf_dispatcher(&format, list));
			else if (*(format + 1) == '\0')
				format++;
			else
				ret += ft_pf_pad(&format);
		}
		f = ft_strchr(format, '%');
		ret += ft_pf_putstr_aux(ft_strsub(format, 0, f ? f - format
					: (int)ft_strlen(format)), &format);
	}
	va_end(list);
	return (ret);
}
