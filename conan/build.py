import os
from conans import tools
from cpt.packager import ConanMultiPackager


if __name__ == "__main__":

    builder = ConanMultiPackager(
        username='ledocc',
        login_username='ledocc',
        upload="https://api.bintray.com/conan/ledocc/public-conan",
        reference="gen_prog/"+tools.load("version.txt"),
        stable_branch_pattern="master",
        channel="testing"
        )
    builder.add_common_builds()

    filtered_items = []
    for settings, options, env_vars, build_requires, reference in builder.items:
        settings["compiler.cppstd"] = "14"
        if settings["compiler"] == "gcc":
            settings["compiler.libcxx"] = "libstdc++11"
        elif ( settings["compiler"] == "clang" ):
            if ( "compiler.libcxx" not in settings ) or ( settings["compiler.libcxx"] == "libstdc++" ):
                settings["compiler.libcxx"] = "libstdc++11"
        filtered_items.append([settings, options, env_vars, build_requires, reference])
    builder.items = filtered_items

    builder.run()
