from codegen.xml import all, val, vals, die
from codegen import line_prefix
import re, xml.dom.minidom

_name_map = {
    "BasicFB": "basic",
    "SimpleFB": "simple",
    "StructuredType": "struct",
    "AdapterType": "adapter",
    "FBNetwork": "composite",
    "SubAppType": "subapp",
}


def blockType(elt: xml.dom.minidom.Element = None):
    typeName = all("BasicFB|SimpleFB|StructuredType|self::AdapterType|self::SubAppType|FBNetwork", elt)[0].tagName
    if typeName not in _name_map: return None
    return _name_map[typeName]


def block(name: str):
    """Return block element of the given type name"""
    return all(f"../../System/FBType[@Name='{name}']|../../System/SubAppType[@Name='{name}']")[0]


def adapter(name_or_pin):
    """Return adapter element of the given type name or plug/socket"""
    if not isinstance(name_or_pin, str): name_or_pin = val("@Type", name_or_pin)
    return all(f"../../System/AdapterType[@Name='{name_or_pin}']")[0]


def struct(name_or_pin: str):
    """Return struct element of the given type name"""
    if not isinstance(name_or_pin, str): name_or_pin = val("@Type", name_or_pin)
    return all(f"../../System/DataType[@Name='{name_or_pin}']")[0]


def interfaces(type: str, elt=None):
    """Return all interface element of the given type. Allowed types are: "EventInputs", "EventOutputs", "InputVars", "OutputVars", "Sockets", "Plugs" """
    return all(f"InterfaceList/{type}/*", elt)


def pin(name: str, elt=None):
    """Return interface pin of the given name"""
    return all(f"InterfaceList/*/*[@Name='{name}']", elt)[0]


def nativeCode(type: str, alg=None, *, indent=1, prefix=None):
    """Return native code embedded in tagged comments of the form (* <type> ... *)"""
    if prefix is None: prefix = line_prefix()

    result = []
    for algorithm in algorithms(alg):
        rawtext = val("ST", algorithm)
        match = re.search("(?:\\(?|^ )\\* *<" + type + "> *\n(.*)\\*\\)", rawtext, re.DOTALL | re.MULTILINE)
        if not match: continue
        text = match[1]

        text = re.sub("^ ?\\* <[a-zA-Z0-9_:]+>\n.*", "", text, flags=re.DOTALL | re.MULTILINE)  # strip following code segments
        text = re.sub("^ ?\\* ", "", text, flags=re.MULTILINE)  # strip comment continuation prefix, if any
        text = re.sub("\n", "\n" + prefix, text)  # add prefix to subsequent lines
        text = re.sub("\n[\t ]*(\\* *)*$", "", text)  # strip comment trailer
        result.append(text)

    return ("\n" + (prefix * indent)).join(result)


def actions(state_or_alg: xml.dom.minidom.Element):
    """Return all actions of the given ECC state or algorithm"""
    if isAlgorithm(state_or_alg):
        return all(f"../ECC/ECState/ECAction[@Action='{val('@Name', state_or_alg)}']", state_or_alg)

    if not isState(state_or_alg):
        die(f"Need ECState or Algorithm element, not {state_or_alg}")

    return all("ECAction", state_or_alg)


def states(alg_or_block: xml.dom.minidom.Element = None):
    """Return all ECC states where the given algorithm is used, or all states of the given block"""
    if not isAlgorithm(alg_or_block): return all("./*/ECC/ECState", alg_or_block)
    return all(f"../ECC/ECState/ECAction[@Action='{val('@Name', alg_or_block)}']/..", alg_or_block)


def transitions(pin: xml.dom.minidom.Element):
    """Return transitions that use a given pin"""
    name = pinName(pin)
    return all(f"../../../*/ECC/ECTransition[@Condition = '{name}' or substring-before(@Condition, '.') = '{name}' or substring-before(@Condition, '[') = '{name}']", pin)


def incomingTransitions(state: xml.dom.minidom.Element):
    """Return incoming transitions of given ECC state"""
    if not isState(state): die(f"Need ECState element, not {state}")
    return all(f"../ECTransition[@Destination='{val('@Name', state)}']", state)


def outgoingTransitions(state: xml.dom.minidom.Element):
    """Return outgoing transitions of given ECC state"""
    if not isState(state): die(f"Need ECState element, not {state}")
    return all(f"../ECTransition[@Source='{val('@Name', state)}']", state)


def condition(trans: xml.dom.minidom.Element):
    """Return condition of given transition"""
    return val("@Condition", trans)


def targetState(trans: xml.dom.minidom.Element):
    """Return target state of the given ECC transition"""
    if not isTransition(trans): die(f"Need ECTransition element, not {trans}")
    return all(f"../ECState[@Name='{val('@Destination', trans)}']", trans)[0]


def sourceState(trans: xml.dom.minidom.Element):
    """Return target state of the given ECC transition"""
    if not isTransition(trans): die(f"Need ECTransition element, not {trans}")
    return all(f"../ECState[@Name='{val('@Source', trans)}']", trans)[0]


def algorithm(name_or_action, elt=None):
    """Return algorithm of the given name or action"""
    if isAction(name_or_action): return all(f"../../Algorithm[@Name='{val('@Algorithm', name_or_action)}']", name_or_action)[0]
    return all(f"./*/Algorithm[@Name='{name_or_action}']", elt)[0]


def algName(action, elt=None):
    """Return algorithm name of the given action"""
    return val('@Algorithm', action)


def pinName(action_or_transition_or_pin, elt=None):
    """Return pin name of the given action or transition, stripping extended conditions or adapter members"""
    if isTransition(action_or_transition_or_pin):
        name = val("@Condition", action_or_transition_or_pin)
        if "[" in name: name = name[:name.index("[")]
    elif isAction(action_or_transition_or_pin):
        name = val('@Output', action_or_transition_or_pin)
    else:
        name = val("@Name", action_or_transition_or_pin)

    if "." in name: name = name[:name.index(".")]
    return name


def name(elt):
    """Return element name"""
    return val('@Name', elt)


def type(elt):
    """Return element type"""
    return val("@Type", elt)


def algorithms(elt=None):
    """Return all algorithms of the current block or the given ECC state/action/transition"""
    if isTransition(elt): elt = targetState(elt)
    if isState(elt): return [algorithm(action) for action in actions(elt)]
    if isAction(elt): return [algorithm(elt)]
    if isAlgorithm(elt): return [elt]
    return all("./*/Algorithm", elt)


def isAction(elt: xml.dom.minidom.Element):
    return elt and elt.tagName == "ECAction"


def isState(elt: xml.dom.minidom.Element):
    return elt and elt.tagName == "ECState"


def isTransition(elt: xml.dom.minidom.Element):
    return elt and elt.tagName == "ECTransition"


def isUnconditional(elt: xml.dom.minidom.Element):
    return elt and val("@Condition", elt) == "1"


def isAlgorithm(elt: xml.dom.minidom.Element):
    return elt and elt.tagName == "Algorithm"
