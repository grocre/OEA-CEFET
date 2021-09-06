import os

busca = "21330600"

path = "cep_ordenado.dat"
file = open(path, "rb")

start = 0
size = os.stat(path).st_size
lines = size // 300

found = False

while start <= lines:
    mean = (start + lines)// 2
    file.seek(mean * 300, 0)
    line = file.readline()

    cep = line.strip()[-8:].decode("latin-1")

    if cep == busca: 
        found = True
        line = line.decode("latin-1").strip("\n").split(" "*58)
        print("Encontrado na linha: {}, o cep {} é referente à rua {}, bairro {}, cidade {} e estado {}!!".format(mean, line[4], line[0], line[1], line[2], line[3]))
        break
    elif cep >= busca: 
        lines = mean - 1
    else: 
        start = mean + 1

if not found: 
    print("Não consegui encontrar")

file.close()