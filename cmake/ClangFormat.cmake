function(ApplyClangFormat target directory)
    find_program(CLANG_FORMAT_PATH clang-format REQUIRED)
    set(PATTERN h hpp c cc cpp cxx)
    list(TRANSFORM PATTERN PREPEND "${directory}/*.")
    file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
            LIST_DIRECTORIES false ${PATTERN}
    )
    message("Formatting with clang-format ${target}")
    add_custom_command(TARGET ${target}
            PRE_BUILD COMMAND
            ${CLANG_FORMAT_PATH} -i --style=file ${SOURCE_FILES}
    )
endfunction()