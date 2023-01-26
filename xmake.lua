set_languages("c++23")

add_rules("mode.debug", "mode.release")

target("framework")
    set_kind("static")

    add_includedirs("common/boost_1_81_0")
    
    add_files("common/framework/**.cpp")
target_end()

target("server")
    set_kind("binary")

    add_deps("framework")

    add_includedirs("common/boost_1_81_0")
    add_includedirs("common/framework")

    add_files("src/server/**.cpp")
target_end()

target("client")
    set_kind("binary")

    add_deps("framework")

    add_includedirs("common/boost_1_81_0")
    add_includedirs("common/framework")

    add_files("src/client/**.cpp")
target_end()