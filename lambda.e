# Ian Braudaway #
# make lambda test #

func f[x]
:
    return lambda [y] 
    : 
        return x + y 
    ;
;

func main[]
:
    var a = f[3]
    var b = f[11]

    # should be 8 #
    print["a[5] is "]
    print[a[5]]

    # should be 17 #
    print["b[6] is "]
    print[b[6]]

    # should be 13 #
    print["a[10] is "]
    print[a[10]]
;

main[]
