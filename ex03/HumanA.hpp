/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 10:24:18 by kong              #+#    #+#             */
/*   Updated: 2026/08/25 12:12:33 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include "HumanA.h"

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