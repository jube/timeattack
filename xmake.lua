set_project("timeattack")
set_version("0.1.0")

add_repositories("gf-repo https://github.com/GamedevFramework/xmake-repo")

add_requires("gamedevframework1", "box2d 2")

add_rules("mode.debug", "mode.releasedbg", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = "$(buildir)"})

set_policy("build.warning", true)
set_warnings("allextra")
set_languages("cxx17")
set_encodings("utf-8")

if is_plat("windows") then
  add_cxflags("/wd4251") -- Disable warning: class needs to have dll-interface to be used by clients of class blah blah blah
  add_defines("NOMINMAX", "_CRT_SECURE_NO_WARNINGS")
end

set_configdir("$(buildir)/config")
set_configvar("TIMEATTACK_DATADIR", "$(projectdir)/data/timeattack")
add_configfiles("code/config.h.in", {pattern = "@(.-)@"})

target("timeattack")
    set_kind("binary")
    add_files("code/timeattack.cc")
    add_files("code/bits/*.cc")
    add_files("vendor/gf-box2d/gfb2d/*.cc")
    add_includedirs("vendor/gf-box2d")
    add_includedirs("$(buildir)/config")
    add_packages("gamedevframework1", "box2d")
