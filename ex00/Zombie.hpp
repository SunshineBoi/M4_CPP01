/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 17:31:47 by kong              #+#    #+#             */
/*   Updated: 2026/08/27 19:09:33 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>

class Zombie
{
private:
	std::string name;

public:
	Zombie( std::string name );
	Zombie( const Zombie& other );
	Zombie&	operator=( const Zombie& other );
	~Zombie();

	void	announce( void );
};

Zombie* newZombie( std::string name );
void    randomChump( std::string name );

#endif
