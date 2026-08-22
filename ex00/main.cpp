/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 17:31:58 by kong              #+#    #+#             */
/*   Updated: 2026/08/22 21:55:39 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main()
{
	// scenario 1:
	// Heap Harry: BraiiiiiiinnnzzzZ...
	// Zombie Heap Harry is dead! or is it..      ← dtor fires right at `delete`
	Zombie*	heapZombie = newZombie("Heap Harry");
	heapZombie->announce();
	delete heapZombie;

	// scenario 2:
	// Stack Sally: BraiiiiiiinnnzzzZ...
	// Zombie Stack Sally is dead! or is it..     ← dtor fires automatically when randomChump() returns
	randomChump("Stack Sally");

	Zombie	original("Original Oz");
	Zombie	copy(original);
	Zombie	assigned("temp");
	assigned = original;
	copy.announce(); // copy zombie becomes original zombie in stack
	assigned.announce(); // assigned zombie becomes original zombie in stack

	return (0);
}
