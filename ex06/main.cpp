/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 22:09:12 by kong              #+#    #+#             */
/*   Updated: 2026/08/27 16:30:45 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int ac, char **av)
{
	Harl		harl;

	if (ac != 2)
	{
		std::cerr << "Error: Invalid number of arguments!" << std::endl;
		return (1);
	}
	harl.complain(av[1]);
	return (0);
}
