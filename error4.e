# Ian Braudaway #
# make error 4 #

func badAssign[]
    :
        # Semantic Error. Attempting to assign 1 to undeclared variable. #    
        undeclaredVariable = 1
    ;

badAssign[]