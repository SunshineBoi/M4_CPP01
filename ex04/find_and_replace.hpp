/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_replace.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:10:06 by kong              #+#    #+#             */
/*   Updated: 2026/08/26 15:11:35 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_AND_REPLACE_HPP
# define FIND_AND_REPLACE_HPP

#include <fstream>
#include <iterator>
#include <iostream>
#include <string>

bool		read_file(std::string filename, std::string& out);
bool		write_file(std::string filename, std::string res);
std::string	replace_all(std::string buf, std::string s1, std::string s2);

#endif
