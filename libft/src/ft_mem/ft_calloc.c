/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 02:00:10 by envyilma          #+#    #+#             */
/*   Updated: 2023/08/21 17:48:56 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/*
"ft_calloc" fonksiyonu, bellekte yeni bir alan 
	ayrılmasını ve bu alanın sıfırlandığını sağlar.
size" parametresi, bellekte ayrılacak 
	her bir elemanın boyutunu belirler. 
Bu değer, byte cinsinden verilir ve bellekte 
	kaç byte'lık alanın ayrılacağını belirler. 
Örneğin, "size" değeri 4 ise, her bir eleman için 4 byte bellek alanı ayrılır.
"count" parametresi, bellekte 
	ayrılacak alanın boyutunu belirler. 
Bu değer, bellekte kaç adet "size" 
	boyutunda elemanın saklanacağını belirler. 
Örneğin, "count" değeri 5 ise ve "size" değeri 4 ise, 
	toplam 20 byte (5 x 4) bellek alanı ayrılır.
*/