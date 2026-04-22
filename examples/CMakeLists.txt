add_executable(example_spp
    example_spp.c
)

add_executable(generate_corpus
    generate_corpus.c
)

target_link_libraries(example_spp
    PRIVATE vulnccsds
)

target_link_libraries(generate_corpus
    PRIVATE vulnccsds
)