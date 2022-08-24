#include "unitls.h"
#include <libxml/parser.h>
#include <libxml/tree.h>

int analysis_xml_files()
{
    xmlDocPtr pXml; //xml files pointer
    xmlNodePtr curNode;
    xmlNodePtr fatherNode;

    char* xmlName = "help.xml";

    pXml = xmlReadFile(xmlName,"UTF-8",XML_PARSE_RECOVER);
    if(pXml == NULL){
        fprintf(stderr,"Document not parsed successfully.");
        return -1;
    }

    curNode = xmlDocGetRootElement(pXml);

    if(curNode == NULL)
    {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(pXml);
        return -1;
    }

    if(xmlStrcmp(curNode->name, BAD_CAST"help"))
    {
        fprintf(stderr, "document of the wrong type, root node != root\n");
        xmlFreeDoc(pXml);
        return -1;
    }

    curNode = curNode->xmlChildrenNode;

    while(curNode != NULL)
    {
        if(xmlStrcmp(curNode->name, (const xmlChar*)("text")))
        {
            printf("curname is : %s\n", curNode->name);
            if(curNode->children!=NULL)
            {
                fatherNode = curNode;
                curNode = curNode->xmlChildrenNode;
                while (curNode != NULL)
                {
                    xmlChar* content = NULL;
                    if(xmlStrcmp(curNode->name, (const xmlChar*)("text")))
                    {
                        content = xmlNodeGetContent(curNode);
                        printf("%s\n", content);
                        xmlFree(content);
                    }
                    curNode = curNode->next;
                }
            }
            curNode = fatherNode;
        }
        curNode = curNode->next;
    }

    return 0;
}