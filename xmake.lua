
add_rules("mode.debug", "mode.release")


set_languages("cxx26")


set_toolchains("gcc")
add_cxxflags(
    "-Wall",
    "-Wextra",
    "-Werror",
    "-Wpedantic",
    "-Wshadow",
    "-Wconversion",
    "-fno-exceptions",
    "-fno-rtti"
)

if is_mode("release") then
    add_cxxflags("-march=native", "-mavx")
end


add_requires("fmt")


target("tmes")
    set_default(true)
    set_kind("binary")

    set_policy("build.c++.modules", true)

    add_files("src/**.cpp")
    add_files("src/**.cppm", {rules = "cxx.build.modules"})
    add_includedirs("src", {public = true})

    add_packages("fmt")

