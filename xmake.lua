set_languages("c++23")

add_rules("mode.debug", "mode.release")

target("server")
    set_kind("binary")

    add_includedirs("common/boost_1_81_0")

    add_files("src/server/**.cpp")
target_end()

target("client")
    set_kind("binary")

    add_includedirs("common/boost_1_81_0")

    add_files("src/client/**.cpp")
target_end()