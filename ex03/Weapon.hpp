/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 22:38:53 by kong              #+#    #+#             */
/*   Updated: 2026/08/27 19:06:25 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>
# include <iostream>

class Weapon
{
private:
	std::string	type;
public:
	Weapon(std::string weapon_type);
	Weapon(const Weapon& other);
	Weapon& operator=(const Weapon& other);
	~Weapon();

	const std::string& getType();
	void	setType(std::string weapon_type);
};

#endif
