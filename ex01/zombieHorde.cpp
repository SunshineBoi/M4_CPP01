/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 22:16:23 by kong              #+#    #+#             */
/*   Updated: 2026/08/24 17:41:35 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	int		i = 0;
	Zombie*	horde;

	// calling new(n) does raw allocation only, just like malloc
	// calling ::operator is to ensure it always refer to global version and not accidentally refers to some overloaded new.
	void* raw = ::operator new(N * sizeof(Zombie));
	horde = static_cast<Zombie*>(raw);

	while (i < N)
	{
		new (&horde[i]) Zombie(name);
		i++;
	}
	return (horde);
}
