#include "actions.h"
#include "iostream"
#include <limits>

std::string ChooseAction ( ) {
    // TODO: Protect against integers while()
    std::string election;

    while ( true ) {
        std::cout
                << "\nOptions:\n\t - read (r)\n\t - write (w)\n\t - update/override (u)"
                   "\n\t - delete (d)\n\t - quit (q)\n\t - print content (p)\n";
        std::cout << "Election: ";
        std::cin >> election;
        std::cout << "\n";
        std::cin.ignore( std::numeric_limits < std::streamsize >::max( ), '\n' );

        if ( election == "r" || election == "w" || election == "u" ||
             election == "d" || election == "q" || election == "p" ) {
            break;
        }
        std::cout << "Error: Choose one of the options...\n";

    };

    return election;
}

void AddFileNameToMSGPackByAction ( MSGPack &sendPack, const std::string &election ) {
    // TODO: control fileName length
    std::string fileName;
    if ( election != "p" ) {
        std::cout << "Set file path name: ";
        std::cin >> fileName;
        std::cin.clear( );
        std::cin.ignore( std::numeric_limits < std::streamsize >::max( ), '\n' );
        sendPack.setFileName( fileName );
    }
}

void AddContentToMSGPack ( MSGPack &sendPack, const std::string &election ) {
    std::string content;
    if ( election == UPDATE_COMMAND || election == WRITE_COMMAND ) {
        std::cout << "Write the content of the file:\n";
        std::cin >> content;
        std::cin.clear( );
        std::cin.ignore( std::numeric_limits < std::streamsize >::max( ), '\n' );
        sendPack.setContent( content );
    }
}

