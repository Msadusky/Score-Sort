//=============================================================================
// Mike Sadusky
// scoresort.cpp
// Reads in a text file of students with their score on an exam.
// Outputs the list sorted by last name in alphabetical order
// with their rank of performace based on the exam scores.
//=============================================================================

#include <fstream>
#include <iostream>
#include <string>
#include <map>

// Function to format output in a readable manner
std::string tabName(std::string);

// Function to determine letter grade equivalent of students score
char letterGrade(int);

int main(int argc, char* argv[])
{
	// If the user requests anymore or less than one text file
	if(argc != 2)
	{
		std::cerr << "\nUsage: " << argv[0] <<" [NAME OF TEXT FILE HERE]\n" << std::endl;

		// Program ended with errors
		return 1;
	}
	// If only file was requested
	else
	{
		// Initializing multimap container to store text file
		std::multimap<std::string, std::string> nameSort;
		std::multimap<std::string, std::string>::iterator in;
		std::multimap<int, std::string> scoreSort;
		std::multimap<int, std::string>::iterator is;

		// Initializng variables to read text file in
		std::ifstream readFile;
		char* fileName = argv[1];
		std::string firstName;
		std::string lastName;
		std::string fullName;
		int score = 0;

		// Open the text file to read from
		readFile.open(fileName, std::ifstream::in);

		// If the file opened successfully
		if(readFile.is_open())
		{
			// While there's data to be read
			while(readFile >> firstName)
			{
				// Reading and formatting text from the file
				firstName = tabName(firstName);
				readFile >> lastName;
				lastName = tabName(lastName);
				readFile >> score;

				// Concatenating first and last for a variable with the whole name
				fullName = firstName + lastName;

				// Inserting whole name, with the key being the last name
				nameSort.insert(std::make_pair<std::string, std::string>(lastName, fullName));

				// Inserting the whole name with the key being their score
				scoreSort.insert(std::make_pair<int, std::string>(score, fullName));

				// Clearing the variables for next iteration
				firstName.clear();
				lastName.clear();
				fullName.clear();
				score = 0;
			}

			// Close the file
			readFile.close();
		}
		else
		{
			// Print out that the file didn't open
			std::cerr << "\nFile: " << argv[1] << " failed to open.\n" << std::endl;
			std::cerr << "Did you spell it correctly?\n";
			std::cerr << "Does the file exist in this directory?\n" << std::endl;

			// Program ended with errors
			return 1;
		}

		// Printing out column labels
		std::cout << "\nFirst\t\tLast\t\tScore\tRank\tGrade" << std::endl;
		for(int i = 0; i < 55; ++i)
		{
			std::cout << "-";
		}
		std::cout << std::endl;

		// Iterating through sorted map of names
		for(in = nameSort.begin(); in != nameSort.end(); ++in)
		{
			// Using a simple iterator to determine rank,
			// since scoreSort multimap already has scores sorted
			// ranks can be easily determined by position of score
			// in the container
			int rank = scoreSort.size();

			// Iterating through the sorted map of scores
			for(is = scoreSort.begin(); is != scoreSort.end(); ++is)
			{
				// If the full names match
				if((*in).second == (*is).second)
				{
					// Make grade equal to the return of the letterGrade method
					// which returns the letter grade equivalent of the score
					// passed to it
					char grade = letterGrade((*is).first);

					// Print out their full name, their score, their rank, and
					// their letter grade
					std::cout << (*in).second << (*is).first << "\t" << rank
						<< "\t" << grade << std::endl;
				}
				// Since rank starts at the size of the container
				// and the container sorts from highest to lowest
				// have to decrement rank to appropriately label
				// students
				--rank;
			}
		}
		std::cout << std::endl;


	}

	// Program ended with no errors
	return 0;
}

//=================
// Begin functions
//=================

// Accepts string value for editing
std::string tabName(std::string name)
{
	if(name.size() >= 8)
	{
		name += "\t";
	}
	else
	{
		name += "\t\t";
	}

	return name;
}

// Determines student's letter grade
char letterGrade(int num)
{
	if(num >= 90)
	{
		return 'A';
	}
	else if(num >= 80)
	{
		return 'B';
	}
	else if(num >= 70)
	{
		return 'C';
	}
	else if(num >= 60)
	{
		return 'D';
	}
	else
	{
		return 'F';
	}
}
