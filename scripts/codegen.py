#!/bin/sh
SHELL_BASED_TOOLCHAIN_AUTODETECT_STARTUP_CODE_HIDDEN_FROM_PYTHON=""" "
base="$(cd "$(dirname "$0")"/..; pwd)/toolchains"
if [ ! -d "$base/lib/python3.9/site-packages/wheezy" ]; then
    "$base/bin/pip" install wheezy.template py-dom-xpath-six
fi
exec "$base/bin/python" "$0" "$@"
"""

import wheezy.template.engine, wheezy.template.ext.core, wheezy.template.ext.code, wheezy.template.loader
import xml.dom.minidom, xpath
import os.path, glob, importlib

# The root XML node in the 4diac sys file (`/System` or the user-selected type, e.g. some `/System/FBType`)
sysroot = None


class FordiacCodeGenerator:
    @staticmethod
    def main(libdir, template, sysfile, subtype):
        global sysroot

        searchpath = [os.path.dirname(template)]
        engine = wheezy.template.engine.Engine(
            loader=wheezy.template.loader.FileLoader(searchpath),
            extensions=[wheezy.template.ext.core.CoreExtension(), wheezy.template.ext.code.CodeExtension()]
        )

        try:
            template = engine.get_template(os.path.abspath(template))
        except Exception as e:
            raise Exception(f"{e}\n\nERROR: Could not parse template")

        library = []
        if os.path.isdir(sysfile):
            basedir = sysfile
            sysfile = glob.glob(f"{basedir}/*.sys")[0]

            for ext in ["fbt", "sub", "adp", "dtp"]:
                for file in glob.iglob(f"{basedir}/Type Library/**/*.{ext}", recursive=True):
                    try:
                        library.append(xml.dom.minidom.parse(file))
                    except Exception as e:
                        raise Exception(f"{e}\n\nERROR: Could not parse library file {file}")

        try:
            tree = xml.dom.minidom.parse(sysfile)
        except Exception as e:
            raise Exception(f"{e}\n\nERROR: Could not parse 4diac sys file")

        sysroot = xpath.find("/System", tree)[0]
        if not sysroot: raise Exception("Invalid 4diac sys file")

        for libentry in library:
            sysroot.appendChild(xpath.find("/*", libentry)[0])

        if subtype is not None:
            sysroot = xpath.find(f"/System/*[@Name='{subtype}']", tree)[0]

        context = {}
        for lib in glob.glob(f"{libdir}/codegen/*.py"):
            modname = os.path.basename(lib)[:-3]
            mod = importlib.import_module("codegen." + modname)
            context[modname] = mod
            for attr in dir(mod):
                if attr.startswith("_"): continue
                context[attr] = getattr(mod, attr)

        print(template.render(context))


# Command line script logic.
import sys, os, traceback

if __name__ == '__main__':
    try:
        if len(sys.argv) < 3:
            raise Exception(f"Wrong number of arguments: {len(sys.argv)}")
        if len(sys.argv) < 4: sys.argv.append(None)
        FordiacCodeGenerator.main(os.path.dirname(sys.argv[0]), sys.argv[1], sys.argv[2], sys.argv[3])

    except Exception as e:
        traceback.print_exc()
        print(f"\nERROR: {str(e)}\nUsage: {sys.argv[0]} <template> <4diac sys-file or project directory> [<type name>]")
        sys.exit(1)
