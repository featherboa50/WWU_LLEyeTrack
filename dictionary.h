# ifndef __GENERIC_DICTIONARY__
# define __GENERIC_DICTIONARY__



#include <fstream>  // std::ifstream & std::ofstream
#include <map>      // std::map
#include <utility>  // std::pair



template<
    class word,
    class definition = word
>
class dictionary{

    std::map< word, definition > data;


  public:


     dictionary() = default;
    ~dictionary() = default;


    /**************************************************************************/
    //                          Read-In Constructor                           //

    dictionary(

        std::ifstream& infile,

        std::pair<word,definition>* (*read_entry)( std::ifstream& )

    ) :data() {

        read_dictionary( infile, read_entry );

    }



    /**************************************************************************/
    //                      Add Entry to the Dictionary                       //

    inline void add_entry( const std::pair< word, definition >& entry ){

        add_entry( std::get<0>(entry), std::get<1>(entry) );

    }


    void add_entry( word W, definition D ){

        data[ W ] = D;

    }



    /**************************************************************************/
    //                     Get Entry from the Dictionary                      //

    const definition* get_entry( const word& W ) const {

        if ( data.count( W ) )
            return &data.at( W );

        return nullptr;

    }



    /**************************************************************************/
    //                    Delete Entry in the Dictionary                      //

    void delete_entry( const word& W ){

        data.erase( W );

    }



    /**************************************************************************/
    //                      Write Dictionary out to File                      //

    void write_dictionary(

        std::ofstream& outfile,

        void (*write_entry)( std::ofstream&, const std::pair<word,definition>& )

    ){

        for( auto it = data.begin(); it != data.end(); ++it )

            write_entry( outfile, *it );

    }


    void write_dictionary(

        std::ofstream& outfile,

        void (*write_entry)( std::ofstream&, const word&, const definition& )

    ){

        for( auto it = data.begin(); it != data.end(); ++it )

            write_entry( outfile, it->first, it->second );

    }




    /**************************************************************************/
    //                      Read Dictionary in from File                      //

    void read_dictionary(

        std::ifstream& infile,

        std::pair<word,definition>* (*read_entry)( std::ifstream& )

    ){
        std::pair< word, definition >* entry;

        while( entry  = read_entry( infile ) ){

            word       W  =  std::get< 0 >( *entry );
            definition D  =  std::get< 1 >( *entry );

            data[ W ] = D;

        }
    }

};



#endif // __GENERIC_DICTIONARY__