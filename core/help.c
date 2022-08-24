#include "help.h"


int init_help_manual(){
    int ret = 0;
    printf("start help manual init...");
    // version 0.0.2 将文件二进制化，对比xml文件是否有修改，如果无修改则读取原二进制文件，如果有修改则重新初始化。

    // version 0.0.1 不论怎样都要重新处理xml文件来构建help manual
    ret = analaysis_xml_files();
    if(ret = 0){
        printf("analaysis xml files failed!\n");
    }
    
    return ret;
}
void Adb_help_manual(){

}