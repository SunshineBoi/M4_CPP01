/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 10:31:18 by kong              #+#    #+#             */
/*   Updated: 2026/08/25 17:29:55 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string nama, Weapon& starter_weapon) 
	: name(nama), weapon(starter_weapon) {};

// any member type without a default ctor, must be initialized
// in the ctor initializer list, and not in the body.
HumanA::HumanA(const HumanA& other)
	: name(other.name), weapon(other.weapon) {};

HumanA& HumanA::operator=(const HumanA& other)
{
	if (this != &other)
	{
		name = other.name;
		// weapon = other.weapon;
		// weapon cannot be assigned because it would silently modify current weapon's value, instead of changing to a different weapon's instance.
		// why? because weapon is a Reference, which cannot be rebound
	}
	return (*this);
}

HumanA::~HumanA() {};

void	HumanA::attack()
{
	std::cout
		<< name
		<< " attacks with their "
		<< weapon.getType()
		<< std::endl;
}
