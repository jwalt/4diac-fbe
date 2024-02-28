from codegen.xml import all, Assert
import codegen.iec61499 as iec


def className():
    return iec.name(None)


def sym(name):
    escape_table = {"_": "::", "-": "__"}
    shorthand_table = {
        "STD": "std_msgs::",
        "SENS": "sensor_msgs::msg::",
        "GEOM": "geometry_msgs::msg::"
    }

    parts = name.split("_")
    out = parts[0]
    parts = parts[1:]
    ignore_next = False

    if out == "ROS" and parts[0] in shorthand_table:
        out = shorthand_table[parts[0]]
        parts = parts[1:]
        ignore_next = True

    for p in parts:
        if ignore_next:
            out += p
            ignore_next = False
        elif len(p) == 0:
            out += "::"
            ignore_next = True
        elif p[0] in escape_table:
            out += escape_table[p[0]] + p[1:]
        elif p[0] == "#":
            out += int(p[1:3], 16) + p[3:]
        else:
            out += "_" + p

    return out


def msgtype(elt):
    if elt is None: return "void"
    return sym(iec.type(iec.pin("PAYLOAD", iec.adapter(elt))))


def incoming_message(state_or_alg_or_trans):
    # If given a state or algorithm, this assumes that all incoming
    # transitions for an algorithm use the same data type and that all
    # algorithms of a state have the same incoming data type.
    if iec.isAlgorithm(state_or_alg_or_trans):
        states = iec.states(state_or_alg_or_trans)
        if len(states) == 0: return None
        state_or_alg_or_trans = states[0]

    if iec.isState(state_or_alg_or_trans):
        trans = iec.incomingTransitions(state_or_alg_or_trans)
        if len(trans) == 0: return None
        state_or_alg_or_trans = trans[0]

    name = iec.pinName(state_or_alg_or_trans)
    if name == "1": return None
    return iec.pin(name)


def outgoing_message(state_or_alg_or_action):
    # If given a state or algorithm, this assumes that all incoming
    # transitions for an algorithm use the same data type and that all
    # algorithms of a state have the same incoming data type.
    if iec.isAlgorithm(state_or_alg_or_action):
        states = iec.states(state_or_alg_or_action)
        if len(states) == 0: return None
        state_or_alg_or_action = states[0]

    if iec.isState(state_or_alg_or_action):
        actions = iec.actions(state_or_alg_or_action)
        if len(actions) == 0: return None
        state_or_alg_or_action = actions[0]

    name = iec.pinName(state_or_alg_or_action)
    if name == "1": return None
    return iec.pin(name)


def include_file(sym):
    out = sym.split("::")
    converted = ""
    for ch in out[-1]:
        if ch.isupper():
            converted += "_"
        converted += ch.lower()
    out[-1] = converted[1:] + ".hpp"
    out = "/".join(out)
    return out


def AssertROSCompatibleAdapter(elt=None):
    Assert(iec.blockType(elt) == "adapter", "Element is not an adapter")
    Assert(len(iec.interfaces("EventInputs", elt)) == 0, "ROS-compatible adapters cannot have event inputs")
    Assert(len(iec.interfaces("InputVars", elt)) == 0, "ROS-compatible adapters cannot have event inputs")
    Assert(len(iec.interfaces("EventOutputs", elt)) == 1, "ROS-compatible adapters must have a single event output called 'MSG'")
    Assert(iec.name(iec.interfaces("EventOutputs", elt)[0]) == "MSG", "ROS-compatible adapters must have a single event output called 'MSG'")
    Assert(len(iec.interfaces("OutputVars", elt)) == 1, "ROS-compatible adapters must have a single data output")
    Assert(iec.name(iec.interfaces("OutputVars", elt)[0]) == "PAYLOAD", "ROS-compatible adapters must have a single data output called 'PAYLOAD'")
    return ""


def AssertROSCompatibleInterface(elt=None):
    Assert(len(iec.interfaces("EventInputs", elt)) == 0, "This template only works with ROS-compatible sockets/plugs, no plain events/data allowed")
    Assert(len(iec.interfaces("EventOutputs", elt)) == 0, "This template only works with ROS-compatible sockets/plugs, no plain events/data allowed")
    Assert(len(iec.interfaces("InputVars", elt)) == 0, "This template only works with ROS-compatible sockets/plugs, no plain events/data allowed")
    Assert(len(iec.interfaces("OutputVars", elt)) == 0, "This template only works with ROS-compatible sockets/plugs, no plain events/data allowed")
    for sock in iec.interfaces("Sockets", elt):
        AssertROSCompatibleAdapter(iec.adapter(sock))
    for plug in iec.interfaces("Plugs", elt):
        AssertROSCompatibleAdapter(iec.adapter(plug))
    return ""


def AssertROSCompatibleECC(elt=None):
    for alg in iec.algorithms(elt):
        msgtypes = []
        for state in all(f"BasicFB/ECC/ECState[ECAction[@Algorithm='{iec.name(alg)}']]"):
            for trans in all(f"BasicFB/ECC/ECTransition[@Destination='{iec.name(state)}' and @Condition != 1]"):
                msg = incoming_message(trans)
                if msg is not None: msgtypes.append(msgtype(msg))
        Assert(len(msgtypes) == 0 or len(set(msgtypes)) == 1, "ECC is incompatible with ROS: inbound ECC transitions must have matching message types")

        for outmsg in all(f"BasicFB/ECC/ECState/ECAction[@Algorithm='{alg}']"):
            msg = outgoing_message(outmsg)
            if msg is not None: msgtypes.append(msgtype(msg))
        Assert(len(msgtypes) == 0 or len(set(msgtypes)) == 1, "ECC is incompatible with ROS: ECC action outputs must have matching message types")

    return ""
