# -*- coding: utf-8 -*-

def contagem():
        
    uppercase = 0
    lowercase = 0
    digit = 0
    space = 0
    newline = 0

    path = input("Digite o caminho do arquivo incluindo também a extensão do mesmo: \n")

    file = open(path, 'r', encoding='utf-8')

    for line in file:
        for letter in line:

            if(letter.isupper()):
                uppercase += 1

            if(letter.islower()):
                lowercase += 1

            if(letter.isdigit()):
                digit += 1        

            if(letter.isspace()):
                space += 1
            
            if(letter == chr(10)):
                newline += 1

    print("O arquivo em questão possui {} letras maiusculas, {} letras minúsculas, {} números, {} espaços e {} quebras de linha".format(uppercase, lowercase, digit, space, newline))

contagem()