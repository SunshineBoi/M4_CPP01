/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_replace.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 15:09:53 by kong              #+#    #+#             */
/*   Updated: 2026/08/26 15:23:36 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_and_replace.hpp"

bool	read_file(std::string filename, std::string& out)
{
	// 1. open file with input file stream
	std::ifstream file(filename.c_str());
	// 2. check status
	if (!file.is_open())
	{
		std::cerr << "Error: failed to open file!" << std::endl;
		return (0);
	}
	// 3. create the full string with string's range ctor
	// start iterator - reads raw chars directly from stream's buffer, advancing one at a time.
	// end iterator - special end-of-stream sentinel, the default constructed to mean ends.
	out = std::string(
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>());
	file.close();
	return (1);
}

bool	write_file(std::string filename, std::string res)
{
	// 5. output into new file with Output File Stream
	std::ofstream new_file((filename).c_str());
	if (new_file.is_open())
	{
		new_file << res;
		new_file.close();
		std::cout << filename << " is created." << std::endl;
		return (1);
	}
	else
	{
		std::cerr << "Error: failed to create file!" << std::endl;
		return (0);
	}
}

std::string	replace_all(std::string buf, std::string s1, std::string s2)
{
	// 4. search and replace
	size_t pos = 0;
	std::string result;

	while (true)
	{
		size_t found = buf.find(s1, pos);
		// ? npos is a STATIC MEMBER CONSTANT that represents an invalid, not found position inside a string
		// npos as indicator for "Not Found"
		if (found == std::string::npos)
		{
			// it can be used as indicator for "Until the End" as length argument
			result += buf.substr(pos, std::string::npos);
			break ;
		}
		result += buf.substr(pos, found - pos);  // copy up to found index
		result += s2;  // copy the replaced substring
		pos = found + s1.length();  // adjust position
	}
	return (result);
}

