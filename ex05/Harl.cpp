/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 18:23:08 by kong              #+#    #+#             */
/*   Updated: 2026/08/26 22:33:24 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

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
	std::cout 
		<< "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!"
		<< std::endl;
}

void	Harl::info(void)
{
	std::cout
		<< "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" 
		<< std::endl;
}

void	Harl::warning(void)
{
	std::cout 
		<< "I think I deserve to have some extra bacon for free. I've been coming for years, whereas you started working here just last month." 
		<< std::endl;
}

void	Harl::error(void)
{
	std::cout
		<< "This is unacceptable! I want to speak to the manager now." 
		<< std::endl;
}

void	Harl::complain(std::string level)
{
	// use an array to represent levels
	std::string	levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	
	/* this is ugly
	void (Harl::*debug_ptr)(void) = &Harl::debug;
	void (Harl::*info_ptr)(void) = &Harl::info;
	void (Harl::*warning_ptr)(void) = &Harl::warning;
	void (Harl::*error_ptr)(void) = &Harl::error;
	void (Harl::*levels_fn[])(void) = {debug_ptr, info_ptr, warning_ptr, error_ptr}; 
	
	or do this:
	void (Harl::*levels_fn[])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error}; */

	// cleaner way to write - make fn pointer a type
	typedef void (Harl::*HarlPtr)(void);
	HarlPtr levels_fn[] = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

	for (int i = 0; i < 4; i++)
	{
		if (levels[i] == level)
		{
			// square bracket is to grab the fn pointer
			// `*` deref the pointer to get to fn object
			// `this` instance then invoke this fn
			(this->*levels_fn[i])();
			return ;
		}
	}
	std::cerr << "Invalid command!" << std::endl;
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

