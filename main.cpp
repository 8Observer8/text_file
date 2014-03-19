#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <iostream>

//! Error codes
enum ErrorType {
    //! None errors
    errNone = 0,

    //! Error of the opening of a file
    errFileOpen = -1000,

    //! Error of the writing of a file
    errFileWrite = -1001,

    //! Wrong data
    errDataBad = -5000
};

ErrorType readData( const QString &fileName, QString &data );
ErrorType writeResult( const QString &fileName, QString &data );
void showData( const QString &data );
ErrorType showError( const QString &fileName, ErrorType errorCode );

/*!
 * Working with a text file
 */
int main( int argc, char *argv[] ) {
    QCoreApplication a( argc, argv );

    QString data;
    ErrorType errorCode = ErrorType::errNone;

    // Read data from a file
    QString iFileName = QString( "input.txt" );
    errorCode = readData( iFileName, data );
    if ( errorCode != ErrorType::errNone ) {
        return showError( iFileName, errorCode );
    }

    // Show data on the screen
    showData( data );

    // Data processing
    data += QString( ", World" );

    // Write data to a file
    QString oFileName = QString( "output.txt" );
    writeResult(oFileName, data);
    if ( errorCode != ErrorType::errNone ) {
        return showError( oFileName, errorCode );
    }

    return a.exec( );
}

/*!
 * Read data from the file
 * \param fileName File name
 * \param data data
 * \return Error code
 */
ErrorType readData( const QString &fileName, QString &data ) {
    QFile file( fileName );
    if ( !file.open( QIODevice::ReadOnly ) ) {
        return ErrorType::errFileOpen;
    }

    data = file.readAll( );

    file.close( );
    return ErrorType::errNone;
}

/*!
 * Write data to the file
 * \param fileName Fleile name
 * \param data Data
 * \return Error code
 */
ErrorType writeResult( const QString &fileName, QString &data ) {
    QFile file( fileName );

    if ( !file.open( QIODevice::WriteOnly ) ) {
        return ErrorType::errFileOpen;
    }

    QTextStream stream( &file );
    stream << data;
    file.close( );

    if ( stream.status( ) != QTextStream::Ok ) {
        return ErrorType::errFileWrite;
    }

    return ErrorType::errNone;
}

/*!
 * Show data on the screen
 * \param data Data
 */
void showData( const QString &data ) {
    std::cout << data.toStdString( ) << std::endl;
}

/*!
 * Write the error code to the file
 * \param fileName File name
 * \param errorCode Error code
 * \return Error code
 */
ErrorType showError( const QString &fileName, ErrorType errorCode ) {
    switch ( errorCode ) {
    case ErrorType::errFileOpen:
        std::cerr << "Error: cannot open the file " << fileName.toStdString( ) << std::endl;
        break;
    case ErrorType::errFileWrite:
        std::cerr << "Error: cannot write to the file " << fileName.toStdString( ) << std::endl;
        break;
    case ErrorType::errDataBad:
        std::cerr << "Error: incorrect data in the file " << fileName.toStdString( ) << std::endl;
        break;
    default:
        std::cerr << "Error code: " << errorCode << "; file name: " << fileName.toStdString( ) << std::endl;
        break;
    }

    return errorCode;
}
