/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 17:31:58 by kong              #+#    #+#             */
/*   Updated: 2026/08/24 22:03:45 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main()
{
	int		N = 4;
	Zombie*	horde = zombieHorde(N, "Billy");
	int		i;

	i = 0;
	while (i < N)
	{
		horde[i].announce();
		i++;
	}

	i = 0;
	while (i < N)
	{
		horde[i].~Zombie();
		i++;
	}
	::operator delete(horde);

	return (0);
}
