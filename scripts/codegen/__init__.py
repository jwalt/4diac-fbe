import inspect


def line_prefix():
    lines = ""

    # evil code: look up the accumulated output array from wheezy.template, which is a local variable called "_b"
    for f in inspect.stack():
        if "_b" in f.frame.f_locals:
            lines = "".join(f.frame.f_locals["_b"])
            break

    prefix = lines
    if "\n" in prefix:
        prefix = prefix[prefix.rindex("\n") + 1:]
    return prefix
