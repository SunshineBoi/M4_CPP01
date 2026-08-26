/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kong <kong@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 17:41:37 by kong              #+#    #+#             */
/*   Updated: 2026/08/26 16:48:06 by kong             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_and_replace.hpp"

int main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cerr << "Invalid number of arguments!" << std::endl;
		return (1);
	}
	std::string filename = std::string(av[1]);
	std::string s1 = std::string(av[2]);
	if (s1.empty())
	{
		std::cerr << "Error: s1 is empty!" << std::endl;
		return (1);
	}
	std::string s2 = std::string(av[3]);
	std::string buf;

	if (!read_file(filename, buf))
		return (1);
	std::string result = replace_all(buf, s1, s2);
	if (!write_file(filename + ".replace", result))
		return (1);
	return (0);
}

/*
1. why string ctor allows str(start_iter, end_iter) ?
It officials signature looks like this:
>>>
template <class InputIt>
std::string::string(InputIt first, InputIt, last); <<<
Basically, it loops from first to last and allocates required memory,
	then, it copies each character into new block and places a null terminator.

2. why do we provide <char> def to istreambuf_iterator?
- streambuf is a class template.
- there is other character type like wide-character text file <wchar_t> (2-4 bytes)
- it needs to be explicit when there isn't any argument passed to the function

3. new string functions:
- .find(target_substr, starting_pos)
- .substr(starting_pos, length)

4. For file stream spcifically, we cant initiate it as:
>>>
std::ifstream file = std::ifstream(filename); <<<
why? because file stream doesnt allow for copying (operator=)
RHS is building a temporary object, then copying into LHS.
Usually, classes like string allows that, but filestream specifically blocks it.
Only one object owner to each filestream (C++ intentionally privatize the copying).

! But note, this applies to C++98 and not in the modern C++ anymore,
	modern C++ skips the temp object building instead even with LHS = RHS

*/
