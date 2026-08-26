/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 22:09:12 by kong              #+#    #+#             */
/*   Updated: 2026/08/26 22:40:52 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main()
{
	Harl		harl;
	std::string	levels[] = {"DEBUG", "INFO", "WARNING", "ERROR", "HAALAND"};

	for (int i = 0; i < 5; i++)
	{
		std::cout << "-- level: " << levels[i] << " --" << std::endl;
		harl.complain(levels[i]);
		std::cout << std::endl;
	}
	return (0);
}
