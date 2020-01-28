/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmousson <mmousson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:25:48 by mmousson          #+#    #+#             */
/*   Updated: 2018/12/11 05:39:08 by mmousson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define UNUSED(x) (void)(x)

int				ft_printf(const char *format, ...);

/*
** Structure responsible of holding informations about : Attributes, Field Width
** and Precision
*/

typedef struct	s_pf_infos
{
	char		space;
	char		sharp;
	char		zero;
	char		justify;
	char		plus;
	char		conversion;
	char		is_x;
	char		is_b_x;
	int			width;
	int			precision;
	int			bkp;

}				t_pf_infos;

int				ft_ending_format(t_pf_infos *inf, int size_of_var, int is_neg);
int				ft_pf_format_output(t_pf_infos *inf, int size_of_var,
					int is_neg);

/*
** =====================  CHAR FORMATING  ====================
*/

int				ft_pf_putchar(va_list ap, t_pf_infos *inf);
int				ft_pf_putstr(va_list ap, t_pf_infos *inf);

/*
** =====================  INT FORMATING  =====================
*/

int				ft_pf_putint(va_list ap, t_pf_infos *inf);
int				ft_pf_putlint(va_list ap, t_pf_infos *inf);
int				ft_pf_putllint(va_list ap, t_pf_infos *inf);
int				ft_pf_putsint(va_list ap, t_pf_infos *inf);
int				ft_pf_putcint(va_list ap, t_pf_infos *inf);

int				ft_pf_putuint(va_list ap, t_pf_infos *inf);
int				ft_pf_putulint(va_list ap, t_pf_infos *inf);
int				ft_pf_putullint(va_list ap, t_pf_infos *inf);
int				ft_pf_putusint(va_list ap, t_pf_infos *inf);
int				ft_pf_putucint(va_list ap, t_pf_infos *inf);

int				ft_pf_putllint_aux(long long int nb, t_pf_infos *inf);
int				ft_pf_putullint_aux(unsigned long long int nb,
					t_pf_infos *inf);

/*
** ===================== OCTAL FORMATING =====================
*/

int				ft_pf_putoctal_ui(va_list ap, t_pf_infos *inf);
int				ft_pf_putoctal_uli(va_list ap, t_pf_infos *inf);
int				ft_pf_putoctal_ulli(va_list ap, t_pf_infos *inf);
int				ft_pf_putoctal_usi(va_list ap, t_pf_infos *inf);
int				ft_pf_putoctal_uci(va_list ap, t_pf_infos *inf);
int				ft_pf_putoctal_ulli_aux(unsigned long long int nb,
					t_pf_infos *inf);

/*
** ================== HEXADECIMAL FORMATING ===================
*/

int				ft_pf_put_lhexa(va_list ap, t_pf_infos *inf);
int				ft_pf_put_lhexa_l(va_list ap, t_pf_infos *inf);
int				ft_pf_put_lhexa_ll(va_list ap, t_pf_infos *inf);
int				ft_pf_put_lhexa_s(va_list ap, t_pf_infos *inf);
int				ft_pf_put_lhexa_c(va_list ap, t_pf_infos *inf);

int				ft_pf_put_hexa_aux(unsigned long long int nb, t_pf_infos *inf);

/*
** ================= FLOATING POINT FORMATTING ===============
*/

int				ft_pf_putfloat(long double f, t_pf_infos *inf);
int				ft_pf_putfloat_f(va_list ap, t_pf_infos *inf);
int				ft_pf_putfloat_lf(va_list ap, t_pf_infos *inf);
int				ft_pf_putfloat_llf(va_list ap, t_pf_infos *inf);

char			*ft_pf_putfloat_get_addend_start(void);
char			*ft_pf_putfloat_get_mantissa(int exponent);
int				ft_pf_putfloat_count_dec(long double f);
char			*ft_pf_binary_exponantiation(char *base, char *pow);
int				ft_float_pad(long double f, t_pf_infos *inf,
					int res_len, int man_len);
int				ft_pf_putfloat_show(char *result, short res_len, short man_len,
					t_pf_infos *inf);

/*
** ==================== POINTER FORMATING ====================
*/

int				ft_put_pointer(va_list ap, t_pf_infos *inf);

/*
** Functions responsible for reading and finding the right flag and then
** finding a pointer to the right function
*/

int				ft_pf_dispatcher(const char **str, va_list args);
int				ft_flag_offset(char c, int current_offset);
int				ft_pf_c_in_str(char c, char *str);
int				ft_conversion_or_flag(char c);
int				ft_conversion(char c);
void			ft_pf_parse_attributes(t_pf_infos *inf, char conv);
void			ft_pf_get_attributes(t_pf_infos *inf, const char *str);
t_pf_infos		*ft_pf_initiate_attributes(void);

/*
** ==================== AUXILIARY FUNCTIONS ====================
*/

int				ft_magnitude(long long int nb, int base);
int				ft_unsigned_magnitude(unsigned long long int nb, int base);

#endif
