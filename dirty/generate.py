cont = """
%s\\
%s\\
struct Accessor\\
{\\
    constexpr static auto get()\\
    {\\
        return ::mp::make<::mp::TupleTag>(%s);\\
    }\\
};
"""
N = 41
define = "#define DefineStructImpl%d(%s)"
paras = "Type,"
members = ""
ret = ""
for i in range(2, N + 1):
    members += "ArgsDropBack m%d ArgsBack m%d;" % (i - 1, i - 1)
    paras += ("m%d," % (i-1))
    ret += "::mp::make<::mp::TupleTag>(FwdStaticStr(ArgsBack m%d), ::mp::detail::MemberGetter<&Type::ArgsBack m%d>{})," % (i-1, i-1)
    print(cont % (define % (i, paras[:-1]), members, ret[:-1]))
