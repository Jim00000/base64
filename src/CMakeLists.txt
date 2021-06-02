add_library(base64 base64encode.cpp base64decode.cpp)
target_include_directories(base64 PRIVATE ${PROJECT_SOURCE_DIR}/include)