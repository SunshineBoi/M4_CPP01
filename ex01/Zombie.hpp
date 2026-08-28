/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 17:31:47 by kong              #+#    #+#             */
/*   Updated: 2026/08/28 11:22:44 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>
# include <new>

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

Zombie* zombieHorde( int N, std::string name );

#endif
