/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 10:24:18 by kong              #+#    #+#             */
/*   Updated: 2026/08/27 19:07:04 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"

class HumanA
{
private:
	std::string	name;
	Weapon&		weapon;

public:
	HumanA(std::string nama, Weapon& starter_weapon);
	HumanA(const HumanA& other);
	HumanA& operator=(const HumanA& other);
	~HumanA();

	void	attack();
};

#endif