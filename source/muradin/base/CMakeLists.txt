set(base_SRCS log_warper.cc thread.cc timestamp.cc)

add_library(muradin_base ${base_SRCS})
target_link_libraries(muradin_base pthread )
