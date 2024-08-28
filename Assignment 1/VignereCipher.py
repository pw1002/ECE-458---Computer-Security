import math
import pandas as pd
import matplotlib.pyplot as plt

def createSubstrings(cipherText, n):
    substrings = [None] * n
    for x in range(0, n):
        substrings[x] = cipherText[x::n]
    return substrings

def barGraph(substrings):
    for str in substrings:
        frequency = [0] * 26
        for chr in str:
            match chr:
                case "a":
                    frequency[0] += 1
                case "b":
                    frequency[1] += 1
                case "c":
                    frequency[2] += 1
                case "d":
                    frequency[3] += 1
                case "e":
                    frequency[4] += 1
                case "f":
                    frequency[5] += 1
                case "g":
                    frequency[6] += 1
                case "h":
                    frequency[7] += 1
                case "i":
                    frequency[8] += 1
                case "j":
                    frequency[9] += 1
                case "k":
                    frequency[10] += 1
                case "l":
                    frequency[11] += 1
                case "m":
                    frequency[12] += 1
                case "n":
                    frequency[13] += 1
                case "o":
                    frequency[14] += 1
                case "p":
                    frequency[15] += 1
                case "q":
                    frequency[16] += 1
                case "r":
                    frequency[17] += 1
                case "s":
                    frequency[18] += 1
                case "t":
                    frequency[19] += 1
                case "u":
                    frequency[20] += 1
                case "v":
                    frequency[21] += 1
                case "w":
                    frequency[22] += 1
                case "x":
                    frequency[23] += 1
                case "y":
                    frequency[24] += 1
                case "z":
                    frequency[25] += 1 
                case _:
                    print("Not a valid character")
        # Convert to percentage
        for x in range (0, len(frequency)):
            frequency[x] = float(frequency[x]/len(str) * 100)
       
        langs = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
        df = pd.DataFrame ({"Letters": langs, "Frequency": frequency})
        df_sorted_desc = df.sort_values('Frequency', ascending = False)
        fig = plt.figure(figsize=(10,6))
        plt.bar('Letters', 'Frequency', data=df_sorted_desc)
        plt.xlabel("Letters", size = 15)
        plt.ylabel("Frequency (%)", size = 15)
        plt.show()

def decrypt(cipherText):
    plaintext = ""
    key = "nqsbqkg"
    index = 0

    for c in cipherText:
        offset = 26 - (ord(key[index]) - ord('a'))
        decrypted = chr((ord(c) - ord('a') + offset) % 26 + ord('a'))

        plaintext += decrypted
        index = (index + 1) %len(key)

    return plaintext

def encrypt(plainText):
    key = "nqsbqkg"
    cipherText = ""

    index = 0

    for c in plainText:
        offset = ord(key[index]) - ord('a')
        encrypted = chr((ord(c) - ord('a') + offset) % 26 + ord('a'))
        cipherText += encrypted

        index = (index + 1) % len(key)
    
    return cipherText

def main():
    f = open("C:/Users/phill/OneDrive - University of Waterloo/WATERLOO STUFF/Spring 2023/ECE 458/Assignment 1/ciphertext.txt", "r")
    cipherText = f.read()
    n = int(input("Enter the value of n: "))
    substrings = createSubstrings(cipherText, n)
    barGraph(substrings) #show statistics (letter frequencies) of the ciphertext in a bar graph

    plainText = decrypt(cipherText) #decrypt the ciphertext using known key
    print("Plaintext is : " + plainText + "\n")
    cipherTextCheck = encrypt(plainText) #encrypt the plaintext using known key 
    print("Ciphertext Check is : " + cipherTextCheck)

    
if __name__ == '__main__':
   main()