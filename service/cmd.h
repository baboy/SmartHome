//
//  cmd.h
//  HRC
//
//  Created by baboy on 3/8/14.
//  Copyright (c) 2014 baboy. All rights reserved.
//

#ifndef HRC_cmd_h
#define HRC_cmd_h

enum{
    CmdQuery
};

typedef struct SCmd{
    unsigned short prefix; // 2 bytes;
    unsigned short version;// 2 bytes;
    int timestamp;// 4 bytes;
    int cmd;// 4bytes
    int device;// 4 bytes
    int msg_length;//3bytes
    void *msg;// data_length bytes
}Cmd;

void * create_cmd_data(Cmd cmd);
Cmd get_cmd(void *cmd_data);

#endif
