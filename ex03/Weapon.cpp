/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 10:31:46 by kong              #+#    #+#             */
/*   Updated: 2026/08/25 10:58:41 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string weapon_type) : type(weapon_type) {};

Weapon::Weapon(const Weapon& other)
{
	type = other.type;
}

Weapon& Weapon::operator=(const Weapon& other)
{
	if (this != &other)
	{
		type = other.type;
	}
	return (*this);
}

Weapon::~Weapon() {};

const std::string& Weapon::getType()
{
	return (type);
}

void	Weapon::setType(std::string weapon_type)
{
	type = weapon_type;
}
