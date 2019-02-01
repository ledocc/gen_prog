from cpt.packager import ConanMultiPackager


if __name__ == "__main__":
    builder = ConanMultiPackager()
    builder.add_common_builds()

    if platform.system() == "Linux":
        filtered_builds = []
        for settings, options, env_vars, build_requires in builder.builds:
            if ( settings["compiler"] == "clang" ) or ( settings["compiler"] == "gcc" ):
                settings_libstdcxx11 = settings.copy()
                settings_libstdcxx11["compiler.libcxx"] = "libstdc++11"
                filtered_builds.append([settings_libstdcxx11, options, env_vars, build_requires])
            filtered_builds.append([settings, options, env_vars, build_requires])
        builder.builds = filtered_builds

    builder.run()
