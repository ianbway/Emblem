# Ian Braudaway #
# make error 3 # 

func problemTest[] 
    :
        print["This test will be bad because we have two greater than signs."] 
        print["The recognizer should think that we missed nesting an expression."] 
        print["Here we go:"]
        # Syntax Error # 
        while [1 >> 5]
        :
            print["Should not make it this far."] 
        ;
        print["Should not make it this far."] 
    ;