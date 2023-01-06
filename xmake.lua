set_languages("c++23")

add_rules("mode.debug", "mode.release")

target("society")
    set_kind("binary")

    add_includedirs("common/boost_1_81_0")

    add_files("src/main.cpp", "src/client.cpp")
