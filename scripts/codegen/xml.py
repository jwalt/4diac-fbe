# The root XML node in the 4diac sys file (`/System` or the user-selected type, e.g. some `/System/FBType`)
from __main__ import sysroot
import xpath


def die(msg: str):
    raise Exception(msg)


def Assert(condition: bool, msg: str):
    if not condition: die(msg)
    return ""


def all(xp: str, ctx=None):
    return xpath.find(xp, ctx or sysroot)


def val(xp: str, ctx=None):
    return str(xpath.findvalue(xp, ctx or sysroot))


def vals(xp: str, ctx=None):
    return [str(x) for x in xpath.findvalues(xp, ctx or sysroot)]
