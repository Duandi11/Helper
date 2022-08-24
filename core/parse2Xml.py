from multiprocessing import context
from xml.etree.ElementTree import Element
from xml.etree.ElementTree import SubElement
from xml.etree.ElementTree import ElementTree

from xml.dom import minidom

sourceFileName = "/home/duandi/.bash_aliases"
sourceFile = []
targetFileName = './hello.xml'

def readShell(filename):
    f = open(filename,'r',encoding='utf-8')
    # 根据#数量解析文件，并且要构造对应的数据结构
    data = f.readlines()
    for i in data:
        if i.startswith('#'):
            sourceFile.append(i.replace('\n',''))


def generateXml(sourceFile, targetFileName):
    # generate help root node
    Root = ''
    second = ''
    index = 0
    while index <len(sourceFile) :
        if sourceFile[index].startswith('# '):
            Root = Element(sourceFile[index])
        elif sourceFile[index].startswith('## '):
            second = SubElement(Root, sourceFile[index])
        else:
            child = SubElement(second, sourceFile[index])
            child.text = sourceFile[index]
        index += 1
    prettyXml(Root,'\t', '\n')
    tree = ElementTree(Root)

    tree.write(targetFileName, encoding='utf-8')

def prettyXml(element, indent, newline, level = 0):
    if element:
        if element.text == None or element.text.isspace():
            element.text = newline + indent * (level + 1)
        else:
            element.text = newline + indent * (level + 1) + element.text.strip() + newline + indent * (level + 1)

    temp = list(element)
    for subelement in temp:

        if temp.index(subelement) < (len(temp) - 1):
            subelement.tail = newline + indent * (level + 1)
        else:
            subelement.tail = newline + indent * level

        prettyXml(subelement, indent, newline, level = level + 1)


readShell(sourceFileName)
generateXml(sourceFile, targetFileName)


