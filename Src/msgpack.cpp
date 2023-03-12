#include "msgpack.h"
#include <set>

MSGPack::MSGPack ( std::string &com, std::string &file, std::string &cnt ) {

    command = com;
    fileName = file;
    content = cnt;

}

void MSGPack::Pack ( MSGPack &packMSG, const std::string &msg ) {

    unsigned int i = 0;
    bool init = false;
    int size = 0;
    unsigned int elements = 0;

    char *characters = const_cast<char *>(msg.c_str( ));

    while ( true ) {

        if ( characters[i] == '}' ) {
            break;
        }

        if ( characters[i] == '{' && !init )
            init = true;

        if ( init ) {
            if ( characters[i] == 'L' ) {
                ++i;
                char tmpSize[10] = "\0";

                for ( int j = 0; j < 10; ++j ) {
                    if ( characters[i] == 'C' ) {
                        break;
                    }
                    tmpSize[j] = characters[i];
                    ++i;
                    //TODO: control if i>10
                }
                // TODO: replace strtol
                size = atoi( tmpSize );
            }

            if ( characters[i] == 'C' ) {
                ++i;
                std::string buff;

                if ( size != 0 ) {
                    for ( int j = 0; j < size; ++j ) {
                        buff.push_back( characters[i] );
                        if (( j + 1 ) >= size ) {
                            break;
                        }
                        ++i;
                    }
                }

                if ( elements == 0 ) {
                    std::string s( buff );
                    packMSG.setCommand( s );
                } else if ( elements == 1 ) {
                    std::string s( buff );
                    packMSG.setFileName( s );
                } else if ( elements == 2 ) {
                    std::string s( buff );
                    packMSG.setContent( s );
                }
                ++elements;
            }
        }
        ++i;
    }

}

void MSGPack::PackToString ( const MSGPack &packMSG, std::string &msg ) {

    msg.append( "{" );

    msg.append( "L" );
    msg.append( std::to_string( packMSG.command.length( )));
    msg.append( "C" );
    msg.append( packMSG.command );

    msg.append( "L" );
    msg.append( std::to_string( packMSG.fileName.length( )));
    msg.append( "C" );
    msg.append( packMSG.fileName );

    msg.append( "L" );
    msg.append( std::to_string( packMSG.content.length( )));
    msg.append( "C" );
    msg.append( packMSG.content );

    msg.append( "}" );

}

void MSGPack::PrintContent ( MSGPack &packMSG ) {

    int j = 0;
    int size = 0;
    int element = 0;
    std::set < std::string > driveContent;
    std::string msg = packMSG.getContent( );

    if ( packMSG.getCommand( ) == "p" ) {
        for ( int i = 0; i < packMSG.getContent( ).length( ); ++i ) {
            if ( msg[i] == ';' ) {
                size = i - j;
                std::string pathFile;
                pathFile = msg.substr( j, size );
                if ( driveContent.emplace( pathFile ).second )
                    std::cout << "\t" << pathFile << "\n";
                ++i;
                j = i;
                ++element;
            }
        }
    } else if ( packMSG.getCommand( ) == "e" ) {
        std::cout << "\t" << "Error!" << "\n";
    } else {
        std::cout << "\t" << "Success!" << "\n";
    }


}
