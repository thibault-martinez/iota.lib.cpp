######################
# This file sets the project specific parameters for the dependencies
######################

######## Settings for libcurl ########
set(BUILD_CURL_EXE OFF CACHE BOOL "" FORCE)
set(USE_MANUAL OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(HTTP_ONLY ON CACHE BOOL "" FORCE)
set(CMAKE_USE_OPENSSL OFF CACHE BOOL "" FORCE)
set(CMAKE_USE_LIBSSH2 OFF CACHE BOOL "" FORCE)
set(CURL_CA_PATH_SET OFF CACHE BOOL "" FORCE)
set(CURL_STATICLIB ON CACHE BOOL "" FORCE)

######## Settings for cpr ########
set(BUILD_CPR_TESTS ON CACHE BOOL "" FORCE) # set to include gtest
set(CMAKE_USE_OPENSSL OFF CACHE BOOL "" FORCE)