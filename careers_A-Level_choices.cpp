// classes example
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <ctime>
#include <algorithm> // use abs() needed for sort
#include <random>
#include <string>



// EXAMINATION COMMENT.   YEAR PERFORMANCE REGULARITY, HOMEWORK IF BAD. ABILITIES AND POTENTIAL. REVISION AND END.


//#include <string> //
//#include<math.h> // use sqrt()



#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std;





//**********************************************************************************
// main function
//**********************************************************************************
int main( int argc, const char* argv[] )
{
    std::cout << endl ;
    std::cout << BOLDYELLOW << "    _________________________________________________" << std::endl ;
    std::cout << BOLDYELLOW << "            _=_                                      " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "          q(-_-)p                                    " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "          '_) (_`         A-LEVEL CHOICE CHECK        " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "          /__/  \\         Carles Triguero 2026      " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "        _(<_   / )_                                  " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "       (__\\_\\_|_/__)                               " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "    _________________________________________________" << RESET << std::endl ;
    std::cout << endl ;
    
    
    
    
        // Check the number of arguments (1 means only the name of the program => No argument)
        if ( argc == 1 )
        {
            cout << "\t Wrong usage. You should execute:" << endl ;
            cout << BOLDRED << "\t " << argv[0] << " [File to analyze.dat]" << RESET << endl ;
            cout << " " << endl ;
            return (0) ;
        }
    
        // Check if the file exists
        ifstream file(argv[1]) ;
        if (!file)
        {
            std::cout << BOLDRED <<"    -> ERROR: File test.xyz does not exist. ABORTING" << RESET << std::endl ;
            std::cout << std::endl ;
            abort () ;
        }
        file.close() ;
    
        std::cout << YELLOW << "    -> File " << BOLDYELLOW << argv[1] << RESET << YELLOW << " found" << RESET << std::endl ;
    
        unsigned int bins = 100 ;        // Number of bins default
    
        for ( int k = 1; k < argc ; ++k )
        {
            if ( ( argv[k] == std::string("-h") ) || ( argv[k] == std::string("-HELP") ) || ( argv[k] == std::string("-H") ) || ( argv[k] == std::string("-help") ) )
            {
                cout  << BOLDBLACK << "    HELP:" << RESET << std::endl ;
                cout << "    Generates a histogram with the second column of a file containing real data" << std::endl ;
                cout << "    [Column can be changed and also addapted to integer data]" << std::endl ;
                cout << "    ------------------------------------------------" << std::endl ;
                cout << BOLDBLACK << "    Execution: ./a.out file.dat [+flags]" << RESET << std::endl ;
                cout << BOLDBLACK << "    Mandatory flags:" << RESET << std::endl ;
                cout << "    -bins" << "\t" << "    to set the number of bins (e.g. ./a.out file.dat -bins 100) default bins=100" << std::endl ;
                cout << BOLDBLACK << "    Optional flags:" << RESET << std::endl ;
                cout << "    -h" << "\t" << "    to get help  (e.g. ./a.out -help)" << std::endl ;
                cout << "    -gle" << "\t" << "    to generate gle graphs of histogram and PDF  (e.g. ./a.out file.dat -bins 100 -gle)" << std::endl ;
                cout << std::endl ;
                return (0) ;
            }
            if ( ( argv[k] == std::string("-bins") ) || ( argv[k] == std::string("-bin") )  || ( argv[k] == std::string("-b") ) ) { bins = atoi(argv[k+1]) ; }
            //        if ( ( argv[k] == std::string("-gle") ) || ( argv[k] == std::string("-g") )  || ( argv[k] == std::string("-GLE") ) ) { Ly = atoi(argv[k+1]) ; }
        }
    
    
    
        // Count execution time
        int start_s=clock();
    
    
    
        // Files to store data
        ofstream Reports ;
        Reports.open ("Reports.txt", ios::out | ios::trunc); // Report file to copy and paste on sims
    
    
    
    
    
    
        // Input file definition
        std::string File(argv[1]); // set up a stringstream variable named convert, initialized with the input from argv[1]
    
    
        cout << YELLOW << "    -> Processing file: " << BOLDYELLOW << File << RESET << endl ;
    
    
    

    
        // Data file input to read
        std::ifstream InputFile(File);
        
    
    // GCSE GRADES input variables data     
    std::string surname,name,year,reg,candidate,entries,ARTD,BIOL,BUSI,CHEM,CHIN,CCIV,DTEC,ECON,ELAN,ELIT,FREN,GEOG,GERM,HIST,HOEC,ITEC,ITAR,LATI,MATH,FMAT,MUSI,PEAR,PESE,PHYS,POLI,RELI,RUSS,SPAN,SPOR;
    // A-LEVEL CHOICES
    std::string CARTD,CBIOL,CBUSI,CCHEM,CCCIV,CCOMS,CDTEC,CDRTH,CECON,CELIT,CENVT,CFREN,CGEOG,CGERM,CGOPO,CHESO,CHIST,CLATI,CMATH,CFMAT,CMOIM,CMUSI,CNUFO,CPHYS,CPSYC,CRELI,CRUSS,CSPAN,CSPOR,CTEDE,CTRAV;
    
    // Variable string to read the whole line
    std::string line ;            

    // // Skiping very first line
    // getline(InputFile, line);

    // // reading first line to get the topics
    // getline(InputFile, line);
    // std::stringstream aa(line);
    

    // cout << "File headers" << endl ;

// READING DATA FOR EACH PUPIL GCSE GRADES AND A-LEVEL CHOICES
    
while (getline(InputFile, line))
{
std::stringstream aa(line);

// FIXED FIELDS (TSV-safe parsing)
std::string surname, name, year, reg, candidate, entries;

std::getline(aa, surname, '\t');
std::getline(aa, name, '\t');
std::getline(aa, year, '\t');
std::getline(aa, reg, '\t');
std::getline(aa, candidate, '\t');
std::getline(aa, entries, '\t');

// GCSE SUBJECT GRADES (ALL TSV-SAFE)
std::string ARTD, BIOL, BUSI, CHEM, CHIN, CCIV, DTEC, ECON, ELAN,
            ELIT, FREN, GEOG, GERM, HIST, HOEC, ITEC, ITAR,
            LATI, MATH, FMAT, MUSI, PEAR, PESE, PHYS, POLI,
            RELI, RUSS, SPAN, SPOR;

std::getline(aa, ARTD, '\t'); // Art & Desigb
std::getline(aa, BIOL, '\t'); // Biology
std::getline(aa, BUSI, '\t'); // Business Studies
std::getline(aa, CHEM, '\t'); // Chemistry
std::getline(aa, CHIN, '\t'); // Chinese
std::getline(aa, CCIV, '\t'); // Classical Civilization
std::getline(aa, DTEC, '\t'); // Digital Technology
std::getline(aa, ECON, '\t'); // Economics
std::getline(aa, ELAN, '\t'); // English Languaje
std::getline(aa, ELIT, '\t'); // English Literature
std::getline(aa, FREN, '\t'); // French
std::getline(aa, GEOG, '\t'); // Geography
std::getline(aa, GERM, '\t'); // German
std::getline(aa, HIST, '\t'); // History
std::getline(aa, HOEC, '\t'); // Home Economics
std::getline(aa, ITEC, '\t'); // Information Technology
std::getline(aa, ITAR, '\t'); // IT/Art
std::getline(aa, LATI, '\t'); // Latin
std::getline(aa, MATH, '\t'); // Mathematics
std::getline(aa, FMAT, '\t'); // Further Mathematics
std::getline(aa, MUSI, '\t'); // Music
std::getline(aa, PEAR, '\t'); // Performing Arts
std::getline(aa, PESE, '\t'); // Personal and Social Education
std::getline(aa, PHYS, '\t'); // Physics
std::getline(aa, POLI, '\t'); // Politics
std::getline(aa, RELI, '\t'); // Religious Studies
std::getline(aa, RUSS, '\t'); // Russian
std::getline(aa, SPAN, '\t'); // Spanish
std::getline(aa, SPOR, '\t'); // Sport/PE Studies


std::vector<std::string> Achoices;
std::string choice;

while (std::getline(aa, choice, '\t'))
{
    if (!choice.empty())
        Achoices.push_back(choice);
}


// Check number of choices:
// std::size_t numChoices = Achoices.size();
// Output info:
std::cout << name << " " << surname << " number of choices is: " << Achoices.size() << " choices are: " ;
for (const auto& choice : Achoices)
{
    std::cout << choice << " " ;
}
std::cout << std::endl;







//  A LEVEL ART AND DESIGN

// Checks if CARTD is in the choices (Achoices vector)

    if (std::find(Achoices.begin(), Achoices.end(), "CARTD") != Achoices.end())
    {
        // Check if: grade is B or higher for Art and Design AND for English Languaje
        if((ARTD == "B" || ARTD == "A" || ARTD == "A*") && (ELAN == "B" || ELAN == "A" || ELAN == "A*"))
        {
            std::cout << BOLDGREEN << " YES Art and Design" << RESET << " Art des =" << ARTD << " Eng lan=" << ELAN << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Art and Design" << RESET << " Art des =" << ARTD << " Eng lan=" << ELAN << endl ;
        }
    }


//  A LEVEL BIOLOGY

// Checks if CBIOL is in the choices (Achoices vector)

    if (std::find(Achoices.begin(), Achoices.end(), "CBIOL") != Achoices.end())
    {
        // Check if: grade is A or higher for biology or AA in double award
        if(BIOL == "A" || BIOL == "A*" || BIOL == "AA" || BIOL == "A*A" || BIOL == "AA*" || BIOL == "A*A*")
        {
            std::cout << BOLDGREEN << " YES Biology" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Biology" << RESET << endl ;
        }
    }


//  A LEVEL BUSINESS STUDIES

    if (std::find(Achoices.begin(), Achoices.end(), "CBUSI") != Achoices.end())
    {
        if( BUSI == "B" || BUSI == "A" || BUSI == "A*" || ((BUSI == "C*" || BUSI == "B" || BUSI == "A" || BUSI == "A*") && ELAN == "B") )
         {
            std::cout << BOLDGREEN << " YES Busines Studies" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Busines Studies" << RESET << endl ;
        }
    }




//  A LEVEL CHEMISTRY

// Checks if BUSINESS STUDIES is in the choices (Achoices vector)

    if (std::find(Achoices.begin(), Achoices.end(), "CCHEM") != Achoices.end())
    {
        if((CHEM == "A" || CHEM == "A*") && (MATH == "A" || MATH == "A*"))
        {
            std::cout << BOLDGREEN << " YES Chemistry" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Chemistry" << RESET << endl ;
        }
    }



//  A LEVEL CLASSICAL CIVILIZATION  (!CCIV.empty()) checks that any value non empty is sufficient to acces A level.


// THIS COULD BE IMPLEMENTED AS:
// bool goodGrade(const std::string& g)
// {
//     return g == "A" || g == "A*" || g == "B";
// }
// if (!CCIV.empty() || BGrade(HIST) || BGrade(ELAN) || BGrade(ELIT) || BGrade(LATI) || BGrade(RELI))


    if (std::find(Achoices.begin(), Achoices.end(), "CCCVI") != Achoices.end())
    {
        if((!CCIV.empty()) || (HIST == "B" || HIST == "A" || HIST == "A*") || (ELAN == "B" || ELAN == "A" || ELAN == "A*") || (ELIT == "B" || ELIT == "A" || ELIT == "A*") || (LATI == "B" || LATI == "A" || LATI == "A*")  || (RELI == "B" || RELI == "A" || RELI == "A*"))
        {
            std::cout << BOLDGREEN << " YES Classical Civilization" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Classical Civilization" << RESET << endl ;
        }
    }


    

//  A LEVEL COMPUTER SCIENCE no AQE CONSIDERED 2 CONDITION HERE!!!

    if (std::find(Achoices.begin(), Achoices.end(), "CCOMS") != Achoices.end())
    {
        // Check if: grade is A or higher for biology or AA in double award
        if((DTEC == "A" || DTEC == "A*") && (MATH == "B" || MATH == "A" || MATH == "A*"))
        {
            std::cout << BOLDGREEN << " YES Computer Science" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Computer Science but check HOD + A in MATHS" << RESET << endl ;
        }
    }




//  A LEVEL DIGITAL TECHNOLOGY  gcse compUTER science NOT CONSIERED CHECK

    if (std::find(Achoices.begin(), Achoices.end(), "CDTEC") != Achoices.end())
    {
        // Check if: grade is A or higher for biology or AA in double award
        if((DTEC == "C*" || DTEC == "B" || DTEC == "A" || DTEC == "A*") || (ELAN == "B" || ELAN == "A" || ELAN == "A*"))
        {
            std::cout << BOLDGREEN << " YES Digital Technology" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Digital Technology" << RESET << endl ;
        }
    }



//  A LEVEL DRAMA AND THEATRE STUDIES  IS DRAMA GCSE PERFORMIN ARTS PEAR 6 to what number???

    if (std::find(Achoices.begin(), Achoices.end(), "CDRTH") != Achoices.end())
    {
        if((PEAR == "6" || PEAR == "7" || PEAR == "8") && (ELIT == "B" || ELIT == "A" || ELIT == "A*"))
        {
            std::cout << BOLDGREEN << " YES Drama and Theatre Studies" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Drama and Theatre Studies" << RESET << endl ;
        }
    }


//  A LEVEL ECONOMICS

    if (std::find(Achoices.begin(), Achoices.end(), "CECON") != Achoices.end())
    {
        if((ECON == "B" || ECON == "A" || ECON == "A*") || ((ELAN == "B" || ELAN == "A" || ELAN == "A*") && (MATH == "B" || MATH == "A" || MATH == "A*")))
        {
            std::cout << BOLDGREEN << " YES Economics" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Economics" << RESET << endl ;
        }
    }

//  A LEVEL ENGLISH LITERATURE

    if (std::find(Achoices.begin(), Achoices.end(), "CELIT") != Achoices.end())
    {
        if ((ELIT == "A" || ELIT == "A*") && (ELAN == "B" || ELAN == "A" || ELAN == "A*"))
        {
            std::cout << BOLDGREEN << " YES English Literature" << RESET << std::endl;
        }
        else if ((ELAN == "A" || ELAN == "A*") && (ELIT == "B" || ELIT == "A" || ELIT == "A*"))
        {
            std::cout << BOLDGREEN << " (If HOD approval) YES English Literature" << RESET << std::endl;
        }
        else
        {
            std::cout << BOLDRED << " NO English Literature" << RESET << std::endl;
        }
    }


// //  A LEVEL ENVIROMENTAL TECHNOLOGY  (DIGITAL OR INFORMATION TECHNOLOGY???)  CHECK THE DOUBLE AWARD CONDITION...

//     if (std::find(Achoices.begin(), Achoices.end(), "CECON") != Achoices.end())
//     {
//         if((MATH == "B" || MATH == "A" || MATH == "A*") || (TECH == "B" || TECH == "A" || TECH == "A*") || (PHYS == "B" || PHYS == "A" || PHYS == "A*") || (DSCI == "BB" || DSCI == "AB" ))
//         {
//             std::cout << BOLDGREEN << " YES Enviromental Technology" << RESET << endl ;
//         }
//         else
//         {
//             std::cout << BOLDRED << " NO Enviromental Technology" << RESET << endl ;
//         }
//     }









} // While reading line finish here



        InputFile.close() ;

    

    return (0) ;
}
