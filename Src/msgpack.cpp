#include "msgpack.h"

MSGPack::MSGPack ( std::string &com, std::string &file, std::string &cnt ) {

    command = com;
    fileName = file;
    content = cnt;

}

void MSGPack::Pack ( const std::string &msg, MSGPack &packMSG ) {

    unsigned int i = 0;
    bool init = false;
    int size = 0;
    unsigned int elements = 0;

    char *characters = const_cast<char *>(msg.c_str( ));

    while ( 1 ) {

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
                //TODO try new operator
                char *buff = ( char * ) malloc( size * sizeof( char ) + 1 ); // +1 for '\0'
                for ( int j = 0; j < size; ++j ) {
                    buff[j] = characters[i];
                    if (( j + 1 ) >= size ) {
                        buff[j + 1] = '\0';
                        break;
                    }
                    ++i;
                }

                if ( elements == 0 ) {
                    std::string s( buff );
                    packMSG.setCommand( s );
                } else if ( elements == 1 ) {
                    std::string s( buff );
                    packMSG.setFileName( s );
                } else if ( elements == 2 ) {
                    std::string s( buff );
                    packMSG.setContent( s);
                }
                ++elements;

                free( buff );
            }
        }
        ++i;
    }

}

void MSGPack::Unpack ( const MSGPack &packMSG, std::string &msg ) {

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

    msg.append( "}\0" );

}


