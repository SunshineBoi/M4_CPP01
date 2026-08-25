/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 10:55:42 by kong              #+#    #+#             */
/*   Updated: 2026/08/25 13:14:32 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
	{
		Weapon club = Weapon("crude spiked club");
		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");
		HumanB jim("Jim");
		jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}

	// note here, watergun has to be an lvalue, so we cant do something:
		// `Weapon& watergun = Weapon("WATER GUN");`
	// because we are assigning an rvalue to the reference.
	// but it works if we can include const
		// `const int& ref = 20;`
	Weapon watergun ("WATER GUN");  // same as: Weapon watergun = Weapon("WATER GUN");
	HumanA ha = HumanA("Haaland", watergun);
	ha.attack();
	watergun.setType("SUPER WATER GUN!");
	ha.attack();

	return (0);
}

/*
Reach for a reference when the association is mandatory and fixed for the object's lifetime;
Reach for a pointer when it needs to be either optional (nullable) or 
 	reassignable to a different object over time (or both, as with HumanB). 
Nullability alone would still often lead you to a pointer, 
	but rebindability is the other half of why references can't do the job
	even if you didn't care about null.

Each human being doesnt hold its own copies of weapon,
hence, pass by value doesnt work, it has to reference to the instance of weapon created.

*/
