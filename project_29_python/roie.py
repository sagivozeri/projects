option_1 = ("start")
option_2 = ("stop")
option_3 = ("quit")

while True:
    game_begin = input ("what do you want? ")
    if game_begin == ("help"):
        print ("""
        start - to start the car
        stop - to stop the car
        quit - to exit""")
        while True:
            answer = input ("> ")
            if answer == option_1:
                print ("we are ready to go")
            elif answer == option_2:
                print ("car stopped")
            elif answer == option_3:
                print ("done")
                break
            else:
                print ("error")
    elif game_begin == ("quit"):
        print ("bye bye")
        break
    else:
        print ("i don't understand.")
