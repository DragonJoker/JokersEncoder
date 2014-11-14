# *******************************<+>***************************************
#
# File        : DateUtils.cmake
#
# Description : Date utilities.
#               Macros available:
#                   get_date
#
# Project     : JokersEncoder
#
# *********************************<+>**************************************
 
macro( get_date TODAY DAY MONTH YEAR )
    if ( WIN32 )
        execute_process( COMMAND "cmd" " /C date /T" OUTPUT_VARIABLE ${TODAY} )
        string(REGEX REPLACE "(..)/(..)/(....).*" "\\1" ${DAY} ${${TODAY}} )
        string(REGEX REPLACE "(..)/(..)/(....).*" "\\2" ${MONTH} ${${TODAY}} )
        string(REGEX REPLACE "(..)/(..)/(....).*" "\\3" ${YEAR} ${${TODAY}} )
        string(REGEX REPLACE "(..)/(..)/(....).*" "\\3\\2\\1" ${TODAY} ${${TODAY}} )
    elseif ( UNIX )
        execute_process( COMMAND "date" "+%Y-%m-%d" OUTPUT_VARIABLE ${TODAY} )
        string( REGEX REPLACE "(....)-(..)-(..).*" "\\3" ${DAY} ${${TODAY}} )
        string( REGEX REPLACE "(....)-(..)-(..).*" "\\2" ${MONTH} ${${TODAY}} )
        string( REGEX REPLACE "(....)-(..)-(..).*" "\\1" ${YEAR} ${${TODAY}} )
        string( REGEX REPLACE "(....)-(..)-(..).*" "\\1\\2\\3" ${TODAY} ${${TODAY}} )
    else ()
        message( SEND_ERROR "get_date not available" )
        SET( ${DAY} 00 )
        SET( ${MONTH} 00 )
        SET( ${YEAR} 00 )
        SET( ${TODAY} 000000 )
    endif()
endmacro( get_date )
