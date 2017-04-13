/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp-generator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svelhinh <svelhinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:15:21 by svelhinh          #+#    #+#             */
/*   Updated: 2017/04/13 11:47:48 by svelhinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename Out>
void split(const string &s, char delim, Out result) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

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
	<< "\tvirtual ~" << filename << "( void );" << endl << endl
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
	<< filename << "::" << "~" << filename << "( void )" << endl
	<< "{" << endl
	<< "\treturn;" << endl
	<< "}" << endl << endl
	<< filename << " & " << filename << "::operator=( " << filename << " const & rhs )" << endl
	<< "{" << endl
	<< "\treturn *this;" << endl
	<< "}" << endl;

	outputFile.close();
}

void	generateClassTemplate(string filename)
{
	ofstream	outputFile;

	outputFile.open(filename + string(".hpp"));

	outputFile << "#ifndef " << filename << "_hpp" << endl
	<< "#define " << filename << "_hpp" << endl << endl
	<< "template< typename T >" << endl
	<< "class " << filename << endl
	<< "{" << endl
	<< "public:" << endl
	<< "\t" << filename << "( void );" << endl
	<< "\t" << filename << "( " << filename << "< T > const & src );" << endl
	<< "\tvirtual ~" << filename << "( void );" << endl << endl
	<< "\t" << filename << " & operator=( " << filename << " const & rhs );" << endl
	<< "};" << endl << endl
	<< "#endif" << endl;

	outputFile.close();
}

void	generateGettersSetters(string filename)
{
	ofstream	outputFile;
	ifstream	inputFile;
	string		data;
	vector< string >		varLines;
	vector< vector< string > >		varSplit;
	vector< string >		varTypes;
	vector< string >		varNames;

	inputFile.open(filename + string(".hpp"));

	int i = 0;

	while (getline(inputFile, data))
    {
		if (i)
		{
			if (data == "};" || data == "public:")
				break;
			if (data == "")
				continue;
			varLines.push_back(data);
		}
		if (!data.compare("private:"))
			i = 1;
    }

	for (size_t j = 0; j < varLines.size(); j++)
	{
		if (strstr(varLines[j].c_str(), "static"))
			continue;
		varSplit.push_back(split(varLines[j], ' '));
	}

	for (size_t k = 0; k < varSplit.size(); k++)
	{
		for (size_t j = 0; j < varSplit.size(); j++)
		{
			if (strchr(varSplit[k][j].c_str(), '\t'))
			{
				varSplit[k][j].erase(std::remove(varSplit[k][j].begin(), varSplit[k][j].end(), '\t'), varSplit[k][j].end());
				varTypes.push_back(varSplit[k][j]);
				if (!strchr(varSplit[k][j + 1].c_str(), ';'))
				{
					varTypes[k] += " " + varSplit[k][j + 1];
					j++;
				}
			}
			else if (strchr(varSplit[k][j].c_str(), ';'))
			{
				varSplit[k][j].erase(std::remove(varSplit[k][j].begin(), varSplit[k][j].end(), ';'), varSplit[k][j].end());
				varNames.push_back(varSplit[k][j]);
			}
		}
	}

	inputFile.close();


	for (size_t j = 0; j < varNames.size(); j++)
		cout << varTypes[j] << " " << varNames[j] << endl;

	outputFile.open(filename + string(".hpp"), ofstream::app);

	for (size_t j = 0; j < varNames.size(); j++)
		outputFile << varTypes[j] << " get" << varNames[j] << "( void ) const;" << endl;

	for (size_t j = 0; j < varNames.size(); j++)
		outputFile << "void set" << varNames[j] << "( " << varTypes[j] << " " << varNames[j] << "_ );" << endl;

	outputFile.close();



	outputFile.open(filename + string(".cpp"), ofstream::app);

	outputFile << endl;

	for (size_t j = 0; j < varNames.size(); j++)
	{
		outputFile << varTypes[j] << " " << filename << "::get" << varNames[j] << "( void ) const" << endl
		<< "{" << endl
		<< "\t return " << varNames[j] << ";" << endl
		<< "}" << endl << endl;
	}

	for (size_t j = 0; j < varNames.size(); j++)
	{
		outputFile << "void " << filename << "::set" << varNames[j] << "( " << varTypes[j] << " " << varNames[j] << "_ )" << endl
		<< "{" << endl
		<< "\t" << varNames[j] << " = " << varNames[j] << "_;" << endl
		<< "}" << endl << endl;
	}

	outputFile.close();
}

int	main(int ac, char **av)
{
	if (ac == 1)
		generateClass("Default");
	else if (!strcmp(av[1], "-f"))
	{
		for (int i = 2; i < ac; i++)
			generateClass(av[i]);
	}
	else if (!strcmp(av[1], "-gs"))
	{
		for (int i = 2; i < ac; i++)
			generateGettersSetters(av[2]);
	}
	else if (!strcmp(av[1], "-t"))
	{
		for (int i = 2; i < ac; i++)
			generateClassTemplate(av[i]);
	}
	return 0;
}
