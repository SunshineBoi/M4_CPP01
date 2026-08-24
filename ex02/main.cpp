/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 22:21:08 by kong              #+#    #+#             */
/*   Updated: 2026/08/24 22:27:28 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int	main(void)
{
	std::string msg = "HI THIS IS BRAIN";
	std::string* stringPTR = &msg;
	std::string& stringREF = msg;

	std::cout 
		<< "memory address of the string variable: "
		<< &msg
		<< std::endl;
	std::cout 
		<< "memory address held by stringPTR: "
		<< stringPTR
		<< std::endl;
	std::cout 
		<< "memory address held by stringREF: "
		<< &stringREF
		<< std::endl;

	std::cout
		<< "value of string variable: "
		<< msg
		<< std::endl;
	std::cout
		<< "value of stringPTR: "
		<< *stringPTR
		<< std::endl;
	std::cout
		<< "value of stringREF: "
		<< stringREF
		<< std::endl;
	return (0);
}
