// A-Level Entry Eligibility System - ALEES

// The aim of this program is to process student GCSE results and A-level subject choices, 
// then apply predefined entry criteria (MCB rules) to determine whether each student is 
// eligible to study their selected A-level subjects. The system reads data from a structured 
// input file, evaluates subject-specific requirements, and outputs clear decisions indicating 
// whether each choice is approved or rejected. It is designed to support consistent and 
// efficient academic progression decisions based on attainment data.

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
//#include <string> //
//#include<math.h> // use sqrt()


// COLORS FOR SCREEN OUTPUT
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


// USED FOR GENERAL ENTRY TO ALEVEL PATHWAY 1
int gradeValue(const std::string& g)
{
    if (g == "A*") return 9;
    if (g == "A")  return 8;
    if (g == "B")  return 7;
    if (g == "C*") return 6;
    if (g == "C")  return 5;
    return 0;
}

// USED FOR GENERAL ENTRY TO ALEVEL PATHWAY 2
int gradePoints(const std::string& g)
{
    if (g == "A*") return 4;
    if (g == "A")  return 3;
    if (g == "B")  return 2;
    if (g == "C*") return 1;   // OR 1.5 (see note below)
    if (g == "C")  return 1;
    return 0;
}


//**********************************************************************************
// main function
//**********************************************************************************
int main( int argc, const char* argv[] )
{
    std::cout << endl ;
    std::cout << BOLDYELLOW << "    ______________________________________________________________" << std::endl ;
    std::cout << BOLDYELLOW << "            _=_                                      " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "          q(-_-)p                                    " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "          '_) (_`         A-Level Entry Eligibility System - ALEES        " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "          /__/  \\         Carles Triguero 2026      " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "        _(<_   / )_                                  " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "       (__\\_\\_|_/__)                               " << RESET << std::endl ;
    std::cout << BOLDYELLOW << "    ______________________________________________________________" << RESET << std::endl ;
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
std::getline(aa, HOEC, '\t'); // Home Economics/Food and Nutrition?
std::getline(aa, ITEC, '\t'); // Information Technology
std::getline(aa, ITAR, '\t'); // IT/Art
std::getline(aa, LATI, '\t'); // Latin
std::getline(aa, MATH, '\t'); // Mathematics
std::getline(aa, FMAT, '\t'); // Further Mathematics
std::getline(aa, MUSI, '\t'); // Music
std::getline(aa, PEAR, '\t'); // Performing Arts/Drama
std::getline(aa, PESE, '\t'); // Personal and Social Education
std::getline(aa, PHYS, '\t'); // Physics
std::getline(aa, POLI, '\t'); // Politics
std::getline(aa, RELI, '\t'); // Religious Studies
std::getline(aa, RUSS, '\t'); // Russian
std::getline(aa, SPAN, '\t'); // Spanish
std::getline(aa, SPOR, '\t'); // Sport/PE Studies


// A-LEVEL CHOICES READ INTO ACHOICES VECTOR ONLY NON EMPTY ENTRIES
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




// START ELEGIBILITY FOR A LEVEL IN GENERAL:

// PATHWAY 1

std::vector<std::string> gcses = {
    ARTD, BIOL, BUSI, CHEM, CHIN, CCIV, DTEC, ECON,
    ELAN, ELIT, FREN, GEOG, GERM, HIST, HOEC, ITEC,
    ITAR, LATI, MATH, FMAT, MUSI, PEAR, PESE, PHYS,
    POLI, RELI, RUSS, SPAN, SPOR
};
int countCplus = 0;
int countBplus = 0;
for (const auto& g : gcses)
{
    int val = gradeValue(g);

    if (val >= 5) countCplus++;  // C or above
    if (val >= 7) countBplus++;  // B or above
}
bool englishOK = (gradeValue(ELAN) >= 5);
bool mathsOK   = (gradeValue(MATH) >= 5);

bool pathway1 =
    (countCplus >= 6) &&
    englishOK &&
    mathsOK &&
    (countBplus >= 3);

if (pathway1)
{
    std::cout << BOLDYELLOW << surname << " " << name
              << BOLDGREEN << " -> Pathway 1: ELIGIBLE" << RESET; // << std::endl;

    // Decisions << surname << " " << name
    //           << " -> Pathway 1: ELIGIBLE\n";
}
else
{
    std::cout << BOLDYELLOW << surname << " " << name
              << BOLDRED << " -> Pathway 1: NOT ELIGIBLE" << RESET;// << std::endl;

    // Decisions << surname << " " << name
    //           << " -> Pathway 1: NOT ELIGIBLE\n";
}

// PATHWAY 2

double totalPoints = 0;

for (const auto& g : gcses)
{
    totalPoints += gradePoints(g);
}

bool pathway2 =
    (totalPoints >= 12) &&
    (gradeValue(ELAN) >= 5) &&
    (gradeValue(MATH) >= 5);

if (pathway2)
{
    std::cout << BOLDGREEN
              << " -> Pathway 2: ELIGIBLE (" << totalPoints << " GCSE points)" << RESET << std::endl;
}
else
{
    std::cout << BOLDRED 
              << " -> Pathway 2: NOT ELIGIBLE (" << totalPoints << " GCSE points)" << RESET << std::endl;
}

// END ELEGIBILITY FOR A LEVEL IN GENERAL:


















//  A-LEVEL ART AND DESIGN (AR)

// Checks if CARTD is in the choices (Achoices vector)

    if (std::find(Achoices.begin(), Achoices.end(), "Ar") != Achoices.end())
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

//  A-LEVEL BIOLOGY (BI)

    if (std::find(Achoices.begin(), Achoices.end(), "Bi") != Achoices.end())
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


//  A-LEVEL BUSINESS STUDIES (BS)

    if (std::find(Achoices.begin(), Achoices.end(), "Bs") != Achoices.end())
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


//  A-LEVEL CHEMISTRY (CH)

    if (std::find(Achoices.begin(), Achoices.end(), "Ch") != Achoices.end())
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

// //  A LEVEL CLASSICAL CIVILIZATION   (!CCIV.empty()) checks that any value non empty is sufficient to acces A level.


// // THIS COULD BE IMPLEMENTED AS:
// // bool goodGrade(const std::string& g)
// // {
// //     return g == "A" || g == "A*" || g == "B";
// // }
// // if (!CCIV.empty() || BGrade(HIST) || BGrade(ELAN) || BGrade(ELIT) || BGrade(LATI) || BGrade(RELI))


//     if (std::find(Achoices.begin(), Achoices.end(), "CCCVI") != Achoices.end())
//     {
//         if((!CCIV.empty()) || (HIST == "B" || HIST == "A" || HIST == "A*") || (ELAN == "B" || ELAN == "A" || ELAN == "A*") || (ELIT == "B" || ELIT == "A" || ELIT == "A*") || (LATI == "B" || LATI == "A" || LATI == "A*")  || (RELI == "B" || RELI == "A" || RELI == "A*"))
//         {
//             std::cout << BOLDGREEN << " YES Classical Civilization" << RESET << endl ;
//         }
//         else
//         {
//             std::cout << BOLDRED << " NO Classical Civilization" << RESET << endl ;
//         }
//     }


//  A-LEVEL COMPUTER SCIENCE (CP) no AQE CONSIDERED 2 CONDITION HERE!!!

    if (std::find(Achoices.begin(), Achoices.end(), "Cp") != Achoices.end())
    {
        if((DTEC == "A" || DTEC == "A*") && (MATH == "B" || MATH == "A" || MATH == "A*"))
        {
            std::cout << BOLDGREEN << " YES Computer Science" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Computer Science but check HOD + A in MATHS" << RESET << endl ;
        }
    }

//  A-LEVEL DIGITAL TECHNOLOGY (DT)  gcse compUTER science NOT CONSIERED CHECK

    if (std::find(Achoices.begin(), Achoices.end(), "Dt") != Achoices.end())
    {
        if((DTEC == "C*" || DTEC == "B" || DTEC == "A" || DTEC == "A*") || (ELAN == "B" || ELAN == "A" || ELAN == "A*"))
        {
            std::cout << BOLDGREEN << " YES Digital Technology" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Digital Technology" << RESET << endl ;
        }
    }

//  A-LEVEL DRAMA AND THEATRE STUDIES (DR)  IS DRAMA GCSE PERFORMIN ARTS PEAR 6 to what number???

    if (std::find(Achoices.begin(), Achoices.end(), "Dr") != Achoices.end())
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

//  A-LEVEL ECONOMICS (EC)

    if (std::find(Achoices.begin(), Achoices.end(), "Ec") != Achoices.end())
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

//  A-LEVEL ENGLISH LITERATURE (ET)

    if (std::find(Achoices.begin(), Achoices.end(), "Et") != Achoices.end())
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

// //  A-LEVEL ENVIROMENTAL TECHNOLOGY (EV)  (DIGITAL OR INFORMATION TECHNOLOGY???)  ******check
//     if (std::find(Achoices.begin(), Achoices.end(), "Ev") != Achoices.end())
//     {
//         if((MATH == "B" || MATH == "A" || MATH == "A*") || (TECH == "B" || TECH == "A" || TECH == "A*") || (PHYS == "B" || PHYS == "A" || PHYS == "A*"))
//         {
//             std::cout << BOLDGREEN << " YES Enviromental Technology" << RESET << endl ;
//         }
//         else
//         {
//             std::cout << BOLDRED << " NO Enviromental Technology" << RESET << endl ;
//         }
//     }

//  A-LEVEL FRENCH (FR)  
    if (std::find(Achoices.begin(), Achoices.end(), "Fr") != Achoices.end())
    {
        if(FREN == "B" || FREN == "A" || FREN == "A*")
        {
            std::cout << BOLDGREEN << " YES French" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO French" << RESET << endl ;
        }
    }

//  A-LEVEL GEOGRAPHY (Gg)  
    if (std::find(Achoices.begin(), Achoices.end(), "Gg") != Achoices.end())
    {
        if((GEOG == "B" || GEOG == "A" || GEOG == "A*") || ((ELAN == "B" || ELAN == "A" || ELAN == "A*") && (MATH == "B" || MATH == "A" || MATH == "A*")))
        {
            std::cout << BOLDGREEN << " YES Geography" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Geography" << RESET << endl ;
        }
    }

//  A-LEVEL GERMAN (Gr)  
    if (std::find(Achoices.begin(), Achoices.end(), "Gr") != Achoices.end())
    {
        if(GERM == "B" || GERM == "A" || GERM == "A*")
        {
            std::cout << BOLDGREEN << " YES German" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO German" << RESET << endl ;
        }
    }

//  A-LEVEL GOVERMENT AND POLITICS (Po)  
    if (std::find(Achoices.begin(), Achoices.end(), "Po") != Achoices.end())
    {
        if(POLI == "B" || POLI == "A" || POLI == "A*" || POLI == "A*" || ELAN == "B" || ELAN == "A" || ELAN == "A*" || HIST == "B" || HIST == "A" || HIST == "A*")
        {
            std::cout << BOLDGREEN << " YES Goverment and Politics" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Goverment and Politics" << RESET << endl ;
        }
    }

//  A-LEVEL HEALTH AND SOCIAL CARE (Hs)  
    if (std::find(Achoices.begin(), Achoices.end(), "Hs") != Achoices.end())
    {
        if(PESE == "B" || PESE == "A" || PESE == "A*" || ELAN == "B" || ELAN == "A" || ELAN == "A*")
        {
            std::cout << BOLDGREEN << " YES Health and Social Care" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Health and Social Care" << RESET << endl ;
        }
    }

//  A-LEVEL HISTORY (Hi)  
    if (std::find(Achoices.begin(), Achoices.end(), "Hi") != Achoices.end())
    {
        if(HIST == "B" || HIST == "A" || HIST == "A*" || ELIT == "A" || ELIT == "A*" || ELAN == "A" || ELAN == "A*")
        {
            std::cout << BOLDGREEN << " YES History" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO History" << RESET << endl ;
        }
    }

//  A-LEVEL LATIN (La)        ***********************CHECK MAX NUMERICAL VALUE
    if (std::find(Achoices.begin(), Achoices.end(), "La") != Achoices.end())
    {
        if(LATI == "6" || LATI == "7" || LATI == "8")
        {
            std::cout << BOLDGREEN << " YES Latin" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Latin" << RESET << endl ;
        }
    }

//  A-LEVEL MATHEMATICS (Ma)  ************CHECK DIFFERENCE BETWEEN ROUTE 1 and 2???

    if (std::find(Achoices.begin(), Achoices.end(), "M2") != Achoices.end())
    {
        // Route 1                                                               
        if((MATH == "A" || MATH == "A*") && (FMAT == "B" || FMAT == "A" || FMAT == "A*"))
        {
            std::cout << BOLDGREEN << " YES Mathematics ROUTE 1" << RESET << endl ;
        }
        else if(MATH == "A" || MATH == "A*")
        {
            std::cout << BOLDGREEN << " YES Mathematics using ROUTE 2" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Mathematics" << RESET << endl ;
        }
    }


//  A-LEVEL MATHEMATICS (Ma)

    if (std::find(Achoices.begin(), Achoices.end(), "Ma") != Achoices.end())
    {
        // Route 1                                                               
        if((MATH == "A" || MATH == "A*") && (FMAT == "B" || FMAT == "A" || FMAT == "A*"))
        {
            std::cout << BOLDGREEN << " YES Mathematics ROUTE 1" << RESET << endl ;
        }
        else if(MATH == "A" || MATH == "A*")
        {
            std::cout << BOLDGREEN << " YES Mathematics using ROUTE 2" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Mathematics" << RESET << endl ;
        }
    }

//  A-LEVEL FURTHER MATHEMATICS (Fm)

    if (std::find(Achoices.begin(), Achoices.end(), "Fm") != Achoices.end())
    {                                                           
        if(FMAT == "A*" && MATH == "A*")
        {
            std::cout << BOLDGREEN << " YES Further Mathematics" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Further Mathematics" << RESET << endl ;
        }
    }


//  A-LEVEL MOVING IMAGE ART (Mv)

    if (std::find(Achoices.begin(), Achoices.end(), "Mv") != Achoices.end())
    {                                                     
        if(ITAR == "B" || ITAR == "A" || ITAR == "A*")
        {
            std::cout << BOLDGREEN << " YES Moving Image Arts" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Moving Image Arts" << RESET << endl ;
        }
    }

//  A-LEVEL MUSIC (Mu)             *********************CHECK AND GRADE 5 IN INSTRUMENT OR VOICE

    if (std::find(Achoices.begin(), Achoices.end(), "Mu") != Achoices.end())
    {                                                              
        if(MUSI == "B" || MUSI == "A" || MUSI == "A*") // AND GRADE 5
        {
            std::cout << BOLDGREEN << " YES Music" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " (If HOD approval on acceptable audition) YES Music" << RESET << endl ;
        }
    }

//  A-LEVEL NUTRITION AND FOOD SCIENCE (Nf)

    if (std::find(Achoices.begin(), Achoices.end(), "Nf") != Achoices.end())
    {                                                     
        if(HOEC == "B" || HOEC == "A" || HOEC == "A*" || BIOL == "B" || BIOL == "A" || BIOL == "A*" || CHEM == "B" || CHEM == "A" || CHEM == "A*")
        {
            std::cout << BOLDGREEN << " YES Nutrition and Food Science" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Nutrition and Food Science" << RESET << endl ;
        }
    }

//  A-LEVEL PHYSICS (Ph)

    if (std::find(Achoices.begin(), Achoices.end(), "Ph") != Achoices.end())
    {                                                           
        if((PHYS == "A" || PHYS == "A*") && (PHYS == "A" || PHYS == "A*"))
        {
            std::cout << BOLDGREEN << " YES Physics" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Physics" << RESET << endl ;
        }
    }

//  A-LEVEL PSYCHOLOGY (Ps)                *** check if correct implementation ***

    if (std::find(Achoices.begin(), Achoices.end(), "Ps") != Achoices.end())
    {      

    bool mathA  = (MATH == "A"  || MATH == "A*");
    bool mathB  = (MATH == "B"  || mathA);

    bool elanA  = (ELAN == "A"  || ELAN == "A*");
    bool elanB  = (ELAN == "B"  || elanA);

    bool physA  = (PHYS == "A"  || PHYS == "A*");
    bool physB  = (PHYS == "B"  || physA);

    bool chemA  = (CHEM == "A"  || CHEM == "A*");
    bool chemB  = (CHEM == "B"  || chemA);

    bool biolA  = (BIOL == "A"  || BIOL == "A*");
    bool biolB  = (BIOL == "B"  || biolA);

    bool psychPhys = (mathA && elanB && physB) || (mathB && elanA && physB) || (mathB && elanB && physA);
    bool psychChem = (mathA && elanB && chemB) || (mathB && elanA && chemB) || (mathB && elanB && chemA);
    bool psychBiol = (mathA && elanB && biolB) || (mathB && elanA && biolB) || (mathB && elanB && biolA);

    bool psychology = psychPhys || psychChem || psychBiol;

        if (psychology)
        {
            std::cout << BOLDGREEN << " YES Psychology" << RESET << std::endl;
        }
        else
        {
            std::cout << BOLDRED << " NO Psychology" << RESET << std::endl;
        }
    }

//  A-LEVEL RELIGIOUS STUDIES (Re)

    if (std::find(Achoices.begin(), Achoices.end(), "Re") != Achoices.end())
    {                                                           
        if(RELI == "B" || RELI == "A" || RELI == "A*" || ELAN == "B" || ELAN == "A" || ELAN == "A*" || HIST == "B" || HIST == "A" || HIST == "A*") 
        {
            std::cout << BOLDGREEN << " YES Religious Studies" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Religious Studies" << RESET << endl ;
        }
    }

//  A-LEVEL RUSSIAN (Ru)               ******************NUMBER POSIBILITIES

    if (std::find(Achoices.begin(), Achoices.end(), "Ru") != Achoices.end())
    {                                                           
        if(RUSS == "6" || RUSS == "7") 
        {
            std::cout << BOLDGREEN << " YES Russian" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Russian" << RESET << endl ;
        }
    }

//  A-LEVEL SPANISH (Sp)

    if (std::find(Achoices.begin(), Achoices.end(), "Sp") != Achoices.end())
    {                                                           
        if(SPAN == "B" || SPAN == "A" || SPAN == "A*") 
        {
            std::cout << BOLDGREEN << " YES Spanish" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Spanish" << RESET << endl ;
        }
    }

//  A-LEVEL SPORT/B-TECH (Pe)

    if (std::find(Achoices.begin(), Achoices.end(), "Pe") != Achoices.end())
    {                                                           
        if((ELAN == "C*" || ELAN == "B" || ELAN == "A"|| ELAN == "A*") && (MATH == "C*" || MATH == "B" || MATH == "A"|| MATH == "A*")) 
        {
            std::cout << BOLDGREEN << " YES Sport" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Sport" << RESET << endl ;
        }
    }

//  A-LEVEL TECHNOLOGY AND DESIGN (Tl)  to what gcse corresponds for a B????? is dtec??????

    if (std::find(Achoices.begin(), Achoices.end(), "Tl") != Achoices.end())
    {                                                           
        if(DTEC == "C*" || MATH == "B" || MATH == "A"|| MATH == "A*" || PHYS == "B" || PHYS == "A"|| PHYS == "A*") 
        {
            std::cout << BOLDGREEN << " YES Technology and Design" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Technology and Design" << RESET << endl ;
        }
    }

//  A-LEVEL TRAVEL AND TOURISM (Tt)

    if (std::find(Achoices.begin(), Achoices.end(), "Tt") != Achoices.end())
    {                                                           
        if((ELAN == "C*" || ELAN == "B" || ELAN == "A"|| ELAN == "A*" || ELAN == "B" || ELAN == "A"|| ELAN == "A*") && (MATH == "C*" || MATH == "B" || MATH == "A"|| MATH == "A*" || PHYS == "B" || PHYS == "A"|| PHYS == "A*")) 
        {
            std::cout << BOLDGREEN << " YES Travel and Tourism" << RESET << endl ;
        }
        else
        {
            std::cout << BOLDRED << " NO Travel and Tourism" << RESET << endl ;
        }
    }

} // While reading line finish here

        InputFile.close() ;

    return (0) ;
}