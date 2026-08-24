/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 17:31:44 by kong              #+#    #+#             */
/*   Updated: 2026/08/24 17:41:37 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name) : name(name) {}

Zombie::Zombie(const Zombie& other)
{
	name = other.name;
}

Zombie& Zombie::operator=(const Zombie& other)
{
	if (this != &other)
	{
		name = other.name;
	}
	return (*this);
}

Zombie::~Zombie()
{
	std::cout << "Zombie " << name << " is dead! or is it.." << std::endl;
}

void	Zombie::announce( void )
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}