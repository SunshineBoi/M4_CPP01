/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 18:46:25 by kong              #+#    #+#             */
/*   Updated: 2026/08/22 18:50:12 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

// This function creates a zombie, names it, and returns it so you can use it outside of the function scope.
Zombie*	newZombie(std::string name)
{
	return new Zombie(name);
}
