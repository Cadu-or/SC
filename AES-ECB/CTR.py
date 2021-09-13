import AES
import cv2


def GetPlaintext(nonce, count):
    bloco = []

    return bloco

def SetNonce():
    string = ''

    return string


def CTRCypto(filename, round, op, chave):
    chave_aux = []
    for i in range(16):
        chave_aux.append(chave[i])
    
    imagem = cv2.imread(filename)
    cv2.imshow("Original", imagem)
    cv2.waitKey(0)

    if(op == 1):
        print("Cifrando...")

    elif(op == 2):
        print("Decifrando...")


    return 0