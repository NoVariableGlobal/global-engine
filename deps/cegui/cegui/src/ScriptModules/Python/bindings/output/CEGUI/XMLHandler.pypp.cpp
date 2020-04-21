// This file has been generated by Py++.

#include "boost/python.hpp"
#include "generators/include/python_CEGUI.h"
#include "XMLHandler.pypp.hpp"

namespace bp = boost::python;

struct XMLHandler_wrapper : CEGUI::XMLHandler, bp::wrapper< CEGUI::XMLHandler > {

    XMLHandler_wrapper( )
    : CEGUI::XMLHandler( )
      , bp::wrapper< CEGUI::XMLHandler >(){
        // null constructor
    
    }

    virtual void elementEnd( ::CEGUI::String const & element ) {
        if( bp::override func_elementEnd = this->get_override( "elementEnd" ) )
            func_elementEnd( boost::ref(element) );
        else{
            this->CEGUI::XMLHandler::elementEnd( boost::ref(element) );
        }
    }
    
    void default_elementEnd( ::CEGUI::String const & element ) {
        CEGUI::XMLHandler::elementEnd( boost::ref(element) );
    }

    virtual void elementStart( ::CEGUI::String const & element, ::CEGUI::XMLAttributes const & attributes ) {
        if( bp::override func_elementStart = this->get_override( "elementStart" ) )
            func_elementStart( boost::ref(element), boost::ref(attributes) );
        else{
            this->CEGUI::XMLHandler::elementStart( boost::ref(element), boost::ref(attributes) );
        }
    }
    
    void default_elementStart( ::CEGUI::String const & element, ::CEGUI::XMLAttributes const & attributes ) {
        CEGUI::XMLHandler::elementStart( boost::ref(element), boost::ref(attributes) );
    }

    virtual ::CEGUI::String const & getDefaultResourceGroup(  ) const {
        throw std::logic_error("warning W1049: This method could not be overriden in Python - method returns reference to local variable!");
    }

    virtual void text( ::CEGUI::String const & text ) {
        if( bp::override func_text = this->get_override( "text" ) )
            func_text( boost::ref(text) );
        else{
            this->CEGUI::XMLHandler::text( boost::ref(text) );
        }
    }
    
    void default_text( ::CEGUI::String const & text ) {
        CEGUI::XMLHandler::text( boost::ref(text) );
    }

};

void register_XMLHandler_class(){

    { //::CEGUI::XMLHandler
        typedef bp::class_< XMLHandler_wrapper, boost::noncopyable > XMLHandler_exposer_t;
        XMLHandler_exposer_t XMLHandler_exposer = XMLHandler_exposer_t( "XMLHandler", bp::init< >("*!\n\
        \n\
            XMLHandler base class constructor.\n\
         *\n") );
        bp::scope XMLHandler_scope( XMLHandler_exposer );
        { //::CEGUI::XMLHandler::elementEnd
        
            typedef void ( ::CEGUI::XMLHandler::*elementEnd_function_type )( ::CEGUI::String const & ) ;
            typedef void ( XMLHandler_wrapper::*default_elementEnd_function_type )( ::CEGUI::String const & ) ;
            
            XMLHandler_exposer.def( 
                "elementEnd"
                , elementEnd_function_type(&::CEGUI::XMLHandler::elementEnd)
                , default_elementEnd_function_type(&XMLHandler_wrapper::default_elementEnd)
                , ( bp::arg("element") ) );
        
        }
        { //::CEGUI::XMLHandler::elementStart
        
            typedef void ( ::CEGUI::XMLHandler::*elementStart_function_type )( ::CEGUI::String const &,::CEGUI::XMLAttributes const & ) ;
            typedef void ( XMLHandler_wrapper::*default_elementStart_function_type )( ::CEGUI::String const &,::CEGUI::XMLAttributes const & ) ;
            
            XMLHandler_exposer.def( 
                "elementStart"
                , elementStart_function_type(&::CEGUI::XMLHandler::elementStart)
                , default_elementStart_function_type(&XMLHandler_wrapper::default_elementStart)
                , ( bp::arg("element"), bp::arg("attributes") ) );
        
        }
        { //::CEGUI::XMLHandler::getDefaultResourceGroup
        
            typedef ::CEGUI::String const & ( ::CEGUI::XMLHandler::*getDefaultResourceGroup_function_type )(  ) const;
            
            XMLHandler_exposer.def( 
                "getDefaultResourceGroup"
                , bp::pure_virtual( getDefaultResourceGroup_function_type(&::CEGUI::XMLHandler::getDefaultResourceGroup) )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "*!\n\
            \n\
                Retrieves the default resource group to be used when handling files\n\
             *\n" );
        
        }
        { //::CEGUI::XMLHandler::getSchemaName
        
            typedef ::CEGUI::String const & ( ::CEGUI::XMLHandler::*getSchemaName_function_type )(  ) const;
            
            XMLHandler_exposer.def( 
                "getSchemaName"
                , getSchemaName_function_type(&::CEGUI::XMLHandler::getSchemaName)
                , bp::return_value_policy< bp::copy_const_reference >() );
        
        }
        { //::CEGUI::XMLHandler::handleContainer
        
            typedef void ( ::CEGUI::XMLHandler::*handleContainer_function_type )( ::CEGUI::RawDataContainer const & ) ;
            
            XMLHandler_exposer.def( 
                "handleContainer"
                , handleContainer_function_type( &::CEGUI::XMLHandler::handleContainer )
                , ( bp::arg("source") )
                , "*!\n\
                    \n\
                        Takes given RawDataContainer containing XML and handles it\n\
            \n\
                    This is basically a convenience function used by NamedXMLResourceManager\n\
            \n\
                     internal\n\
                        No need for this to be virtual\n\
                     *\n" );
        
        }
        { //::CEGUI::XMLHandler::handleFile
        
            typedef void ( ::CEGUI::XMLHandler::*handleFile_function_type )( ::CEGUI::String const &,::CEGUI::String const & ) ;
            
            XMLHandler_exposer.def( 
                "handleFile"
                , handleFile_function_type( &::CEGUI::XMLHandler::handleFile )
                , ( bp::arg("fileName"), bp::arg("resourceGroup") )
                , "*!\n\
                    \n\
                        Takes given file containing XML and handles it\n\
            \n\
                    This is basically a convenience function used by NamedXMLResourceManager\n\
            \n\
                     internal\n\
                        No need for this to be virtual\n\
                     *\n" );
        
        }
        { //::CEGUI::XMLHandler::handleString
        
            typedef void ( ::CEGUI::XMLHandler::*handleString_function_type )( ::CEGUI::String const & ) ;
            
            XMLHandler_exposer.def( 
                "handleString"
                , handleString_function_type( &::CEGUI::XMLHandler::handleString )
                , ( bp::arg("source") )
                , "*!\n\
                    \n\
                        Takes given string containing XML source and handles it\n\
            \n\
                    This is basically a convenience function used by NamedXMLResourceManager\n\
            \n\
                     internal\n\
                        No need for this to be virtual\n\
                     *\n" );
        
        }
        { //::CEGUI::XMLHandler::text
        
            typedef void ( ::CEGUI::XMLHandler::*text_function_type )( ::CEGUI::String const & ) ;
            typedef void ( XMLHandler_wrapper::*default_text_function_type )( ::CEGUI::String const & ) ;
            
            XMLHandler_exposer.def( 
                "text"
                , text_function_type(&::CEGUI::XMLHandler::text)
                , default_text_function_type(&XMLHandler_wrapper::default_text)
                , ( bp::arg("text") ) );
        
        }
    }

}