#!/usr/bin/env python3
import sys
import os
import shutil

def main(argv):
    appname = argv[1]
    binFile = argv[2]
    manFile = argv[3]
    print("Packing '{}' :".format(appname))

    filename = appname.lower()

    binFileContent = getFile(binFile)
    manFileContent = getFile(manFile)

    if len(manFileContent) > 65534 :
        manFileContent = manFileContent[0: 65534]

    if manFileContent[-1] != 0x00 :
        manFileContent.append(0x00)

    version         = 0x01
    codeOffset      = len(manFileContent) + 11
    codeSize        = len(binFileContent)
    headerlength    = len(manFileContent)

    print("Format version       : {}.".format(hex(version)))
    print("Binary code offset   : {}.".format(hex(codeOffset)))
    print("Binary code size     : {} bytes.".format(codeSize))
    print("Header length        : {} bytes.".format(headerlength))

    appFileContent = version.to_bytes(1, 'big') + codeOffset.to_bytes(4, 'big') + codeSize.to_bytes(4, 'big') + headerlength.to_bytes(2, 'big') + manFileContent + binFileContent

    print("App file size : {} bytes.".format(len(appFileContent)))

    writeFile("{}.app".format(appname), appFileContent)

def getFile(fn) :
    print("Reading file '{}'".format(fn))
    f = open(fn, "rb")
    return bytearray(f.read())

def writeFile(fn, content) :
    print("Writing file '{}'".format(fn))
    f = open(fn , "wb+")
    f.write(content)

if __name__ == "__main__":
    main(sys.argv)
