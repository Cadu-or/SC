import ECB
import AES
import cv2
import random
from random import choice
import string
from string import ascii_letters, digits


def GetPlaintext(nonce, count):
    bloco = []
    str1 = str(count)
    while(len(str1) < 8):
        str1 = '0' + str1

    str1 = nonce + str1
    bloco = []

    a = bytes(str1, 'ascii')

    for i in range(16):
        bloco.append(a[i])

    return bloco


def SetNonce():
    letters = string.ascii_lowercase
    letters2 = string.ascii_uppercase
    numbers = string.digits
    result = letters + letters2 + numbers
    result_str = ''.join(random.choice(result) for i in range(8))
    print("Nonce gerado:", result_str)
    print("Guarde-a caso queira decifrar")

    return result_str


def SplitB(blocos):
    cifra_aux = []
    cifra = []

    for j in range(0, len(blocos), 16):
        for i in range(16):
            cifra_aux.append(blocos[i+j])
        cifra.append(cifra_aux)
        cifra_aux = []

    return cifra


def CTRCypto(filename, round, op, chave):
    chave_aux = []
    cifrado = []
    for i in range(16):
        chave_aux.append(chave[i])

    imagem = cv2.imread(filename)
    cv2.imshow("Original", imagem)
    cv2.waitKey(0)

    if(op == 1):
        print("Cifrando...")
        str1 = SetNonce()
        block = ECB.CreateBlock(imagem)
        block = SplitB(block)

        for i in range(len(block)):
            t = GetPlaintext(str1, i)
            aux = AES.AESfunc(round, t, chave_aux, op)
            cifrado.extend(AES.MakeXor(aux, block[i]))

        cifrado = ECB.JoinBlocks(cifrado, imagem)
        cv2.imwrite("resultado.png", cifrado)
        cv2.imshow("Original", cifrado)
        cv2.waitKey(-1)

    elif(op == 2):
        nonce = input("Informe o nonce: ")
        print("Decifrando...")

        block = ECB.CreateBlock(imagem)
        block = SplitB(block)

        for i in range(len(block)):
            t = GetPlaintext(nonce, i)
            t = AES.AESfunc(round, t, chave_aux, 1)
            cifrado.extend(AES.MakeXor(t, block[i]))

        cifrado = ECB.JoinBlocks(cifrado, imagem)
        cv2.imwrite("resultado.png", cifrado)
        cv2.imshow("Original", cifrado)
        cv2.waitKey(-1)

    return 0
