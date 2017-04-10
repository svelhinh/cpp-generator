/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp-generator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:15:21 by svelhinh          #+#    #+#             */
/*   Updated: 2017/04/10 15:15:22 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <string>

using namespace std;

void	generateClass(string filename)
{
	ofstream	outputFile;

	outputFile.open(filename + string(".hpp"));

	outputFile << "#ifndef " << filename << "_hpp" << endl
	<< "#define " << filename << "_hpp" << endl << endl
	<< "class " << filename << endl
	<< "{" << endl
	<< "public:" << endl
	<< "\t" << filename << "( void );" << endl
	<< "\t" << filename << "( " << filename << " const & src );" << endl
	<< "\t~" << filename << "(void);" << endl << endl
	<< "\t" << filename << " & operator=( " << filename << " const & rhs );" << endl
	<< "};" << endl << endl
	<< "#endif" << endl;

	outputFile.close();

	outputFile.open(filename + string(".cpp"));

	outputFile << "#include \"" << filename << ".hpp\"" << endl << endl
	<< filename << "::" << filename << "( void )" << endl
	<< "{" << endl
	<< "\treturn;" << endl
	<< "}" << endl << endl
	<< filename << "::" << filename << "( " << filename << " const & src )" << endl
	<< "{" << endl
	<< "\t*this = src;" << endl
	<< "\treturn;" << endl
	<< "}" << endl << endl
	<< "~" << filename << "::" << filename << "( void )" << endl
	<< "{" << endl
	<< "\treturn;" << endl
	<< "}" << endl << endl
	<< filename << " & " << filename << "::operator=( " << filename << " const & rhs )" << endl
	<< "{" << endl
	<< "\treturn *this;" << endl
	<< "}" << endl;

	outputFile.close();
}

int	main(int ac, char **av)
{
	if (ac == 1)
		generateClass("Default");
	else
	{
		for (int i = 1; i < ac; i++)
			generateClass(av[i]);
	}
	return 0;
}
