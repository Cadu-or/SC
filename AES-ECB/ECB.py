from AES import AESfunc
from PIL import Image
import base64
import cv2
import sys
import io

key = [0x2b, 0x28, 0xab, 0x09,
       0x7e, 0xae, 0xf7, 0xcf,
       0x15, 0xd2, 0x15, 0x4f,
       0x16, 0xa6, 0x88, 0x3c]

def JoinBlocks(blocos, imagem):
    output = []
    aux2 = []
    aux2 = 0
    aux = imagem
    for i in range(imagem.shape[0]):
        for j in range(imagem.shape[1]):
            for k in range(imagem.shape[2]):
                aux[i][j][k] = blocos[aux2]
                aux2 = aux2+1
    
    return aux
                


def SplitBlocks(blocos, op, chave, round):
    cifra = []
    cifra_aux = []
    
    for j in range(0, len(blocos), 16):
        for i in range(16):
            cifra_aux.append(blocos[i+j])

        cifra.extend(AESfunc(round, cifra_aux, chave, op))
        cifra_aux = []
    return cifra


def CreateBlock(imagem):
    bloco = []
    for i in range(imagem.shape[0]):
        for j in range(imagem.shape[1]):
            for k in range(imagem.shape[2]):
                bloco.append(imagem[i][j][k])
    
    while(len(bloco) % 16 != 0):
        bloco.append(0)

    return bloco
         

def ECBCrypto(filenamem, round, op, chave):
    chave_aux = []
    for i in range(16):
        chave_aux.append(chave[i])

    imagem = cv2.imread(filenamem)
    cv2.imshow("Original", imagem)
    cv2.waitKey(0)

    print("Cifrando...")
    cifrado = imagem
    bloco = CreateBlock(imagem)
    bloco = SplitBlocks(bloco, op, chave, round)
    cifrado = JoinBlocks(bloco, imagem)

    cv2.imwrite("resultado.png", cifrado)
    cv2.imshow("Original", cifrado)

    cv2.waitKey(-1)