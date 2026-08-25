/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 10:50:28 by kong              #+#    #+#             */
/*   Updated: 2026/08/25 17:30:23 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "HumanB.hpp"

HumanB::HumanB(std::string nama) : name(nama), weapon(NULL) {};

// any member type without a default ctor, must be initialized
// in the ctor initializer list, and not in the body.
// Next, since weapon is a pointer, this is actually making a shallow copy (copying the weapon address only)
// to create a deep : `weapon(other.weapon ? new Weapon(*other.weapon) : NULL)
HumanB::HumanB(const HumanB& other)
	: name(other.name), weapon(other.weapon) {};

HumanB& HumanB::operator=(const HumanB& other)
{
	if (this != &other)
	{
		name = other.name;
		weapon = other.weapon;
	}
	return (*this);
}

HumanB::~HumanB() {};

void	HumanB::setWeapon(Weapon& weaponize)
{
	// if member's name has the same name as param's,
	// use this->weapon = &weapon;
	weapon = &weaponize;
}

void	HumanB::attack()
{
	if (weapon)
	{
		std::cout
		<< name
		<< " attacks with their "
		<< weapon->getType()
		<< std::endl;
	}
	else
	{
		std::cout
		<< name
		<< " has no weapon to attack with!"
		<< std::endl;
	}
}
