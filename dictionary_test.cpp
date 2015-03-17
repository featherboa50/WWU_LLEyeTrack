


// Compile with: g++ -o dtest dictionary_test.cpp -std=c++11


#include "dictionary.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

// ignore this
// #include <QtCore/QString>
// #include "/usr/include/qt5/QtCore/qstring.h"
// g++ -o test test.cpp -I/usr/include/qt5 -fPIE



void test_print( std::string S, dictionary< std::string >& D ){
    auto def = D.get_entry( S );
    if( def )
        std::cout << S << ": " << *def << '\n';
    else
        std::cout << S << " is undefined.\n";

}



void write_line( std::ofstream& outfile, const std::pair< std::string, std::string >& entry){
    outfile << std::get<0>(entry) << " : " << std::get<1>(entry) << '\n';
}

void write_line2( std::ofstream& outfile, const std::string& W, const std::string& D ){
    outfile << W << " : " << D << '\n';
}



std::pair< std::string, std::string >* read_line( std::ifstream& infile ){

    std::string S(1000,'\0');
    infile.getline(&S[0],1000);

    int len = strlen(&S[0]);
    if( !len )
        return nullptr;

    int i;
    for( i = 0 ; i < len && S.substr(i,3) != " : " ; i++ ) ;

    std::string W = S.substr(0,i); // word
    std::string D = S.substr(i+3); // definition

    std::pair< std::string, std::string >* P =
        new (std::nothrow) std::pair< std::string, std::string >( W, D );

    return P;
}



int main(){

    std::cout << '\n';

    dictionary< std::string > dict;


    dict.add_entry("alpha","first greek letter");
    test_print("alpha",dict);
    test_print("beta",dict);
    std::cout << '\n';

    dict.add_entry("beta","second greek letter");
    test_print("alpha",dict);
    test_print("beta",dict);
    std::cout << '\n';

    dict.add_entry("alpha","code word for the letter \'a\'");
    test_print("alpha",dict);
    test_print("beta",dict);
    std::cout << '\n';


    std::ofstream outF("output.txt");
    dict.write_dictionary(outF,write_line2);
    outF.close();


    dict.delete_entry("alpha");
    test_print("alpha",dict);
    test_print("beta",dict);
    std::cout << '\n';


    std::ifstream inF("output.txt");
    dictionary< std::string > dict2( inF, read_line );
    inF.close();

    test_print("alpha",dict2);
    test_print("beta",dict2);

}