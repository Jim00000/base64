add_executable(testBase64 testentry.cpp testbase64encode.cpp testbase64decode.cpp)
target_include_directories(testBase64 PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(testBase64 base64 gtest gtest_main)