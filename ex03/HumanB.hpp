/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 10:49:46 by kong              #+#    #+#             */
/*   Updated: 2026/08/27 19:06:47 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"

class HumanB
{
private:
	std::string	name;
	Weapon*		weapon;

public:
	HumanB(std::string nama);
	HumanB(const HumanB& other);
	HumanB& operator=(const HumanB& other);
	~HumanB();

	void	setWeapon(Weapon& weaponize);
	void	attack();
};

#endif