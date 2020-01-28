/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:26:07 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/11 05:38:27 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	(*g_func[50])(va_list ap, t_pf_infos *inf) = {
	&ft_pf_putchar,
	&ft_pf_putint,
	&ft_pf_putfloat_f,
	&ft_pf_putint,
	&ft_pf_putoctal_ui,
	&ft_put_pointer,
	&ft_pf_putstr,
	&ft_pf_putuint,
	&ft_pf_put_lhexa,
	&ft_pf_put_lhexa,
	NULL,
	&ft_pf_putlint,
	&ft_pf_putfloat_lf,
	&ft_pf_putlint,
	&ft_pf_putoctal_uli,
	NULL,
	NULL,
	&ft_pf_putulint,
	&ft_pf_put_lhexa_l,
	&ft_pf_put_lhexa_l,
	NULL,
	&ft_pf_putllint,
	&ft_pf_putfloat_llf,
	&ft_pf_putllint,
	&ft_pf_putoctal_ulli,
	NULL,
	NULL,
	&ft_pf_putullint,
	&ft_pf_put_lhexa_ll,
	&ft_pf_put_lhexa_ll,
	NULL,
	&ft_pf_putsint,
	NULL,
	&ft_pf_putsint,
	&ft_pf_putoctal_usi,
	NULL,
	NULL,
	&ft_pf_putusint,
	&ft_pf_put_lhexa_s,
	&ft_pf_put_lhexa_s,
	NULL,
	&ft_pf_putcint,
	NULL,
	&ft_pf_putcint,
	&ft_pf_putoctal_uci,
	NULL,
	NULL,
	&ft_pf_putucint,
	&ft_pf_put_lhexa_c,
	&ft_pf_put_lhexa_c
};

int	ft_no_conversions(const char *str, const char *s)
{
	while (*str && str <= s)
	{
		if (ft_pf_c_in_str(*str, "_cspdiouxXf"))
			return (0);
		str++;
	}
	return (1);
}

int	invalid(t_pf_infos *inf)
{
	int		res;
	int		rep;
	char	pad;

	res = 0;
	pad = (inf->zero == 1) ? '0' : ' ';
	rep = inf->width;
	if (inf->justify == 1)
		res += (int)write(1, "%", 1);
	while (rep-- > 1)
		res += (int)write(1, &pad, 1);
	if (inf->justify == -1)
		res += (int)write(1, "%", 1);
	return (res);
}

int	ft_pf_dispatcher(const char **str, va_list args)
{
	int			r;
	t_pf_infos	*inf;
	const char	*s;

	r = 0;
	s = (*str);
	if (!(inf = ft_pf_initiate_attributes()))
		return (0);
	while (ft_isdigit(*++s) || *s == '#' || *s == '+' || *s == '-'
		|| *s == '.' || *s == ' ' || *s == '*')
		ft_pf_get_attributes(inf, s);
	while (ft_conversion_or_flag(*s) && r % 10 == 0)
	{
		inf->is_x = (*s == 'x') ? 1 : inf->is_x;
		inf->is_b_x = (*s == 'X') ? 1 : inf->is_b_x;
		r += ft_flag_offset(*s, r) + ft_pf_c_in_str(*s, "cdfiopsuxX");
		s++;
	}
	if ((r = ft_no_conversions(*str, s) ? 100 : r) == 100)
		s++;
	ft_pf_parse_attributes(inf, *(s - 1));
	r = ((r <= 49 && (*g_func[r])) ? (*g_func[r])(args, inf) : invalid(inf));
	free(inf);
	*str = s;
	return (r);
}
