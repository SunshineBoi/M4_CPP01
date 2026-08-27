/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 18:23:08 by kong              #+#    #+#             */
/*   Updated: 2026/08/27 16:23:35 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void	Harl::print_title(std::string str)
{
	std::cout
		<< "[ "
		<< str
		<< " ]"
		<< std::endl;
}

Harl::Harl() {}

Harl::Harl(const Harl& other) { (void)other; }

Harl& Harl::operator=(const Harl& other)
{
	(void)other;
	return (*this);
}

Harl::~Harl() {}

void	Harl::debug(void)
{
	print_title("DEBUG");
	std::cout
		<< "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!\n"
		<< std::endl;
}

void	Harl::info(void)
{
	print_title("INFO");
	std::cout
		<< "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!\n" 
		<< std::endl;
}

void	Harl::warning(void)
{
	print_title("WARNING");
	std::cout 
		<< "I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month.\n" 
		<< std::endl;
}

void	Harl::error(void)
{
	print_title("ERROR");
	std::cout
		<< "This is unacceptable! I want to speak to the manager now.\n" 
		<< std::endl;
}

void	Harl::complain(std::string level)
{
	enum	levels { DEBUG, INFO, WARNING, ERROR };
	std::string	levelNames[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	int		ilevel = -1;

	typedef void (Harl::*FnPtr)(void);
	FnPtr harl_fn[] = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

	for (int i = 0; i < 4; i++)
	{
		if (levelNames[i] == level)
			ilevel = i;
	}
	switch (ilevel)
	{
		case DEBUG:
			(this->*harl_fn[0])();
			// fallthrough
		case INFO:
			(this->*harl_fn[1])();
			// fallthrough
		case WARNING:
			(this->*harl_fn[2])();
			// fallthrough
		case ERROR:
			(this->*harl_fn[3])();
			break ;
		default:
			std::cout 
				<< "[ Probably complaining about insignificant problems ]" 
				<< std::endl;
	}
}

/*
Format of pointer to member function
>>> return_type (ClassName::*ptr_name)(arg_types); <<<

What the different with normal function pointer is : added a ClassName.
- so at compile time, it looks up the correct member function across classes.
- during runtime, object instance `this` will be able to invoke it

To use it:
>>> void (Robot::*ptr)() = &Robot::action; <<<
! Notice: `&` is required even though in C, assumed function will decay into pointer.
Member functions do not "decay" automatically: 
Unlike standalone functions, a member function cannot exist or run without an object instance.
Because it behaves differently under the hood, 
the language forces you to explicitly say "I want the address of this member" by typing the &.
*/

