import AES
import ECB

while(1):
    print("MENU", end = "\n")

    print("1 - Cifrar imagem com ECB", end = '\n')
    print("2 - Decifrar imagem com ECB", end = '\n')
    print("0 - Sair", end = '\n')
    op = int(input("Escolha uma opcao: "))

    if(op == 1):
        r = int(input("Escolha o numero de rodadas (maximo 13) "))

        arq = input("Informe o nome do arquivo da imagem a ser cifrada (especificando o formato). Ex.: gato.jpg ")
        chave = input("Informe a chave: ")
        while(len(chave) > 16):
            print(bytes(chave, 'ascii'))
            chave = input("Chave maior que 128 bits, informe outra: ")
            print
        while(len(chave) < 16):
            chave += '0'
        ECB.ECBCrypto(arq, r, 1, bytes(chave, 'ascii'))

    elif(op == 2):
        r = int(input("Escolha o numero de rodadas (maximo 13) "))

        arq = input("Informe o nome do arquivo da imagem a ser decifrada (especificando o formato). Ex.: gato.jpg ")
        chave = input("Informe a chave: ")
        while(len(chave) > 16):
            print(bytes(chave, 'ascii'))
            chave = input("Chave maior que 128 bits, informe outra: ")
            print
        while(len(chave) < 16):
            chave = chave + '0'
        ECB.ECBCrypto(arq, r, 2, bytes(chave, 'ascii'))
    else:
        print("Opcao invalida")
        break