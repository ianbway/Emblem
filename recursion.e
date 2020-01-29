# Ian Braudaway #
# make recursion test #

func fact[n]
:
    # base case #
    if [n <= 1]
    :
    	print[n] 
        return 1
    ;

    else
    :
    	print[n]
        return n * fact[n-1]
    ;    
;

fact[10]