import random
import hashlib
import re
import time

#list of possible characters in the hash for random generation
character = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
charlist = list(character)
flag = False
i = 1
counter = 0
#Opening and accessing the MD5 Hashed passwords in the file
file = open("/Users/siddarthrudraraju/Documents/ITP125 Final Project/hashes.txt", "r")
MD = (file.readline()).strip()
starttime = time.time()
while(flag==False):
    counter += 1
    #Generates random strings of length i with characters from the list
    guess = str(random.choices(charlist, k=i))
    length = len(guess)
    #Extracting and sorting out the randomly generated string
    guess = guess[2:length-2]
    guesspass = re.sub("[^A-Za-z0-9]", "", guess)
    #Converting the string into an MD5 Hash Password
    result = (hashlib.md5(guesspass.encode())).hexdigest()
    #Comparing the strings to check if there is a match and calculating time taken
    if(result.strip() == MD.strip()):
        MD = (file.readline()).strip()
        endtime = time.time()
        totaltime = str(endtime - starttime)
        print("Password: " + guesspass + " Time taken to crack: " + totaltime)
        starttime = time.time()
        if(i>7):
            flag = True
            next 
    #Stops generating a string of length 'i' after a certain amount of iterations and starts
    #generating longer strings as it is likely the password is not of length 'i' after a certain amount of iterations.
    if(i<3):
        if(counter>15000):
            i += 1
            counter = 0
    elif(i<4):
        if(counter>1000000):
            i += 1
            counter = 0
    elif(i<5):
        if(counter>100000000):
            i += 1
            counter = 0
    elif (i<6):
        if (counter>3000000000):
            i += 1
            counter = 0

    elif(i<7):
        if(counter>30000000000):
            i += 1
            counter = 0
    else:
        if(counter>500000000000):
            i += 1
            counter = 0
file.close()



